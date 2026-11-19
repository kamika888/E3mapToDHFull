# Patch 18: Salient Topological Evacuation & Momentum Engine (STEM) - Implementation Status & Reference

**Status**: Stage 1A–1C Dynamic Quota + Step 5C Neck Holding Lock & Stage 2 Front AI Salient De-Prioritization Complete | **`Darkest Hour_modified.exe` SHA-256**: `7157C8C6B8ECEF0370ED8C6365F7E56F0A9DCD5DD0CC6BF474A7A84C21E64BC1`  
**Related Docs**: [Front AI Architecture](../engine/front_ai.md) | [STEM Strategic Defense Plan](plan_stem_strategic_defense.md) | [stem_debug.csv Columns](../stem_debug_columns.md) | [Patcher](../../tools/patch_darkest_hour.bat) | [Settings](../../db/mod_settings.ini)

---

## 1. Executive Summary

Patch 18 (STEM) adds topological encirclement detection and salient evacuation to `CFrontAI` using an hourly per-province vertex-disjoint residual max-flow pass (Option C) rooted in a dedicated `.mod` cave block (`0x00DCBAB0..0x00DCCEB3`). Following the initial realignment, persistent evacuation registry, save-reload registry reset, `REB` vtable guard, and Option B per-province rollout, Step 5 was upgraded from greedy Option B path blocking to **Option C (Split-Node Residual Vertex-Disjoint Max-Flow)** up to `SalientNeckWidthThreshold` within the local $K$-hop frontline strip (`SalientSearchDepth`), evaluating both unthreatened and `is_threatened == 1` frontline provinces accurately without greedy diagonal blocking.

Live validation (`PID 44220`, `21–22 August 1941`, and `PID 55632`, `19 November 1941`, `SalientNeckWidthThreshold = 3`, `SalientSearchDepth = 5`) confirmed that:
- `Cave_PostLoadInit` (`0x00DCCB62`) clears `g_pGraphTable + 0x30000..+0x3BFFF` (`48 KB`) on scenario/savegame load, preventing stale evacuation slots from persisting across save reloads.
- Bounded $K$-hop frontline expansion (`SalientSearchDepth = 5`, configurable via `db/mod_settings.ini`, `-1` for unlimited propagation terminating at Supply Depots / Capital) limits the local subgraph (`100..109` provinces) and cleanly isolates horizon roots without spilling beyond hop $K$.
- Active-front early exit skips non-AI countries (`CRebelCountry` `0x007E5934` / `CHumanCountry` `0x007F04E0`), peaceful countries, and fronts without hostile border pressure.
- Option C split-node max-flow eliminates greedy Option B's false positive on **Kowel (`3274`)**: Option B routed `3274 -> 503 -> 562 -> 225`, stranding `3395 Kamen Koszyrski` at `2/3` and causing a `3274 <-> 503` shuttle against retail `CFrontAI::MoveUnitsToFront`, whereas Option C finds all `3/3` disjoint paths (`503 -> 3275 -> 272 -> 221 -> 218 -> 217`, `506 -> 502 -> 267 -> 227 -> 238 -> 3419 -> 3420`, `3395 -> 562 -> 225 -> 1566 -> 241 -> 239`) and holds `3274` (`neck=0`). Meanwhile true `< 3` bottlenecks remain flagged (`3280 Telshe -> 206`, `500/501/507/1173/3396/7984 -> 229`, `7335 Augustow -> 209`, and the Bialystok pocket).
- Threatened frontline provinces (`+0x24000 == 1`) remain excluded from Pass-1 Safe BFS and intermediate transit, yet are evaluated as evacuation sources through their safe neighbors (`first_hop` stored in `parent[P]` from Pass 1's trace).
- In `Cave_STEM_UpdateAndEvacuate_Internal` (`0x00DCC873`), `.arrived_or_safe` clears `evac_slot` not only on arrival at `dest_prov`, but also when the occupied province becomes safe (`neck[esi] == 0`), stopping stale marches cleanly.
- Allied-access pathing (`CCountry::CanEnterOrTraceSupply` @ `0x0044A690`), `UseSupplyDepotsAsCores`, `NeckThreatRatio` / `NeckCollapsingOrgThreshold`, and the `0x00681CD0` cancellation shield (`g_pGraphTable + 0x34000` & `[pArmy + 0x17B] = 2`) continue to protect evacuating units until reaching `dest_prov`.

---

## 2. `db/mod_settings.ini` Wiring Audit

### 2.1 `[FrontAI]` & `[Engine]` Configuration Status

| Section | Variable | Current INI | Binary Slot VA | Status | Notes |
| :--- | :--- | :---: | :---: | :--- | :--- |
| `[FrontAI]` | `EnableEncirclementDefense` | `1` | `0x00DCBAB0` | **Wired & Active** | Master gate checked by `0x00DCCC3D` (`Cave_STEM_HourlyPerCountry`) and evacuation checks. |
| `[FrontAI]` | `SalientNeckWidthThreshold` | `3` | `0x00DCBAB4` | **Wired & Active** | Minimum required unthreatened vertex-disjoint escape paths per province (`Cave_STEM_UpdateGraphTable` @ `0x00DCBDD5`) and Pass-2 bridge fallback threshold. |
| `[FrontAI]` | `SalientSearchDepth` | `5` | `0x00DCBAB8` | **Wired & Active** | Reused scrapped slot (`0x00DCBB30`); bounds inward frontline BFS hops (`> 0`), or `-1` for depot/capital termination (`0x7FFF` cap). |
| `[FrontAI]` | `UseSupplyDepotsAsCores` | `1` | `0x00DCBABC` | **Wired & Active** | When `1`, accessible provinces (`0x0044A690`) in the strip with a local supply stockpile (`[pProv + 0x270] > 0.0f`) or supplied controller capital act as core roots (`is_core_root`). |
| `[FrontAI]` | `NeckThreatRatio` | `1.5` | `0x00DCBAC0` | **Wired & Active** | Dynamically read by `0x00DCBDD5`; hostile-to-friendly ground combat strength ratio needed to flag a province as threatened (`+0x24000`). |
| `[FrontAI]` | `NeckCollapsingOrgThreshold` | `10.0` | `0x00DCBAC4` | **Wired & Active** | Dynamically read by `0x00DCBDD5` (binary default `30.0`); average friendly defender organization threshold triggering threat flag alongside `NeckThreatRatio`. |
| `[FrontAI]` | `SalientEvacuationQuota` | `0.0` | `0x00DCBACC` | **Pending (Unreferenced)** | Loaded from `db/mod_settings.ini` into `0x00DCBACC`, but not yet referenced by STEM evacuation code. |
| `[FrontAI]` | `BottleneckDefenseBoost` | `3.5` | `0x00DCBAD0` | **Pending (Unreferenced)** | Loaded from `db/mod_settings.ini` into `0x00DCBAD0`, but not yet wired into `CFrontAI` province priority weighting. |
| `[FrontAI]` | `SpearheadWinningOdds` | *removed* | `0x00DCBAC8` | **Scrapped** | INI key removed. Header slot `0x00DCBAC8` retained only for struct alignment; unreferenced by runtime code. |
| `[Engine]` | `AlwaysShowMovementArrows` | `1` | `0x00DCBAD8` | **Wired & Active** | Loaded by `Cave_LoadEngineSettings` (`0x00DCCBC6`); controls forced arrow rendering (`0x00DCCACE` / `0x00DCCB2C`). |
| `[Engine]` | `AutoNoFog` | `1` | `0x00DCBAE8` | **Wired & Active** | Loaded by `Cave_LoadEngineSettings` (`0x00DCCBC6`); applied on scenario/save load (`0x00DCCB62`) and hourly tick (`0x00DCCC88`). |
| `[Engine]` | `AutoShowId` | `1` | `0x00DCBAEC` | **Wired & Active** | Loaded by `Cave_LoadEngineSettings` (`0x00DCCBC6`); applied on scenario/save load (`0x00DCCB62`) and hourly tick (`0x00DCCC88`). |

---

## 3. Realized Hook & Cave Architecture

### 3.1 Active Hooks into Retail `Darkest Hour.exe`

| Retail Address | Target / Cave Function | Role |
| :--- | :--- | :--- |
| `0x005AEDBE` | `Cave_STEM_HourlyAllCountries` (`0x00DCE0FD`) | Hourly AI tick: initializes `g_pGraphTable` (`0xC0000` bytes), clears transient buffers while preserving `norm_prio_f32` (`+0x58000`), and dispatches `Cave_STEM_HourlyPerCountry` (`0x00DCE0B2`). |
| `0x00682A58` | `Cave_FrontAI_ManageReservesAndSalients` (`0x00DCE1CC`) | Wrapper around retail `CFrontAI::ManageRearReserves` (`0x00681CD0`); shields evacuating units from `0x00681CD0` and registers them in `[CFrontAI + 0xC8]`. |
| `0x00683EB6` | `Cave_FrontAI_LoopAAdjCheck` (`0x00DCE353`) | **Stage 2 Hook 7A**: Wraps `0x004E9500`; excludes adjacent border candidates with `Q == 1.0` or `0 < Q < 1.0 && divs >= AdjustedPriority` from Loop A. |
| `0x00684088` | `Cave_FrontAI_LoopACheckCand` (`0x00DCE3D2`) | **Stage 2 Hook 7B**: Gates and scales Loop A candidate scoring `(en_str - fr_str)` toward `(1 - Q)` in both `[ebp - 0x58]` and full-front scans. |
| `0x006840F6` | `Cave_FrontAI_LoopAStoreBest` (`0x00DCE47B`) | **Stage 2 Hook 7C**: Stores the Stage 2 scaled winning Loop A candidate score (`g_fLoopACandScore` -> `[ebp - 0x48]`). |
| `0x00684131` | `Cave_FrontAI_LoopAFallbackCheck` (`0x00DCE486`) | **Stage 2 Hook 7D**: Wraps `0x004E9500` on Loop A's `edi == 0` fallback (`0x00684117`) to block marching into an evacuating head province (`quota_q8 > 0`). |
| `0x00684551` | `Cave_FrontAI_ScaleReceiverShare` (`0x00DCE4D7`) | **Stage 2 Hook 8A**: Caches `norm_prio_f32` (`+0x58000`), scales receiver share `S(u)` by `(1 - Q(u))` (suppressing `even`-mode `deficit = 1` when `Q > 0 && S_adj * D_front < 1.0`), and syncs telemetry via `Cave_STEM_SyncTelemetryPrio` (`0x00DCDBAD`). |
| `0x0068470D` | `Cave_FrontAI_ScaleDonorShare2` (`0x00DCE576`) | **Stage 2 Hook 8B**: Scales Loop B donor share `[ebp - 0x44]` by `(1 - Q(u))`. |
| `0x0068526A` | `Cave_FrontAI_ScaleDonorShare3` (`0x00DCE5D2`) | **Stage 2 Hook 8C**: Scales helper `0x006851D0` donor share `[esp + 0x20]` by `(1 - Q(u))`. |
| `0x004301D7` | `Cave_STEM_SaveGameHook` (`0x00DCE634`) | Post-save `Cave_STEM_UpdateGraphTable` refresh & semicolon-delimited `stem_debug.csv` dump (with Stage 2 `NormPrio` & `AdjPrio`). |
| `0x005226C1` | `Cave_DeselectArrows` (`0x00DCDFA1`) | Supports `AlwaysShowMovementArrows` when deselected on map. |
| `0x00DCAE55` | `Cave_PostLoadInit` (`0x00DCDFD7`) | Clears `g_pGraphTable + 0x30000..+0xBFFFF` (`576 KB`) on scenario/save load and applies `AutoNoFog`, `AutoShowId`, and `AlwaysShowMovementArrows`. |

### 3.2 Cave Layout (`.mod` Patch 18 Chunk @ `0x00DCBAB0..0x00DCE8D1`)

- `0x00DCBAB0..0x00DCBAF0`: Parameter header (`EnableEncirclementDefense`, `SalientNeckWidthThreshold`, `SalientSearchDepth`, `UseSupplyDepotsAsCores`, `NeckThreatRatio`, `NeckCollapsingOrgThreshold`, `SalientEvacuationQuota`, `BottleneckDefenseBoost`, `g_pGraphTable` at `0x00DCBAD4`, `AlwaysShowMovementArrows`, `AutoNoFog`, `AutoShowId`).
- `0x00DCBDA0..0x00DCBF49`: `[Engine]` INI keys, float constants, `stem_debug.csv` format strings (`32` printf arguments), and `g_fLoopACandScore` (`0x00DCBF46`).
- `0x00DCBF4A`: `Cave_STEM_UpdateGraphTable` - AI vtable + active-front gating, clean initialization (`dist=0xFFFF, neck=0, is_cut=0, parent=0`), threat + `prov_flags |= 0x20` scanning, bounded $K$-hop frontline expansion, Pass-1 Safe BFS, Option C residual max-flow (`Step 5A`), corridor contraction & continuous quota (`Step 5B`), reverse-topological Active Neck Holding Lock (`Step 5C`), Pass-2 bridge fallback, and `Cave_STEM_SyncTelemetryPrio` (`0x00DCDBAD`).
- `0x00DCDCB4`: `Cave_STEM_GetUnitEvacSlot` / `0x00DCDCE8`: `Cave_STEM_UpdateAndEvacuate_Internal`.
- `0x00DCDF43`: `Cave_ShowAllMovingArrows` / `0x00DCDFA1`: `Cave_DeselectArrows` / `0x00DCDFD7`: `Cave_PostLoadInit` / `0x00DCE03B`: `Cave_LoadEngineSettings`.
- `0x00DCE0B2`: `Cave_STEM_HourlyPerCountry` / `0x00DCE0FD`: `Cave_STEM_HourlyAllCountries` / `0x00DCE1CC`: `Cave_FrontAI_ManageReservesAndSalients`.
- `0x00DCE353..0x00DCE633`: Stage 2 Loop A (`0x00DCE353`, `0x00DCE3D2`, `0x00DCE47B`, `0x00DCE486`) and Loop B (`0x00DCE4D7`, `0x00DCE576`, `0x00DCE5D2`) handlers.
- `0x00DCE634..0x00DCE8D1`: `Cave_STEM_SaveGameHook` (`stem_debug.csv` writer).

### 3.3 Hooks & Code Removed During Cleanup

- `0x004E7616` & `0x004E7905`: Removed inline cave hooks that overwrote unit organization / state during combat checks.
- `0x00DCBADC`: Cleared legacy org/hook storage slot.
- `0x006A5790` (and dead spearhead stubs): Removed orphaned spearhead override checks after scrapping `SpearheadWinningOdds` and `AbortSpearheadOnNeckCollapse`.
- Tarjan 1-vertex articulation loop (`.tarjan_start`..`.neck_propagate`): Replaced inside `0x00DCBDD5` with Local $K$-Hop Frontline Search + Exposed-Seeded Option B Path-Blocking BFS.

---

## 4. Issues Addressed During Realignment, Cleanup & Option B Upgrade

1. **Memory Aliasing Between `+0x24000` and `+0x26000` (Phase 1)**: Rebuilt `Cave_STEM_UpdateGraphTable` (`0x00DCBDD5`) with proper stride sizing so province threat flags (`+0x24000`) and attack flags (`+0x26000`) do not alias in scratch memory.
2. **Retail Rear-Reserve Replacement & Org Mutation Bug (Phase 2)**: Restored retail `CFrontAI::ManageRearReserves` (`0x00681CD0`) behind wrapper `Cave_FrontAI_ManageReservesAndSalients` (`0x00DCCD2D`) at `0x00682A58`, and removed `0x004E7616` / `0x004E7905` org-corruption hooks.
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
   - Added persistent per-unit evacuation tracking (`Cave_STEM_GetUnitEvacSlot` @ `0x00DCC83F`, backed by `g_pGraphTable + 0x34000..0x3BFFF` `4,096` 8-byte slots `[id:u32, type:u16, dest_prov:u16]`) inside `Cave_STEM_UpdateAndEvacuate_Internal` (`0x00DCC873`) so units remain in Evacuation Mode across ticks until arriving at `dest_prov`.
   - Updated `Cave_FrontAI_ManageReservesAndSalients` (`0x00DCCD2D`) to prune retail rear-reserve nodes in `[CFrontAI + 0xC8]` belonging to evacuating units, temporarily set `[pArmy + 0x17B] = 2` around retail `0x00681CD0` so `ManageRearReserves` does not cancel evacuating marches (`0x00682950`) or pull units back into rear-reserve provinces (such as `505 Bialystok`), restore `[pArmy + 0x17B] = 0`, and re-exempt them in `[CFrontAI + 0xC8]` (`+0x0F = 0x5A`).
9. **Save-Reload Registry Reset & `CFrontProvince*` Seeding Fix**:
   - Added `+0x30000..+0x3BFFF` (`48 KB`) clearing inside `Cave_PostLoadInit` (`0x00DCCB62`) so savegame reloads do not carry over prior session evacuation flags or slots.
   - Dereferenced `dword ptr [CFrontProvince* + 0x04]` in `[pFront + 0x04]` when seeding exposed frontline provinces, initialized `g_pGraphTable` entries cleanly to `dist = 0xFFFF, neck = 0, is_cut = 0, parent = 0`, guarded unsigned `dist` comparisons against `0xFFFF`, and guarded Pass-2 against spilling beyond the $K$-hop horizon into deep rear.
10. **`CRebelCountry` (`0x007E5934`) / `CHumanCountry` (`0x007F04E0`) Vtable Guard (Reload Exception Fix)**:
   - Fixed an access violation at `0x00DCBE2F` (`cmp dword ptr [esi+0x118], 0`) triggered on Rebels (`TAG = REB`, `0x157`) after multiple reloads: `CRebelCountry` allocates only `0x13C84` bytes, so reading `+0x13C84` read 4 bytes past heap object bounds into non-zero recycled heap memory. Both `Cave_STEM_HourlyPerCountry` (`0x00DCCC3D`) and `Cave_STEM_UpdateGraphTable` (`0x00DCBDD5`) now verify `CCountry` vtable (`0x007F66CC` / `0x007E5464`) and `CAI` vtable (`0x007F3D54`) before dereferencing `+0x13C84`.
11. **Per-Province Independent Path Evaluation & Threatened Source Support**:
   - Replaced level-component aggregation (`dist >= cur_d`, which masked bottlenecks on `3280 Telshe` and `7335 Augustow`) with direct per-province vertex-disjoint path counting across all exposed frontline provinces (including `is_threatened == 1`), deriving `first_hop` (`parent[P]`) from Pass 1's trace and chaining multi-hop necks after interior cascade evaluation.
12. **Option C Split-Node Residual Max-Flow & Safe-Province Slot Cleanup**:
   - Upgraded Step 5 from greedy Option B path blocking to Option C split-node residual max-flow (`+0x18000` `flow_prev`, `+0x20000` `bpar_in`, `+0x26000` `optc_q`, `+0x2A000` `used`, `+0x2C000..0x2FFFF` `16 KB` split-state `vis`, `+0x3C000..0x3FFFF` `flow_next`, with `prov_flags` bit `0x10` for `in_eval_q`), eliminating false-positive greedy blocking on `3274 Kowel` (`3/3` paths found instead of `2/3`).
   - Updated `.arrived_or_safe` inside `Cave_STEM_UpdateAndEvacuate_Internal` (`0x00DCC873`) to clear `evac_slot` whenever the unit's current province has `neck[esi] == 0`.

---

## 5. Remaining Known Issues & Proposed Solution Steps

### Issue 1: Natural Peninsulas & Small 1-2 Province Frontline Bumps Under High `SalientNeckWidthThreshold`
- **Observed Symptom**:
  - When `SalientNeckWidthThreshold >= 3`, any single-province frontline bump touching only 2 rear neighbors (e.g., `3280 Telshe` backed by `206` and `3281`, or narrow coastal peninsulas like Crimea / `1884`+`7978`) has `actualSafeNeckWidth = 2 < 3` and steps back 1 province into a wider line even when unattacked.
- **Proposed Solution Steps**:
  1. Compute geographical/unthreatened `NaturalWidth` for the sector and require `actualSafeNeckWidth < min(SalientNeckWidthThreshold, NaturalWidth)` (or apply a perimeter/threat gate when unthreatened) if static holding of narrow bumps under threshold `>= 3` is desired.

### Issue 2: ~~Option B Diagonal-Shortcut Over-Caution~~ (Resolved by Option C)
- **Resolution**:
  - Live debugging on `PID 55632` (`19 November 1941`) showed Option B's greedy first BFS (`3274 -> 503 -> 562 -> 225 ...`) stranding `3395` and falsely reporting `2/3` paths for `3274 Kowel` (causing a `3274 <-> 503` shuttle with `MoveUnitsToFront`). Replacing Option B with split-node residual max-flow (Option C) resolved `3274 Kowel` to `3/3` paths (`neck=0`).

### Issue 3: Post-Evacuation Exterior Reinforcement Inflow
- **Observed Symptom**: Once evacuating divisions arrive at `dest_prov` (clearing their evacuation slot) or while exterior reserve divisions operate nearby, `CFrontAI::MoveUnitsToFront` can still order them back into an endangered pocket (`neck != 0`) once `+0x30000` clears.
- **Proposed Solution Steps**:
  1. Prevent `CFrontAI::MoveUnitsToFront` from assigning exterior reinforcements into provinces currently marked unsafe (`neck != 0` / `+0x30000 == 1`) or reachable only through a collapsing/breached neck.

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
  2. Evaluate whether any front with `[esi + 0x10C].Count() <= 0 && [esi + 0x125] != 0` needs `0x00682A54` routed into the STEM exemption pass of `0x00DCCD2D` so `[CFrontAI + 0xC8]` still exempts evacuating units on zero-reserve fronts.

### Issue 6: Future Breakthrough / Spearhead Architecture (On Hold)
- **Current State**: `SpearheadWinningOdds` and `AbortSpearheadOnNeckCollapse` were intentionally removed in Phase 3 (with `0x00DCBAB8` repurposed to `SalientSearchDepth`).
- **Proposed Direction**: Any future offensive breakout protection should model overall corridor width, flank-holding reserve ratio, and supply-line robustness rather than blankly exempting attacking units from evacuation.
