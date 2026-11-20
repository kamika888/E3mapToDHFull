# STEM Encirclement Defense - Tester's Guide

This guide explains how the AI's **Salient Evacuation & Pocket Defense system (STEM)** works in plain English, how to inspect its decisions in `stem_debug.csv`, and what each setting in `db/mod_settings.ini` controls while testing.

> **Current Implementation Note (Stages 1 + 2 + 3)**:
> * The danger scoring (`SalientEvacuationQuota`), bottleneck holding lock, Front AI reinforcement suppression (`NormAIPrio` -> `AdjAIPrio`), and **bottleneck defense boosting / interior neck hold (`BottleneckDefenseBoost`, `AggNeckQuota`, `FinalAIPrio`)** are active.
> * Once a province's `SalientEvacuationQuota` goes above `0.000`, divisions inside it evacuate toward safety while Front AI cuts that province's target troop count (`AdjAIPrio`) and boosts the supporting neck bottlenecks (`FinalAIPrio`). Partial per-division withdrawal budgets (keeping a fractional screen behind when `0 < Quota < 1`) are planned for Stage 4.

---

## 1. The Core Idea in Plain Language

Normal Hearts of Iron / Darkest Hour AI only looks one province ahead. If the enemy attacks the sides ("shoulders") of a bulge in the frontline, the AI keeps reinforcing the tip of the bulge until it gets surrounded and destroyed.

STEM solves this in four steps every game hour:

1. **Map safe escape routes (`F_Paths`)**:
   Starting from each frontline province, STEM looks backward toward safe rear territory (the capital, supply depots, or open ground beyond `SalientSearchDepth` hops) and counts how many **completely separate** escape routes exist (up to `SalientNeckWidthThreshold`, default `3`).
   * **3 or more separate routes (`F_Paths >= 3`)**: Safe. Do nothing (`Quota = 0.000`).
   * **0 routes remaining (`F_Paths == 0`)**: Cut off or hanging by a collapsing thread. Full evacuation (`Quota = 1.000`).
   * **1 or 2 routes (`1 <= F_Paths < 3`)**: The province sits in a salient / pocket behind narrow bottlenecks (`CutProv1`, `CutProv2`). Evaluate how dangerous those bottlenecks are.

2. **Check if the bottleneck can actually be attacked (`Natural Geography Gate`)**:
   If none of a pocket's bottlenecks touch an enemy province or a collapsing friendly province (`F_Exp == 0`) - and the pocket itself isn't collapsing - the AI stays calm (`Quota = 0.000`).
   * *Example*: **Crimea** sits behind the narrow 1-province neck of `1827 Dzankoj` / `254 Kerch`. As long as Perekop/Dzankoj is holding fine, Crimea stays defended at `0.000`. The moment `1827 Dzankoj` starts collapsing, Crimea unlocks evacuation.

3. **Score how much danger the pocket is in (`SalientEvacuationQuota`, `0.000` to `1.000`)**:
   The quota multiplies three simple factors together:
   $$\text{SalientEvacuationQuota} = \text{D\_Width} \times \text{T\_Neck} \times \text{V\_Ret}$$
   * **`D_Width` (*How narrow/damaged is the exit?*)**
     Fewer open routes = higher urgency.
     * Safe/sheltered bottleneck = `1.0` open door.
     * Exposed bottleneck that is still holding (`T < 1.0`) = `0.5` open door (`ExposedIntactPathCredit`).
     * Critical/collapsing bottleneck (`T >= 1.0` or `IsThreatened = 1`) = `0.0` open doors.
   * **`T_Neck` (*How hard is the enemy pushing the bottleneck?*)**
     Compares enemy pressure against our defenders at the worst bottleneck:
     * **0.0** = Quiet border or equal force (`1:1` or better, no org collapse).
     * **1.0** = Serious danger (`1.5:1` enemy superiority or low defender org).
     * **1.5** = Overwhelming danger or unguarded hole on the bottleneck.
     * Multiple exposed bottlenecks at the same time get an extra `+25%` urgency per extra exposed cut (`MultiExposedCutBonus`).
   * **`V_Ret` (*Is the pocket valuable enough to hold longer?*)**
     Looks at total **VP and IC** in the province + friendly neighbors (`0.50` to `1.00`). High-value areas like Kiev or Leningrad drop slightly slower (`V_Ret = 0.50`), unless the province itself is collapsing or all bottlenecks are critical (`V_Ret = 1.00`).

4. **Hold the bottleneck open while salient troops escape (`Holding Lock`)**:
   If forward provinces inside a pocket are evacuating (`Quota > 0`) and still have troops inside (even retreating ones), any bottleneck behind them (`CutProv1` / `CutProv2` closer to safety) is **locked at `Quota = 0.000`** so the exit garrison doesn't abandon its post before the trapped troops get out.
   * *Example (Bialystok salient)*: When the Germans attack `209 Grodno`, troops in `505 Bialystok`, `1875 Lomza`, `6515 Bielsk Podlaski`, `6516 Grajewo`, and `7335 Augustow` evacuate to `102 Wolkowysk` (`EvacDestNeck = 102`), while `102 Wolkowysk` holds at `Quota = 0.000`. Once those provinces clear out (or if `102`'s own rear at Brest is also broken), `102` unlocks and they withdraw together toward `210 Slonim`.

5. **Stop Front AI from marching replacements back into the pocket (`NormAIPrio` -> `AdjAIPrio`)**:
   Front AI reduces each evacuating province's desired division count by `(1 - Quota)` (`AdjAIPrio = NormAIPrio * (1 - Quota)`), stopping both rear reserves and neighboring frontline units from walking back into collapsing pockets.

6. **Reinforce and hold the bottleneck line (`BottleneckDefenseBoost` -> `FinalAIPrio`)**:
   Whenever one or more salient provinces evacuate through a bottleneck `B`, STEM aggregates their quotas (`AggNeckQuota`, using `MAX`/`AVERAGE`/`MIN` via `BottleneckQuotaAggregation`) and boosts `B`'s target priority by `BottleneckDefenseBoost * AggNeckQuota` (`+3.5` divisions at full `1.000` quota by default):
   * **Frontline bottlenecks** pull extra divisions through Front AI and attract adjacent reserves (`FinalAIPrio = AdjAIPrio + Boost`).
   * **Interior bottlenecks** (1+ hops behind the active frontline, like `102 Wolkowysk` before Grodno falls) hold up to `BottleneckDefenseBoost * AggNeckQuota` division-equivalents in place instead of letting Loop A push them away, releasing only surplus divisions above that garrison requirement.
   * If a bottleneck province itself starts evacuating (`SalientEvacuationQuota > 0`), the boost automatically clears (`AggNeckQuota = 0`) so it does not pull reinforcements against its own retreat.

---

## 2. How to Test & Inspect `stem_debug.csv`

### Quick Setup for Observing the AI
In `Mods/E3mapToDHFull/db/mod_settings.ini`:
* `[FrontAI]` -> `EnableEncirclementDefense = 1`
* Helpful visual toggles under `[Engine]` (already enabled in the mod):
  * `AlwaysShowMovementArrows = 1` (shows movement and retreat arrows for all countries on the map)
  * `AutoNoFog = 1` (reveals the whole map automatically)
  * `AutoShowId = 1` (shows province IDs in the corner/tooltip)

> **Important**: `db/mod_settings.ini` is loaded **when Darkest Hour starts**. If you edit any numbers in `mod_settings.ini`, **restart the game** for the new values to take effect.

### Generating & Opening `stem_debug.csv`
1. Run the scenario and let at least one in-game hour/day pass (or trigger an attack) so Front AI evaluates the front.
2. **Save the game** (manual save or autosave).
3. Open `stem_debug.csv` in the Darkest Hour root folder (using Excel, LibreOffice Calc, or a CSV viewer; the separator is semicolon `;`).

### What the Columns Mean (Tester Cheat Sheet)

| Column | Plain-English Meaning | What to Look For |
|---|---|---|
| `CountryTag` | AI country owning the province (e.g., `SOV`, `GER`). | Filter by tag to focus on one side. |
| `ProvID`, `ProvName` | Province ID and name. | Match against province IDs on the map (`showid`). |
| `Dist` | Hops away from the nearest safe rear anchor (`0` = safe rear core/horizon). | Should decrease along the escape path (`8 -> 7 -> 6 -> ... -> 0`). |
| `IsThreatened` | `1` if friendly defenders here are losing combat badly, low org, or an unguarded tile has an enemy marching into it. | Flips to `1` during heavy enemy assaults on key shoulders (e.g., Grodno). |
| `F_Paths` | Safe vertex-disjoint escape routes from this province (`0..SalientNeckWidthThreshold`). | `>= 3` means safe (`Quota = 0`). `1` or `2` means salient/bottleneck logic applies. |
| `F_Exp` | Number of bottlenecks exposed to enemy land borders or threatening neighbors. | `0` triggers the Natural Geography Gate (`Quota = 0` if `IsThreatened = 0`). |
| `F_Crit` | Number of exposed bottlenecks in critical condition (`IsThreatened = 1` or `T >= 1.0`). | `>= 1` pushes `V_Ret = 1.0` and raises urgency. |
| `CutProv1`, `CutProv2` | The controlling bottleneck province IDs along the escape corridor. | E.g., `102` (Wolkowysk) and `209` (Grodno) for the Bialystok salient. |
| `EvacDestNeck` | Target safe rally province ID (`0` = not evacuating). | Should point to the intermediate locked neck (e.g., `102`) until upstream clears. |
| `FrStr`, `InbStr`, `MinOrg` | At the reference bottleneck (`v_ref`): friendly defending division-equivalents (`FrStr`), inbound friendly divisions (`InbStr`), and lowest defender org (`255` = not in defensive combat). | Effective defense = `FrStr + InboundFriendlyStrWeight * InbStr`. |
| `EnStr` | Weighted enemy threat facing `v_ref` (`ActiveEnemyAttackWeight` for attackers/movers + `IdleEnemyPresenceWeight` for idle neighbors + spillover). | On a quiet `1:1` border, a `1.0` enemy div shows `0.25` here. |
| `VP_IC_Val` | Combined `VP * VPWeight + IC * ICWeight` for this province and friendly neighbors. | Higher value pulls `V_Ret` down toward `0.50` when bottlenecks are not critical. |
| `D_Width` | Width deficit factor (`0.000` to `1.000`). | How narrow/compromised the exit routes are. |
| `T_Neck` | Bottleneck threat urgency factor (`0.00` to `1.50`). | **`0.00` on quiet or `1:1` fronts**; rises toward `1.00`+ when enemy outnumbers `1.5:1` or defender org collapses. |
| `V_Ret` | Value retention multiplier (`0.500` to `1.000`). | `1.000` when collapsing or bottlenecks are critical. |
| `SalientEvacuationQuota` | Final quota (`0.000` to `1.000`) = `D_Width * T_Neck * V_Ret` (with overrides). | `0.000` = hold normally; `> 0.000` = evacuate and reduce Front AI allocation. |
| `NormAIPrio`, `AdjAIPrio` | Front AI's normal desired division count (`NormAIPrio`) and STEM-reduced target (`AdjAIPrio = NormAIPrio * (1 - Quota)`). | Evacuating provinces (`Quota = 1.000`) should drop to `AdjAIPrio = 0.0`. |
| `IsBottleneck`, `AggNeckQuota` | `1` if evacuating salient provinces depend on this bottleneck; `AggNeckQuota` (`0.000` to `1.000`) is the combined neck pressure (`MAX`/`AVERAGE`/`MIN`). | Active bottlenecks like `102` or `209` show `IsBottleneck = 1` and `AggNeckQuota > 0` (even interior necks!). |
| `FinalAIPrio` | Boosted target priority (`AdjAIPrio + BottleneckDefenseBoost * AggNeckQuota`) in divisions. | Should be ~`3.5` divisions higher than `AdjAIPrio` when `AggNeckQuota = 1.000`. |

---

## 3. Recommended Scenarios to Verify

1. **Quiet `1:1` Border / Salient**:
   * Put roughly equal non-attacking forces (`1:1`) facing a 1-2 route salient.
   * *Expected*: `IdleEnemyPresenceWeight = 0.25` makes `EnStr` ~25% of `FrStr` (`R ~ 0.25 <= 1.0`), so **`T_Neck = 0.00`**, **`SalientEvacuationQuota = 0.000`**, and `AdjAIPrio == NormAIPrio`. No panic evacuation.
2. **Active `1:1` Skirmish (High Org)**:
   * An enemy attacks at `1:1` strength while defenders still have high org (`>= 2 * NeckCollapsingOrgThreshold`).
   * *Expected*: `R = 1.0 <= NeckThreatMinRatio (1.0)`, so **`T_Neck = 0.00`** and **`SalientEvacuationQuota = 0.000`**.
3. **Outnumbered Shoulder Assault (`>= 1.5:1`, e.g., Grodno at Barbarossa start)**:
   * Germans heavily attack `209 Grodno`.
   * *Expected*: `IsThreatened = 1` on `209`, `F_Exp >= 1`, `F_Crit >= 1`, `T_Neck = 1.50` on Bialystok provinces (`505`, `1875`, `6515`, `6516`, `7335`). They evacuate to **`EvacDestNeck = 102` (`Wolkowysk`)** while `102 Wolkowysk` stays locked at **`SalientEvacuationQuota = 0.000`** until upstream troops leave.
4. **Natural Choke Point (Crimea)**:
   * Narrow peninsula behind `1827 Dzankoj` / `254 Kerch` before enemy breaks `1827`.
   * *Expected*: `F_Exp = 0` -> **`SalientEvacuationQuota = 0.000`**; unlocks immediately once `1827` becomes `IsThreatened = 1`.
5. **Reinforcement Suppression (`NormAIPrio` vs `AdjAIPrio`)**:
   * Save while a salient is evacuating and inspect neighboring rear reserves or front provinces.
   * *Expected*: Evacuating border provinces have `AdjAIPrio = 0.0` (when `Quota = 1.0`) and do not pull new Front AI divisions into the closing pocket.
6. **Bottleneck Reinforcement & Interior Neck Hold (`IsBottleneck`, `AggNeckQuota`, `FinalAIPrio`)**:
   * Save while the Bialystok salient is evacuating toward `102 Wolkowysk` (`IsBottleneck = 1`).
   * *Expected*: `102 Wolkowysk` (even if behind the front line) appears in `stem_debug.csv` with `IsBottleneck = 1`, `AggNeckQuota > 0`, and `FinalAIPrio` boosted by `BottleneckDefenseBoost * AggNeckQuota` (`~3.5` divs at `1.000`); armies inside `102` up to that requirement stay anchored there instead of marching away, while excess troops above that requirement remain free to move.

---

## 4. `[FrontAI]` Settings Cheat Sheet (`db/mod_settings.ini`)

### Master & Topology Controls

| Variable | Default | Effect When Changed |
|---|---|---|
| `EnableEncirclementDefense` | `1` | `1` = STEM active; `0` = vanilla Darkest Hour Front AI. |
| `SalientNeckWidthThreshold` | `3` | Maximum escape routes to still check as a salient (`3` catches 1- and 2-route pockets; `2` only catches 1-route chokepoints). |
| `SalientSearchDepth` | `5` | How many provinces inward from the front to search (`-1` = search all the way back to Capital/Depots). |
| `UseSupplyDepotsAsCores` | `1` | `1` = friendly supply depots count as safe anchors (prevents islands/enclaves with depots from trying to evacuate across oceans). |

### How Sensitive Is Threat Detection? (`T_Neck` & `EnStr`)

| Variable | Default | What It Controls / How to Tune |
|---|---|---|
| `IdleEnemyPresenceWeight` | `0.25` | Weight on **idle** enemy troops sitting across the border. Lower (`0.1`) to ignore bigger quiet stacks; raise (`0.5`+) to panic earlier over unengaged enemy concentrations. |
| `ActiveEnemyAttackWeight` | `1.0` | Weight on enemy troops **actively attacking or marching** into us. |
| `ThreatenedNeighborStrWeight` | `1.0` | Weight on threat spilling inward from an already-collapsing neighbor province. |
| `InboundFriendlyStrWeight` | `0.5` | How much our **inbound reinforcing troops** count toward holding the neck (`0.0` = ignore marching help, `1.0` = count them at full value). |
| `NeckThreatMinRatio` | `1.0` | Enemy-to-friendly force ratio where danger **begins** (`1.0` = 1:1). Raise to `1.25` if the AI still flinches too easily; lower to `0.75` to react before parity is lost. |
| `NeckThreatRatio` | `1.5` | Force ratio where danger reaches **critical (`1.0`)**. Raise (`2.0`) to make the AI braver; lower (`1.3`) to make it withdraw sooner. |
| `NeckCollapsingOrgThreshold` | `10.0` | Org danger begins below `2x` this value (under `20` org in `Mods/E3mapToDHFull`) when defending in combat. Raise if low-org divisions hold too long. |
| `NeckThreatMinFloor` | `0.0` | Minimum `T` floor (`0.0` allows safe necks to stay at `0.000` quota). |
| `NeckThreatMaxCap` | `1.5` | Maximum `T` ceiling (also assigned to completely unguarded exposed bottlenecks). |
| `MultiExposedCutBonus` | `0.25` | Extra threat multiplier per additional exposed bottleneck (`+0.25` = +25% urgency per extra open flank). |
| `NeckThreatWeight` | `1.0` | Overall multiplier on `T_Neck` (`0.5` halves threat urgency across the board; `1.5` amplifies it). |

### Width, Value Hold & Cutoffs

| Variable | Default | What It Controls / How to Tune |
|---|---|---|
| `ExposedIntactPathCredit` | `0.5` | How much an exposed-but-still-holding bottleneck counts as an "open door" (`0.5` = half a door; raise to `0.75` to stay calmer before a flank breaks). |
| `WidthDeficitWeight` | `1.0` | Overall multiplier on `D_Width`. |
| `ValueRetentionVPWeight` | `1.0` | Value weight per Victory Point (`VP`) when calculating `V_Ret`. |
| `ValueRetentionICWeight` | `0.5` | Value weight per factory (`IC`) when calculating `V_Ret`. |
| `ValueRetentionScale` | `0.02` | How strongly VP/IC slows evacuation (`0.0` disables holding for VP/IC completely). |
| `ValueRetentionMinFloor` | `0.5` | Maximum discount from high VP/IC (`0.5` = at most cuts quota in half when bottlenecks aren't critical). |
| `ThreatenedSourceQuotaFloor` | `0.85` | Minimum quota when the province itself is already collapsing (`IsThreatened = 1`). |
| `MinEvacuationQuotaThreshold` | `0.05` | Noise filter: any final quota below this threshold snaps cleanly to `0.000`. |
| `BottleneckDefenseBoost` | `3.5` | Extra divisions requested/held at a bottleneck province when `AggNeckQuota = 1.000` (applies to both frontline and interior bottlenecks). |
| `BottleneckQuotaAggregation` | `0` | How multiple evacuating provinces sharing the same bottleneck combine into `AggNeckQuota`: `0 = MAX`, `1 = AVERAGE`, `2 = MIN`. |

*(Remember: changing `db/mod_settings.ini` requires restarting Darkest Hour because settings are read once on startup.)*
