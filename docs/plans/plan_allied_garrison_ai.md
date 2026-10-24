# Patch 11: Allied Territory Garrison AI Architecture & Implementation

**Engine**: Darkest Hour 1.05.2 (checksum TENE)  
**Binary Executable**: `Darkest Hour.exe`  
**Primary Subsystem**: `CGarrisonAI` (`FUN_0068ba50` @ `0x0068BA50`), `CAITransportMinister` (`0x0069F7F0`), `CAIUnitMinister` (`0x006939F0`)  
**Status**: Fully Implemented & Verified in `patch_darkest_hour.bat`

---

## 1. Overview & Objectives

In vanilla Darkest Hour, script parameters in `garrison = { ... }` (such as `area_multiplier`, `province_priorities`, and `country_priorities`) are strictly confined to the AI country's directly controlled sovereign territory. Whenever an AI country was scripted to assist an ally (e.g. UK defending France at Paris, or USA garrisoning post-war France and Italy):
1. **Ignored Allied Territory**: The engine's garrison loop only traversed domestic `CArea*` clusters (`pCountry + 0xE86E`), ignoring all allied regions.
2. **Peacetime Evacuation Bug**: If troops were positioned in or landed on foreign allied soil during peacetime, `CAIUnitMinister::ManageExpeditionaryForces` (`0x006939F0`) immediately classified them as "stranded abroad", wrote a domestic evacuation target (`[pArmy + 0x298] = home_port`), and ordered transport ships to evacuate them home in an endless loop.
3. **Peacetime Need Wipeout**: At instruction `0x0068C742`, the vanilla engine unconditionally wiped overseas area division requirements to zero during peacetime (`mov dword ptr [ebp-0x2C], 0`).
4. **Anti-Partisan Priority Wipeout**: At instruction `0x0068B978`, interior allied provinces with zero revolt risk (such as Paris) had their configured priorities wiped from `100.0` down to `0.0`.
5. **Missing Threat Inheritance**: Allied border provinces (such as Amiens bordering German-occupied territory) failed to inherit threat priorities from `country_priorities = { GER = 30 }` because the AI only scanned borders of its own national soil.
6. **Overseas Transport Dispatch Blockade**: In Phase 4 (`0x0068D922` - `0x0068DF9C`), foreign provinces and ports in allied shortage areas were rejected by Cave D due to a stale active-area comparison, preventing `CAITransportMinister::DispatchTransport` from ever being called.

**Patch 11** comprehensively resolves all six barriers across the entire garrison and strategic transport pipeline, enabling AI allies to actively dispatch transport fleets, cross the sea, and garrison allied soil both in peacetime and wartime.

---

## 2. Master Hook & Cave Reference Matrix

Patch 11 introduces **13 hooks** across 4 key engine subsystems, utilizing dedicated code caves in the expanded `.mod` PE section (`0x00DCA300` - `0x00DCAB00`):

| Hook # | Virtual Address | File Offset | Length | Target Cave | Description |
|---|---|---|---|---|---|
| **Hook 1** | `0x0068D8B9` | `0x0028D8B9` | 8 bytes | `Cave A` (`0x00DCA320`) | Multi-Area Allied Iterator with resumption & duplicate suppression |
| **Hook 2** | `0x0068C18E` | `0x0028C18E` | 8 bytes | `Cave B` (`0x00DCA500`) | Non-controlled province filter bypass via `IsAlliedOrAccess` |
| **Hook 3** | `0x0068C55A` | `0x0028C55A` | 10 bytes | `Cave C` (`0x00DCA550`) | Allied province counting & area quota calculation |
| **Hook 4** | `0x0068C5B6` | `0x0028C5B6` | 5 bytes | `Cave F` (`0x00DCA640`) | Coastal/border flag calculation for active allied areas |
| **Hook 5** | `0x0068C816` | `0x0028C816` | 7 bytes | `Cave G` (`0x00DCA670`) | Garrison cap calculation for active allied areas |
| **Hook 6** | `0x0068DA09` | `0x0028DA09` | 8 bytes | `Cave D` (`0x00DCA5A0`) | Foreign allied destination province & debarkation port recognition |
| **Hook 7** | `0x0068E291` | `0x0028E291` | 6 bytes | `Cave E` (`0x00DCA600`) | State cleanup at completion of `UpdateGarrisons` |
| **Hook 8** | `0x0069F815` | `0x0029F815` | 12 bytes | `Cave H` (`0x00DCA7E0`) | `CAITransportMinister` transport mission execution to allied ports |
| **Hook 9** | `0x00693CBD` | `0x00293CBD` | 7 bytes | `Cave I` (`0x00DCA820`) | Peacetime foreign garrison repatriation bypass (relocated to Stage 2 entry; Stage 1 wartime expeditionary transfers preserved) |
| **Hook 10** | `0x0068C742` | `0x0028C742` | 7 bytes | `Cave J` (`0x00DCA690`) | Peacetime overseas area need preservation |
| **Hook 11** | `0x0068B978` | `0x0028B978` | 12 bytes | `Cave K` (`0x00DCA8F0`) | Interior province priority preservation (bypasses anti-partisan wipe) |
| **Hook 12** | `0x0068B89E` | `0x0028B89E` | 14 bytes | `Cave L` (`0x00DCA920`) | Dynamic border threat inheritance from `country_priorities` |
| **Hook 13** | `0x00696ECD` | `0x00296ECD` | 16 bytes | `Cave M` (`0x00DCAA00`) | Unassigned Army Distributor Pass to `CGarrisonAI` |
| **Helper** | — | — | — | `0x00DCA700` | Diplomatic alliance & military access validator (`IsAlliedOrAccess`) |

---

## 3. Subsystem Architecture & Implementation Details

### 3.1 Multi-Area Allied Iterator (`Cave A` @ `0x00DCA320`)
When `CGarrisonAI::UpdateGarrisons` completes scanning the AI's domestic areas (`ESI == NULL`), Hook 1 redirects control to Cave A:
1. **Dynamic Resumption (`[0x00DCA30C]`)**: Cave A maintains a stateful pointer to the current multiplier node in `CAI::m_AreaMultiplierList` (`[pCountry->m_pAI + 0x358]`), which the AI parser (`0x006BD9B0`) populates in top-to-bottom script order (appending each node to the tail).
2. **Duplicate Area Suppression & First-In-List Precedence (`seen_areas` buffer @ `0x00DCA4B4`)**: Because multiple province seeds frequently point to the same contiguous `CArea*` cluster (e.g. Paris 56, Amiens 54, and Caen 39 all belong to France Metro), Cave A dispatches the `CArea*` upon encountering the **first** matching province in `m_AreaMultiplierList`, records the `CArea*` in `seen_areas` (`seen_count` @ `0x00DCA4B0`), and skips any subsequent province entries belonging to that same `CArea*`. Combined with the engine's multiplier lookup loop (`0x0068C62E` – `0x0068C67D`), which also breaks on the first matching node (`0x0068C66A: jne 0x0068C675`), **the first entry in the list always wins and later entries in the same area are ignored**—matching vanilla Darkest Hour behavior.
3. **Defensive Validation**:
   - `pCountry->m_pAI != NULL`: Guards human-controlled or uninitialized nations from dereferencing null AI pointers.
   - `1 <= prov_id < 15000`: Validates province ID bounds prior to calling `GetProvince` (`0x004E9370`).
4. **Execution Splicing**: Once an allied area is validated, Cave A injects the pointer into a single-node buffer (`0x00DCA300`), loads `ESI = 0x00DCA300`, and loops back to `0x0068BC07` to execute the full garrison calculations for that allied territory.

### 3.2 Diplomatic Alliance & Access Helper (`IsAlliedOrAccess` @ `0x00DCA700`)
A centralized, register-safe helper routine that determines whether Country A and Country B share military access:
- **Multilateral Factions**: Compares faction master pointers (`[pCountry + 0x3350]`).
- **Master / Puppet Relations**: Verifies puppet status in both directions via `[pCountry + 0x12DA] + 0x3B30`.
- **Bilateral Treaties**: Calls engine diplomatic queries `FUN_005861A0` (Alliance) and `FUN_005861E0` (Military Access).
- Preserves callee registers `EBX`, `ESI`, `EDI` and returns `AL = 1` (valid) or `AL = 0` (invalid).

### 3.3 Peacetime Repatriation Bypass (`Cave I` @ `0x00DCA820`)
In vanilla, `CAIUnitMinister::ManageExpeditionaryForces` (`0x006939F0`) automatically orders any division stationed on foreign soil during peacetime to evacuate home:
1. **Relocated Hook 9 at `0x00693CBD`**:
   - `0x00693A86` is preserved as vanilla (`cmp [ebp-0x28], eax; je 0x00693EB1`), allowing Stage 1 wartime expeditionary transfers to defending allies (e.g. Norway 1940) to execute without interference.
   - Hook 9 intercepts at `0x00693CBD` (Stage 2 entry: repatriation routine).
2. **Non-Intrusive Passive Immunity Guard**:
   - Loads `CProvince*` from stack frame `[ebp - 0x14]`.
   - Checks if unit is on foreign soil belonging to an ally with military access (`call 0x00DCA700`).
   - If `[pArmy + 0x298] != 0`: unit has an active target (e.g. marching to port, embarking, strategic redeployment, or invasion). Cave I **does not touch or cancel** the unit's orders; it immediately jumps to `0x00693EB1` to bypass peacetime repatriation.
   - If already assigned to `CGarrisonAI` (`[pArmy + 0x1F4] == pCountry->m_pGarrisonAI`), it jumps to `0x00693EB1` to preserve the active garrison assignment.
   - If the province area matches an active allied area configured in `area_multiplier` (`CAI::m_AreaMultiplierList`), Cave I caches the active area in `[0x00DCA318]` and jumps to `0x00693EB1`.
   - Units with no allied garrison need and no active target fall through to vanilla repatriation (`mov ecx, ebx; call 0x006A9D50; jmp 0x00693CC4`).
   - Crucially, `call 0x0068EE00` (`CGarrisonAI::AddArmy`) and order-wiping (`target = 0`) are completely eliminated from this repatriation hook, preventing departing or transiting units from being hijacked mid-march.

### 3.4 Overseas Transport Dispatch Recognition (`Cave D` @ `0x00DCA5A0`)
In Phase 4 of `CGarrisonAI::UpdateGarrisons`, the engine scans shortage areas queued in `[ebp - 0x104]` to find destination provinces (`[ebp - 0x38]`) and ports (`[ebp - 0x28]`):
1. Hook 6 at `0x0068DA09` calls Cave D.
2. Cave D evaluates the province controller:
   - Domestic provinces are accepted immediately (`jmp 0x0068DA11`).
   - Foreign provinces are checked via `IsAlliedOrAccess(self, controller)`. If allied or granted military access, they are accepted as valid destinations.
3. This allows the engine to recognize French, Italian, and other allied ports (e.g. Cherbourg, Brest, Naples, Taranto).
4. For surplus divisions in a different theater (e.g. North America), `FindPath` confirms no land connection exists across the ocean, jumping to `0x0068DF9C`.
5. The engine loads the discovered allied debarkation port (`[ebp - 0x28]`) and calls `CAITransportMinister::DispatchTransport` (`0x0068DF83`), sailing surplus divisions across the ocean to fulfill allied garrison deficits.

### 3.5 Inland Priority & Threat Inheritance (`Cave K` & `Cave L`)
- **Cave K (`0x00DCA8F0`)**: Intercepts `0x0068B978`. If bit 3 (`0x8`, explicit `province_priorities`) or bit 1 (`0x2`, foreign border) is set in the province flags, the vanilla anti-partisan priority zero-wipe is bypassed, ensuring interior capitals (Paris = 100, Rome = 960) maintain their configured weights.
- **Cave L (`0x00DCA920`)**: Intercepts `0x0068B89E`. When evaluating borders of allied provinces, Cave L searches `CAI::m_CountryPrioritiesList` (`[pCountry->m_pAI + 0x324]`). If an adjacent foreign province belongs to a prioritized rival (e.g. GER = 30), the allied border province automatically inherits that priority weight.

### 3.6 Unassigned Army Distributor Pass (`Cave M` @ `0x00DCAA00`)
In vanilla Darkest Hour, `CMilitaryAI::DistributeArmiesToMinisters` (`0x00695A00`) distributes armies to ministers by looping exclusively through domestic theaters in `m_TheaterList` (`CCountry + 0xe880`).
- **The Theater Limitation**:
  - In `TestSave6`, the UK directly owned/controlled Caen (`PROV39`). This caused the engine to generate an active UK Continental `CTheater`. When `DistributeArmiesToMinisters` ran, it traversed the continental theater and registered the troops in Caen to `CGarrisonAI`.
  - In `TestSave7`, Caen was controlled by France. The UK held 0 continental territory, so the UK had **only 1 theater: Britain**. `DistributeArmiesToMinisters` skipped all troops in France at `0x00695E01` because their area did not match Britain.
- **The Temporary Cave I Hack & Its Removal**:
  - Early in development, Cave I (inside `ManageExpeditionaryForces`) forcibly called `CGarrisonAI::RegisterArmy` on foreign units as a side effect.
  - When Cave I was updated to be non-aggressive (to prevent hijacking moving US divisions in Italy), this forced call was removed. Because `DistributeArmiesToMinisters` was skipping them, divisions landing in France were left unassigned (`pArmy->m_pAIController == CMilitaryAI`).
  - As a result, `CGarrisonAI::m_ArmyList` had 0 units in France, so `CGarrisonAI` could not order the divisions in Caen to march inland to Paris and Amiens.
- **The Clean Architecture of Cave M**:
  - Hooked at `0x00696ECD` (6 bytes: `jmp 0x00DCAA00; nop`), preserving the `0x00696ED3` exit boundary so exiled nations with `m_TheaterList == NULL` (`0x00695A6E: je 0x00696ED3`) do not clobber stack memory.
  - Sweeps `m_pMilitaryAI->m_ArmyList` (`[ebx + 0x20c]`).
  - Validates:
    1. `pArmy->m_pAIController == CMilitaryAI` (unassigned).
    2. `pArmy->m_dwTargetProvince == 0` (passive check: no active move, embark, invasion, or transit orders).
    3. `IsNavalOrAirUnit(pArmy) == 0` (land army only).
    4. `CanMove(pArmy) == 1` (mobile unit).
    5. Valid province location and area.
    6. If foreign territory: controller must be allied/access via native `0x0044A690`, AND province area must match an active entry in `m_AreaMultiplierList` with `multiplier > 0.0`.
  - Calls `CGarrisonAI::RegisterArmy(pArmy)` (`call dword ptr [edx + 0x1a8]`).
  - `CGarrisonAI` now takes ownership of the divisions. During the next garrison cycle, `CGarrisonAI::UpdateGarrisons` identifies the surplus in Caen and orders them to march inland to Paris and Amiens.

---

## 4. Verification & Testing History

1. **UK Cross-Channel Garrison (DH Lite, `TestSave6` & `TestSave7`)**:
   - British divisions in Portsmouth and Dover embark onto naval transports, cross the English Channel, debark at Caen (Province 39), and march inland on foot to defend Paris (56) and Amiens (54).
2. **USA Transatlantic Peacetime Garrison (DH Full / E3Map 1946)**:
   - Surplus American divisions stationed in the USA Home Area (Norfolk, New York) embark onto naval transport fleets, cross the Atlantic Ocean, debark at French ports (Cherbourg, Brest) and Italian ports (Naples, Genoa), and march inland to garrison Paris, Rome, Naples, and allied border zones.
3. **Hardening & Optimization Pass (V3 Architecture)**:
   - **Finding 1**: Reverted dead-code Hook 5 (`0x0068C816`) to vanilla bytes (`8A 45 E3 84 C0 75 08`) and eliminated Cave G.
   - **Finding 2**: Eliminated global cache `[0x00DCA318]`, restricted repatriation immunity in `Cave I` and garrison registration in `Cave M` strictly to areas with `area_multiplier > 0.0`.
   - **Finding 3**: Rewrote `IsAlliedOrAccess` (`0x00DCA700`) using native engine function `CCountry::HasAccessFromOrIsAllied` (`0x0044A690`), fixing false positives on non-aggression pacts (`0x005861E0`).
   - **Finding 4**: Shrunk Hook 13 to 6 bytes (`0x00696ECD`), preserving `0x00696ED3` exit site for nations without theaters.
   - **Finding 5**: Added `multiplier <= 0.0` check in `Cave A` (`0x00DCA320`), allowing AI scripts to disable allied garrisoning via `= 0`.
   - **Finding 6**: Implemented `seen_areas` table at `0x00DCAB20` storing `{ CArea*, orig_56, orig_5A, orig_5E }`, restored in `Cave E` (`0x00DCA5D0`) to protect host nation AI state.
   - **Finding 7**: Fixed vanilla Phase 4 transport dispatch loop at `0x0068DFCA` (`jne 0x0068DB06`), trying the next surplus army rather than aborting the shortage area.
   - **Finding 8**: Cleaned up Cave F at `0x00DCA650` for allied area peacetime evaluation.
4. **Patcher Reversion & Re-application Verification**:
   - Patched executable hash verified at `04EDF33128E9878FCECC586BE083DC2D9DE1B53B73ED9084596BB56D66BE25BB`.
   - Live testing in DH Lite with `TestSave7` verified unpaused time advancement from July 7 to July 10, 1936, with zero exceptions, clean division movement out of Caen toward Paris and Amiens, and stable debug session.
   - Patcher verification (`patch_darkest_hour.bat -Verify`) confirms 100% integrity across all signatures and chunks.

---

## 5. Modular 3-Mode Configuration & Control Gates

Patch 11 incorporates a modular two-tier control architecture allowing full engine-wide or country-specific toggles with three operational modes:

### 5.1 Global Engine Setting (`db\mod_settings.ini`)
```ini
[AI]
; Enable Allied Territory Garrison AI:
; 0 = No foreign garrisons outside directly controlled territory (vanilla DH behavior)
; 1 = Allow garrisons in ally territory only
; 2 = Allow garrisons in ally and military access territory (default)
EnableAlliedGarrison = 2
```
- Loaded via `GetPrivateProfileIntA` with default `2` into global memory `[0x00DCA290]`.
- If set to `0`, all hooks route through Control Gates directly back to vanilla Darkest Hour execution paths.
- If set to `1`, only domestic and allied territory qualifies; military access nations are excluded.
- If set to `2`, domestic, allied, and military access nations qualify.

### 5.2 Country-Specific Override (`no_foreign_garrison` Local Flag)
- If a nation sets `no_foreign_garrison` via AI flags (`flags = { no_foreign_garrison = <value> }`), scenario `.inc` files, or event scripting (`type = local_setflag which = no_foreign_garrison value = <value>`):
  - **`0`**: Allow ally and military access garrisons (default; inherits global setting).
  - **`1`**: Allow only ally garrisons (disallows military access territory, even if global setting is 2).
  - **`2`**: Allow no foreign garrisons, ally or military access (forces vanilla DH behavior for this specific country).
- If the flag is omitted or set to `0`, the nation inherits the global `EnableAlliedGarrison` setting.

### 5.3 Control Gates & Implementation Details
- **`DetermineGarrisonMode` (`0x00DCAB60`)**:
  - Reads global `EnableAlliedGarrison` (`[0x00DCAB00]`). Returns `AL = 0` if disabled.
  - Queries `no_foreign_garrison` from `pCountry->m_pAI->m_flags` (`[pCountry + 0x120 + 0x4C]`).
  - Clamps effective mode to `0` (disabled), `1` (allied only), or `2` (allied and military access).
- **`IsAlliedOrAccess` (`0x00DCAC00`)**:
  - Section 1: Verifies parameters and determines effective mode (`0x00DCAB60`).
  - Section 2 (Alliance Check): Checks major faction alliance (`[pCountry + 0x3350]`) and master/puppet relations (`[pDiplomacy + 0x3B30]`). Returns `AL = 1` if allied.
  - Fix 1 (NAP Disambiguation): The 22-byte call to `0x005861E0` (Non-Aggression Pact, offset `+0x36`) was permanently replaced with NOPs at `0x00DCAC73 - 0x00DCAC88`. NAPs never count as alliances.
  - Section 3 (Mode Check): `cmp byte ptr [ebp - 4], 2; jb ret_false`. Mode 1 strictly rejects non-allies, ensuring occupation troops withdraw under `no_foreign_garrison = 1` or `EnableAlliedGarrison = 1`.
  - Section 4 (Military Access): If Mode 2, queries `CDiplomacy::HasAccessTo` (`0x005861A0`, offset `+0x37`) in both directions. Returns `AL = 1` if access is granted.
- **Rogue Foreign Area Injection Bypass (`Cave A` @ `0x00DCA320`)**:
  - Fix 2: Jumps at `0x00DCA336` and `0x00DCA384` are permanently redirected to `0x00DCA43A` (clean exit of Cave A).
  - Bypasses the Phase 3 Fallback division-list scanner (`0x00DCAEB0`), ensuring areas not explicitly configured in `area_multiplier` are never evaluated or garrisoned.
- **Patcher Status**: Fully synchronized in `patch_darkest_hour.bat` and `tools/patch_darkest_hour.bat` (Verified SHA256: `DBA433A40F6AF9272E2AAB8065EF5CD3B41320C48EA1AD3D90328693B18DB305`).

---

## 6. Pending Challenge: Landlocked Overseas Repatriation (Issue 3)

### 6.1 Problem Architecture
In `CMilitaryAI::ManageExpeditionaryForces` (`0x006939F0`):
- For overseas nations (e.g. USA or UK in Austria) with zero continental sovereign territory:
  - `CanMarchTo` to domestic homeland fails across the ocean.
  - `0x006AAFF0` (naval transport) fails because Austria is landlocked.
  - Vanilla aborts at `0x00693E57: je 0x693EB1`, leaving divisions permanently trapped.

### 6.2 Solution Design
Hook at `0x00693E57` (failure branch of naval transport):
- Does NOT disturb normal naval transport for coastal units (e.g. British divisions in France returning across the Channel).
- Only when both overland domestic march and naval transport have failed, triggers an allied overland fallback to find adjacent allied territory (e.g. West Germany or Italy) via `CanMarchTo`, issuing a native march order across the border.
