# Patch 11: Allied Territory Garrison AI Architecture & Implementation

**Engine**: Darkest Hour 1.05.2 (checksum TENE)  
**Binary Executable**: `Darkest Hour.exe`  
**Primary Subsystems**: `CGarrisonAI` (`FUN_0068ba50` @ `0x0068BA50`), `CInvasionAI` / `CAITransportMinister` (`0x0069F7F0`), `CAIUnitMinister` (`0x006939F0`), `CMilitaryAI` (`0x00695A00`)  
**Status**: Fully Implemented & Verified in `patch_darkest_hour.bat` (`SHA256 = 68C94AD513473B54AD3BC30B666FE138085AE60D5F0C46CFF211FA9DD177534A`)

---

## 1. Overview & Objectives

For the baseline retail engine behavior and limitations, see **[Garrison AI Architecture & Division Quotas (Retail Engine)](../engine/garrison_ai.md)**.

**Patch 11** extends the Darkest Hour Garrison AI, Military AI, Transport/Invasion AI, and Unit Minister subsystems to allow AI nations to station, reinforce, and withdraw divisions in foreign allied and military-access territory based on standard AI script directives (`area_multiplier`, `province_priorities`, `country_priorities`) while respecting global (`db\mod_settings.ini`) and per-country (`no_foreign_garrison`) configuration switches.

Key capabilities introduced by Patch 11:
1. **Multi-Area Foreign Evaluation**: Appends foreign allied/access areas configured in `area_multiplier` (`[CAI + 0x358]`) to `CGarrisonAI::UpdateGarrisons` (`Cave A`), preserving host-nation `CArea` fields and restoring them on exit (`Cave E`).
2. **Allied & Access Province Priority & Port Recognition**: Permits `CGarrisonAI` to evaluate priorities (`Cave B`), preserve interior priorities (`Cave K`), inherit border threat from `country_priorities` (`Cave L`), and select destination provinces/ports (`Cave D`) on allied or military-access territory.
3. **Configurable Multipliers**: Exposes the land-connected rear multiplier (`GarrisonLandConnectedMultiplier`, Hook 16) and wartime rear/allied multiplier (`GarrisonWartimeMultiplier`, Hook 17 / `Cave N`) in `db\mod_settings.ini`, while ensuring foreign allied areas ignore host-nation `CFrontAI` front overrides (`Cave G`) and check `CCountry::IsAtWar()` / `FindAlliedFrontNeedingTroops()` before applying wartime halving (`Cave N`).
4. **Deterministic Overland Dispatch & Repatriation**:
   - Retains inter-area overland marching units inside `CGarrisonAI::m_ArmyList` (`Hook 24` at `0x0068DF74`) and counts moving units in their final destination area rather than their origin area (`Hook 20` / `Cave R` calling `0x0051C0C0`).
   - Prevents non-homeland shortage areas from pulling surplus units out of other foreign areas (`Hook 22` / `Cave U`).
   - Orders any leftover foreign surplus units in `[ebp - 0x6C]` at the end of Phase 4 to march overland back to the country's capital area (`Hook 23` / `Cave T` calling `0x0044E1D0`).
   - Restricts `CMilitaryAI::DistributeArmiesToMinisters` registration (`Cave M`) and `ManageExpeditionaryForces` repatriation immunity (`Cave I`) strictly to areas targeted by `fn_IsAreaTargeted` (`0x00DCACD5`).
5. **Overseas Transport Delivery & `CInvasionAI` Hardening**:
   - Protects peacetime allied/access transport missions and `CGarrisonAI`-owned units from pre-departure threat cancellation (`Cave H`), authorizes military-access port unloading (`Hooks 14 & 15`), and continues scanning surplus candidate armies on transport failure (`0x0068DFCA`).
   - Overrides `CInvasionAI::vtable[0x198/4]` (`0x007F56AC` -> `0x00DCA870`) and sanitizes list traversal (`Hook 21` / `Cave S`) to prevent dangling-pointer crashes when invasion/transport units are destroyed in combat.

---

## 2. Master Hook & Cave Reference Matrix

Patch 11 utilizes code caves in the `.mod` PE section (`0x00DCA188` - `0x00DCAF90`):

| Hook / Patch | Virtual Address | File Offset | Length | Target / Cave | Description |
|---|---|---|---|---|---|
| **Hook 1** | `0x0068D8B9` | `0x0028D8B9` | 8 bytes | `Cave A` (`0x00DCA320`) | Multi-area allied iterator over `m_AreaMultiplierList` with `seen_areas` de-duplication |
| **Hook 2** | `0x0068C18E` | `0x0028C18E` | 8 bytes | `Cave B` (`0x00DCA500`) | Non-controlled province filter bypass via `IsAlliedOrAccess_Switchable` |
| **Hook 3** | `0x0068C55A` | `0x0028C55A` | 10 bytes | `Cave C` (`0x00DCA550`) | Allied province counting & area quota calculation |
| **Hook 4** | `0x0068C5B6` | `0x0028C5B6` | 5 bytes | `Cave F` (`0x00DCA650`) | Coastal & border flag calculation for active allied areas |
| **Hook 5** | `0x0068C816` | `0x0028C816` | 7 bytes | `Cave G` (`0x00DCA670`) | Foreign allied area front-override bypass (preserves `area_multiplier` when `[0x00DCA310] != 0`) |
| **Hook 6** | `0x0068DA09` | `0x0028DA09` | 8 bytes | `Cave D` (`0x00DCA5A0`) | Phase 4 foreign allied destination province & debarkation port recognition |
| **Inline Fix** | `0x0068DFCA` | `0x0028DFCA` | 6 bytes | Inline (`0x0068DFCA`) | Phase 4 transport dispatch loop continuation (`jne 0x0068DB06` instead of aborting to `0x0068DB11`) |
| **Hook 7** | `0x0068E291` | `0x0028E291` | 6 bytes | `Cave E` (`0x00DCA5D0`) | Host-nation `CArea` metadata restoration (`+0x56`, `+0x5A`, `+0x5E` from `0x00DCAB20`) & state cleanup |
| **Hook 8** | `0x0069F815` | `0x0029F815` | 12 bytes | `Cave H` (`0x00DCA7E0`) | `CInvasionAI::Update` vtable guard & transport mission threat cancellation gate |
| **Hook 9** | `0x00693CBD` | `0x00293CBD` | 7 bytes | `Cave I` (`0x00DCA820`) | Stage 2 peacetime foreign garrison repatriation bypass (gated by `fn_IsAreaTargeted`) |
| **Hook 10** | `0x0068C742` | `0x0028C742` | 7 bytes | `Cave J` (`0x00DCA690`) | Peacetime overseas area need preservation (`[0x00DCA310] != 0`) |
| **Hook 11** | `0x0068B978` | `0x0028B978` | 12 bytes | `Cave K` (`0x00DCA8F0`) | Interior province priority preservation (bypasses anti-partisan zero-wipe) |
| **Hook 12** | `0x0068B89E` | `0x0028B89E` | 13 bytes | `Cave L` (`0x00DCA920`) | Dynamic border threat inheritance from `country_priorities` |
| **Hook 13** | `0x00696ECD` | `0x00296ECD` | 16 bytes | `Cave M` (`0x00DCAA00`) | Unassigned foreign army distributor pass to `CGarrisonAI` (gated by `fn_IsAreaTargeted`) |
| **Hook 14** | `0x005177C1` | `0x001177C1` | 21 bytes | `0x00DCA700` | `CUnit::CanFleetUnloadAtProvince` military access unload authorization |
| **Hook 15** | `0x00522CFB` | `0x00122CFB` | 21 bytes | `0x00DCA700` | `CUnit::CanMoveToProvince` military access amphibious disembarkation authorization |
| **Hook 16** | `0x0068C7D3` | `0x0028C7D3` | 18 bytes | Inline (`0x0068C7D3`) | Configurable land-connected area multiplier (`GarrisonLandConnectedMultiplier` @ `0x00DCAAE0`) |
| **Hook 17** | `0x0068CAF0` | `0x0028CAF0` | 51 bytes | `Cave N` (`0x00DCA980`) | Configurable wartime rear & allied area multiplier (`GarrisonWartimeMultiplier` @ `0x00DCAAE4`) |
| **Hook 20** | `0x0068BCB1` | `0x0028BCB1` | 20 bytes | `Cave R` (`0x00DCA188`) | Destination-aware en-route unit counting via `0x0051C0C0` (`GetFinalMoveTargetProvince`) |
| **Hook 21** | `0x006A0280` | `0x002A0280` | 8 bytes | `Cave S` (`0x00DCA890`) | `CInvasionAI::Update` linked-list node pointer sanitization |
| **Vtable Fix** | `0x007F56AC` | `0x003F56AC` | 4 bytes | `0x00DCA870` | `CInvasionAI::vtable[0x198/4]` override -> `fn_invasion_remove_unit` |
| **Hook 22** | `0x0068DAAE` | `0x0028DAAE` | 7 bytes | `Cave U` (`0x00DCA1C4`) | Phase 4 foreign surplus candidate filter (prevents cross-foreign-area siphoning) |
| **Hook 23** | `0x0068DB16` | `0x0028DB16` | 6 bytes | `Cave T` (`0x00DCA6B9`) | Phase 4 final capital repatriation pass for leftover foreign surplus in `[ebp - 0x6C]` |
| **Hook 24** | `0x0068DF74` | `0x0028DF74` | 21 bytes | Inline (21 NOPs) | Retains overland inter-area marching units in `CGarrisonAI` instead of transferring to `CTheatreAI` |
| **Helper** | `0x00DCAB60` | `0x00485B60` | 128 bytes | `DetermineGarrisonMode` | Evaluates `EnableAlliedGarrison` (`0x00DCAB00`) and `no_foreign_garrison` (`[pCountry+0x120+0x4C]`) |
| **Helper** | `0x00DCA700` -> `0x00DCAC00` | `0x00485700` / `0x00485C00` | 213 bytes | `IsAlliedOrAccess_Switchable` | Diplomatic alliance & military access validator with Mode 0/1/2 enforcement |
| **Helper** | `0x00DCACD5` | `0x00485CD5` | 120 bytes | `fn_IsAreaTargeted` | Checks whether a `CArea*` has a positive entry in `m_AreaMultiplierList` or `m_ProvincePrioritiesList` |

---

## 3. Subsystem Architecture & Implementation Details

### 3.1 Phase 2: Multi-Area Allied Iterator (`Cave A` @ `0x00DCA320` & `Cave E` @ `0x00DCA5D0`)
When `CGarrisonAI::UpdateGarrisons` finishes iterating the country's domestic `m_AreaList` (`ESI == NULL` at `0x0068D8B9`), **Hook 1** jumps to `Cave A` (`0x00DCA320`):
1. **Resumption Pointer (`[0x00DCA30C]`)**: Iterates through `CAI::m_AreaMultiplierList` (`[pCountry->m_pAI + 0x358]`).
2. **Positive Multiplier Filter**: Checks `cmp dword ptr [ecx + 4], 0; jle next_node`. Entries with `multiplier <= 0.0` are skipped, allowing AI scripts to disable garrisoning in an area by setting `= 0`.
3. **Duplicate Area Suppression ("First-In-List Wins", `0x00DCA4B4`)**: Records each evaluated `CArea*` in `seen_areas` (`0x00DCA4B4`, count at `0x00DCA4B0`) and skips subsequent province seeds that resolve to an already-evaluated `CArea*`.
4. **Host Metadata Backup & Restoration (`0x00DCAB20` & `Cave E` @ `0x00DCA5D0`)**: Before evaluating a foreign `CArea*`, `Cave A` saves its original `{ CArea*, orig_56, orig_5A, orig_5E }` in the backup table at `0x00DCAB20`. When `UpdateGarrisons` exits at `0x0068E291`, **Hook 7** (`Cave E`) restores those fields so the host nation's own AI state is never polluted.
5. **No Unconfigured Area Injection**: Jumps at `0x00DCA336` and `0x00DCA384` exit directly to `0x00DCA43A` -> `0x0068D8C1` once `m_AreaMultiplierList` is exhausted, ensuring unconfigured foreign areas are never injected into the evaluation pass.

### 3.2 Foreign Area Multiplier Preservation (`Cave G` @ `0x00DCA670` & `Cave J` @ `0x00DCA690`)
1. **Peacetime Need Preservation (`Hook 10` @ `0x0068C742` -> `Cave J` @ `0x00DCA690`)**:
   - Bypasses the `mov dword ptr [ebp - 0x2C], 0` peacetime overseas wipe when `[0x00DCA310] != 0` (active foreign allied area).
2. **Foreign Front-Override Bypass (`Hook 5` @ `0x0068C816` -> `Cave G` @ `0x00DCA670`)**:
   - In the area header scan (`0x0068C0B0` - `0x0068C170`), `[ebp - 0xE3]` is set by comparing `[pFrontAI + 0x38] == pArea` across the evaluating country's `CFrontAI` list (`[pCountry + 0xE880]`). Because foreign allied areas do not belong to the donor country's `CFrontAI` list, `[ebp - 0xE3]` can remain `0` while `[ebp - 0x1E]` is polluted, which at `0x0068C816` would overwrite `area_multiplier` with `1.0`.
   - `Cave G` checks `cmp dword ptr [0x00DCA310], 0; jne 0x0068C825`, skipping the `1.0` override for foreign allied areas in Phase 2 so their configured `area_multiplier` is always respected.

### 3.3 Configurable Multipliers (`Hook 16` @ `0x0068C7D3` & `Hook 17` / `Cave N` @ `0x00DCA980`)
1. **Land-Connected Area Multiplier (`Hook 16` @ `0x0068C7D3`)**:
   - Replaces the hardcoded integer division by 3 with `fild dword ptr [ebp - 0x2C]; fmul dword ptr [0x00DCAAE0]; fistp dword ptr [ebp - 0x2C]`, reading `GarrisonLandConnectedMultiplier` (`0x00DCAAE0`, default `0.333`).
2. **Wartime Rear & Allied Area Multiplier (`Hook 17` @ `0x0068CAF0` -> `Cave N` @ `0x00DCA980`)**:
   - Redirects the 51-byte wartime halving block (`0x0068CAF0` - `0x0068CB22`) to `Cave N`:
     ```asm
     0x00DCA980: cmp dword ptr [0x00DCA310], 0
     0x00DCA987: jne 0x00DCA997                  ; Foreign allied area -> skip domestic front flags, go to war check
     0x00DCA989: mov al, byte ptr [ebp - 0x11]   ; Domestic front check 1
     0x00DCA98C: test al, al
     0x00DCA98E: jne 0x00DCA9C9                  ; Active front -> do not halve
     0x00DCA990: mov al, byte ptr [ebp - 0x1E]   ; Domestic front check 2
     0x00DCA993: test al, al
     0x00DCA995: jne 0x00DCA9C9                  ; Active front -> do not halve
     0x00DCA997: mov eax, dword ptr [ebp - 0xE0] ; FindAlliedFrontNeedingTroops()
     0x00DCA99D: test eax, eax
     0x00DCA99F: jne 0x00DCA9AD                  ; Allied front needs troops -> apply wartime multiplier
     0x00DCA9A1: mov ecx, dword ptr [ebx + 0x0A] ; pCountry
     0x00DCA9A4: call 0x0044BEB0                 ; CCountry::IsAtWar()
     0x00DCA9A9: test al, al
     0x00DCA9AB: je 0x00DCA9C9                   ; At peace -> skip wartime multiplier
     0x00DCA9AD: fild dword ptr [ebp - 0x2C]
     0x00DCA9B0: fmul dword ptr [0x00DCAAE4]     ; * g_fGarrisonWartimeMultiplier (default 0.5)
     0x00DCA9B6: fistp dword ptr [ebp - 0x2C]
     0x00DCA9B9: mov esi, dword ptr [ebp - 0x2C]
     0x00DCA9BC: mov eax, esi
     0x00DCA9BE: sub eax, dword ptr [ebp - 0x44]
     0x00DCA9C1: mov dword ptr [ebp - 0x24], eax
     0x00DCA9C4: jmp 0x0068CB26
     0x00DCA9C9: jmp 0x0068CB23
     ```
   - **Domestic Areas (`[0x00DCA310] == 0`)**: Preserves front-area immunity (`[ebp - 0x11]` and `[ebp - 0x1E]`), and replaces `[ebp - 0x4E]` with `CCountry::IsAtWar()` (`0x0044BEB0`) so maritime/island nations at war also scale their rear areas by `GarrisonWartimeMultiplier`.
   - **Foreign Allied Areas (`[0x00DCA310] != 0`)**: Bypasses `[ebp - 0x11]` / `[ebp - 0x1E]` (which can be non-deterministically set by `CFrontAI` state across reloads) and branches to `0x00DCA997` to check `FindAlliedFrontNeedingTroops()` (`[ebp - 0xE0]`) and `CCountry::IsAtWar()` (`0x0044BEB0`). Thus, foreign allied areas are scaled by `GarrisonWartimeMultiplier` (`0.5x`) when at war and remain unscaled (`1.0x`) during peacetime.

### 3.4 En-Route Overland Unit Tracking & Foreign Surplus Repatriation (`Hooks 20, 22, 23, 24`)
To ensure exact division counts without over-dispatch, reload inconsistency, or endless back-and-forth marching between allied areas:
1. **Retaining Overland Marching Units in `CGarrisonAI` (`Hook 24` @ `0x0068DF74`, 21 NOPs)**:
   - When `UpdateGarrisons` dispatches a surplus unit overland to a needy area (`0x0068DE12` - `0x0068DF88`), retail code at `0x0068DF74` called `pDestTheatre->AddUnit(esi)`, removing the marching unit from `CGarrisonAI::m_ArmyList` (`[ebx + 0x94]`) until arrival. While in transit, `UpdateGarrisons` could no longer see the unit and repeatedly dispatched additional replacements every day.
   - **Hook 24** replaces the 21-byte `pDestTheatre->AddUnit(esi)` transfer at `0x0068DF74` - `0x0068DF88` with `NOP`s so overland marching units remain registered in `CGarrisonAI::m_ArmyList` throughout their march.
2. **Destination-Aware Unit Counting (`Hook 20` @ `0x0068BCB1` -> `Cave R` @ `0x00DCA188`)**:
   - When `UpdateGarrisons` counts units in `[ebx + 0x94]` (`0x0068BC91` - `0x0068BD00`), `Cave R` checks `cmp dword ptr [edi + 0x298], 0` (`pUnit->IsMoving()`):
     - If stationary (`<= 0`), it uses the unit's current province `[edi + 0x220]`.
     - If moving (`> 0`), it calls `0x0051C0C0` (`CUnit::GetFinalMoveTargetProvince()`, which traverses the movement path `[edi + 0x170]` to return the final destination province ID) and resolves `GetProvince(id)->m_pArea`.
   - Consequently, the moment a unit is ordered to march from Area A to Area B, it is immediately counted toward Area B's `nDivisions` and deducted from Area A's `nDivisions`.
3. **Phase 4 Foreign Surplus Candidate Filter (`Hook 22` @ `0x0068DAAE` -> `Cave U` @ `0x00DCA1C4`)**:
   - During Phase 4 (`0x0068DA90` - `0x0068DB11`), when a non-homeland shortage area searches `[ebp - 0x6C]` for candidate surplus units, `Cave U` rejects candidate units located on foreign soil (`[pUnitProv + 0x3D8] != pCountry`), preventing foreign allied areas from pulling surplus units out of other foreign allied areas.
4. **Phase 4 Final Capital Repatriation Pass (`Hook 23` @ `0x0068DB16` -> `Cave T` @ `0x00DCA6B9`)**:
   - When the Phase 4 needy-area queue `[ebp - 0x104]` is exhausted (`0x0068DB16`), any surplus units still remaining in `[ebp - 0x6C]` that are sitting on foreign soil would otherwise remain stranded whenever the homeland capital area itself had no deficit (`nAreaLack <= 0`).
   - `Cave T` calls `0x0044E1D0` (`CCountry::GetCapitalArea()`) and, if the capital area is non-null, re-enters the Phase 4 dispatch body (`0x0068D938`) once with the capital area as destination so all remaining foreign surplus units in `[ebp - 0x6C]` are ordered to march overland back to the homeland.

### 3.5 Target-Aware Army Registration & Peacetime Repatriation (`Cave M`, `Cave I`, `fn_IsAreaTargeted`)
1. **`fn_IsAreaTargeted` (`0x00DCACD5`)**:
   - Inspects `m_AreaMultiplierList` (`[pAI + 0x358]`) and `m_ProvincePrioritiesList` (`[pAI + 0x336]`) for the given `CArea*`. Returns `AL = 1` only if an entry in that area has a strictly positive (`> 0`) multiplier or priority.
2. **Unassigned Foreign Army Distributor (`Hook 13` @ `0x00696ECD` -> `Cave M` @ `0x00DCAA00`)**:
   - Sweeps `CMilitaryAI::m_ArmyList` (`[ebx + 0x20C]`) for idle land armies (`[pArmy + 0x1F4] == ebx`, `[pArmy + 0x298] == 0`) located in foreign allied/access provinces where `fn_IsAreaTargeted` returns `1`, and registers them to `CGarrisonAI` (`call dword ptr [edx + 0x1A8]`).
   - Units in unconfigured foreign areas (`fn_IsAreaTargeted == 0`) are left unassigned so `ManageExpeditionaryForces` can repatriate them.
3. **Peacetime Repatriation Filter (`Hook 9` @ `0x00693CBD` -> `Cave I` @ `0x00DCA820`)**:
   - Placed at Stage 2 entry of `CAIUnitMinister::ManageExpeditionaryForces` (`0x00693CBD`), preserving Stage 1 wartime expeditionary transfers (`0x00693A86`).
   - If the unit is on foreign allied/access soil (`IsAlliedOrAccess_Switchable == 1`) and either has an active movement target (`[pArmy + 0x298] != 0`) or is in an area where `fn_IsAreaTargeted == 1`, `Cave I` jumps to `0x00693EB1` (bypassing peacetime evacuation). Otherwise, it falls through to retail repatriation (`0x00693CC4`).

### 3.6 Overseas Transport Delivery & `CInvasionAI` Dangling Pointer Fixes (`Cave H`, `Cave S`, Vtable Override)
1. **Transport Mission Threat Gate & Vtable Guard (`Hook 8` @ `0x0069F815` -> `Cave H` @ `0x00DCA7E0`)**:
   - Validates `[ebx] == 0x007E85C0` (living `CArmy` vtable); if invalid/freed, jumps to `0x006A0278` (next unit).
   - If `[ebx + 0x1F4] != ebp` (army already owned by `CGarrisonAI` rather than `CInvasionAI`), skips invasion attack planning and jumps to `0x006A0278`.
   - Preserves retail's non-ally bypass (`IsAlliedWith == 0` -> `0x0069F871`) and bypasses pre-departure threat cancellation for peacetime allied missions (`IsAtWar == 0` -> `0x0069F871`).
2. **`CInvasionAI` Destroyed Unit Unlinking (`0x007F56AC` -> `fn_invasion_remove_unit` @ `0x00DCA870`)**:
   - Redirects `CInvasionAI::vtable[0x198/4]` from `CMinisterAI::vfn_198` (`0x006709A0`) to `0x00DCA870`, which calls both `CInvasionAI::RemoveArmy` (`0x006A1040`) and `CInvasionAI::RemoveTransport` (`0x006A1220`) when a unit is destroyed.
3. **List Node Sanitization (`Hook 21` @ `0x006A0280` -> `Cave S` @ `0x00DCA890`)**:
   - Validates linked-list node pointers at the end of `CInvasionAI::Update`'s unit loop against null, unmapped (`<= 0x10000`), or freed (`0xDFDFDFDF` / `0xD0D0D0D0`) memory markers.

---

## 4. Configuration & Control Gates (`db\mod_settings.ini` & `no_foreign_garrison`)

### 4.1 Global Engine Settings (`db\mod_settings.ini`)
```ini
[AI]
; Enable Allied Territory Garrison AI:
; 0 = No foreign garrisons outside directly controlled territory (vanilla DH behavior)
; 1 = Allow garrisons in ally territory only
; 2 = Allow garrisons in ally and military access territory (default)
EnableAlliedGarrison = 2

; Multiplier applied to garrison requirement for areas with direct land connection to homeland (default = 0.333, 1.0 = do nothing / no division)
GarrisonLandConnectedMultiplier = 0.333

; Multiplier applied to garrison requirement during wartime (default = 0.5, 1.0 = do nothing / no halving)
GarrisonWartimeMultiplier = 0.5
```

### 4.2 Country-Specific Override (`no_foreign_garrison` Local Flag)
Evaluated by `DetermineGarrisonMode` (`0x00DCAB60`) from `pCountry->m_pAI->m_flags` (`[pCountry + 0x120 + 0x4C]`):
- **`0` (or unset)**: Inherit global `EnableAlliedGarrison` setting.
- **`1`**: Clamp effective mode to at most `1` (ally territory only; excludes military access).
- **`2`**: Clamp effective mode to `0` (disables all foreign garrisons for this country).

### 4.3 `IsAlliedOrAccess_Switchable` (`0x00DCA700` -> `0x00DCAC00`)
- Returns `1` immediately if `CountryA == CountryB` (domestic territory).
- Queries `DetermineGarrisonMode(CountryA)` (`0x00DCAB60`). Returns `0` if effective mode is `0`.
- **Mode >= 1 (Alliances)**: Checks major faction membership (`[pCountry + 0x3350]`) and bilateral military alliance treaties (`CCountry::IsAlliedWith` @ `0x0044B300`). Non-aggression pacts (`0x005861E0`) and non-allied neutral puppets without military access return `0`.
- **Mode == 2 (Military Access)**: Checks `CDiplomacy::HasAccessTo` (`0x005861A0`, relation offset `+0x37`) in both directions.

---

## 5. Binary Signatures & Verification

| File | Status | SHA-256 |
|---|---|---|
| `Darkest Hour_original.exe` | Pristine v1.05.2 (TENE) | `7A1AE8BB802377B6C9EC808F420ACE58475D1816464390422CF97AD450A51EB4` |
| `Darkest Hour_modified.exe` | Patched (`v59` All Fixes) | `68C94AD513473B54AD3BC30B666FE138085AE60D5F0C46CFF211FA9DD177534A` |
