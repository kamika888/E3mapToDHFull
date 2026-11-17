# Patch 18: Salient Topological Evacuation & Momentum Engine (STEM) - Implementation Status & Reference

**Status**: Local K-Hop Option B Bottleneck Engine & Save-Reload Reset Complete | **Binary SHA-256**: `BD954DB86D85920BD40002EB410D4F335A3924B412B0DCE2FD3602DBEC87833C`  
**Related Docs**: [Front AI Architecture](../engine/front_ai.md) | [Plans Index](README.md) | [Patcher](../../tools/patch_darkest_hour.bat) | [Settings](../../db/mod_settings.ini)

---

## 1. Executive Summary

Patch 18 (STEM) adds topological encirclement detection and salient evacuation to `CFrontAI` using an hourly frontline bottleneck / BFS pass rooted in a dedicated `.mod` cave block (`0x00DCBAB0..0x00DCCD0A`). Following the initial realignment and persistent evacuation registry, STEM was upgraded to a **Local K-Hop Frontline Search + Option B (Threshold-Capped Greedy Path-Blocking BFS)** engine with **Save-Reload Registry Clearing** so that `SalientNeckWidthThreshold` directly measures actual unthreatened escape paths (`IF actualSafeNeckWidth < SalientNeckWidthThreshold => Withdraw`) even when attacked shoulders fall and combat temporarily pauses.

Live validation (`PID 4740`, `28 September 1941`, and `PID 7588`, `24 August 1941`, `SalientNeckWidthThreshold = 3`, `SalientSearchDepth = 5`) confirmed that:
- `Cave_PostLoadInit` (`0x00DCCAB8`) clears `g_pGraphTable + 0x30000..+0x3BFFF` (`48 KB`) on scenario/savegame load, preventing stale evacuation slots from persisting across save reloads.
- Bounded $K$-hop frontline expansion (`SalientSearchDepth = 5`, configurable via `db/mod_settings.ini`, `-1` for unlimited propagation terminating at Supply Depots / Capital) restricts graph evaluation to `105..109` active-front provinces (`~13%` of the USSR map) and cleanly isolates horizon roots without spilling beyond hop $K$.
- Active-front early exit skips non-AI countries (`CRebelCountry` `0x007E5934` / `CHumanCountry` `0x007F04E0`), peaceful countries, and fronts without hostile border pressure.
- Option B vertex-disjoint safe path counting detects the Lvov 3-province bottleneck (`3273 Brody` threatened, leaving `< 3` safe corridors through `229 Ternopol` / `1401 Hotin`), assigning `neck = 229` across all `8` Lvov salient provinces (`500, 501, 507, 1173, 1884, 3396, 7978, 7984`) and dispatching/maintaining evacuation marches to `229 Ternopol` for every non-retreating division inside the pocket.
- Allied-access pathing (`CCountry::CanEnterOrTraceSupply` @ `0x0044A690`), `UseSupplyDepotsAsCores`, `NeckThreatRatio` / `NeckCollapsingOrgThreshold`, and the `0x00681CD0` cancellation shield (`g_pGraphTable + 0x34000` & `[pArmy + 0x17B] = 2`) continue to protect evacuating units until reaching `dest_prov`.

---

## 2. `db/mod_settings.ini` Wiring Audit

### 2.1 `[FrontAI]` & `[Engine]` Configuration Status

| Section | Variable | Current INI | Binary Slot VA | Status | Notes |
| :--- | :--- | :---: | :---: | :--- | :--- |
| `[FrontAI]` | `EnableEncirclementDefense` | `1` | `0x00DCBAB0` | **Wired & Active** | Master gate checked by `0x00DCCB93` (`Cave_STEM_HourlyPerCountry`) and evacuation checks. |
| `[FrontAI]` | `SalientNeckWidthThreshold` | `3` | `0x00DCBAB4` | **Wired & Active** | Minimum required unthreatened vertex-disjoint escape paths in Option B (`Cave_STEM_UpdateGraphTable` @ `0x00DCBDD5`) and Pass-2 bridge fallback threshold. |
| `[FrontAI]` | `SalientSearchDepth` | `5` | `0x00DCBAB8` | **Wired & Active** | Reused scrapped slot (`0x00DCBB30`); bounds inward frontline BFS hops (`> 0`), or `-1` for depot/capital termination (`0x7FFF` cap). |
| `[FrontAI]` | `UseSupplyDepotsAsCores` | `1` | `0x00DCBABC` | **Wired & Active** | When `1`, accessible provinces (`0x0044A690`) in the strip with a local supply stockpile (`[pProv + 0x270] > 0.0f`) or supplied controller capital act as core roots (`is_core_root`). |
| `[FrontAI]` | `NeckThreatRatio` | `1.5` | `0x00DCBAC0` | **Wired & Active** | Dynamically read by `0x00DCBDD5`; hostile-to-friendly ground combat strength ratio needed to flag a province as threatened (`+0x24000`). |
| `[FrontAI]` | `NeckCollapsingOrgThreshold` | `10.0` | `0x00DCBAC4` | **Wired & Active** | Dynamically read by `0x00DCBDD5` (binary default `30.0`); average friendly defender organization threshold triggering threat flag alongside `NeckThreatRatio`. |
| `[FrontAI]` | `SalientEvacuationQuota` | `0.0` | `0x00DCBACC` | **Pending (Unreferenced)** | Loaded from `db/mod_settings.ini` into `0x00DCBACC`, but not yet referenced by STEM evacuation code. |
| `[FrontAI]` | `BottleneckDefenseBoost` | `3.5` | `0x00DCBAD0` | **Pending (Unreferenced)** | Loaded from `db/mod_settings.ini` into `0x00DCBAD0`, but not yet wired into `CFrontAI` province priority weighting. |
| `[FrontAI]` | `SpearheadWinningOdds` | *removed* | `0x00DCBAC8` | **Scrapped** | INI key removed. Header slot `0x00DCBAC8` retained only for struct alignment; unreferenced by runtime code. |
| `[Engine]` | `AlwaysShowMovementArrows` | `1` | `0x00DCBAD8` | **Wired & Active** | Loaded by `Cave_LoadEngineSettings` (`0x00DCCB1C`); controls forced arrow rendering (`0x00DCCA24` / `0x00DCCA82`). |
| `[Engine]` | `AutoNoFog` | `1` | `0x00DCBAE8` | **Wired & Active** | Loaded by `Cave_LoadEngineSettings` (`0x00DCCB1C`); applied on scenario/save load (`0x00DCCAB8`) and hourly tick (`0x00DCCBDE`). |
| `[Engine]` | `AutoShowId` | `1` | `0x00DCBAEC` | **Wired & Active** | Loaded by `Cave_LoadEngineSettings` (`0x00DCCB1C`); applied on scenario/save load (`0x00DCCAB8`) and hourly tick (`0x00DCCBDE`). |

---

## 3. Realized Hook & Cave Architecture

### 3.1 Active Hooks into Retail `Darkest Hour.exe`

| Retail Address | Target / Cave Function | Role |
| :--- | :--- | :--- |
| `0x005AEDBE` | `Cave_STEM_HourlyAllCountries` (`0x00DCCBDE`) | Hourly AI tick: initializes STEM scratchpad & dispatches `Cave_STEM_HourlyPerCountry` (`0x00DCCB93`). |
| `0x00682A58` | `Cave_FrontAI_ManageReservesAndSalients` (`0x00DCCC83`) | Wrapper around retail `CFrontAI::ManageRearReserves` (`0x00681CD0`); shields evacuating units from `0x00681CD0` and registers them in `[CFrontAI + 0xC8]`. |
| `0x005226C1` | `Cave_DeselectArrows` (`0x00DCCA82`) | Supports `AlwaysShowMovementArrows` when deselected on map. |
| `0x00DCAE55` | `Cave_PostLoadInit` (`0x00DCCAB8`) | Clears `g_pGraphTable + 0x30000..+0x3BFFF` (`48 KB`) on scenario/save load and applies `AutoNoFog`, `AutoShowId`, and `AlwaysShowMovementArrows`. |

### 3.2 Cave Layout (`.mod` Patch 18 Chunk @ `0x00DCBAB0..0x00DCCD0A`)

- `0x00DCBAB0..0x00DCBAF0`: Parameter header (strings & loaded INI values; `0x00DCBAB8`/`0x00DCBB30` wired to `SalientSearchDepth`, `0x00DCBADC` zeroed, stale `0x00DCBC00..0x00DCBC2B` and `0x00DCBD60..0x00DCBD9F` regions sanitized, `0x00DCBCD7: jmp 0x00DCCB1C`).
- `0x00DCBDA0..0x00DCBDD4`: `[Engine]` ASCII key strings.
- `0x00DCBDD5`: `Cave_STEM_UpdateGraphTable` - performs AI vtable (`0x007F66CC` / `0x007E5464`) + `CAI` vtable (`0x007F3D54`) + active-front gating, clean initialization (`dist=0xFFFF, neck=0, is_cut=0, parent=0`), threat scanning (`+0x24000`/`+0x26000`), bounded $K$-hop frontline expansion (`+0x14000` `fdist_plus_1`, `+0x28000` `prov_flags`), Pass-1 Local Safe BFS, Exposed-Seeded Option B vertex-disjoint path-blocking BFS (`+0x20000` `optb_prev` reserved for Option C, `+0x2A000` blocked, `+0x2C000` visited, `+0x2E000` queue), and Pass-2 bridge fallback.
- `0x00DCC721`: `Cave_STEM_GetUnitEvacSlot` - hashes `(TypeId.id, TypeId.type)` into persistent `g_pGraphTable + 0x34000..0x3BFFF` (`4,096` 8-byte slots `[id:u32, type:u16, dest_prov:u16]`) to persist active evacuation destinations across ticks.
- `0x00DCC755`: `Cave_STEM_UpdateAndEvacuate_Internal` - preserves en-route evacuation marches until reaching `dest_prov` and dispatches combat/overland evacuations.
- `0x00DCCA24`: `Cave_ShowAllMovingArrows` / `0x00DCCA82`: `Cave_DeselectArrows`.
- `0x00DCCAB8`: `Cave_PostLoadInit` / `0x00DCCB1C`: `Cave_LoadEngineSettings`.
- `0x00DCCB93`: `Cave_STEM_HourlyPerCountry` / `0x00DCCBDE`: `Cave_STEM_HourlyAllCountries`.
- `0x00DCCC83`: `Cave_FrontAI_ManageReservesAndSalients`.

### 3.3 Hooks & Code Removed During Cleanup

- `0x004E7616` & `0x004E7905`: Removed inline cave hooks that overwrote unit organization / state during combat checks.
- `0x00DCBADC`: Cleared legacy org/hook storage slot.
- `0x006A5790` (and dead spearhead stubs): Removed orphaned spearhead override checks after scrapping `SpearheadWinningOdds` and `AbortSpearheadOnNeckCollapse`.
- Tarjan 1-vertex articulation loop (`.tarjan_start`..`.neck_propagate`): Replaced inside `0x00DCBDD5` with Local $K$-Hop Frontline Search + Exposed-Seeded Option B Path-Blocking BFS.

---

## 4. Issues Addressed During Realignment, Cleanup & Option B Upgrade

1. **Memory Aliasing Between `+0x24000` and `+0x26000` (Phase 1)**: Rebuilt `Cave_STEM_UpdateGraphTable` (`0x00DCBDD5`) with proper stride sizing so province threat flags (`+0x24000`) and attack flags (`+0x26000`) do not alias in scratch memory.
2. **Retail Rear-Reserve Replacement & Org Mutation Bug (Phase 2)**: Restored retail `CFrontAI::ManageRearReserves` (`0x00681CD0`) behind wrapper `0x00DCCC47` at `0x00682A58`, and removed `0x004E7616` / `0x004E7905` org-corruption hooks.
3. **Flawed Spearhead Architecture Removal (Phase 3)**: Completely removed `SpearheadWinningOdds` and `AbortSpearheadOnNeckCollapse` because exempting attacking units would strand breakout stacks when a salient evacuates and allow opponents to bait AI attacks into encirclements; repurposed `0x00DCBAB8` (`0x00DCBB30`) for `SalientSearchDepth`.
4. **False-Positive Cut Flag Propagation & Tarjan 1-Vertex Limitation (Phase 3A -> Option B)**: Initially added threatened-shoulder checks to `.tarjan_check_cut`, then superseded Tarjan entirely with Exposed-Seeded Option B vertex-disjoint safe path counting so `SalientNeckWidthThreshold > 2` (e.g. `3`) evaluates actual safe neck width without requiring 1-vertex cut points or active-combat-only triggers.
5. **Hardcoded Threat/Org Formulas & False Evacuation Under Light Attacks (Phase 4)**: Wired `NeckThreatRatio` (`0x00DCBAC0`) and `NeckCollapsingOrgThreshold` (`0x00DCBAC4`) dynamically, fixed unit strength/organization structure offsets and scalar FPU comparisons, and added an active combat guard so non-attacked provinces never trigger `+0x24000 = 1`.
6. **Depot Cores, Allied Territory Blocking, and Multi-Connection Salients (Phase 5)**:
   - Wired `UseSupplyDepotsAsCores` (`0x00DCBABC`) to seed accessible provinces (`CCountry::CanEnterOrTraceSupply` @ `0x0044A690`) having `[pProv + 0x270] > 0.0f` or a supplied controller capital.
   - Replaced strict self-control-only BFS neighbor gating with `CCountry::CanEnterOrTraceSupply` (`0x0044A690`; self/ally/puppet/master/access) and hostile-war filtering (`0x0044B280`) so pockets separated by allied territory keep valid supply/escape paths.
   - Added Pass-2 bridge fallback bounded to the $K$-hop strip / threatened bridge nodes.
7. **Unrelated Patch 1 & Patch 4 Crash / `.data` Collision Fix (Session Side-Fix)**:
   - Fixed Patch 1 (`AllowExpForcesToPlayers` @ `0x004CCCB6`): replaced a crashing cave detour with `call [edx+0x1c]; jmp 0x007E2FB3`.
   - Relocated `AllowExpForcesToPlayers` and `AllowPuppetTrade` variables out of retail `.data` (`0x0088077C` / `0x00880780`) to clean `.mod` memory (`0x00DC9FF0` / `0x00DC9FF4`) across Patches 4 and 6.
8. **Persistent Evacuation Mode & `0x00681CD0` Rear-Reserve Cancellation Fix**:
   - Added persistent per-unit evacuation tracking (`Cave_STEM_GetUnitEvacSlot` @ `0x00DCC6FF`, backed by `g_pGraphTable + 0x34000..0x3BFFF` `4,096` 8-byte slots `[id:u32, type:u16, dest_prov:u16]`) inside `Cave_STEM_UpdateAndEvacuate_Internal` (`0x00DCC733`) so units remain in Evacuation Mode across ticks until arriving at `dest_prov`.
   - Updated `Cave_FrontAI_ManageReservesAndSalients` (`0x00DCCC47`) to prune retail rear-reserve nodes in `[CFrontAI + 0xC8]` belonging to evacuating units, temporarily set `[pArmy + 0x17B] = 2` around retail `0x00681CD0` so `ManageRearReserves` does not cancel evacuating marches (`0x00682950`) or pull units back into rear-reserve provinces (such as `505 Bialystok`), restore `[pArmy + 0x17B] = 0`, and re-exempt them in `[CFrontAI + 0xC8]` (`+0x0F = 0x5A`).
9. **Save-Reload Registry Reset & `CFrontProvince*` Seeding Fix**:
   - Added `+0x30000..+0x3BFFF` (`48 KB`) clearing inside `Cave_PostLoadInit` (`0x00DCCAB8`) so savegame reloads do not carry over prior session evacuation flags or slots.
   - Dereferenced `dword ptr [CFrontProvince* + 0x04]` in `[pFront + 0x04]` when seeding exposed frontline provinces, initialized `g_pGraphTable` entries cleanly to `dist = 0xFFFF, neck = 0, is_cut = 0, parent = 0`, guarded unsigned `dist` comparisons against `0xFFFF`, and guarded Pass-2 against spilling beyond the $K$-hop horizon into deep rear.
10. **`CRebelCountry` (`0x007E5934`) / `CHumanCountry` (`0x007F04E0`) Vtable Guard (Reload Exception Fix)**:
   - Fixed an access violation at `0x00DCBE2F` (`cmp dword ptr [esi+0x118], 0`) triggered on Rebels (`TAG = REB`, `0x157`) after multiple reloads: `CRebelCountry` allocates only `0x13C84` bytes, so reading `+0x13C84` read 4 bytes past heap object bounds into non-zero recycled heap memory. Both `Cave_STEM_HourlyPerCountry` (`0x00DCCB93`) and `Cave_STEM_UpdateGraphTable` (`0x00DCBDD5`) now verify `CCountry` vtable (`0x007F66CC` / `0x007E5464`) and `CAI` vtable (`0x007F3D54`) before dereferencing `+0x13C84`.

---

## 5. Remaining Known Issues & Proposed Solution Steps

### Issue 1: Natural Peninsulas & Small 1-2 Province Frontline Bumps Under High `SalientNeckWidthThreshold`
- **Observed Symptom**:
  - When `SalientNeckWidthThreshold >= 3` and `|C| > |safe_exits(C)|` is omitted (so 1-province tips are also evaluated against `SalientNeckWidthThreshold`), any single-province frontline bump touching only 2 rear neighbors (e.g., `3274 Kowel` backed by `503` and `1885`) or a narrow geographical peninsula (e.g., unattacked Crimea or `1884`+`7978`) has `actualSafeNeckWidth = 2 < 3` and steps back 1 province into a wider line.
- **Proposed Solution Steps**:
  1. Compute geographical/unthreatened `NaturalWidth` for the sector and require `actualSafeNeckWidth < min(SalientNeckWidthThreshold, NaturalWidth)` (or apply a perimeter/threat gate when unthreatened) if static holding of narrow bumps under threshold `>= 3` is desired.

### Issue 2: Option B Diagonal-Shortcut Over-Caution (Backup: Option C)
- **Observed Behavior**:
  - Verified on a synthetic `Z-Bridge` crossover graph: greedy shortest-path blocking (Option B) can pick an asymmetric 2-hop diagonal shortcut and mark both parallel lanes blocked, finding `W - 1` paths instead of `W` (never produces false negatives; only conservative 1-hop early withdrawals). Matched Option C across all 9 live Soviet test scenarios on `PID 4740`.
- **Proposed Solution Steps**:
  1. Reserve `+0x20000..+0x23FFF` (`uint16_t flow_to / flow_from`) to upgrade the inner Option B path-search loop in-place to Option C (Node-Split Maximum Flow with Residual Undo) if diagonal crossover false positives arise in playtesting.

### Issue 3: Post-Evacuation Exterior Reinforcement Inflow
- **Observed Symptom**: Once evacuating divisions arrive at `dest_prov` (clearing their evacuation slot) or while exterior reserve divisions operate nearby, `CFrontAI::MoveUnitsToFront` can still order them back into an endangered pocket once `+0x30000` clears.
- **Proposed Solution Steps**:
  1. Prevent `CFrontAI::MoveUnitsToFront` from assigning exterior reinforcements into provinces currently marked `+0x30000 == 1` or reachable only through a collapsing/breached neck.

### Issue 4: Unwired Settings (`SalientEvacuationQuota`, `BottleneckDefenseBoost`)
- **Current State**: Both keys are loaded from `db/mod_settings.ini` into `0x00DCBACC` and `0x00DCBAD0` at startup, but neither value is consumed by `Cave_STEM_UpdateGraphTable` or `Cave_FrontAI_ManageReservesAndSalients`.
- **Proposed Solution Steps**:
  1. Implement `SalientEvacuationQuota` (fractional threshold controlling whether a delaying screen remains vs. `0.0` full evacuation).
  2. Implement `BottleneckDefenseBoost` to raise defensive reinforcement weight on un-collapsed neck/shoulder provinces before collapse, while blocking reinforcement once evacuation triggers.

### Issue 5: Retail Caller Gate `0x00682A43` & Combat Defeat Retreat Direction
- **Observed Behavior**:
  - In retail `Darkest Hour.exe`, `0x00682A43` (`test al, al; je ...` when `[esi + 0x10C].Count() <= 0 && [esi + 0x125] != 0`) calls `Clear([esi + 0xC8])` and skips calling `0x00682A58` (`Cave_FrontAI_ManageReservesAndSalients`), though hourly STEM graph updates still execute via `0x005AEDBE`.
  - Retail combat defeat retreat direction does not consult STEM escape-BFS distances toward supply depots/capital cores, so defeated units can retreat deeper into a closing pocket rather than out through the neck.
- **Proposed Solution Steps**:
  1. Audit defeat-retreat target selection to prefer lower STEM BFS-distance provinces toward cores/depots when an active pocket/threat flag exists.
  2. Evaluate whether any front with `[esi + 0x10C].Count() <= 0 && [esi + 0x125] != 0` needs `0x00682A54` routed into the STEM exemption pass of `0x00DCCC83` so `[CFrontAI + 0xC8]` still exempts evacuating units on zero-reserve fronts.

### Issue 6: Future Breakthrough / Spearhead Architecture (On Hold)
- **Current State**: `SpearheadWinningOdds` and `AbortSpearheadOnNeckCollapse` were intentionally removed in Phase 3 (with `0x00DCBAB8` repurposed to `SalientSearchDepth`).
- **Proposed Direction**: Any future offensive breakout protection should model overall corridor width, flank-holding reserve ratio, and supply-line robustness rather than blankly exempting attacking units from evacuation.
