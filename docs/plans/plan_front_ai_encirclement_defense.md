# Patch 18: Salient Topological Evacuation & Momentum Engine (STEM) - Implementation Status & Reference

**Status**: Stages 1-5 Complete & Validated | **`Darkest Hour_modified.exe` SHA-256**: `76E7AA63FA4758313297239E866CCFAA00AF2B0CA19A5CB6F7ABFC7E371D1E27`  
**Related Docs**: [Front AI Architecture](../engine/front_ai.md) | [STEM Strategic Defense Plan](plan_stem_strategic_defense.md) | [STEM Testing Guide](../stem_testing_guide.md) | [stem_debug.csv Columns](../stem_debug_columns.md) | [Patcher](../../tools/patch_darkest_hour.bat) | [Settings](../../db/mod_settings.ini)

---

## 1. Executive Summary

Patch 18 (STEM) adds topological encirclement detection, dynamic strategic evacuation, Front AI salient de-prioritization, bottleneck defense reinforcement, partial withdrawal selection, and load-balanced outward combat retreat direction to `CFrontAI` and `CLandArmy`. Its `.mod` code cave (`32 KB` section `0x00DC9000..0x00DD1000`, Patch 18 block `0x00DCBAB0..0x00DD0C6A`: `752`-byte header + `20,170`-byte code across `6,548` instructions, `918` bytes free) backs an expanded **`0xEC000`-byte (`944 KB`) `g_pGraphTable`** buffer (`+0x80000..+0xBFFFF` holds temporary save-triggered telemetry for `stem_debug.csv`).

All five implementation stages are complete and validated:
- **Stage 1 (Topological Min-Cut, Dynamic Quota & Holding Lock)**: Bounded `K`-hop frontline strip expansion (`SalientSearchDepth`), Supply Depot / Capital core seeding (`UseSupplyDepotsAsCores`), allied/military-access traversal (`0x0044A690`), Option C split-node residual max-flow (`+0x2C000`), Step 5A/5B downstream corridor cut contraction & **Natural Geography Gate** (`F_Exp == 0 && !IsThreatened => Q = 0.0`), continuous `SalientEvacuationQuota = D_Width * T_Neck * V_Ret`, Step 5C reverse-topological neck holding lock (`Dist[N] < Dist[P]`) + Pass 2 `.raw_lock_loop`, persistent evacuation registry (`+0x34000..+0x3BFFF`) shielded around `0x00681CD0` via `Hook 4`, and save-triggered `stem_debug.csv` telemetry (`Hook 6`).
- **Stage 2 (Front AI Salient De-Prioritization)**: Loop A (`Hooks 7A-7D`) and Loop B (`Hooks 8A-8C`) reduce evacuating province allocations by `(1 - Quota)`, cache unadjusted `NormAIPrio` (`+0x58000`), and suppress empty-province `deficit = 1` floors in `even` mode.
- **Stage 3 (Bottleneck Reinforcement & Interior Neck Hold)**: Aggregates upstream quotas into `neck_agg_q8` (`+0x42000`, `MAX`/`AVERAGE`/`MIN`), injects interior bottlenecks into `[CFrontAI + 0x04]` (`Hook 4` + `Hook 9B`), holds interior neck garrisons in Loop A (`Hook 9A`), attracts Loop A/B reserves using `BottleneckDefenseBoost * AggNeckQuota`, and cleans up injected descriptors cleanly before `CAI::UpdateFronts` (`Hook 10`).
- **Stage 4 (Partial Budgets, 4-Tier Selector, Parity & Bottleneck Stability)**: Computes whole-division targets (`TargetStayDivs`, `StayingDivs`, `EvacDivBudget` at `+0xC0000`), selects excess corps without overshoot (`num_divs <= EvacDivBudget`) in 4-tier order (not in combat -> slowest -> highest org -> highest strength), splits oversized non-combat corps when needed (`.uae_split_try`), disables province terrain modifiers inside `CFrontAI::MoveUnitsToFront` (`Hooks 11A-11F`), refines Pass 0 combat progress (`0x004BEBE0`) & province-wide weighted avg org, and adds **Threat-Sustaining Neck Floor** (`.s5e_fin_threat_floor`) + **Step 5E Threatened-Shoulder Boost** (`.s5ea_chk_thrt_nbs`).
- **Stage 5 (Outward Load-Balanced Combat Retreat Direction)**: Stamps multi-country `retreat_snap` (`+0xD8000`) and hourly `retreat_div_load` (`+0xE8000` via `.ugt_stamp_div_load` @ `0x00DCE0C4`), and hooks `CLandArmy::SelectRetreatProvince` (`0x00508E10`) with **Hooks 12A/12B/12C** to steer combat defeats away from closing pockets, bypass `m_LastProvince` filters for verified STEM exits, and spread retreating corps across low-load safe rear exits.

---

## 2. `db/mod_settings.ini` Wiring Audit

### 2.1 Primary `[FrontAI]` & `[Engine]` Slots (`0x00DCBAB0..0x00DCBAEC`)

| Section | Variable | Default | Current Mod INI | Binary Slot VA | Status | Notes |
| :--- | :--- | :---: | :---: | :---: | :--- | :--- |
| `[FrontAI]` | `EnableEncirclementDefense` | `1` | `1` | `0x00DCBAB0` | **Wired & Active** | Master gate checked by `0x00DCFABC`, `0x00DCFB07`, and all STEM hooks. |
| `[FrontAI]` | `SalientNeckWidthThreshold` | `2` | `3` | `0x00DCBAB4` | **Wired & Active** | Minimum required unthreatened vertex-disjoint escape paths per province (`Cave_STEM_UpdateGraphTable` @ `0x00DCC24C`). |
| `[FrontAI]` | `SalientSearchDepth` | `5` | `5` | `0x00DCBAB8` | **Wired & Active** | Bounds inward frontline BFS hops (`> 0`), or `-1` for depot/capital termination (`0x7FFF` cap). |
| `[FrontAI]` | `UseSupplyDepotsAsCores` | `1` | `1` | `0x00DCBABC` | **Wired & Active** | When `1`, accessible provinces (`0x0044A690`) in the strip with a supply stockpile (`[pProv + 0x270] > 0.0f`) or supplied controller capital act as core roots. |
| `[FrontAI]` | `NeckThreatRatio` | `1.5` | `1.5` | `0x00DCBAC0` | **Wired & Active** | Hostile-to-friendly ground strength ratio where neck threat reaches critical `1.0`. |
| `[FrontAI]` | `NeckCollapsingOrgThreshold` | `30.0` | `10.0` | `0x00DCBAC4` | **Wired & Active** | Province-wide weighted average defender organization threshold triggering combat collapse / org threat (`T_org`). |
| `[FrontAI]` | `SpearheadWinningOdds` | *removed* | *removed* | `0x00DCBAC8` | **Scrapped** | INI key removed; slot retained only for header alignment. |
| `[FrontAI]` | `SalientEvacuationQuota` | `0.0` | `0.0` | `0x00DCBACC` | **Superseded** | Loaded into `0x00DCBACC`; superseded at runtime by continuous `quota_q8[P]` (`+0x40000`). |
| `[FrontAI]` | `BottleneckDefenseBoost` | `3.5` | `10` | `0x00DCBAD0` | **Wired & Active** | Extra divisions added to frontline bottlenecks (`Loop B` / `Loop A` attraction) and held at interior bottlenecks (`Hook 9A`) scaled by `neck_agg_q8[B] / 255`. |
| `[FrontAI]` | `BottleneckQuotaAggregation` | `0` | `0` | `0x00DCBADC` | **Wired & Active** | Loaded by `Cave_LoadEngineSettings` (`0x00DCFA0E`); selects `0 = MAX`, `1 = AVERAGE`, or `2 = MIN` aggregation in Step 5E. |
| `[Engine]` | `AlwaysShowMovementArrows` | `0` | `1` | `0x00DCBAD8` | **Wired & Active** | Loaded by `Cave_LoadEngineSettings` (`0x00DCFA0E`); controls map arrow retention (`Cave_ShowAllMovingArrows` / `Cave_DeselectArrows`). |
| `[Engine]` | `AutoNoFog` | `0` | `1` | `0x00DCBAE8` | **Wired & Active** | Applied on scenario/save load (`0x00DCF974`) and hourly tick (`0x00DCFB07`). |
| `[Engine]` | `AutoShowId` | `0` | `1` | `0x00DCBAEC` | **Wired & Active** | Applied on scenario/save load (`0x00DCF974`) and hourly tick (`0x00DCFB07`). |

### 2.2 `[FrontAI]` Quota Factor Table (`tbl_FrontAIFloatConfigs` @ `0x00DCC1A9`, Loaded by `Cave_LoadEngineSettings` @ `0x00DCFA0E`)

| Key | Default | Current Mod INI | Binary Slot VA |
| :--- | :---: | :---: | :---: |
| `IdleEnemyPresenceWeight` | `0.25` | `0.85` | `0x00DCBFE8` |
| `ActiveEnemyAttackWeight` | `1.0` | `1.0` | `0x00DCC004` |
| `ThreatenedNeighborStrWeight` | `1.0` | `1.0` | `0x00DCC020` |
| `InboundFriendlyStrWeight` | `0.5` | `0.5` | `0x00DCC040` |
| `NeckThreatMinRatio` | `1.0` | `0.8` | `0x00DCC05D` |
| `NeckThreatMinFloor` | `0.0` (compiled `0.2`) | `0.2` | `0x00DCC074` |
| `NeckThreatMaxCap` | `1.5` | `1.5` | `0x00DCC08B` |
| `MultiExposedCutBonus` | `0.25` | `0.25` | `0x00DCC0A0` |
| `NeckThreatWeight` | `1.0` | `1.3` | `0x00DCC0B9` |
| `ExposedIntactPathCredit` | `0.5` | `0.5` | `0x00DCC0CE` |
| `WidthDeficitWeight` | `1.0` | `1.2` | `0x00DCC0EA` |
| `ValueRetentionVPWeight` | `1.0` | `1.0` | `0x00DCC101` |
| `ValueRetentionICWeight` | `0.5` | `0.5` | `0x00DCC11C` |
| `ValueRetentionScale` | `0.02` | `0.02` | `0x00DCC137` |
| `ValueRetentionMinFloor` | `0.5` | `0.5` | `0x00DCC14F` |
| `ThreatenedSourceQuotaFloor` | `0.85` | `0.85` | `0x00DCC16A` |
| `MinEvacuationQuotaThreshold` | `0.05` | `0.05` | `0x00DCC189` |

---

## 3. Realized Hook & Cave Architecture

### 3.1 Active Hooks into Retail `Darkest Hour.exe` (`24` Patch Sites + INI Loader Chain)

| Retail Address | Target / Cave Function | Role |
| :--- | :--- | :--- |
| `0x00DCB7E6` -> `0x00DCBC30..0x00DCBCD7` | `Cave_LoadEngineSettings` (`0x00DCFA0E`) | INI loader tail: reads `[Engine]` flags, `BottleneckQuotaAggregation`, and the 17 `[FrontAI]` quota floats (`0x00DCC1A9`). |
| `0x00DCAE55` | `Cave_PostLoadInit` (`0x00DCF974`) | Allocates `g_pGraphTable` (`0xEC000`), zeroes `+0x30000..+0xEBFFF` (`0x2F000` dwords) on scenario/save load, applies `[Engine]` toggles, and refreshes read-only STEM state (`0x00DD0C11`). |
| `0x005226C1` | `Cave_DeselectArrows` (`0x00DCF93E`) | Supports `AlwaysShowMovementArrows` (`0x00DCBAD8`) when units are deselected on map. |
| `0x005AEDBE` | `Cave_STEM_HourlyAllCountries` (`0x00DCFB07`) | Hourly AI tick: allocates `0xEC000` bytes if needed, clears hourly buffers while preserving `norm_prio_f32` (`+0x58000`) and persistent front-basin flags (`+0xD6200..+0xD63FF`), and dispatches `Cave_STEM_HourlyPerCountry` (`0x00DCFABC`). |
| `0x00682A58` | `Cave_FrontAI_ManageReservesAndSalients` (`0x00DCFC04`) | **Hook 4**: Wraps `CFrontAI::ManageRearReserves` (`0x00681CD0`), shields evacuating units in `[CFrontAI + 0xC8]`, and injects/prunes adjacent interior bottlenecks (`+0x42 = 0x5B`). |
| `0x006836D5` | `Cave_FrontAI_Pass1SetNoLandEnemyFlag` (`0x00DCFFEE`) | **Stage 3 Hook 9B**: Preserves `+0x8D = 0` on injected interior bottleneck `CFrontProvince` descriptors so Loop B feeds them defenders. |
| `0x00693EE0` | `Cave_FrontAI_PreUpdateFrontsCleanInjected` (`0x00DD0032`) | **Stage 3 Hook 10**: Cleans up `+0x42 = 0x5B` injected descriptors and resets `[CProvince + 0x4A8] = 0` before `CAI::UpdateFronts` evaluates front merges. |
| `0x00683C9D` | `Cave_FrontAI_LoopAIsFrontOrHeldNeck` (`0x00DD00D5`) | **Stage 3 Hook 9A**: Wraps `0x006813E0`; holds stationary interior bottleneck garrisons up to `BottleneckDefenseBoost * Q_agg` while letting surplus armies push forward. |
| `0x00683EB6` | `Cave_FrontAI_LoopAAdjCheck` (`0x00DD01AE`) | **Stage 2/4 Hook 7A**: Wraps `0x004E9500`; excludes adjacent border candidates when `Q == 1.0`, `AdjAIPrio < 1.0`, or `divs >= round(AdjAIPrio)`. |
| `0x00684088` | `Cave_FrontAI_LoopACheckCand` (`0x00DD0248`) | **Stage 2/3/4 Hook 7B**: Synchronizes candidate gating with Stage 4 `TargetStayDivs`, scales `(en_str - fr_str)` by `(1 - Q)`, and adds `BottleneckDefenseBoost * Q_agg` to under-strength bottlenecks. |
| `0x006840F6` | `Cave_FrontAI_LoopAStoreBest` (`0x00DD0364`) | **Stage 2 Hook 7C**: Stores the Stage 2 scaled winning Loop A candidate score (`g_fLoopACandScore` @ `0x00DCBFE4` -> `[ebp - 0x48]`). |
| `0x00684131` | `Cave_FrontAI_LoopAFallbackCheck` (`0x00DD036F`) | **Stage 2 Hook 7D**: Wraps `0x004E9500` on Loop A's `edi == 0` fallback (`0x00684117`) to block marching into an evacuating head province (`quota_q8 > 0`). |
| `0x00684551` | `Cave_FrontAI_ScaleReceiverShare` (`0x00DD03C0`) | **Stage 2/3 Hook 8A**: Caches `norm_prio_f32` (`+0x58000`), scales receiver share `S(u)` by `(1 - Q(u))`, adds Stage 3 bottleneck boost `(BottleneckDefenseBoost * Q_agg) / D_front`, and syncs telemetry via `Cave_STEM_SyncTelemetryPrio` (`0x00DCE9E6`). |
| `0x0068470D` | `Cave_FrontAI_ScaleDonorShare2` (`0x00DD04C8`) | **Stage 2/3 Hook 8B**: Scales Loop B donor share `[ebp - 0x44]` by `(1 - Q(u))` and adds Stage 3 bottleneck boost `(BottleneckDefenseBoost * Q_agg) / D_front`. |
| `0x0068526A` | `Cave_FrontAI_ScaleDonorShare3` (`0x00DD056D`) | **Stage 2/3 Hook 8C**: Scales helper `0x006851D0` donor share `[esp + 0x20]` by `(1 - Q(u))` and adds Stage 3 bottleneck boost `(BottleneckDefenseBoost * Q_agg) / D_front`. |
| `0x00682DA5`, `0x00682FE4`, `0x00683127`, `0x006833C0`, `0x00684E1F` | `Cave_FrontAI_GetRawCombatStr` (`0x00DD0623`) | **Stage 4 Hooks 11A-11E**: Passes null province pointer to strength helper `0x0051B410` inside `CFrontAI::MoveUnitsToFront` so terrain modifiers do not skew Front AI strength parity. |
| `0x00684ED8` | `Cave_FrontAI_GetRawCombatStr_Eax` (`0x00DD0621`) | **Stage 4 Hook 11F**: Sets `ecx = eax` then falls through to `Cave_FrontAI_GetRawCombatStr` (`0x00DD0623`) for receiver raw strength parity. |
| `0x0050908C` | `Cave_STEM_ScoreRetreatProvince` (`0x00DD0639`) | **Stage 5 Hook 12A**: Inside `CLandArmy::SelectRetreatProvince` (`0x00508E10`), overrides retreat scoring across Bands A1 (load-balanced outward exit), A2 (`parent`/`neck`), C (anti-pocket penalty `0.0005x`, floor `0.25f`), and B (neutral load-balanced fallback). |
| `0x00508FBB` | `Cave_STEM_RetreatAllowSafeExit` (`0x00DD07F9`) | **Stage 5 Hook 12B**: Runs `[edi + 0x22E]->vtbl[+8]()` and bypasses retail `m_LastProvince` hard-filtering (`0x00508FCC`) when evaluating a verified Band A1/A2 safe exit. |
| `0x005090E2` | `Cave_STEM_RecordRetreatLoad` (`0x00DD08CF`) | **Stage 5 Hook 12C**: Saturating-adds `[edi + 0x2E]` divisions into `retreat_div_load[chosen]` (`+0xE8000`) immediately upon selecting a retreat destination. |
| `0x004301D7` | `Cave_STEM_SaveGameHook` (`0x00DD0932`) | **Hook 6**: Refreshes read-only STEM state via `Cave_STEM_RefreshAllCountriesReadOnly` (`0x00DD0C11`) while preserving `+0xC0000..+0xC7FFF` Stage 4 hourly telemetry and `+0xD6200..+0xD63FF` front-basin flags, then dumps semicolon-delimited `stem_debug.csv`. |

### 3.2 Cave Layout (`.mod` Patch 18 Chunk @ `0x00DCBAB0..0x00DD0C6A`)

- `0x00DCBAB0..0x00DCBAF0`: Core parameter header (`EnableEncirclementDefense`, `SalientNeckWidthThreshold`, `SalientSearchDepth`, `UseSupplyDepotsAsCores`, `NeckThreatRatio`, `NeckCollapsingOrgThreshold`, `SalientEvacuationQuota`, `BottleneckDefenseBoost`, `g_pGraphTable` @ `0x00DCBAD4`, `AlwaysShowMovementArrows`, `BottleneckQuotaAggregation`, `AutoNoFog`, `AutoShowId`).
- `0x00DCBDA0..0x00DCC24C`: `[Engine]` INI keys, float constants, `stem_debug.csv` format strings (`szDebugCsvHeader` / `szDebugCsvRowFmt`), `g_fLoopACandScore` (`0x00DCBFE4`), 17 `[FrontAI]` quota float keys/slots (`0x00DCBFE8..0x00DCC1A8`), and `tbl_FrontAIFloatConfigs` (`0x00DCC1A9`).
- `0x00DCC24C`: `Cave_STEM_UpdateGraphTable` -- AI vtable + active-front gating, clean initialization, UI-matching `0x004BEBE0` combat progress & province-wide weighted avg org, bounded `K`-hop frontline + front-basin (`+0xD4000` / `+0xD6200`) scan, Pass-1 Safe BFS, Option C residual max-flow (`Step 5A`), corridor contraction & continuous quota (`Step 5B`), reverse-topological Active Neck Holding Lock (`Step 5C`), Pass-2 bridge fallback & `.raw_lock_loop`, Step 5E bottleneck quota aggregation + `.s5ea_chk_thrt_nbs` + `.s5e_fin_threat_floor`, `Cave_STEM_SyncTelemetryPrio` (`0x00DCE9E6`), and Stage 5 snapshot/load stamping (`.ugt_stamp_div_load` @ `0x00DCE0C4`).
- `0x00DCEB35`: `Cave_STEM_GetUnitEvacSlot` / `0x00DCEB69`: `Cave_STEM_UpdateAndEvacuate_Internal` (Stage 4 budget, 4-tier selector, and `.uae_split_try` oversized-corps splitting).
- `0x00DCF8E0`: `Cave_ShowAllMovingArrows` / `0x00DCF93E`: `Cave_DeselectArrows` / `0x00DCF974`: `Cave_PostLoadInit` / `0x00DCFA0E`: `Cave_LoadEngineSettings`.
- `0x00DCFABC`: `Cave_STEM_HourlyPerCountry` / `0x00DCFB07`: `Cave_STEM_HourlyAllCountries` / `0x00DCFC04`: `Cave_FrontAI_ManageReservesAndSalients`.
- `0x00DCFFEE..0x00DD0639`: Stage 2/3/4 `MoveUnitsToFront` & `UpdateFronts` hooks (`Hook 9B` `0x00DCFFEE`, `Hook 10` `0x00DD0032`, `Hook 9A` `0x00DD00D5`, `Hook 7A-7D` `0x00DD01AE..0x00DD036F`, `Hook 8A-8C` `0x00DD03C0..0x00DD056D`, `Hook 11F/11A-11E` `0x00DD0621..0x00DD0623`).
- `0x00DD0639..0x00DD0932`: Stage 5 combat retreat hooks (`Hook 12A` `0x00DD0639`, `Hook 12B` `0x00DD07F9`, `Hook 12C` `0x00DD08CF`).
- `0x00DD0932..0x00DD0C6A`: `Cave_STEM_SaveGameHook` & `Cave_STEM_RefreshAllCountriesReadOnly` (`0x00DD0C11`).

### 3.3 Hooks & Code Removed During Cleanup

- `0x004E7616` & `0x004E7905`: Removed inline cave hooks that overwrote unit organization / state during combat checks.
- `0x00DCBADC`: Cleared legacy org/hook storage slot and repurposed it for `BottleneckQuotaAggregation`.
- `0x006A5790` (and dead spearhead stubs): Removed orphaned spearhead override checks after scrapping `SpearheadWinningOdds` and `AbortSpearheadOnNeckCollapse`.
- Tarjan 1-vertex articulation loop (`.tarjan_start`..`.neck_propagate`) and greedy Option B blocking: Superseded inside `Cave_STEM_UpdateGraphTable` by Local `K`-Hop Frontline Search + Option C Split-Node Residual Max-Flow.

---

## 4. Issues Addressed Across Phases 1-5 & Stages 1-5

1. **Memory Aliasing Between `+0x24000` and `+0x26000` (Phase 1)**: Rebuilt `Cave_STEM_UpdateGraphTable` with non-overlapping array strides.
2. **Retail Rear-Reserve Replacement & Org Mutation Bug (Phase 2)**: Restored retail `CFrontAI::ManageRearReserves` (`0x00681CD0`) behind `Hook 4` (`0x00682A58`), and removed `0x004E7616` / `0x004E7905` org-corruption hooks.
3. **Flawed Spearhead Architecture Removal (Phase 3)**: Scrapped `SpearheadWinningOdds` and `AbortSpearheadOnNeckCollapse`; repurposed `0x00DCBAB8` for `SalientSearchDepth`.
4. **Tarjan 1-Vertex Limitation (Phase 3A -> Option B)**: Replaced Tarjan with vertex-disjoint safe path counting up to `SalientNeckWidthThreshold`.
5. **Hardcoded Threat/Org Formulas & Active Combat Guard (Phase 4)**: Wired `NeckThreatRatio` and `NeckCollapsingOrgThreshold` dynamically and gated `+0x24000 = 1` on real combat / unguarded hostile entry.
6. **Depot Cores & Allied Territory Pathing (Phase 5)**: Wired `UseSupplyDepotsAsCores` (`[pProv + 0x270] > 0.0f` and supplied controller capital) and `CCountry::CanEnterOrTraceSupply` (`0x0044A690`) + war-hostility filter (`0x0044B280`).
7. **Unrelated Patch 1 & Patch 4 Crash / `.data` Collision Fix**: Relocated `AllowExpForcesToPlayers` and `AllowPuppetTrade` to `0x00DC9FF0` / `0x00DC9FF4`.
8. **Persistent Evacuation Registry & `0x00681CD0` Cancellation Shield**: Tracks active evacuations at `g_pGraphTable + 0x34000..+0x3BFFF` (`4,096` slots) and shields them via `[pArmy + 0x17B] = 2` around `0x00681CD0` + `[CFrontAI + 0xC8]` (`+0x0F = 0x5A`).
9. **Save-Reload Registry Reset & `CFrontProvince*` Seeding Fix**: Clears `+0x30000..+0xEBFFF` in `Cave_PostLoadInit` (`0x00DCF974`), dereferences `[CFrontProvince* + 0x04]`, and guards Pass-2 against spilling past the `K`-hop strip.
10. **`CRebelCountry` (`0x007E5934`) / `CHumanCountry` (`0x007F04E0`) Vtable Guard**: Verifies AI `CCountry` and `CAI` vtables before reading `+0x13C84`.
11. **Per-Province Independent Path Evaluation & Threatened Source Support**: Replaced level-component aggregation with per-province max-flow evaluation from all strip and `is_threatened == 1` frontline provinces.
12. **Option C Split-Node Residual Max-Flow & Safe-Province Slot Cleanup**: Eliminated greedy Option B false positives (`3274 Kowel` now finds `3/3` paths) and cleared `evac_slot` whenever a province becomes safe (`neck == 0`).
13. **Dynamic Salient Quota, Natural Geography Gate & Step 5C Lock (Stage 1)**: Added continuous `D_Width * T_Neck * V_Ret`, Crimea-style `F_Exp == 0` gating, Step 5A/5B downstream cut contraction, Step 5C / Pass 2 neck holding locks, 17 configurable quota floats in `db/mod_settings.ini`, and `stem_debug.csv` save telemetry (`Hook 6`).
14. **Loop A/B Salient De-Prioritization (Stage 2)**: Cut Loop B border shares (`Hooks 8A-8C`) and Loop A interior pushes/fallbacks (`Hooks 7A-7D`) by `(1 - Q)` while excluding active STEM evacuees from `InbStr`.
15. **Bottleneck Defense Boost, Interior Neck Hold & Front Merge Cleanup (Stage 3)**: Aggregated `neck_agg_q8` (`Hook 4` + `Hook 9B` injection, `Hook 9A` Loop A hold, `Hook 7B`/`8A-8C` attraction, `Hook 10` pre-`UpdateFronts` cleanup).
16. **Partial Withdrawal Budgets, Raw Terrain Parity & Threatened-Shoulder Stability (Stage 4 + Pre-Stage-5)**: Added whole-division targets & 4-tier non-overshoot selection, `.uae_split_try` oversized-corps splitting, `Hooks 11A-11F` terrain-free parity, `0x004BEBE0` combat progress + province-wide weighted avg org, `.s5ea_chk_thrt_nbs` Threatened-Shoulder Boost, and `.s5e_fin_threat_floor` Threat-Sustaining Neck Floor (`501 Lvov <-> 1884 Przemysl` fix).
17. **Load-Balanced Outward Combat Retreat Direction (Stage 5)**: Hooked `CLandArmy::SelectRetreatProvince` (`0x00508E10` via `Hooks 12A-12C`) to prioritize low-load outward exits (Band A1) and `parent`/`neck` escapes (Band A2), bypass `m_LastProvince` filters for verified exits, penalize pocket traps (Band C), and spread same-tick retreats across multiple exit provinces.

---

## 5. Remaining Open Considerations & Watchpoints

*(Synced with [plan_stem_strategic_defense.md](plan_stem_strategic_defense.md) Future Considerations.)*

1. **Organization Weighting Directly in `EnStr` & `FrStr`**: Integrate average division organization into idle, active, and inbound strength totals (not only active defensive `MinOrg`), so fresh stacks facing nearly zero-org stacks do not appear `1:1` safe before combat starts.
2. **Division Hardness / Unit-Type Weighting**: Scale `EnStr` and `FrStr` using inverse average stack softness so armored/mechanized spearheads carry realistic weight relative to militia/infantry.
3. **Width-3 Escape Cutoff (`F_Paths == 3`) & `IsThreatened` Hysteresis**: Consider keeping `IsThreatened = 1` when active attacking `EnStr / FrEff >= NeckThreatRatio` even before combat progress hits `<= 0.40`, and canceling obsolete Loop A interior marches if `quota_q8[dest]` rises mid-march.
4. **Multiplicative vs. Hybrid `SalientEvacuationQuota` Formulation**: Evaluate replacing `D_Width * T_Neck * V_Ret` with a hybrid form keeping `V_Ret` multiplicative (`clamp((w_D * max(0, D_Width - D_safe) + w_T * T_Neck) * V_Ret, 0.0, 1.0)`) so `1`-path bottlenecks can raise baseline urgency even when `T_Neck == 0.0`.
5. **Post-Arrival Residual Troop Shuffling Watchpoint**: Primary `501 Lvov <-> 1884 Przemysl` oscillation is fixed by `.s5e_fin_threat_floor`; continue observing minor mid-march shuffling to see if outbound-army `FrStr` exclusion or hysteresis is ever needed.
6. **Straggler Hostage / Pin-the-Tip Edge Case (Step 5C)**: If an enemy pins a single slow straggler at a tip while the neck itself comes under overwhelming direct attack, revisit a direct-collapse override (`IsThreatened[N] == 1` or `F_Paths[N] == 0` breaks the lock).
7. **Multi-Front Seam Interior Bottleneck Ownership (`Hook 4` / `0x00694BE0`)**: Keep current first-tick ownership unless long static stalls between unmerged fronts require garrison-owner tie-breaking in `Hook 4`.
8. **Retail Caller Gate `0x00682A43` (Zero-Reserve Fronts) & Optional Transitive Step 5E Lock-Chain Boost**: Evaluate whether fronts with `[esi + 0x10C].Count() <= 0 && [esi + 0x125] != 0` ever need `0x00682A54` routed through `Hook 4`'s `[CFrontAI + 0xC8]` exemption pass, and whether Step 5C-locked bottlenecks (`102 Wolkowysk`) ever need transitive Step 5E boost propagation onto their own rear cuts (`210 Slonim` / `503 Brest-Litovsk`).
9. **Future Breakthrough / Spearhead Architecture (On Hold)**: Any future offensive breakout protection should model corridor width, flank-holding reserve ratios, and supply robustness rather than exempting attackers blindly.
10. **Temporary `stem_debug.csv` Telemetry Retirement (When Tuning Completes)**: Save telemetry (`+0x80000..+0xBFFFF` `256 KB` + `Cave_STEM_SaveGameHook` CSV dump) remains active for validation/tuning and can later be gated or removed to shrink `g_pGraphTable` by `256 KB`.
