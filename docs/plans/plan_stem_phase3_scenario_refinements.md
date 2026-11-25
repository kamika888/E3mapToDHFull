# Plan: STEM Phase 3 -- Allied Output Isolation, Supply-Core Proximity Gate, Sink Capacity Fix & Per-Division Terrain Defense Scaling

**Status:** Stages 1--2 Implemented & Built (Awaiting User Validation); Stage 3 Proposed (`Cave: 9,680 instructions, 29,562 bytes`, `SHA256 = 940D7F15B34F6B80775AA2EC1E9654141656CD6E9E72E26DE91E008809077A1C`)  
**Target Binary:** `Darkest Hour_modified.exe` (Darkest Hour v1.05.2, Base `0x00400000`)  
**Prerequisite:** [plan_stem_phase2_refinements.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_phase2_refinements.md) (Stages 1--6 Completed & Validated)  
**Companion Reference Docs:**  
- [front_ai.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/engine/front_ai.md)  
- [stem_testing_guide.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/stem_testing_guide.md)  
- [stem_debug_columns.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/stem_debug_columns.md)

---

## 1. Executive Summary & Live 1936 `CHC` Case Study

Live testing against the 1936 E3Map scenario (`CHC` -- Communist China in Shaanxi/Gansu) surfaced **three compounding STEM deficiencies** visible directly in `stem_debug.csv`:

```text
CountryTag;ProvID;ProvName;Dist;IsThreatened;F_Paths;F_Exp;F_Crit;CutProv1;CutProv2;V_Ref;EvacDestNeck;FrStr;EnStr;InbStr;VP_IC_Val;D_Width;T_Neck;V_Ret;SalientEvacuationQuota;NormAIPrio;AdjAIPrio;IsBottleneck;AggNeckQuota;FinalAIPrio;TargetStayDivs;StayingDivs;EvacDivBudget;StatusFlags;EvacMult
CHC;1270;Yanan;0;0;3;0;0;0;0;1270;0;7.9;16.7;0.0;1.3;0.000;0.20;1.000;0.000;1.5;1.5;1;1.000;5.6;0;0;0;0;0.20
CHC;1271;Shenmu;2;0;2;2;2;1270;5570;5570;5571;3.6;3.1;0.0;1.3;1.000;1.95;1.000;0.502;1.0;0.8;0;0.000;0.0;0;0;0;0;0.20
CHC;5554;Qingyang;2;0;2;2;2;5571;1270;5571;1270;3.4;3.6;0.8;0.1;1.000;1.95;1.000;0.502;1.0;0.8;0;0.000;0.0;0;0;0;0;0.20
CHC;5569;Dingbian;2;0;2;2;2;1270;5571;5571;1270;3.4;3.6;0.8;1.3;1.000;1.95;1.000;0.502;2.0;1.6;0;0.000;0.0;2;1;0;0;0.20
CHC;5570;Fuxian;1;0;2;2;1;1270;5571;1270;1270;7.9;16.7;0.0;1.3;1.000;1.95;0.973;0.502;2.0;1.6;0;0.000;0.0;2;2;0;0;0.20
CHC;5571;Suide;1;0;2;2;2;1270;5570;5570;0;3.6;3.1;0.0;2.4;1.000;1.95;1.000;0.000;2.0;2.0;1;0.502;4.4;0;0;0;0;0.20
CHC;5572;Dali;1;1;1;1;1;1270;0;1270;1270;7.9;16.7;0.0;1.2;1.000;1.95;1.000;0.502;0.5;0.4;0;0.000;0.0;0;0;0;0;0.20
```

These telemetry rows expose four distinct underlying causes (organized into three clean implementation stages):

1. **Cross-Country Allied/Access Overwrite Bug (`EvacMult = 0.20` vs. `SalientEvacuationQuota = 0.502`)**:
   - `CHC` (tag index `25`) evaluates its provinces using `local_flags = { stem_evac_modifier = 20 }` (`0.20x`), sets `quota_q8` (`+0x40000`) to `0.200`, and writes `EvacMult = 0.20` and `AdjAIPrio = 1.6` to telemetry (`m_pController == pCountry` guarded).
   - Later in the same hourly tick, allied/military-access tags with higher tag indices (`U58`, `SIK`) run `Cave_STEM_UpdateGraphTable`, traverse `CHC`'s provinces via `.hlp_check_ctrl` (`0x0044A690`), and overwrite the **shared global per-province output arrays** (`+0x40000` `quota_q8`, `+0x42000` `agg_neck_quota`, `+esi*8 + 2` `neck`, `+esi*8 + 4` `is_cut`, `+0xEC000` `prov_status_flags`) with the partner's `GlobalEvacuationMultiplier = 0.502` and `F_Paths = 0` pocket evaluation!
2. **Option C Sink-Saturation Bug (`CutProv1 = 1270 Yanan` on `Dist = 1` & `Dist = 2`)**:
   - Option C max-flow currently marks `Dist == 0` supply sinks (`1270 Yanan`, the Capital) as vertex-saturated after `1` path and extracts `1270` as `CutProv1`. This falsely reduces `F_Paths` (`5570 Fuxian` and `5569 Dingbian` drop below `3`), evaluates `T_Neck` on the exposed capital border (`16.7 / (7.9 * 1.45) = 1.46 -> 1.95`), and orders perimeter mountain tiles to **evacuate into `1270 Yanan`**, collapsing the capital's own defensive ring.
3. **Missing Supply-Origin Proximity Gate (`MinSupplyCoreEvacDist`)**:
   - Even without sink saturation, provinces `1` hop from a true Capital or active Supply Depot (e.g., `5572 Dali`) have a direct 1-step fallback into the supply core with no intermediate neck to sever. Standard combat retreat already covers losing a battle at the perimeter.
4. **Terrain Defense Blind Spot for Partisan Nations & Specialized Units (`Event 9000081`)**:
   - Event `9000081` (`db/events/generic_decisions_rel.txt`) gives `CHC` massive terrain-dependent modifiers (`mountain_defense = +1000`, `jungle_defense = +1000`, `swamp_defense = +1000`, `forest_defense = +500`, `desert_defense = +100`, `plain_defense = -100`, `hill_defense = -60`, `urban_defense = -40`).
   - Meanwhile, different division types (`INF`, `MTN`, `MIL`, `ARM`, `GAR`, etc.) have different terrain modifiers in `db/units/modifiers.csv` (e.g., `DEF_MOUNTAIN` is `0%` for `MTN`, `-15%` for `MIL`, `-20%` for `INF`, `-80%` for `ARM`), so a single country-level lookup would misrepresent mixed stacks.

### Staging Overview

| Stage | Scope | Primary Mechanism & Config Keys |
| :--- | :--- | :--- |
| **Stage 1** | **Controller-Scoped Global Output Isolation** | Guard all clears/commits to persistent global per-province output arrays (`+0x40000`, `+0x42000`, `+esi*8 + 2`, `+esi*8 + 4`, `+0xEC000`) with `prov->m_pController == pCountry` while keeping allied traversal intact in per-pass scratch tables. Fixes `stem_evac_modifier` / `stem_no_evac` across all multi-country alliances. |
| **Stage 2** | **Unbounded Supply-Sink Capacity & Supply-Origin Proximity Gate** | **(2A)** Keep `Dist == 0` supply sinks unsaturated in Option C max-flow so the Capital cannot become a 1-capacity cut vertex (`CutProv1`). **(2B)** Track distance from **true Supply Cores** (`prov_flags & 0x04`, Capital / active Supply Depots only -- *not* the K-hop horizon) and clamp `SalientEvacuationQuota = 0.0` at `SupplyCoreDist <= MinSupplyCoreEvacDist` (`[FrontAI] MinSupplyCoreEvacDist = 1`). |
| **Stage 3** | **Per-Division Live Terrain Defense Scaling (`CDivision + 0x164`)** | Evaluate each division's own engine-cached terrain defense modifier `[pDiv + def_idx*4 + 0x164]` normalized against 1936 baseline `INF` (`INF_BaseDefMod[terrain]`), clamped to `[MinTerrainDefenseMultiplier, MaxTerrainDefenseMultiplier]` (`[FrontAI] MaxTerrainDefenseMultiplier = 3.0`), and apply it inside `.hlp_push_div_eff_str_eax` / `.hlp_calc_army_str_org`. |

> [!IMPORTANT]
> **Execution Rule:** Each stage should be implemented, verified via build / Capstone disassembly audit and `stem_debug.csv` inspection in-game, and signed off before proceeding to the next stage.

---

## 2. Verified Engine Structures & Offsets

All addresses and struct offsets below were verified directly against `Darkest Hour_original.exe` (`v1.05.2`, Base `0x00400000`) and `db/units/modifiers.csv`:

### 2.1 `CDivision::m_fCombatModifiers` (`[pDiv + 0x164]`)
- Verified in `CDivision` constructor/sync (`0x004FBA70`) and `CDivision::GetCombatStrength` (`0x005007DC..0x0050082E`), plus land combat resolution (`0x004C62B7..0x004C62EF`, `0x004C65DB`):
  - **`[pDiv + idx*4 + 0x164]`** (`float[51]`): Pre-computed runtime modifier array maintained by the engine on **every individual `CDivision` object**.
  - Index `idx` for **terrain defense** is mapped directly by `0x0044D660` (`CCountry::GetTerrainModifierIndex(terrainId, isAttacker)`), using `isAttacker = 0` (`eax = 0x1B .. 0x22`):

| `CProvince` Terrain ID (`[pProv + 0x254]`) | Terrain Name | `CDivision` Mod Index (`idx`) | Struct Offset (`pDiv + ...`) | Vanilla `INF` Baseline (`modifiers.csv`) | `INF_BaseDefMod` (`float`) | `.hlp_push_def_mult_eax` Baseline |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `0` | Clear / Plains | `0x1B` (`27`) | `+0x1D0` | `DEF_PLAIN = 5` | `+0.05f` | `1.00f` |
| `1` | Forest | `0x1C` (`28`) | `+0x1D4` | `DEF_FOREST = -7` | `-0.07f` | `1.25f` |
| `2` | Mountain | `0x1D` (`29`) | `+0x1D8` | `DEF_MOUNTAIN = -20` | `-0.20f` | `1.45f` |
| `3` | Desert | `0x1E` (`30`) | `+0x1DC` | `DEF_DESERT = -65` | `-0.65f` | `1.00f` |
| `4` | Marsh / Swamp | `0x21` (`33`) | `+0x1EC` | `DEF_SWAMP = -48` | `-0.48f` | `1.40f` |
| `5` | Hills | `0x1F` (`31`) | `+0x1E0` | `DEF_HILL = 4` | `+0.04f` | `1.20f` |
| `6` | Jungle | `0x20` (`32`) | `+0x1E4` | `DEF_JUNGLE = -58` | `-0.58f` | `1.50f` |
| `7` | Urban | `0x22` (`34`) | `+0x1F0` | `DEF_URBAN = -2` | `-0.02f` | `1.30f` |

- *(Note: `[pProv + 0x254]` `4 = Marsh/Swamp` maps to `idx = 0x21` (`+0x1EC`), while `5 = Hills` maps to `0x1F` (`+0x1E0`), `6 = Jungle` maps to `0x20` (`+0x1E4`), `3 = Desert` maps to `0x1E` (`+0x1DC`), `7 = Urban` maps to `0x22` (`+0x1F0`), matching `0x0044D674..0x0044D6D4` exact jump-table entries.)*
- Why `[pDiv + 0x164]` solves mixed unit types automatically:
  - The engine initializes and updates `[pDiv + idx*4 + 0x164]` from the defending division's own `unit_type` table inside its owner's `CCountry` (`[pCountry + 0x134D8]`, combining `modifiers.csv` unit baselines + researched techs/doctrines + `which = land` / `which = <unit_type>` event modifiers such as Event `9000081`) plus brigade contributions.
  - Evaluating it on `pDiv` handles **mixed stacks** (`MTN` + `INF` + `MIL` + `ARM`), **allied expeditionary forces** standing in the same province, and **event-modified partisan nations** identically with one uniform lookup.

---

## 3. Detailed Stage Specifications

### Stage 1: Controller-Scoped Global Output Isolation

#### 3.1 Root Cause & Scope
In `Cave_STEM_UpdateGraphTable`, `.hlp_check_ctrl` (`0x0044A690`) permits allied and military-access provinces to participate in `K`-hop strip discovery, `fdist` front-distance propagation, and max-flow escape routing. That traversal is **intentional** so allies provide escape corridors and necks across shared fronts.
However, several global arrays in `g_pGraphTable` are **persistent cross-country outputs** indexed globally by `prov_id` (`1..0x1F54`) and read later by `CFrontAI::MoveUnitsToFront` (`Hooks 7-11F`), combat retreat (`Hooks 12A-12C`), and `Cave_STEM_SyncTelemetryPrio`:
- `quota_q8` (`+0x40000`)
- `agg_neck_quota` (`+0x42000`) & `min_neck_quota` (`+0x44000`)
- `evac_hold_u8` (`+0xF0000`) & `prov_status_flags` (`+0xEC000`, specifically persistent hold/blacklist/supply bits `0x01`, `0x02`, `0x04`, `0x10`)
- `GraphNode.neck` (`+esi*8 + 2`) & `GraphNode.is_cut` (`+esi*8 + 4`)

Currently:
- `.ppa_loop` (`lines 948-950`) clears `+0x40000`, `+0x42000`, `+0x44000`, and `and`s `+0xEC000` for **every** province in the strip regardless of `prov->m_pController`.
- `.step5b_loop` (`line 1556`), `.hlp_apply_evac_mult_and_blacklist_esi` (`line 3070`), `.hlp_lock_neck_eax` (`line 3434`), `.chain_necks_loop` (`lines 2260-2261`), `.hlp_accum_cut_vertex` (`line 3466`), and `.s5e_fin_loop` (`lines 2623, 2643, 2647`) write directly to those shared arrays without verifying `prov->m_pController == pCountry` (`[pProv + 0x3D8] == [ebp - 8]`).
- When country `B` (e.g., `U58` or `SIK`) shares military access with country `A` (`CHC`) and runs later in country index order (`0..0x157`), `B` clobbers `A`'s live `quota_q8`, `neck`, `is_cut`, and `agg_neck_quota` using `B`'s `EvacMult` and `B`'s distant capital! Meanwhile `.hlp_write_telemetry` (`lines 4107-4111`) *does* check `m_pController == pCountry`, creating the exact mismatch `EvacMult = 0.20, AdjAIPrio = 1.6` alongside `SalientEvacuationQuota = 0.502`.

#### 3.2 Implementation Design
1. **Separate Working Scratch vs. Committed Global Outputs (or Guard All Output Writes)**:
   - Guard all clears/mutations of persistent global outputs (`+0x40000` `quota_q8`, `+0x42000` `agg_neck_quota`, `+0x44000` `min_neck_quota`, `+0xEC000` `prov_status_flags`, `+0xF0000` `evac_hold_u8`, `+esi*8 + 2` `neck`, and `+esi*8 + 4` `is_cut`) behind `prov->m_pController == pCountry`:
     - Cleanest zero-side-effect pattern for Intra-Pass Step 5B/5C/5E logic:
       - Let Step 5B/5C/5E compute the current pass's working `pass_quota[P]` / `pass_neck[P]` / `pass_iscut[P]` / `pass_agg_neck[P]` freely in scratch (or check `m_pController == pCountry` before touching persistent slots):
         - Actually, look closely: allied retreat routing (`Hook 12`) and unit-withdrawal (`Hook 9A`) ONLY act on provinces belonging to or defended by that country's `CFrontAI` (`m_pController == pCountry` or allied fronts), and telemetry checks `m_pController == pCountry`.
         - Even better: during `.ppa_loop`, only clear `+0x40000`, `+0x42000`, `+0x44000`, `+0xEC000` when `prov->m_pController == pCountry`.
         - Have Step 5B/5C/5E write `pass_neck`, `pass_iscut`, `pass_agg_neck` ONLY if `prov->m_pController == pCountry` -- OR if an interior neck `N` inside an ally's border needs chaining during `pCountry`'s own pass, keep per-pass working `neck` / `is_cut` / `agg_neck` in temporary tables (or expand `g_pGraphTable` / reuse transient buffers after Option C finishes) and commit to global `quota_q8` (`+0x40000`), `neck` (`+esi*8 + 2`), `is_cut` (`+esi*8 + 4`), `agg_neck_quota` (`+0x42000`), and `prov_status_flags` (`+0xEC000`) **strictly when `prov->m_pController == pCountry`**.
   - **Why temporary pass arrays + controller-gated commit is cleanest**:
     - If `CHC` and `SIK` have a bottleneck neck `N` lying on `CHC`'s side protecting a `SIK` salient province (or vice versa), guarding intra-pass `.chain_necks_loop` prematurely would break cross-border neck chaining *within* a pass, whereas committing outputs to persistent global arrays only where `prov->m_pController == pCountry` preserves full cross-border topological accuracy during each pass while guaranteeing **100% isolation** between countries' live outputs!
     - Wait: what about **Stage B cross-controller bottleneck lock vs. `quota_q8`?** Keeping per-country persistent outputs written exclusively by `prov->m_pController == pCountry` ensures `stem_evac_modifier`, `stem_no_evac`, `stem_soft_mode`, `quota_q8`, `EvacDestNeck`, and `IsBottleneck` can never be overwritten by an ally or military-access neighbor.
2. **Allied / Expeditionary Fronts Edge Case Check**:
   - Check how `CFrontAI::MoveUnitsToFront` interacts with allied fronts: when `pCountry` operates armies on an allied front (e.g., `CAN` troops under `ENG` front control or `U58` troops on `CHC` borders), if `U58` reads `quota_q8[P]` on a `CHC` province `P`, reading `CHC`'s own properly computed `quota_q8[P]` (with `CHC`'s own `stem_evac_modifier` and `CHC`'s own capital) is strictly *better* than `U58` smashing `CHC`'s `quota_q8[P]` with `U58`'s `F_Paths = 0` overwrite!

---

### Stage 2: Unbounded Supply-Sink Capacity & Supply-Origin Proximity Gate

#### 3.3 Part 2A -- Fix Option C Sink Saturation on `Dist == 0` Roots
- **Root Cause in `build_and_apply_all.py` (`lines 1369-1376`, `1450-1454`, `1508-1515`)**:
  - In Option C per-province max-flow, every province `v` has split vertices `2*v` (`v_in`) and `2*v + 1` (`v_out`) with unit vertex capacity `1`.
  - When `P` (`Dist == 1`) is directly adjacent to a `Dist == 0` sink `S` (`1270 Yanan`), `.optc_aug_at_src` sets `used[S] = pass` (`+0x2A000 = cl`).
  - On the next augmenting pass, `.optc_nb_from_src` sees `used[S] == cl` and `dist[S] == 0`, so it jumps to `.optc_src_mark_cut_node` and enqueues `2*S` without `2*S + 1`.
  - `.optc_extract_mincut` (`lines 1502-1515`) then extracts **`S` (`1270 Yanan`) itself** as `CutProv1`!
  - Consequences observed on `CHC`:
    1. `5570 Fuxian` (`Dist = 1`, bordering `1270 Yanan` directly AND `5571 Suide`) gets `CutProv1 = 1270`, `CutProv2 = 5571`, `F_Paths = 2`! Because `1270 Yanan` has adjacent enemies (`EnStr = 16.7, FrStr = 7.9`), `T_Neck` reaches `1.95` and `5570` evacuates **into `1270 Yanan`**.
    2. `5569 Dingbian` (`Dist = 2`, reaching `1270 Yanan` via `5570 Fuxian` AND via `5571 Suide`) gets bottlenecked at `CutProv1 = 1270` (`F_Paths = 2` instead of `2` separate paths terminating independently at sink `1270`). Even on larger nations, any `Dist = 2` pair sharing the Capital as their sole `Dist = 0` root erroneously scores `1270` as `CutProv1` and measures frontline enemy threat *on the Capital* as a cut!
- **Fix**:
  1. **True Infinite-Capacity Sinks (`Dist == 0`)**:
     - Do **not** set `used[S]` (`+0x2A000`) when `word ptr [edx + eax*8] == 0` at `.optc_aug_at_src` (`line 1451-1454`) -- only track per-pass duplicate direct-edge prevention (`P -> S`) so a direct `(P -> S)` edge isn't reused twice within the same `W`-path search for a single `P`, while other neighbors `u -> S` (from intermediate vertices `u`, or other paths) can freely enter `S` as an **unbounded sink**.
     - Practically: if `esi == src (P)` and neighbor `eax == S` has `dist[S] == 0`, simply track a tiny per-source bit/gen on `vis_gen[2*S + 1]` (`+0x2C000`) or `edge_used_to_sink[S] == cl` for *direct* `P -> S` jumps ONLY (checked only when `esi == src`), while leaving `used[S]` (`+0x2A000`) `0` for all intermediate `u != src` arrivals into `S`!
     - Never jump to `.optc_src_mark_cut_node` for `word ptr [edx + eax*8] == 0` (`line 1372-1373`), and add `cmp word ptr [edx + eax*8], 0; je .optc_cut_scan_loop` inside `.optc_cut_scan_loop` (`line 1510`) as an explicit safety guard so **no `Dist == 0` sink can ever be emitted as `CutProv1` or `CutProv2`**.

#### 3.4 Part 2B -- True Supply-Core Proximity Gate (`MinSupplyCoreEvacDist`)
- **Why Separate Supply-Core Distance from Generic `Dist`**:
  - In Pass-1 Safe BFS, two distinct sets of provinces receive `Dist = 0`:
    1. **True Supply Cores** (`Capital` when `IC > 0`, and active `Supply Depots` when `UseSupplyDepotsAsCores = 1`), already stamped with bit `0x04` (`prov_flags |= 6`) in `.mark_core_root`.
    2. **K-Hop Horizon Roots** (any friendly rear tile beyond `SalientSearchDepth`), stamped with bit `0x02` (`prov_flags |= 2`) only in `.fdist_mark_horizon_root`.
  - If we gated evacuation on generic `Dist <= 1`, a province `4` hops deep inside an exposed Barbarossa bulge (merely `1` hop inside the arbitrary `SalientSearchDepth = 5` cutoff) would falsely stop evacuating even though it is `15` hops from Berlin!
- **Design**:
  - Add a new `[FrontAI]` config parameter in `db/mod_settings.ini`:
    - **`MinSupplyCoreEvacDist = 1`** (integer, default `1`; range `0..10`; `0` disables proximity suppression).
  - Compute `core_dist[P]` (`uint16_t` or `uint8_t`, e.g., at `+0xF5000` or unused high bytes in `g_pGraphTable`):
    - If `MinSupplyCoreEvacDist > 0`: run a tiny BFS immediately after `.seed_c_init` seeded strictly from the **true Supply-Core roots (`prov_flags & 0x04`)** across unthreatened friendly `strip_provs`, stopping at `depth == MinSupplyCoreEvacDist`! (At `MinSupplyCoreEvacDist = 1`, this traverses `Dist = 0` true Supply Cores to their immediate `core_dist = 1` neighbors -- just 1 BFS frontier layer, microseconds of work! For `MinSupplyCoreEvacDist >= 2`, traversing safe unthreatened friendly tiles `byte ptr [edx + eax + 0x24000] == 0` ensures a threatened frontline tile at `core_dist = 2` behind a breached tile isn't exempted if its safe corridor is blocked.)
  - Whenever `core_dist[P] <= MinSupplyCoreEvacDist` (including `core_dist == 0` cores and `1..MinSupplyCoreEvacDist` ring):
    - Force `SalientEvacuationQuota(P) = 0.0` (and clear `EvacDestNeck(P) = 0`), while preserving `STATUS_BLACKLIST` or setting a dedicated `StatusFlags` bit (e.g., `Bit 5 (0x20) = STATUS_CORE_PROXIMITY`) so telemetry in `stem_debug.csv` clearly explains why `5570 Fuxian` (`Dist = 1`) and `5572 Dali` (`Dist = 1`) have `SalientEvacuationQuota = 0.000`!
  - **Edge Case (`F_Paths == 1` vs `F_Paths == 2` at `core_dist = 1`)**: Wait -- what if `5572 Dali` borders enemies (`IsThreatened = 1`) and is `1` hop from `1270 Yanan`? If `Dali` eventually loses its battle, vanilla / Patch 18 `SelectRetreatProvince` (`Hooks 12A-12C`) immediately retreats its surviving divisions `1` hop directly into `1270 Yanan` (`Dist = 0` safe core!). Keeping `SalientEvacuationQuota = 0.0` ensures AI doesn't pre-emptively abandon the perimeter mountain fortress around the capital before combat is even lost.

---

### Stage 3: Per-Division Live Terrain Defense Scaling (`CDivision + 0x164`)

#### 3.5 Why Not Country-Level Lookups Alone?
- In Darkest Hour, `CCountry` maintains a `[unit_type][modifier_slot]` table (`0x134D8`), NOT a single per-terrain scalar. Even for a single nation:
  - Mountaineers (`MTN`) have `DEF_MOUNTAIN = 0%`, Militia (`MIL`) `-15%`, Infantry (`INF`) `-20%`, Armor (`ARM`) `-80%`.
  - Garrison (`GAR`) has `DEF_URBAN = +10%`, Infantry (`INF`) `-2%`, Armor (`ARM`) `-20%`.
  - Events (like `9000081`), doctrines, and techs shift specific unit classes or all land units by arbitrary percentages, and allied/expeditionary units fighting in the same province carry their own owner country's tech/event modifiers.

#### 3.6 Engine-Native Per-Division Normalization Architecture
Instead of guessing a single country average or hardcoding `local_flag = partisan_mode`, we compute each defending/inbound division's exact **Relative Unit & Country Terrain Defense Factor** directly inside `.hlp_push_div_eff_str_eax` during Pass 0:

1. **Formula (Executed per Division `pDiv` for Target Province `P`)**:
   - Let `eff_base = (Strength / 100.0) * OrgFactor * HardnessFactor` (unchanged Stage 2 formula).
   - If a valid target province `P` (`1..0x1F54`) is supplied:
     - Read province terrain `T = [GetProvince(P) + 0x254]` (`0..7`).
     - Map `T -> div_mod_idx` (`0x1B..0x22`, identical to `0x0044D660` with `isAttacker = 0`):
       - `0 (Plain) -> 0x1B`, `1 (Forest) -> 0x1C`, `2 (Mountain) -> 0x1D`, `3 (Desert) -> 0x1E`, `4 (Swamp) -> 0x21`, `5 (Hills) -> 0x1F`, `6 (Jungle) -> 0x20`, `7 (Urban) -> 0x22`.
     - Read the division's live defense modifier: `div_def = float [pDiv + div_mod_idx*4 + 0x164]`.
     - Look up standard 1936 Infantry baseline (`INF_BaseDefMod[T]` from `db/units/modifiers.csv`):
       - Plain `+0.05`, Forest `-0.07`, Mountain `-0.20`, Desert `-0.65`, Swamp `-0.48`, Hills `+0.04`, Jungle `-0.58`, Urban `-0.02`.
     - Compute relative factor:
       $$\text{DivTerrainFactor} = \text{clamp}\big(1.0 + (\text{div\_def} - \text{INF\_BaseDefMod}[T]),\; 0.35,\; \text{MaxTerrainDefenseMultiplier}\big)$$
     - Multiply `eff_base *= DivTerrainFactor`.
   - When `P == 0` (used for **hostile** armies in `.scan_hostile_armies`, whose province-defense multipliers are applied on the defender via `.hlp_push_def_mult_eax`): `DivTerrainFactor = 1.0`.
   - **Important Check on Inbound Friendly Armies (`.friendly_check_inbound`)**:
     - Pass the **destination province `ecx`** (where the reinforcing corps is marching, from `[[edi + 0x232]]`), NOT its source province, so a mountaineer marching into a mountain bottleneck gets its mountain bonus at the neck while armor marching into a mountain bottleneck does not inflate `InbStr`!

2. **Worked Examples Showing Exact Behavior**:
   - **Standard 1936 `INF` in Mountains** (`div_def = -0.20`):
     `DivTerrainFactor = 1.0 + (-0.20 - (-0.20)) = 1.00x`. Combined with `.hlp_push_def_mult_eax(Mountain) = 1.45x`, total multiplier stays **`1.45x`** (zero regression on normal fronts!).
   - **1936 `MTN` vs `ARM` in Mountains**:
     - `MTN` (`div_def = 0.00`): `DivTerrainFactor = 1.0 + (0.00 - (-0.20)) = 1.20x` (effectively `1.20 * 1.45 = 1.74x`).
     - `ARM` (`div_def = -0.80`): `DivTerrainFactor = 1.0 + (-0.80 - (-0.20)) = 0.40x` (effectively `0.40 * 1.45 = 0.58x` -- STEM recognizes armor cannot hold a mountain neck!).
   - **`CHC` with Event `9000081` (`partisan_mode`)**:
     - **Mountain** (`+1000%`, `div_def = +9.85`): `1.0 + (9.85 - (-0.20)) = 11.05` -> clamped to `MaxTerrainDefenseMultiplier = 3.0x`. Combined with `.hlp_push_def_mult_eax(Mountain) = 1.45x`, `CHC`'s `7.9` Yan'an force evaluates as `7.9 * 3.0 = 23.7` `FrStr` (`* 1.45 = 34.4` effective defense), turning `16.7 / 34.4 = 0.49 <= NeckThreatMinRatio (0.80)` -> `T = 0.20` instead of `1.46 -> 1.95`!
     - **Plains** (`-100%`, `div_def = -0.95`): `1.0 + (-0.95 - 0.05) = 0.00` -> clamped to floor `0.35x`, accurately flagging partisan vulnerability in open plains!

3. **New `[FrontAI]` INI Key**:
   - **`MaxTerrainDefenseMultiplier = 3.0`** (float, default `3.0`, valid floor clamp `>= 1.0`): Caps the per-division relative terrain defense multiplier (`DivTerrainFactor`) so extreme scripted bonuses (like `+1000%` partisan modifiers) strongly suppress false panic without making a 1-division stack completely immune to overwhelming force (e.g., 25:1 attacks).

4. **Exact `AggNeckQuota` Threat-Sustaining Neck Floor Conversion via `AvgDivFrStr[esi]` (`.s5e_fin_threat_floor`, lines 2650-2703)**:
   - Because `FrStr` (`+0x60000`) and `InbStr` (`+0x70000`) directly include `DivTerrainFactor(pDiv, T_target)`, `stem_debug.csv` displays the final terrain-adjusted effective strength values used by `.hlp_eval_cut_threat` (`T_Neck`), making telemetry ratios directly transparent.
   - In `.hlp_eval_cut_threat`, `T_str(esi)` reaches `0.0` when total friendly neck strength satisfies:
     `Required_FrStr[esi] = EnStr[esi] / (max(0.05, NeckThreatMinRatio) * DefMult(esi))`
     where `DefMult(esi)` is `.hlp_push_def_mult_eax(esi)` (`BaseTerrainMult + FortBonus`).
   - Because `Required_FrStr[esi]` is in **`FrStr` units** while `NormAIPrio[esi]` and `avg_divs * BottleneckDefenseBoost` are in **physical division counts**, `.s5e_fin_threat_floor` converts `Required_FrStr[esi]` to physical divisions using `AvgDivFrStr[esi]` (average `FrStr` per physical division at `esi`):
     - During Pass 0 friendly army scanning, accumulate physical division count `prov_div_count[P]` (`uint16_t`) alongside `FrStr[P]` and `InbStr[P]`.
     - If `prov_div_count[esi] > 0` and `FrStr[esi] + InbStr[esi] > 0.05`:
       `AvgDivFrStr[esi] = (FrStr[esi] + InbStr[esi]) / prov_div_count[esi]`
       (automatically capturing the bottleneck stack's exact average `DivTerrainFactor`, `OrgFactor`, `HardnessFactor`, and `Strength/100`).
     - If `prov_div_count[esi] == 0` (empty bottleneck province):
       `AvgDivFrStr[esi]` falls back to the province controller's baseline Infantry `DivTerrainFactor(pCountry, T_esi)` from `[pCountry + 0x134D8]`.
     - Final physical division requirement and floor quota:
       `Required_Divs[esi] = Required_FrStr[esi] / max(0.20, AvgDivFrStr[esi])`
       `Q_floor[esi] = clamp((Required_Divs[esi] - NormAIPrio[esi]) / (avg_divs * BottleneckDefenseBoost), 0.0, 1.0)`
   - This guarantees exact equilibrium between `.hlp_eval_cut_threat` (`T_Neck`) and `.s5e_fin_threat_floor` (`AggNeckQuota`): stationing `Required_Divs[esi]` physical divisions produces `Required_Divs[esi] * AvgDivFrStr[esi] = Required_FrStr[esi]`, keeping `T_str(esi) == 0` without over- or under-allocating bottleneck defenders.

---

## 4. `db/mod_settings.ini` Additions & Binary Budget

| Config Key (`[FrontAI]`) | Type | Default | Used In | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| `MinSupplyCoreEvacDist` | `int` | `1` | Stage 2 | Provinces within `<= N` friendly hops of a true Capital or active Supply Depot (`prov_flags & 0x04`) force `SalientEvacuationQuota = 0.0` (`0` disables). |
| `MaxTerrainDefenseMultiplier` | `float` | `3.0` | Stage 3 | Upper cap for per-division relative terrain defense multiplier `DivTerrainFactor` read from `[pDiv + 0x164]` (`floor = 0.35`). |

- **Cave & `g_pGraphTable` Allocation Status**:
  - `.mod` section ends at `0x00DD9000`. Current built cave usage (`9,680` instructions, `29,562` bytes) leaves ample contiguous free executable space for Stage 3 with zero PE section growth required.
  - Stages 1--2 expanded `g_pGraphTable` across all 5 `VirtualAlloc` call sites from `0x128000` (`1,184 KB`) to **`0x130000` (`1,216 KB`)**, adding `+0x128000` (`pass_quota_q8`), `+0x12A000` (`pass_agg_neck_quota`), `+0x12C000` (`pass_status_flags`), and `+0x12E000` (`core_dist`).

---

## 5. Verification Plan

After each stage is built and deployed via `build_and_apply_all.py` and `patch_darkest_hour.bat -Verify`:
1. **Stage 1 Verification**:
   - Inspect `CHC` (with `stem_evac_modifier = 20`) and `U58` / `SIK` in `stem_debug.csv`: `SalientEvacuationQuota` on `CHC` must now scale by `0.20` (not `0.502`), and toggling `stem_evac_modifier` must synchronously change both `EvacMult` and `SalientEvacuationQuota`.
2. **Stage 2 Verification**:
   - Remove temporary `stem_evac_modifier = 20` override or leave default: verify `CutProv1` on `5570 Fuxian`, `5572 Dali`, and `5569 Dingbian` no longer equals `1270 Yanan`, and with `MinSupplyCoreEvacDist = 1`, verify `5570 Fuxian`, `5571 Suide`, and `5572 Dali` (`core_dist == 1`) have `SalientEvacuationQuota = 0.000` (while a deep salient `> 1` hop from supply origins still evacuates normally).
3. **Stage 3 Verification**:
   - With `CHC` Event `9000081` active (`partisan_mode`), inspect `FrStr` and `T_Neck` in `stem_debug.csv`: mountain `FrStr` scales up (`3.0x` cap), bringing `T_Neck` down into the safe range (`0.20..0.50`) so `5569 Dingbian`, `1271 Shenmu`, and `5554 Qingyang` no longer panic-evacuate, while open plains/desert fronts retain low/penalized strength multipliers and mixed `MTN` / `INF` / `ARM` stacks on normal fronts differentiate accurately.
