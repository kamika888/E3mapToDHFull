# Plan: STEM Phase 4 -- Scenario Regressions, Wartime AI Refresh, Sensitivity Refinements & GDE Scaling

**Status:** Implemented, Built & Verified (`Cave: 10,715 instructions, 32,594 bytes`, `Darkest Hour_modified.exe SHA256 = 1B48DAF6C3451C8D1E43DCAE6C21E343C9A8D883CB445388DDA2632BC211A185`)  
**Target Binary:** `Darkest Hour_modified.exe` (Darkest Hour v1.05.2, Base `0x00400000`)  
**Prerequisite:** [plan_stem_phase3_scenario_refinements.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase3_scenario_refinements.md)  
**Companion Reference Docs:**  
- [stem_test_scenarios.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/stem_test_scenarios.md)  
- [stem_testing_guide.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/stem_testing_guide.md)  
- [stem_debug_columns.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/stem_debug_columns.md)

---

## 1. Overview

Following live testing across the **Bialystok/Grodno (`SOV`)**, **Spanish Civil War (`SPA`)**, and **Inner Mongolia / Suiyuan (`MEN`)** scenarios, five targeted engine refinements were implemented on top of Phase 3:

1. **Bialystok / Grodno Salient Regression Fix**: Restored `SalientEvacuationQuota = 1.000` retention on upstream salient provinces (`7335 Augustow`) when evacuating divisions arrive at the rally neck (`102 Wolkowysk`), preventing premature quota collapse and re-entry back into the pocket.
2. **Stale Wartime `CFrontAI` Distribution Refresh (`Cave_STEM_RefreshStaleWartimeAI`)**: Fixed `SPA`'s 7-day peacetime `0xAC` delay leaving newly mobilized wartime armies unassigned in `[pAI + 0x20C]` with stale `[pAI + 0x50]` front counts and near-zero `NormAIPrio`.
3. **Bottleneck Quota & Shoulder Refinements (`SPA`)**: Capped `AggNeckQuota` by the country's `country_evac_mult` (`+0xF2000`) and `stem_no_evac` (`+0xF6000 & 0x02`), and updated `.hlp_is_viable_shoulder_eax` to allow unthreatened `F_Crit == 1` intermediate shoulders (`338 Caceres` behind `3196 Plasencia`) when `quota < 0.50` and upstream cuts have `IsThreatened == 0`.
4. **Inner Mongolia (`MEN`) Sensitivity & Topology Fixes**:
   - Net breakthrough surplus in `.hlp_calc_cut_enstr_eax` (`ActiveEnStr - (FrStr + InboundWeight * InbStr)`).
   - Pure-interior cut cap (`<= 0.75`, never `F_Crit = 1`) in `.hlp_merge_vertex_into_slot` when `(prov_flags[v] & 8) == 0`.
   - Averaged `T_Neck` across `F_Paths` (`T_sum / F_Paths`, while `V_Ref` remains the highest-threat cut).
   - Smooth partial-evacuation threshold (`max(NormAIPrio, 1.0) * (1 - Q) < 0.50`) replacing the `< 1.0` full-evacuation cliff.
   - Per-slot matching in `.par_do_replace` (`.hlp_is_land_adj_eax_ecx` + `.hlp_par_can_map`), fixing `3754 Wenduremiao` (`F_Exp = 2 -> 1`).
5. **Original-Owner Ground Defense Efficiency (`GDEWeight`) Scaling**: Added power-law `(GDE / 0.80)^GDEWeight` scaling in `.hlp_push_div_eff_str_eax` using each division's original-owner `CCountry` (`+0xE30A`), configurable via `[FrontAI] GDEWeight` in `db/mod_settings.ini`.
6. **Poland 1939 Telemetry & Pass-2 Parent Tie-Breaker**:
   - Guarded `Cave_STEM_SyncTelemetryPrio` against stale `FinalAIPrio` readouts (`+0xF8000` `front_final_q_snap` matching current `(agg_neck_quota << 8) | quota_q8`) so `stem_debug.csv` falls back cleanly whenever `Quota` or `AggNeckQuota` changed since `Hook 8D` last ticked.
   - Added equal-distance parent tie-breaking for Pass-2-only (`F_Paths == 0`) provinces in `.neighbor_loop` (`.hlp_p2_parent_rank_eax`), preferring unthreatened -> lower `F_Crit` -> higher `F_Paths` -> lower `F_Exp` at the same shortest `dist`.

---

## 2. Detailed Changes

### 2.0 Poland 1939 Telemetry Snapshot & Pass-2 Parent Tie-Breaker
- **Stale `FinalAIPrio` Snapshot Validation (`+0xF8000` `front_final_q_snap`)**:
  - `Cave_STEM_UpdateGraphTable` runs every hour and on Save, whereas `front_final_divs` (`+0x118000`) is only recomputed when `CFrontAI::MoveUnitsToFront` (`Hook 8D`) ticks for that front. Previously, `Cave_STEM_SyncTelemetryPrio` printed cached `+0x118000` even after a province flipped between evacuating (`3265 Dirschau`) and bottleneck (`2628 Bielsko`), making `FinalAIPrio` appear inverted in `stem_debug.csv`.
  - `Hook 8D` now packs `(agg_neck_quota << 8) | quota_q8` into `g_pGraphTable + 0xF8000`, and `Cave_STEM_SyncTelemetryPrio` falls back to `.stp_calc_rear_final` (with Stage B's sub-`0.50` / full-evac zeroing + current bottleneck boost) whenever the cached snapshot no longer matches live state.
- **Pass-2 Equal-Distance Parent Tie-Breaker (`.neighbor_loop` + `.hlp_p2_parent_rank_eax`)**:
  - When a Pass-2-only (`F_Paths == 0`) province like `3265 Dirschau` has multiple equal-distance (`dist = 3`) exits (e.g., `208 Bydgoszcz` with `F_Paths = 1` vs `307 Torun` with `F_Paths = 2`), `.neighbor_loop` previously kept whichever neighbor was popped first.
  - `.hlp_p2_parent_rank_eax` now compares candidates at exact shortest distance (`dist[eax] == edi + 1`), ranking `!IsThreatened > lower F_Crit > higher F_Paths > lower F_Exp` without altering distances or re-enqueuing nodes.

### 2.1 Wartime AI Distribution Refresh (`Cave_STEM_RefreshStaleWartimeAI`)
- **Problem**: When a country transitions to war (e.g., `SPA` in the Spanish Civil War), `CAI` can remain gated behind its 7-day peacetime `[pAI + 0xAC]` delay, leaving `[pAI + 0x50]` at its small peacetime count while dozens of armies sit unassigned in `[pAI + 0x20C]` and `CFrontAI::MoveUnitsToFront` computes `NormAIPrio ? 0.1`.
- **Fix**: Added `Cave_STEM_RefreshStaleWartimeAI` (called in `Cave_STEM_UpdateGraphTable` when at war, `[pCountry + 0xE880] != 0`, and all fronts are idle `[pFront + 0x9E] == 0`):
  - Triggers when `[pAI + 0x50]` is stale relative to active land unit count + `[pAI + 0x54]` (or unassigned armies exist in `[pAI + 0x20C]`), resetting the stale delay so `CFrontAI` immediately absorbs and distributes armies across the front.

### 2.2 Bottleneck Quota Cap & Intermediate Shoulder Locking (`SPA`)
- **Problem 1**: Lowering `stem_evac_modifier` / `EvacMult` for `SPA` reduced `SalientEvacuationQuota`, yet `.s5e_fin_threat_floor` still elevated `AggNeckQuota` above what `EvacMult` allowed (e.g., `3196 Plasencia`).
  - **Fix**: Capped `.s5e_fin_threat_floor` by `country_evac_mult` (`+0xF2000`) and skipped it entirely when `stem_no_evac` (`+0xF6000 & 0x02`) is set.
- **Problem 2**: `338 Caceres` (the mandatory approach behind `3196 Plasencia`) was not locked/boosted as a bottleneck shoulder.
  - **Fix**: Updated `.hlp_is_viable_shoulder_eax` to permit unthreatened `F_Crit == 1` intermediate shoulders when `quota < 128` (`< 0.50`) and upstream `CutProv1`/`CutProv2` (`+0x78000`/`+0x78002`) have `IsThreatened == 0`.

### 2.3 Inner Mongolia (`MEN`) Sensitivity & `.par_do_replace` Fix
- **Net Breakthrough Surplus (`.hlp_calc_cut_enstr_eax`)**: When propagating indirect threat from an adjacent `IsThreatened == 1` province, only the net breakthrough surplus `ActiveEnStr - (FrStr + InboundWeight * InbStr)` (when `> 0.05`) is propagated, preventing held/well-defended neighbors from inflating downstream `EnStr`.
- **Pure-Interior Cut Cap (`.hlp_merge_vertex_into_slot`)**: If a cut vertex has `(prov_flags[v] & 8) == 0` (no direct land exposure to an enemy province), its local threat `T` is capped at `0.75` and it is never marked `F_Crit = 1` unless `is_threatened == 1`.
- **Averaged `T_Neck` Across `F_Paths`**: Replaced max-over-cuts `T_Neck` with `T_sum / F_Paths` (`[ebp - 0x88] / [ebp - 0x3C]`) while keeping `V_Ref` pointing to the highest-threat cut vertex.
- **Smooth Partial-Evacuation Threshold**: Replaced the `< 1.0` full-evacuation cliff in Pass 2, `.uae_is_full_evac_dst_eax`, and Stage B `.nfs_b_p1_partial` with `max(NormAIPrio, 1.0) * (1 - Q) < 0.50`.
- **Per-Slot Matching in `.par_do_replace` (`3754 Wenduremiao`)**:
  - Previously, `.par_do_replace` ORed `slot0_exp | slot1_exp` and copied `max(T0, T1)` into both slots when contracting `{3753, 5631} -> {5628, 5632}`, smearing `3753`'s direct `U65` border exposure onto the completely unexposed `3754 -> 5631 -> 5632 -> 1386 -> 5629` corridor (`F_Exp = 2`, `D_Width = 0.800`, `T_Neck = 0.85`).
  - Added `.hlp_is_land_adj_eax_ecx` and `.hlp_par_can_map` to match `(old0, old1)` to `(u0, u1)` via cut-vertex membership (`+0x78000`) and direct passable land adjacency (`conn_type != 4`), with an exposure tie-breaker when symmetric. `3754` now stays at `F_Exp = 1`, preserving the safe `5631 -> 5632` route.

### 2.4 Original-Owner `GDEWeight` Scaling (`.hlp_push_div_eff_str_eax`)
- **Verified Engine Offsets (`Darkest Hour_original.exe`)**:
  - `CCountry::GetGroundDefEff` (`0x0070A480`): `fld dword ptr [ecx + 0xE30A]` (`float`, `ground_def_eff`, token `0x387`).
  - `CUnit::GetOriginalCountry` (`0x00522770`) & `CDivision::UpdateMods` (`0x005054D0`): resolves `[pDiv + 0x6C]` ? `[pUnit + 0x146]` via `0x0089CAD8`, then `[pUnit + 0x248]`, falling back to `[pDiv + 0x58]` via `0x0089CAD8` and `[pDiv + 0x5C]`. This ensures expeditionary divisions (e.g., `JAP` forces lent to `MEN` with `GDE ? 1.13`) use their original owner's `ground_def_eff` rather than the host's (`MEN ? 0.71`, `CHI ? 0.29`).
- **Formula & Config**:
  - Stage 4 of `.hlp_push_div_eff_str_eax` (also reached by unscaled `ecx == 0` idle enemy strength calls) clamps `GDE` to `[0.05, 5.0]` and multiplies division strength by:
    $$\text{GDEFactor} = \left(\frac{\text{GDE}}{0.80}\right)^{\text{GDEWeight}}$$
  - At `GDEWeight = 1.0`, ratios are exact linear GDE ratios; at `GDEWeight = 0.0`, scaling is disabled; default **`GDEWeight = 0.60`** in `db/mod_settings.ini` (`tbl_FrontAIFloatConfigs`, 24 entries).
