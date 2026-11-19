# `stem_debug.csv` Column Reference

Semicolon-delimited (`;`) debug telemetry dumped to `stem_debug.csv` in the Darkest Hour root directory upon saving (manual save or autosave) when `EnableSTEM = 1` in `db/mod_settings.ini`.

| Column | Meaning |
|---|---|
| `CountryTag` | 3-letter tag of the evaluated AI country controlling the province (`UNK` if lookup fails). |
| `ProvID` | Numeric province ID (`1..8020`). |
| `ProvName` | Localized province name read from `[CProvince + 4]` (English name from `map/Map_3/province_names.csv` when running in English; `UNK` if null). |
| `Dist` | BFS hop distance (`0..65535`) from the nearest safe rear horizon / capital / depot (`0` = safe root). |
| `IsThreatened` | `1` if Pass 0 flagged the province as threatened (`+0x24000`), `0` otherwise. Set either when friendly defenders are losing badly in combat here (`CombatStrengthRatioThreshold = 1.5`, i.e., combat progress <= `0.40`, or avg division org < `10.0`), or when an active hostile moving army's immediate next hop (`[army + 0x27E] == 1`, `[army + 0x232]` list head) targets an unguarded friendly province. |
| `F_Paths` | Max-flow count of vertex-disjoint safe escape paths from this province to safe roots, capped at `SalientNeckWidthThreshold` (`3`). Reaching `3` immediately marks the province safe (`SalientEvacuationQuota = 0.000`). |
| `F_Exp` | Count of extracted minimum-cut bottleneck vertices (`1 <= F_Paths < W`) that have `IS_LAND_EXPOSED` (`prov_flags` bit `0x08`: borders a war enemy / hostile army, or borders an `IsThreatened == 1` province). If `F_Exp == 0` and `IsThreatened == 0`, the **Natural Geography Gate** zeroes the quota. |
| `F_Crit` | Subset of `F_Exp` cut vertices that are already `IsThreatened == 1` or have individual bottleneck threat `T(v) >= 1.0`. |
| `CutProv1`, `CutProv2` | First two province IDs on the residual max-flow minimum cut separating the province from the safe rear (`0` if safe, `F_Paths == 0`, or fewer cut vertices exist). |
| `EvacDestNeck` | Resolved evacuation destination neck province ID (`0` when not evacuating). |
| `FrStr` | Friendly non-retreating strength in division-equivalents at **reference vertex `v_ref`** (worst exposed cut vertex if any, else `CutProv1`, else the province itself when safe or `F_Paths == 0`). |
| `EnStr` | Enemy strength threatening `v_ref` (sum of `raw_hostile_str` in adjacent non-friendly provinces, plus Pre-Pass B propagated strength from adjacent `IsThreatened` friendly provinces if `v_ref` itself is not already `IsThreatened`). |
| `InbStr` | Friendly non-retreating strength currently marching into `v_ref` (`[army + 0x27E] == 1` and immediate next hop `[army + 0x232]` head == `v_ref`). |
| `MinOrg` | Minimum average division organization (`0..254`, or `255` when not in defensive combat) of friendly defenders in `v_ref`. |
| `VP_IC_Val` | Strategic value of this province plus its friendly-controlled land neighbors: `sum(max(0, VP) + 0.5 * max(0, IC))`. |
| `D_Width` | Neck-width deficit in `[0.000, 1.000]`, `max(0, (W - (F_shelt + 0.5 * F_intact_exp)) / W)`, where `F_shelt = F_Paths - F_Exp` and `F_intact_exp = F_Exp - F_Crit` (`0.000` when gated safe; `1.000` when `F_Paths == 0`). |
| `T_Neck` | Bottleneck threat urgency clamped to `[0.25, 1.50]`: worst cut vertex threat `T(v_max) * (1 + 0.25 * (F_Exp - 1))`, where `T(v)` combines strength ratio vs `CombatStrengthRatioThreshold` (`1.50` when unguarded with `EnStr > 0.05`) and low-org urgency against `CombatOrgThreshold`. (`0.25` when gated safe; `1.50` when `F_Paths == 0`). |
| `V_Ret` | Value-retention multiplier clamped to `[0.500, 1.000]`: `max(0.5, 1 / (1 + 0.02 * VP_IC_Val))`, bypassed to `1.000` when `IsThreatened == 1`, all cut paths are critical (`F_Crit == F_Paths`), or `F_Paths == 0`. |
| `SalientEvacuationQuota` | Final quota in `[0.000, 1.000]`: `clamp(D_Width * T_Neck * V_Ret, 0.0, 1.0)` (floored at `0.85` if `IsThreatened == 1`, or `1.000` if `F_Crit >= 1`), quantized to `0..255` in `quota_q8`. |
