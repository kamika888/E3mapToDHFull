# STEM Test Scenarios & Issue Remediation Log

Reference catalog of the primary test scenarios used to validate **Patch 18 (STEM)**, along with the specific issues observed in `stem_debug.csv` / live gameplay and how each was remediated.

For column definitions and INI tuning, see [stem_debug_columns.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/stem_debug_columns.md) and [stem_testing_guide.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/stem_testing_guide.md).

---

## 1. Bialystok / Grodno Salient (`SOV` vs `GER`, 1941 Barbarossa)

- **Key Provinces**: `209 Grodno` & `102 Wolkowysk` (corridor shoulders/necks), `7335 Augustow`, `505 Bialystok`, `6515 Bielsk Podlaski`, `6516 Grajewo`, `1875 Lomza` (salient interior/tips), `210 Slonim` & `503 Brest-Litovsk` (downstream rear).
- **What It Tests**: Multi-layer salient detection (`SalientNeckWidthThreshold = 3`), corridor cut contraction (`Step 5B`), active neck holding lock (`Step 5C`), `Support Defence` (`mission_type = 5`) into attacked necks, combat retreat direction (`SelectRetreatProvince`), and anti-flicker hysteresis.

| Issue Encountered | Remediation | Reference |
|---|---|---|
| Source-nearest cut hid `209 Grodno` behind `7335 Augustow`, and `102 Wolkowysk` evacuated before forward troops escaped | Added `Step 5B` series/parallel contraction (`{102, 209}`) and `Step 5C` reverse-`Dist` holding lock (`102` holds `Quota = 0` until upstream clears). | [Phase 1 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_strategic_defense.md) |
| Loop A marched units at `102 Wolkowysk` straight back into `7335`/`505`, and defeated defenders retreated deeper into the pocket | Hooked Loop A (`0x00683C9D..0x00684131`) with interior neck hold + candidate gating, and hooked `0x00508E10` (`Hooks 12A-12C`) for load-balanced outward retreats. | [Phase 1 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_strategic_defense.md) |
| Reinforcements arriving at `209 Grodno` briefly flipped `IsThreatened = 0`, dropping `7335`'s quota and cancelling evacuations mid-march | Added 3-layer hysteresis (`ThreatClearanceCooldownHours = 36`, `EvacReentryCooldownHours = 24`, active march commitment) and fixed `F_Crit` / `T_Neck` retention regression. | [Phase 2 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase2_refinements.md), [Phase 4 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase4_scenario_fixes_and_gde.md) |
| Withdrawing units adjacent to `209 Grodno` halted or auto-retreated on flank contact | Enabled `AllowThreatenedBottleneckWithdrawal = 1`, `Support Defence` (`mission_type = 5`) with battle-end march preservation (`Hook 13`), and flank auto-retreat immunity (`Hook 14`). | [Phase 2 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase2_refinements.md) |

---

## 2. Crimea & Leningrad / Lake Ladoga (`SOV`, 1941)

- **Key Provinces**: `1827 Dzankoj` & `254 Kerch` (Crimea); `187 Leningrad` & `189 Kirisi <-> 7003 Kir'jasaly` (Lake Ladoga impassable lifeline).
- **What It Tests**: Natural Geography Gate (`F_Exp == 0` when sheltered), alternative supply lifelines (`ImpassableSupplyQuotaMultiplier`, `PortSupplyQuotaMultiplier`), and manual `front.province_priorities` evacuation blacklists.

| Issue Encountered | Remediation | Reference |
|---|---|---|
| Crimea evacuated prematurely when `254 Kerch` had `F_Paths = 1` despite `1827 Dzankoj` holding | Natural Geography Gate zeroes `SalientEvacuationQuota` when `F_Exp == 0` and `IsThreatened == 0`; unlocks as soon as `1827` flips `IsThreatened = 1`. | [Phase 1 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_strategic_defense.md) |
| Fortress cities (`187 Leningrad`) with Lake Ladoga (`adj->type == 4`) / port supply still evacuated at full quota | Added `ImpassableSupplyQuotaMultiplier = 0.35` (`StatusFlags +2`), `PortSupplyQuotaMultiplier = 0.50` (`StatusFlags +4`), and `front.province_priorities` blacklist + `Hook 8D` normalization. | [Phase 2 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase2_refinements.md) |

---

## 3. Communist China (`CHC`, 1936 Shaanxi / Gansu)

- **Key Provinces**: `1270 Yanan` (Capital), `5570 Fuxian`, `5569 Dingbian`, `5554 Qingyang`, `5571 Suide`, `5572 Dali`, `1271 Shenmu`.
- **What It Tests**: Multi-ally military-access isolation (`CHC` with `stem_evac_modifier = 20` alongside `U58` / `SIK`), capital supply-sink handling, 1-hop core perimeter defense, heavy terrain modifiers (Event `9000081`), and directional spearhead threat.

| Issue Encountered | Remediation | Reference |
|---|---|---|
| `U58`/`SIK` overwrote `CHC`'s `quota_q8` (`0.20` -> `0.502`) and `neck` via shared `g_pGraphTable` arrays | Guarded all persistent global per-province output writes with `prov->m_pController == pCountry` (Phase 3 Stage 1). | [Phase 3 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase3_scenario_refinements.md) |
| Option C saturated `1270 Yanan` (`CutProv1 = 1270`), ordering perimeter tiles (`5570`, `5572`) to evacuate into the Capital | Kept `Dist == 0` supply sinks unsaturated in Option C and added `MinSupplyCoreEvacDist = 1` gate on true Supply Cores (Phase 3 Stage 2). | [Phase 3 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase3_scenario_refinements.md) |
| Mountain/partisan defense bonuses (Event `9000081`) were ignored in `FrStr`, and `5554 Qingyang` inherited `5554`'s own attackers via `5569` | Added per-division live terrain defense scaling from `[pDiv + 0x164]` (`MaxTerrainDefenseMultiplier = 3.0`, Stage 3) and directional `.hlp_calc_cut_enstr_eax` + cutoff-gated floor (Stage 4). | [Phase 3 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase3_scenario_refinements.md) |

---

## 4. Spanish Civil War (`SPA` vs `SPR`, 1936)

- **Key Provinces**: `3196 Plasencia`, `338 Caceres`, Seville southern salient (with Portuguese military access).
- **What It Tests**: Wartime mobilization into `CFrontAI`, `EvacMult`-respecting bottleneck floors, and multi-hop shoulder locking.

| Issue Encountered | Remediation | Reference |
|---|---|---|
| `SPA` showed `NormAIPrio ? 0.1` across frontline provinces with ~55 armies unassigned in `[pAI + 0x20C]` | Added `Cave_STEM_RefreshStaleWartimeAI` to clear stale peacetime `0xAC` delay when at war with stale `[pAI + 0x50]` or unassigned armies. | [Phase 4 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase4_scenario_fixes_and_gde.md) |
| `3196 Plasencia`'s `AggNeckQuota` exceeded `SPA`'s `EvacMult`, and `338 Caceres` was not marked as a bottleneck | Capped `.s5e_fin_threat_floor` by `country_evac_mult` (and skipped on `stem_no_evac`), and allowed unthreatened `F_Crit == 1` shoulders (`338`) when `quota < 0.50` and upstream cuts are unthreatened. | [Phase 4 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase4_scenario_fixes_and_gde.md) |

---

## 5. Inner Mongolia / Suiyuan Campaign (`MEN` + `JAP` Exp. vs `CHI` / `U65`, 1936–1937)

- **Key Provinces**: `3754 Wenduremiao`, `3753 Shangdu`, `5631 Mandalt`, `5628 Duolun`, `5632 Xiongwangfu`, `5627 Zhangbei`.
- **What It Tests**: Low-density minor-nation fronts with allied (`MAN`) access, parallel 2-cut contraction, and asymmetric `ground_def_eff` (`JAP` `1.13` expeditionaries vs `MEN` `0.71` vs `CHI` `0.29`).

| Issue Encountered | Remediation | Reference |
|---|---|---|
| `MEN` frontline provinces constantly evacuated (`5628` threat propagation + max-cut `T_Neck` + `< 1.0` full-evac cliff) | Switched to net breakthrough surplus, capped pure-interior cuts at `T <= 0.75` (`F_Crit = 0`), averaged `T_Neck` across `F_Paths`, and replaced `< 1.0` cliff with `max(NormAIPrio, 1.0) * (1 - Q) < 0.50`. | [Phase 4 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase4_scenario_fixes_and_gde.md) |
| `3754 Wenduremiao` showed `F_Exp = 2` even when unthreatened because `.par_do_replace` smeared `3753`'s exposure onto `5632` | Added `.hlp_is_land_adj_eax_ecx` + `.hlp_par_can_map` per-slot matching in `.par_do_replace`, preserving `5631 -> 5632` as `exp = 0` (`F_Exp = 1`). | [Phase 4 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase4_scenario_fixes_and_gde.md) |
| `MEN` + `JAP` expeditionaries underestimated their combat power against `CHI` militia due to `GDE` disparity (`1.13` / `0.71` vs `0.29`) | Added power-law `(GDE / 0.80)^GDEWeight` scaling (`GDEWeight = 0.60`) in `.hlp_push_div_eff_str_eax` using original-owner `[CCountry + 0xE30A]`. | [Phase 4 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase4_scenario_fixes_and_gde.md) |

---

## 6. Invasion of Poland (`POL` vs `GER`, 1939)

- **Key Provinces**: `306 Gdynia`, `3265 Dirschau`, `208 Bydgoszcz`, `307 Torun`, `222 Wloclawek`, `7050 Modlin` (Polish Corridor); `2296 Tesin`, `2628 Bielsko`, `486 Katowice`, `3269 Biala` (Silesia / southern flank).
- **What It Tests**: Large multi-front high-pressure campaign with simultaneous `F_Paths = 0` collapses, bottleneck role transitions between ticks, and competing equal-distance corridor exits (`208 Bydgoszcz` vs `307 Torun`).

| Issue Encountered | Remediation | Reference |
|---|---|---|
| `POL` stayed absent from `stem_debug.csv` and idle for 1–2 days at war start (`[pAI + 0x278] == NULL`, `[pAI + 0x214] == 0`) | Added one-shot Trigger C in `Cave_STEM_RefreshStaleWartimeAI` to run `CAI::UpdateFronts` once when newly at war with `0` fronts. | [Phase 4 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase4_scenario_fixes_and_gde.md) |
| `stem_debug.csv` showed inverted `FinalAIPrio` (`2628 Bielsko = 1.0`, `3265 Dirschau = 4.5`) when statuses flipped between `MoveUnitsToFront` ticks | Snapshot `(agg_neck_quota << 8) | quota_q8` in `+0xF8000` (`Hook 8D`) so `Cave_STEM_SyncTelemetryPrio` recomputes stale entries using live quotas/boosts. | [Phase 4 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase4_scenario_fixes_and_gde.md) |
| `3265 Dirschau` (`F_Paths = 0`) locked onto narrower `208 Bydgoszcz` (`F_Paths = 1`) over wider `307 Torun` (`F_Paths = 2`) at equal `Dist = 3` | Added Pass-2 equal-distance parent tie-breaker (`.hlp_p2_parent_rank_eax` in `.neighbor_loop`: `!IsThreatened > lower F_Crit > higher F_Paths > lower F_Exp`). | [Phase 4 Plan](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase4_scenario_fixes_and_gde.md) |
