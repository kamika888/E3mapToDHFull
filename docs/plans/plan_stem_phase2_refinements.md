# Plan: STEM Phase 2 -- Country Controls, Combat Power Realism, Supply Lifelines, Density-Scaled Boosts & Anti-Flicker Hysteresis

**Status:** In Progress (Stage 1--2 Completed & Validated; Stage 3 Implemented -- Awaiting User Validation; Stages 4--6 Pending)  
**Target Binary:** `Darkest Hour_modified.exe` (Darkest Hour v1.05.2, Base `0x00400000`)  
**Prerequisite:** [plan_stem_strategic_defense.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_strategic_defense.md) (Stages 1--5 Completed & Validated)  
**Companion Reference Docs:**  
- [front_ai.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/engine/front_ai.md)  
- [movement_and_orders.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/engine/movement_and_orders.md)  
- [stem_testing_guide.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/stem_testing_guide.md)  
- [stem_debug_columns.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/stem_debug_columns.md)

---

## 1. Executive Summary & Scope

Following the completion and in-game validation of Stages 1--5 of the original [STEM Strategic Defense Plan](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_strategic_defense.md), this Phase 2 plan addresses **10 targeted gameplay, realism, and control refinements** organized into **6 individually testable stages**:

1. **Country-Wide Withdrawal Propensity Modifier (Backward-Compatible via `local_flags`)**: Per-country multiplier on `SalientEvacuationQuota(P)` controlling how readily a nation withdraws from threatened salients versus fighting to the death (`stem_evac_modifier`, `stem_no_evac`).
2. **Country-Wide "Soft STEM" Mode Switch (`local_flags`)**: Per-country switch (`stem_soft_mode = 1`) where STEM adjusts `CFrontAI` priorities (`AdjAIPrio`, `FinalAIPrio`, bottleneck boosts) without launching forced evacuations, army splits, or auto-retreats.
3. **Manual Per-Province Evacuation Blacklist (`front = { province_priorities = { ... } }`)**: Allows AI files to blacklist specific strategic fortresses or peninsulas (e.g., Leningrad `187`, Kola/Murmansk) from STEM evacuation using `front.province_priorities` (`[[pCountry + 0x120] + 0x990]`), while also fixing a vanilla `CFrontAI` bug where `province_priorities` was omitted from Loop B donor calculations (`0x0068470D` and `0x0068526A`).
4. **Alternative Supply Lifelines Over Impassable Connections (`adj->type == 4`) & Direct Sea Access**: Recognizes incoming supply across impassable connections from friendly safe/unthreatened provinces (e.g., Lake Ladoga `189 Kirisi <-> 7003 Kir'jasaly` supplying `187 Leningrad`) and direct coastal sea access (`[pProv + 0x3DC] > 0`, `m_nPortSeaZone`) so supplied pockets reduce evacuation urgency (`SalientEvacuationQuota`) without treating impassable edges as land march routes or running a separate global BFS.
5. **Direct Organization (`ORG`) Weighting in `FrStr`, `EnStr`, and `InbStr`**: Integrates division organization (`[pDiv + 0xF4]` relative to runtime effective max org from `[pDiv + 0xF8]` scaled by `[pCountry->0x244 + 0x3E]` and `CCountry::GetUnitModifier` @ `0x0044C830`) directly into idle, active, and inbound strength calculations (`OrgWeight = 0.85`), removing the legacy active-combat `MinOrg` / `T_org` mechanism while keeping Pass 0's `NeckCollapsingOrgThreshold` `IsThreatened` check.
6. **Division Softness / Hardness Weighting in `FrStr`, `EnStr`, and `InbStr`**: Factors division softness (`[pDiv + 0x2D4]` `m_fSoftness` $\in [0, 100]$) into unit combat power (`HardnessWeight = 0.85`) so hard/armored divisions are weighted significantly higher than militia or soft infantry.
7. **Front-Density Scaling for `BottleneckDefenseBoost`**: Scales the number of divisions requested to reinforce a bottleneck (`EffectiveBottleneckBoost(B)`) with both salient threat (`UpstreamThreat(B)`) and the front's actual division density ($\rho_{\text{front}} = D_{\text{front}} / N_{\text{front\_provs}}$), plus a maximum front-share cap, so a 20-division front is not drained by a 10-division boost while a 500-division front commits realistic operational reserves.
8. **Withdrawing to Threatened Bottlenecks & Adjacent `Support Defence` (`mission_type = 4`)**: Allows evacuating units to withdraw toward bottleneck provinces even when the bottleneck itself is marked `IsThreatened == 1`, and orders withdrawing armies in provinces **adjacent** to an **actively attacked** bottleneck (`[pProv(N) + 0x24C] != 0`) to execute **`Support Defence`** (`CMission::OrderMission` @ `0x0050B600`, `mission_type = 4`) instead of a standard move so they immediately reinforce the defensive battle for the neck.
9. **Anti-Flicker / Hysteresis on Attacked Bottlenecks (`IsThreatened = 1 -> 0` Oscillation)**: Prevents newly arriving reinforcements at an attacked bottleneck from briefly flipping `IsThreatened` from `1 -> 0` for a few hours and causing evacuating troops to cancel their withdrawal mid-march or march back into the salient.
10. **Gate `stem_debug.csv` on `extra_debug_logs >= 1`**: Only generates `stem_debug.csv` on save when `settings.cfg` line 9 (`Extra debug logs`, stored at `byte ptr [0x00DC4B5E]`) is set to `1` or greater.

### Staging Overview

| Stage | Items Covered | Focus & Primary Verification |
| :--- | :--- | :--- |
| **Stage 1** | **#10, #1, #2, #3** (+ `.mod` 64 KB & `g_pGraphTable` 1184 KB expansion) | PE `.mod` expansion (`32 KB -> 64 KB`), `VirtualAlloc` (`0xEC000 -> 0x128000`), `extra_debug_logs` gate for `stem_debug.csv`, country `local_flags` (`stem_evac_modifier`, `stem_no_evac`, `stem_soft_mode`), and `front.province_priorities` evacuation blacklist + two-stage Loop A/B pre/post-STEM normalization fix (`Hook 8D`). |
| **Stage 2** | **#5, #6** | Direct Organization (`[pDiv + 0xF4]` / runtime `[pDiv + 0xF8]` + modifiers) and Softness/Hardness (`[pDiv + 0x2D4]`) weighting in `.hlp_push_div_eff_str_eax` / `.hlp_calc_army_str_org` / `Hook 9A` across `FrStr`, `InbStr`, `EnStr`, and `EnInbStr`; removal of legacy `MinOrg` / `T_org` (preserving Pass 0 `NeckCollapsingOrgThreshold`). |
| **Stage 3** | **#4** | Alternative supply lifeline detection: direct sea access (`[pProv + 0x3DC] > 0`) in `.ppa_loop` and endangered-pocket-only `.hlp_mark_impassable_supply` over `adj->type == 4` (`Impassable`, e.g. `189 <-> 7003`), reducing `SalientEvacuationQuota(P)` for supplied pockets. |
| **Stage 4** | **#7** | Front-density scaling ($\rho_{\text{front}} = D_{\text{front}} / N_{\text{front\_provs}}$) and max-front-share cap for `EffectiveBottleneckBoost(B)` across `Cave_STEM_UpdateGraphTable` and `CFrontAI::MoveUnitsToFront` (`Hooks 7B, 8A--8C, 9A`). |
| **Stage 5** | **#9** | Three-layer anti-flicker hysteresis: (a) attacked-bottleneck `IsThreatened` hold timer (`threat_hold_u8`), (b) evacuation quota re-entry cooldown (`evac_hold_u8`), and (c) in-progress withdrawal march commitment in `.uae_p1_noncombat_locked`. |
| **Stage 6** | **#8** | Allow threatened bottlenecks (`IsThreatened == 1`) as valid withdrawal rally necks (`EvacDestNeck`), and dispatch `Support Defence` (`0x0050B600`, `mission_type = 4`) when a withdrawing army is adjacent to an actively attacked bottleneck (`[pProv + 0x24C] != 0`). |

> [!IMPORTANT]
> **Execution Rule:** Each stage must be implemented, verified via build / patch integrity / static Capstone disassembly checks and manual in-game testing by the user, and explicitly approved by the user before proceeding to the next stage.

---

## 2. Verified Engine Architecture & Struct Offsets

All offsets below were verified directly against `Darkest Hour_modified.exe` (`v1.05.2`):

### 2.1 `.mod` PE Section Expansion (`32 KB -> 64 KB`)
- Current `.mod` section: `VirtualAddress = 0x00DC9000` (RVA `0x009C9000`), `VirtualSize = 0x8000` (`32,768` bytes, up to `0x00DD1000`), `PointerToRawData = 0x00484000`, `SizeOfRawData = 0x8000`.
- Patch 18 currently occupies `0x00DCBAB0..0x00DD0C6A` (`20,922` bytes), leaving `918` bytes before `0x00DD1000`.
- Because `.mod` is the **final section** in the PE image, expanding `.mod` from `0x8000` (`32 KB`) to **`0x10000` (`64 KB`, `0x00DC9000..0x00DD9000`)** requires only:
  1. Updating `OptionalHeader.SizeOfImage` at file offset `0x00000150` from `0x009D1000` to `0x009D9000`.
  2. Updating `.mod` `VirtualSize` at file offset `0x000002A0` from `0x00008000` to `0x00010000`.
  3. Updating `.mod` `SizeOfRawData` at file offset `0x000002A8` from `0x00008000` to `0x00010000`.
  4. Appending `0x8000` (`32,768`) zero bytes to the end of the file (`4,767,744 -> 4,800,512` bytes).
- This unlocks **`33,686` bytes** (`0x00DD0C6A..0x00DD9000`) of contiguous executable/writable space for Phase 2.

### 2.2 `extra_debug_logs` Setting Global (`Item 10`)
- Verified in `settings.cfg` loader (`0x007926BA..0x007926F7`):
  - Line 9 of `settings.cfg` (`Extra debug logs (savedebug.txt): 0 = disabled, 1 = enabled, 2 = enabled + extra map statistics`) is converted via `atoi` (`0x007A7B3C`) into local stack slot `dword ptr [ebp - 0xCE0]`.
  - When that value is `1` (`0x007926D9`) or `2` (`0x007926E9`), the engine sets **`byte ptr [0x00DC4B5E] = 1`** (and for `2`, also `byte ptr [0x00DC4B5F] = 1`). When `0`, `byte ptr [0x00DC4B5E]` remains `0`.

### 2.3 Country `local_flags` Dictionary (`Items 1 & 2`)
- Verified in `Patch 6 Ext` (`0x00DCA13C`) and `docs/event commands.txt` (`L294--298`):
  - Given `pCountry` (`dword ptr [0x0089CAD8 + tag*4]`), `eax = dword ptr [pCountry + 0x120]` is the country AI/flags sub-object.
  - `ecx = eax + 0x4C` is the `CLocalFlags` dictionary (`this` pointer).
  - Calling `push szFlagName; mov edx, [ecx]; call dword ptr [edx + 4]` (`__thiscall` `CLocalFlags::GetFlag(ecx, const char*)`) returns `eax = pFlagEntry` (or `0` if unset).
  - When `eax != 0`, **`movsx eax, word ptr [eax + 0x100]`** reads the signed 16-bit integer value stored by `local_setflag` or scenario/savegame `local_flags = { flag_name = N }`!
  - **Engine Quirk (`docs/event commands.txt` L295)**: In DHFScript, `command = { type = local_setflag which = X value = 0 }` translates `0` into `1`, whereas `command = { type = local_clrflag which = X }` sets the value to `0` (unset). Our flag encoding in Stage 1 explicitly accounts for this quirk.

### 2.4 `front = { province_priorities = { ... } }` Linked List (`Item 3`)
- Verified in `CFrontAI::MoveUnitsToFront` (`0x00684529..0x00684550`):
  - Given `pCountry`, `eax = dword ptr [pCountry + 0x120]`, **`[eax + 0x8FC]`** (`[ebp - 0x88]`) is the `front` AI sub-struct, and **`dword ptr [eax + 0x990]`** (`[ebp - 0x88] + 0x94`) is the head pointer of the `front.province_priorities` linked list.
  - Each node `pNode` has:
    - `pEntry = dword ptr [pNode + 0]`
      - `dword ptr [pEntry + 0]` (`uint32_t`): `province_id`
      - `dword ptr [pEntry + 4]` (`float`): `priority_value`
    - `pNext = dword ptr [pNode + 8]`
  - **Vanilla Bugs Discovered at `0x00684529..0x00684550`, `0x0068470D`, `0x0068526A`, and Loop A**:
    - Vanilla applies `front.province_priorities` **only** at `0x0068454A` (`fmul dword ptr [ecx + 4]`) **after** dividing by the retail front denominator `[ebp - 0x28]` (`0x00684526`), completely omits it on both **donor** share sites (`0x0068470D` and `0x0068526A`), and ignores it in **Loop A** (`0x00684088`).
    - Because denominator `[ebp - 0x28]` (and `[ebp - 0x14]` in `even` mode) is never re-normalized for `front.province_priorities`, bumping a province (e.g. `6516 = 9.0`) inflates `sum(NormAIPrio) > D_front` while leaving every other province at `100%` of its original target -- creating zero donatable surplus on the rest of the front! In Stage 1, Hook 8D (`0x00684474`) performs proper pre-normalization with `max_stack` water-filling across all 5 distribution modes, and Hooks 7A/7B/7D integrate `front.province_priorities` into Loop A.

### 2.5 `CDivision` Strength, Organization, Effective Max Organization & Softness (`Items 5 & 6`)
- Verified in `CDivision` org calculation (`0x004FF8E8..0x004FF931`, `0x00504102..0x00504145`) and `CDivision::AttachBrigade` (`0x005003C0..0x00500560`):
  - `[pDiv + 0xEC]` (`float`): `m_fStrength` (current strength, `0.0..100.0`).
  - `[pDiv + 0xF4]` (`float`): `m_fOrganization` (current organization, `0.0..100.0+`).
  - `[pDiv + 0xF8]` (`float`): `m_fMaxOrganization` (division base max organization), multiplied at runtime by country modifiers **`[[pDiv + 0x5C] + 0x244] + 0x3E`** and **`CCountry::GetUnitModifier([pDiv + 0x5C], pDiv, 2)` (`0x0044C830`)** to form `eff_max_org` (matching `CDivision` @ `0x004FF8E8`).
  - `[pDiv + 0x2D4]` (`float`): `m_fSoftness` (`softness`, updated at `0x00500450` from unit/brigade `[stats + 0x4C]`, clamped against `[0x00DC1744]`, e.g., `100.0` for militia/infantry, `70.0..85.0` for motorized/mechanized, `20.0..35.0` for armor).

### 2.6 `CProvince` Adjacency Types, Coastal Ports, Naval Bases & Supply (`Item 4`)
- Verified in `CProvince` (`stride = 0x4B2` from `dword ptr [0x00AB27B4]`):
  - **Adjacency List (`[pProv + 0x298]`)**: Each node's entry `pAdj = [pNode + 0]` has:
    - `[pAdj + 0x00]` (`uint32_t`): neighbor `prov_id`.
    - `[pAdj + 0x04]` (`uint32_t`): connection `type` (`0` = normal land, `1` = river, `2` = strait/sea-crossing, `4` = `Impassable` in `map/Map_3/adj-defs.csv`, e.g. `7003;189;Impassable;0;` across Lake Ladoga).
    - Darkest Hour blocks land unit movement across `type == 4`, **but traces supply across `type == 4` connections**.
  - **Direct Sea-Zone Exit Offset (`Item 4`, Simplified in Stage 3)**:
    - `[pProv + 0x3DC]` (`int32_t`): `m_nPortSeaZone` (`> 0` if province has direct coastal port/sea-zone exit; verified against all `1,960` coastal provinces in `map/Map_3/Province.csv` with `0` non-ocean false positives; also verified at `0x00432627`, `0x0044AFBD`, `0x004CA49D`). *(Note: `[pProv + 0x1E2]` is Naval Base and `[pProv + 0x1DE]` is Air Base; neither building check nor `+0x46A` / `+0x270` check is needed under the approved simplified Stage 3 design.)*

### 2.7 `CFrontAI` Front Division Count & Frontline Province Count (`Item 7`)
- Verified in `CFrontAI::MoveUnitsToFront` (`0x00684420..0x0068526A` and Hook 8A `0x00DD0405`):
  - `ebx` (`[ebp - 0xA8]`) is `CFrontAI*` (`this`).
  - `[ebx + 0x0C]` (`int32_t`): number of frontline provinces (`N_front_provs`) in this front's `front_provs` list (`[ebx + 0x04]`), used directly by vanilla at `0x00684420: fild dword ptr [ebx + 0x0C]`.
  - `dword ptr [ebp - 0x60]` (`int32_t` in Loop B Hooks 8A/8B; `dword ptr [esp + 0x34]` inside Hook 8C's `call` frame): `D_front` (`total_front_divs`, total friendly divisions assigned to this front).

### 2.8 Native `Support Defence` Dispatch (`CMission::OrderMission` @ `0x0050B600`, `Item 8`)
- Verified in `CFrontAI::ExecuteTactical` (`0x006888C0..0x0068892C`) and `CMission::OrderMission` (`0x0050B600`, `ret 0x44`):
  - `ecx = pArmy + 0x260` (`CMission*` embedded inside `CLandArmy`).
  - Pushes `0x44` bytes (`17` dwords) right-to-left:
    1. `push 1` (`bClearExisting / flag`)
    2. `push 0xBF800000` (`-1.0f`)
    3. `push 0`
    4. `push 1`
    5. `push 0`
    6. `push -1`
    7. `push 1`
    8. `sub esp, 8` -> `end_date` (`6` bytes: `dword = 0`, `word = 0`)
    9. `sub esp, 8` -> `start_date` (`6` bytes copied from `[dword ptr [0x00893530] + 0x14]`, current game hour timestamp)
    10. `push 1`
    11. `push 1`
    12. `push 0x3F800000` (`1.0f`)
    13. `push target_prov_id` (the attacked bottleneck province $N$)
    14. `push 4` (`mission_type = 4`, **`MISSION_SUPPORT_DEFENCE`**)
    15. `push pArmy` (`CLandArmy*`)
    16. `call 0x0050B600` (`CMission::OrderMission`)
  - Effects of `Support Defence` (`mission_type = 4`):
    - Sets `[pArmy + 0x264] = 4` (`MISSION_SUPPORT_DEFENCE`) and `[pArmy + 0x268] = target_prov_id`.
    - When `target_prov_id` is under active attack (`[pTargetProv + 0x24C] != 0`), the engine's combat resolution / support-defense handler automatically includes adjacent armies with `[pArmy + 0x264] == 4 && [pArmy + 0x268] == target_prov_id` (accelerating their reserve arrival / defense support into the battle at `target_prov_id`).

---

## 3. Expanded `g_pGraphTable` Memory Map (`1,184 KB` Total)

In Stage 5 of the original plan, `g_pGraphTable` was allocated via `VirtualAlloc` at **`0x000EC000` (`944 KB`)**, spanning `+0x00000..+0xEBFFF`. In Stage 1 of Phase 2, we expand all five `VirtualAlloc` sites (`0xEC000 -> 0x128000`, `1,212,416` bytes = `1,184 KB`) to unlock `+0xEC000..+0x127FFF` (`240 KB`) for all new Phase 2 per-province and per-country arrays:

| Offset | Size | Type | Name | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| `+0x00000..+0xEBFFF` | `944 KB` | Various | *(Existing Stages 1--5 tables)* | Unchanged from [plan_stem_strategic_defense.md](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_stem_strategic_defense.md). |
| `+0xEC000` | `8 KB` | `uint8_t[8192]` | `prov_status_flags[P]` | Bitfield per province (rebuilt each Pass 0/1/2):<br>- `Bit 0 (0x01)`: Manual Evacuation Blacklist (`front.province_priorities` match, Item 3)<br>- `Bit 1 (0x02)`: Impassable Supply Lifeline (`adj->type == 4` bridgehead/propagation from safe unthreatened neighbor, Item 4)<br>- `Bit 2 (0x04)`: Direct Coastal Sea Supply (`[pProv + 0x3DC] > 0`, Item 4)<br>- `Bit 3 (0x08)`: `IsThreatened` active via Cooldown Hold (`threat_hold_u8 > 0`, Item 9)<br>- `Bit 4 (0x10)`: `EvacQuota` active via Re-Entry Cooldown Hold (`evac_hold_u8 > 0`, Item 9) |
| `+0xEE000` | `8 KB` | `uint8_t[8192]` | `threat_hold_u8[P]` | Persistent hourly countdown timer (`0..255` hours) holding `is_threatened[P] = 1` on an attacked bottleneck to prevent reinforcement-arrival flicker (Item 9). |
| `+0xF0000` | `8 KB` | `uint8_t[8192]` | `evac_hold_u8[P]` | Persistent hourly countdown timer (`0..255` hours) holding an anti-reentry quota floor after evacuation starts (Item 9). |
| `+0xF2000` | `16 KB` | `float[4096]` | `country_evac_mult[tag]` | Cached country-wide withdrawal propensity multiplier (`0.0f..10.0f`, default `1.0f`) read from `local_flags` in Pass 0 (Item 1). |
| `+0xF6000` | `4 KB` | `uint8_t[4096]` | `country_stem_mode[tag]` | Cached country-wide mode flags read from `local_flags` in Pass 0 (`Bit 0 = stem_soft_mode`, `Bit 1 = stem_no_evac`, Items 1 & 2). |
| `+0xF7000` | `16 KB` | `float[4096]` | `country_front_density[tag]` | Cached country-wide active front division density ($\rho_{\text{country}} = \text{TotalFrontDivs} / \max(1, \text{TotalFrontProvs})$) for `Cave_STEM_UpdateGraphTable` & `stem_debug.csv` (Item 7). |
| `+0xFC000` | `16 KB` | `uint16_t[8192]` | `prov_evac_mult_x100[P]` | Effective multiplier (`x100`) written by Pass 3 / Stage 1 telemetry for `stem_debug.csv` Col 30 (`EvacMult`). |
| `+0x100000` | `32 KB` | `float[8192]` | `front_norm_share[P]` | Stage A pre-STEM `front.province_priorities` base share computed by Hook 8D (`0x00684474`) with `max_stack` water-filling across modes `0..4`. |
| `+0x108000` | `32 KB` | `float[8192]` | `front_final_share[P]` | Stage B post-STEM re-normalized Loop B target share (incorporating `evac_quota` and `BottleneckDefenseBoost` summed to `1.0` with evac-safety ceiling). |
| `+0x110000` | `32 KB` | `uint32_t[8192]` | `front_norm_gen[P]` | Generation stamp (`g_dwFrontNormGen` low 29 bits; bit 31 `0x80000000` = finalized/clamped; bit 30 `0x40000000` = ineligible; bit 29 `0x20000000` = STEM `is_basin`). |
| `+0x118000` | `32 KB` | `float[8192]` | `front_final_divs[P]` | Cached post-STEM target divisions (`front_final_share[P] * D_front`) synced to `stem_debug.csv` `FinalAIPrio`. |
| `+0x120000` | `16 KB` | `uint16_t[8192]` | `strip_provs_backup[i]` | Backup of full K-hop strip province list (`0 .. strip_count - 1`) saved in `.ppa_loop` so `.hlp_mark_impassable_supply` scans the intact strip after Step 5A reuses `+0x1C000` (Item 4). |

*(Total used: `0x00000..0x123FFF` = `1,168 KB` out of `1,184 KB` allocated).*

---

## 4. Detailed 6-Stage Implementation & Testing Plan

---

### Stage 1: `.mod` 64 KB & `g_pGraphTable` 1184 KB Expansion, `extra_debug_logs` CSV Gate (Item 10), Country-Wide `local_flags` Controls (Items 1 & 2) & Manual Province Blacklist / Two-Stage `front.province_priorities` Normalization (Item 3)
**Status:** Completed & Validated (Stage 1C Pre/Post-STEM Normalization & Loop A/B Fix Included; `Cave: 7791 instructions, 23959 bytes`, `SHA256 = 6B824361BB988E40641797A2D36B5810B44587D926CE8226765C9E23CB4ED9AB`)

#### 4.1.1 `.mod` PE Section (`0x8000 -> 0x10000`) & `g_pGraphTable` (`0xEC000 -> 0x128000`) Expansion
- Expand `.mod` (`VirtualAddress = 0x00DC9000`) from `0x8000` (`32 KB`) to `0x10000` (`64 KB`, `0x00DC9000..0x00DD9000`):
  - `SizeOfImage` (`0x150`): `0x009D1000 -> 0x009D9000`.
  - `.mod` `VirtualSize` (`0x2A0`) & `SizeOfRawData` (`0x2A8`): `0x00008000 -> 0x00010000`.
- Expand `VirtualAlloc` size from `0xEC000` (`944 KB`) to **`0x128000` (`1,184 KB`)** across all five allocation sites, keeping persistent hourly state (`+0xEE000..+0xF1FFF`) cleared on scenario load (`Cave_PostLoadInit`, clearing `+0x30000..+0x127FFF` and `g_dwFrontNormGen`) and preserved across normal hourly ticks.

#### 4.1.2 Item 10 -- Gate `stem_debug.csv` on `extra_debug_logs >= 1`
- In `Cave_STEM_SaveGameHook` (`0x00DD0932`), immediately after `pushad`:
  - Check **`cmp byte ptr [0x00DC4B5E], 0; je .save_skip_csv`**.
  - When `settings.cfg` line 9 (`Extra debug logs`) is `0`, `Cave_STEM_SaveGameHook` still refreshes runtime STEM graph telemetry if needed, **but skips creating or writing `stem_debug.csv`**.
  - When `Extra debug logs` is `1` or `2` (`byte ptr [0x00DC4B5E] == 1`), `stem_debug.csv` is written normally on every save.

#### 4.1.3 Items 1 & 2 -- Country-Wide Withdrawal Propensity Modifier & Soft-STEM Switch via `local_flags`
- **Flag Names & Backward-Compatible Semantics**:
  - Looked up once per `Cave_STEM_UpdateGraphTable(pCountry)` invocation via `ecx = [pCountry + 0x120] + 0x4C`, `vtable[+4](szFlagName)` (`movsx eax, word ptr [eax + 0x100]`):
  1. **`stem_evac_modifier`** (percentage integer, default when unset/cleared `0` -> `100` = `1.00x`):
     - Scales `SalientEvacuationQuota(P)` for all provinces of that country:
       $$Q_{\text{final}}(P) = \text{clamp}\!\left(Q_{\text{raw}}(P) \times \frac{\text{stem\_evac\_modifier}}{100.0},\; 0.0,\; 1.0\right)$$
     - Example values:
       - Unset (`0`) or `100`: `1.00x` (standard STEM behavior; 100% backward-compatible with all existing saves).
       - `50`: `0.50x` (reluctant to withdraw; requires twice as severe threat/narrowing before reaching full evacuation).
       - `150`: `1.50x` (cautious/elastic defense; withdraws earlier when flanks are threatened).
       - `1` (or `stem_no_evac = 1`): **`0.00x` ("Fight to the Death")** -- sets `SalientEvacuationQuota(P) = 0.000` everywhere. *(Special-casing `value == 1` as `0.00x` alongside `stem_no_evac = 1` ensures that even if a modder writes `command = { type = local_setflag which = stem_evac_modifier value = 0 }` in an event -- which the DH engine internally converts to `1` -- it works as intended!)*
  2. **`stem_no_evac`** (boolean flag, `>= 1` = enabled):
     - Explicit "Fight to the Death" override (`country_evac_mult[tag] = 0.0f`), forcing `SalientEvacuationQuota(P) = 0.000` for all provinces of that country.
  3. **`stem_soft_mode`** (boolean flag, `>= 1` = enabled):
     - When `stem_soft_mode >= 1`:
       - `Cave_STEM_UpdateGraphTable` still computes full `SalientEvacuationQuota(P)` (scaled by `stem_evac_modifier`) and `EffectiveBottleneckBoost(B)`.
       - `CFrontAI::MoveUnitsToFront` (`Hooks 4, 7A--7D, 8A--8C, 9A--9B, 10`) still applies all STEM priority reductions on salients and bottleneck defense boosts on shoulders.
       - **`Cave_STEM_UpdateAndEvacuate_Internal`** and **`Hooks 12A--12C`** (`CLandArmy::SelectRetreatProvince` active-evac override) check `test byte ptr [edi + tag + 0xF6000], 1` and **skip all forced evacuations, army splits, and STEM combat-retreat overrides**!

#### 4.1.4 Item 3 -- Manual Province Evacuation Blacklist via `front = { province_priorities = { ... } }` & Loop B Donor Fix
- **1. Scanning `front.province_priorities` in Pass 0 of `Cave_STEM_UpdateGraphTable`**:
  - Walk the linked list at `[[pCountry + 0x120] + 0x990]` (`node = [node + 8]`, `entry = [node + 0]`, `prov_id = [entry + 0]`, `float prio = [entry + 4]`).
  - Mark `prov_status_flags[prov_id] |= 0x01` (Blacklisted from STEM evacuation) if **either**:
    - `prio < 0.0f` (Negative sentinel convention, e.g., `province_priorities = { 187 = -1 }` or `187 = -3.0`, matching `garrison.province_priorities = -1`), **OR**
    - `prio >= EvacuationBlacklistPriorityThreshold` (configurable in `db/mod_settings.ini`, default **`5.0f`**, e.g., `province_priorities = { 187 = 10.0 }`).
  - For any province with `prov_status_flags[P] & 0x01`:
    - `quota_q8[P] = 0`, `neck[P] = 0`, and `Cave_STEM_UpdateAndEvacuate_Internal` never evacuates units out of `P`.
    - Note: `P` still participates normally in the BFS graph and can still receive `BottleneckDefenseBoost` if it is a cut vertex/shoulder!
- **2. Two-Stage Pre/Post-STEM Normalization & Loop A/B Fix for `front.province_priorities` (Hooks 7A/7B/7D, 8A/8B/8C, and 8D)**:
  - **Two-Stage Hook 8D (`Cave_FrontAI_NormalizeFrontShares` @ `0x00684474`, `8 bytes` replaced)**: Runs right before Loop B (`CFrontAI::MoveUnitsToFront`) regardless of `EnableEncirclementDefense`:
    - *Stage A (Pre-STEM Base Shares)*: Excludes ineligible provinces (`no_en`, `0x4E9500`, `0x4E9440`, or STEM `is_basin == 1`), computes `weight(P) = max(0.0, raw(fp, mode)) * |prio(P)|` across all 5 modes (`0=even`, `1=reactive`, `2=defensive`, `3=offensive`, `4=op_defensive`) with quiet-front `|prio|` fallback, and runs iterative `max_stack` water-filling (`cap_share = ([0x00DC15FC] * [0x00DC15CC]) / D_front`, up to `64` passes) into `front_norm_share[P]` (`+0x100000`).
    - *Stage B (Post-STEM Re-Normalization)*: When `EnableEncirclementDefense == 1`, applies `evac_quota` (`+0x40000`, with sub-1-div zeroing) and `BottleneckDefenseBoost` (`+0x42000`) to `front_norm_share[P]` (including `is_basin == 1` interior bottlenecks), then re-normalizes total post-STEM target shares back to `1.0` (`sum = D_front`) using iterative water-filling capped at `min(cap_share, s_adj)` for partially-evacuating provinces (`evac_q > 0 && neck_q == 0`) so evacuating provinces never scale upward. Stores `front_final_share[P]` (`+0x108000`) and `front_final_divs[P]` (`+0x118000`) stamped with 29-bit `g_dwFrontNormGen` in `front_norm_gen[P]` (`+0x110000`). (When `EnableEncirclementDefense == 0`, copies `front_norm_share[P]` directly into `front_final_share[P]`).
  - **Loop B & Telemetry Integration (`Hook 8A` @ `0x00684551`, `Hook 8B` @ `0x0068470D`, `Hook 8C` @ `0x0068526A`, `Cave_STEM_SyncTelemetryPrio`)**: All three Loop B share readers consume `front_final_share[P]` directly when `(front_norm_gen[P] & 0x1FFFFFFF) == g_dwFrontNormGen` (preventing total `FinalAIPrio > D_front` from starving donors), and `Cave_STEM_SyncTelemetryPrio` reads `front_final_divs[P]` for active front provinces so `stem_debug.csv` `FinalAIPrio` matches Loop B's exact target.
  - **Loop A Integration (`Hook 7A` @ `0x00683EB6`, `Hook 7B` @ `0x00684088`, `Hook 7D` @ `0x00684131`)**: Even when `EnableEncirclementDefense == 0`, `Hook 7B` ranks unassigned reserve destinations by `(|prio| * en_str) - fr_str` (capping `|prio|` at `1.0` once `cur_divs >= max_stack` and skipping explicit `prio == 0.0`), while `Hooks 7A/7D` prevent pushing reserves into `prio == 0.0` provinces.

#### 4.1.5 New INI Keys & `stem_debug.csv` Updates for Stage 1
- **`db/mod_settings.ini` (`[FrontAI]` section)**:
  - `EvacuationBlacklistPriorityThreshold = 5.0` (Engine default `5.0`, mod INI `10.0`; set `<= 0` to only blacklist negative values `prio < 0.0` in `front.province_priorities`).
- **`stem_debug.csv`**:
  - Append 2 new diagnostic columns after the remaining Phase 1 columns (`CountryTag..EvacDivBudget`, `30` total columns after Stage 2 removes `MinOrg`):
    - **Col 29 (`StatusFlags`)**: Bitmask (`0` = normal, `+1` = Blacklisted via `province_priorities`, `+2` = Impassable Supply Lifeline, `+4` = Port Supply Lifeline, `+8` = Threat Hold Active, `+16` = Evac Hold Active, `+32` = Country Soft-STEM Mode, `+64` = Country Fight-to-the-Death).
    - **Col 30 (`EvacMult`)**: Effective country/supply quota multiplier applied to `P` (formatted `%.2f`, e.g. `1.00`).

#### 4.1.6 Stage 1 Verification & Stopping Point
1. **Build & Automated Smoke Test**:
   - Rebuild `Darkest Hour_modified.exe` / `.bat` patchers and verify `.mod` section is `0x10000` (`64 KB`) and all hooks assemble cleanly.
   - Verify that saving with `Extra debug logs = 0` in `settings.cfg` does NOT overwrite/create `stem_debug.csv`, and saving with `Extra debug logs = 1` DOES generate `stem_debug.csv` with `StatusFlags` and `EvacMult`.
2. **In-Game Test (`local_flags` & `province_priorities` Blacklist)**:
   - Test `stem_evac_modifier = 50`, `stem_no_evac = 1`, and `stem_soft_mode = 1` on `SOV`, plus `province_priorities = { 187 = -1 }` (or `187 = 10.0`), verifying `StatusFlags` and `EvacQuota` in `stem_debug.csv`.
3. **STOP and report Stage 1 results to the user for approval before proceeding to Stage 2.**

---

### Stage 2: Combat Power Realism -- Direct Organization Weighting (Item 5) & Division Softness/Hardness Factor (Item 6) in `FrStr`, `EnStr`, and `InbStr`
**Status:** Completed & Validated (`Cave: 7867 instructions, 24098 bytes`, `SHA256 = C416BCC15C557D1B372942F20CCF0E43CE804B812457B63F2D1105839CF06830`; incl. two latent Phase 1 bugfixes found during validation)

#### 4.2.1 Unified Division Effective Combat Power Formula
- Previously, `.hlp_calc_army_str_org` summed only raw `[pDiv + 0xEC] * 0.01f` for both friendly (`FrStr`, `InbStr`) and enemy (`EnStr`) armies, while `Hook 9A` (`Cave_FrontAI_LoopAIsFrontOrHeldNeck`) likewise summed raw `[pDiv + 0xEC] * 0.01f` when releasing interior bottleneck reserves.
- In Stage 2, we introduce `.hlp_push_div_eff_str_eax` (`0x00DCE612`, called by `.hlp_calc_army_str_org` for Pass 0 friendly, inbound, active hostile, and idle hostile armies, as well as `Hook 9A` @ `0x00DD047F`) so each division $d$ contributes:
  $$\text{DivEffStr}(d) = \frac{\text{Strength}(d)}{100.0} \times \text{OrgFactor}(d) \times \text{HardnessFactor}(d)$$
- **1. Organization Factor (`Item 5`)**:
  - Read `float cur_org = [pDiv + 0xF4]` and compute runtime effective max organization `eff_max_org` matching `CDivision` (`0x004FF8E8`):
    `eff_max_org = [pDiv + 0xF8] * [[pDiv + 0x5C] + 0x244]->0x3E * CCountry::GetUnitModifier([pDiv + 0x5C], pDiv, 2)` (`0x0044C830`).
  - Compute `OrgRatio(d)` (`0.0` if `eff_max_org <= 0.01` to guard divide-by-zero / `NaN`, else):
    $$\text{OrgRatio}(d) = \text{clamp}\!\left(\frac{\text{cur\_org}}{\max(20.0,\; \text{eff\_max\_org})},\; 0.0,\; 1.0\right)$$
  - Apply the single configurable **`OrgWeight`** parameter (`cfg_OrgWeight`, default **`0.85`**):
    $$\text{OrgFactor}(d) = \max\!\left(0.0,\; (1.0 - \text{OrgWeight}) + \text{OrgWeight} \times \text{OrgRatio}(d)\right)$$
    - With default `OrgWeight = 0.85`: a shattered division at `0` ORG gets `0.15x` effective strength (`0.575x` at `50%` ORG, `1.00x` at `100%` ORG). Setting `OrgWeight = 0.0` disables ORG weighting cleanly (`1.00x`).
  - **Removal of Legacy `MinOrg` / `T_org` (Preserving `NeckCollapsingOrgThreshold` `IsThreatened`)**:
    - Because ORG is now baked directly into `FrStr(v)`, `InbStr(v)`, `EnStr(v)`, and `EnInbStr(v)` (`FrEff(v)` and `T_force(v)`), Stage 2 removes the redundant active-combat-only `min_org_q8` (`+0x46000`), `.ect_check_org` (`T_org`) in `.hlp_eval_cut_threat`, and the `MinOrg` column from `stem_debug.csv` (`31 -> 30` columns).
    - Pass 0's `.def_org_fin_loop` (`NeckCollapsingOrgThreshold` comparison setting `is_threatened[P] = 1` when active-combat average defender ORG falls below threshold) is **preserved intact**.
- **2. Softness / Hardness Factor (`Item 6`)**:
  - Read `float softness = [pDiv + 0x2D4]` (`hardness_frac = clamp(100.0 - softness, 0.0, 100.0) * 0.01`).
  - Apply **`HardnessWeight`** (`cfg_HardnessWeight`, default **`0.85`**):
    $$\text{HardnessFactor}(d) = 1.0 + \text{HardnessWeight} \times \frac{\text{clamp}(100.0 - \text{softness},\; 0.0,\; 100.0)}{100.0}$$
    - Examples with `HardnessWeight = 0.85`:
      - Militia / Base Infantry (`100%` softness, `0%` hardness): **`1.00x`**
      - Motorized / Cavalry / Late Infantry (`80%` softness, `20%` hardness): **`1.17x`**
      - Mechanized (`55%` softness, `45%` hardness): **`1.38x`**
      - Panzer / Armor (`30%` softness, `70%` hardness): **`1.60x`**
      - Heavy Armor (`20%` softness, `80%` hardness): **`1.68x`**

#### 4.2.2 Note on Step 6 Evacuation Headcount vs. Combat Strength
- In `Cave_STEM_UpdateGraphTable` (`Pass 0`) and `Hook 9A`: `fr_str`, `inb_str`, `en_str`, and `en_inb_str` use the new ORG + Hardness weighted `DivEffStr(d)` so `T_force(v)` and `SalientEvacuationQuota(P)` accurately reflect whether a neck is threatened by high-org Panzer corps vs. low-org militia.
- Note that `TargetStayDivs`, `StayingDivs`, and `EvacDivBudget` (`Stage 4` of Phase 1) operate on **whole division counts (`+0x2E`)**, NOT strength floats, while `.uae_calc_army_str` / Hook 7B / Loop A candidate scoring continue to match the unified strength representation.

#### 4.2.3 New INI Keys for Stage 2
- **`db/mod_settings.ini` (`[FrontAI]` section)**:
  - `OrgWeight = 0.85` (Organization weight applied in `FrStr`/`EnStr`/`InbStr`: `OrgFactor = (1 - OrgWeight) + OrgWeight * OrgRatio`, `0.0` = disabled, `0.85` -> `0.15x..1.00x`).
  - `HardnessWeight = 0.85` (Bonus strength multiplier at `0%` softness / `100%` hardness; set `0.0` to disable hardness weighting).

#### 4.2.4 Latent Phase 1 Bugfixes & Stage 2 Validation Notes
1. **Latent `edx` Clobber in `.hlp_init_fail` / `.hlp_next_fail` (Resolved)**:
   - When an evacuating province in `.step5e_accum_necks` ended its adjacency list on an `Impassable` (`adj->type == 4`) edge (or `.hlp_init_nb` failed), `.hlp_next_fail` / `.hlp_init_fail` previously left `edx = CProvince->m_pAdjacencies` instead of restoring `edx = [ebp - 4]` (`g_pGraphTable`), causing corrupted reads/writes relative to the province adjacency heap array (`AV @ 0x004318EF`). Fixed by restoring `mov edx, dword ptr [ebp - 4]` in `.hlp_init_fail`, `.hlp_next_fail`, `.s5ea_tnb_done`, and `.s5e_raw_init`.
2. **Infinite Loop on Empty Pass-1 `bfs_q` (`[ebp - 0x10] == 0`, Resolved)**:
   - When an at-war AI country had a `1`-province disconnected front with `0` Pass-1 safe roots (triggered live by `U04` *Syria and Lebanon* at province `7357`), `[ebp - 0x10]` remained `0` into `.raw_rst_done`, setting `[ebp - 0x28] = 0` and spinning infinitely between `.raw_bfs_start` -> `.bfs_queue_loop` -> `.level_comp_start`. Fixed by branching directly to `.raw_prop_start` when `[ebp - 0x10] == 0` at both `.level_comp_start` and `.raw_rst_done`.
3. **Validation**: Rebuilt, verified (`SHA256 = C416BCC15C557D1B372942F20CCF0E43CE804B812457B63F2D1105839CF06830`), and validated in live play by the user (user tuned `HardnessWeight = 3.00` in mod INI).

---

### Stage 3: Alternative Supply Lifelines Over Impassable Connections (`189 <-> 7003`) & Direct Coastal Sea Access (Item 4)
**Status:** Implemented -- Awaiting User Validation (`Cave: 8067 instructions, 24765 bytes`, `SHA256 = 8794E4C17B947BD25198A1415289699E550CDA6E3DE46995EEB9A1C8C332A924`)

#### 4.3.1 Distinguishing Land Escape Routes from Supply Lifelines (Performance-First Simplified Design)
- Troops **cannot** march across `adj->type == 4` (`Impassable`, e.g., `189 Kirisi <-> 7003 Kir'jasaly` across Lake Ladoga) or across sea zones without naval transports. Therefore:
  - `.fdist_bfs_loop`, Step 5A (`F_Paths` Edmonds-Karp flow), and Pass 2 (`.bfs_queue_loop`) **must keep** skipping `adj->type == 4` so `Dist(P)`, `F_Paths(P)`, and `EvacDestNeck(P)` only ever route troops along walkable land edges.
- To avoid adding another full-map BFS per country every game hour, Stage 3 uses two zero-overhead / endangered-pocket-only mechanisms:
  1. **Direct Sea-Zone Exit (`STATUS_PORT_SUPPLY = 0x04`)**: Checked inline inside `.ppa_loop` (`+0x120000` backup & `0xF9` mask reset for `0x02|0x04`) with a single pointer read (`cmp dword ptr [pProv + 0x3DC], 0`), with the accepted tradeoff that only provinces with direct sea access (`m_nPortSeaZone > 0`) receive `0x04` (no separate port-reachability BFS, and no `+0x46A` / Naval Base / `+0x270` checks).
  2. **Endangered-Pocket-Only Impassable Supply Propagation (`STATUS_IMPASSABLE_SUPPLY = 0x02`)**: Invoked once at `.step5b_start` (`.hlp_mark_impassable_supply`) using the strip backup list `+0x120000` saved during `.ppa_loop`:
     - **Pass A (Bridgehead Scan)**: Scans strip provinces (`0 .. [ebp - 0x48] - 1`) that are endangered (`dist != 0` and `cut0 != 0xFFFF`, i.e., `F < W`, catching both Pass-1 `F >= 1` and Pass-2 `F == 0` salient provinces). Iterates their raw adjacency array looking for any `dword ptr [adj + 4] == 4` (`Impassable`) neighbor `eax` that is:
       - unthreatened (`is_threatened[eax] == 0`),
       - safe/non-endangered (`dist[eax] == 0`, OR `(VIS_EVAL & cut0[eax] == 0xFFFF)`, OR `(fdist_p1[eax] == 0 && (flags[eax] & 0x09) == 0)`), AND
       - friendly-controlled (`.hlp_check_ctrl`).
     - Any such endangered province `esi` receives `prov_status_flags[esi] |= 0x02`. If `esi` itself is unthreatened (`is_threatened[esi] == 0`), `esi` is pushed into scratch queue `+0x26000` to propagate supply further into adjacent endangered pockets. If `0` bridgeheads exist (~90%+ of fronts), Pass B skips immediately with zero BFS iterations.
     - **Pass B (Mini-BFS Within Endangered Pocket)**: Expands from `+0x26000` across normal land neighbors (`hlp_init_nb` / `hlp_next_nb`) that are friendly, inside the K-hop strip (`fdist_p1 != 0`), endangered (`dist != 0 && cut0 != 0xFFFF`), and not yet `0x02`, stamping `prov_status_flags[eax] |= 0x02` (e.g., `189 Kirisi ==[Impassable]==> 7003 Kir'jasaly --> 187 Leningrad`), and re-queueing unthreatened neighbors (`is_threatened[eax] == 0`) so actively collapsing nodes receive the supply bonus themselves without forwarding past the breach.

#### 4.3.2 Effect of Alternative Supply Lifelines on `SalientEvacuationQuota(P)` & `EvacMult`
- Helper **`.hlp_mul_alt_supply_esi`** inspects `prov_status_flags[P] & 0x06` (`+0xEC000`):
  - `0x02` (`Impassable Supply`): multiplies quota on `st(0)` by **`ImpassableSupplyQuotaMultiplier`** (INI default **`0.35f`**).
  - `0x04` (`Direct Coastal Sea Supply`): multiplies quota on `st(0)` by **`PortSupplyQuotaMultiplier`** (INI default **`0.50f`**).
  - `0x06` (both bits set, e.g., `187 Leningrad` having both `m_nPortSeaZone > 0` and overland Lake Ladoga connection via `7003 <-> 189`): multiplies `st(0)` by $\min(\text{ImpassableSupplyQuotaMultiplier},\; \text{PortSupplyQuotaMultiplier}) = 0.35$.
- Called in both `.hlp_apply_evac_mult_and_blacklist_esi` at `.aemb_clamp` (covering both Pass-1 Step 5B and Pass-2 `.raw_prop_loop` `F == 0` quotas) and `.hlp_write_telemetry` at `.wt_calc_emult` (so `stem_debug.csv` Col 30 `EvacMult` displays the combined country + alternative-supply multiplier, e.g. `0.35` or `0.50`).
- **Pre-Multiply `[0.0, 1.0]` Clamp Fix**: When `WidthDeficitWeight > 1.0` (`1.2`) and `NeckThreatMaxCap * NeckThreatWeight > 1.0` (`1.5 * 1.3 = 1.95`), unclamped `D_Width * T_Neck * V_Ret` can reach `2.340` prior to `.hlp_apply_evac_mult_and_blacklist_esi`. Clamping raw `Q_raw` to `[0.0, 1.0]` **before** multiplying by `country_evac_mult` and `.hlp_mul_alt_supply_esi` ensures `2.340 * 0.35` does not silently stay at `0.820` (`2.340 -> 1.000 * 0.35 = 0.350`, while keeping the post-multiply `[0.0, 1.0]` clamp for `stem_evac_modifier > 100`).

#### 4.3.3 New INI Keys for Stage 3
- **`db/mod_settings.ini` (`[FrontAI]` section)**:
  - `ImpassableSupplyQuotaMultiplier = 0.35` (Quota multiplier when an endangered pocket province connects via an `adj->type == 4` bridgehead to a friendly safe/unthreatened province; set `1.0` to disable).
  - `PortSupplyQuotaMultiplier = 0.50` (Quota multiplier when a province has direct coastal sea access `[pProv + 0x3DC] > 0`; set `1.0` to disable).

#### 4.3.4 Stage 3 Verification & Stopping Point
1. **Build, Patch Integrity & Static Disassembly Verification (Done)**:
   - Built `build_and_apply_all.py` (`Cave: 8067 instructions, 24765 bytes`, `SHA256 = 8794E4C17B947BD25198A1415289699E550CDA6E3DE46995EEB9A1C8C332A924`), ran both `patch_darkest_hour.bat -Verify` scripts (exit 0), and verified Capstone disassembly of `.ppa_loop` (`+0x120000` backup & `[ecx + 0x3DC]` port check setting `0x04`), `.step5b_start` (`call .hlp_mark_impassable_supply`), `.hlp_mark_impassable_supply`, `.hlp_apply_evac_mult_and_blacklist_esi` (`0x00DCE396` pre-multiply `[0.0, 1.0]` clamp + `call .hlp_mul_alt_supply_esi`), `.hlp_mul_alt_supply_esi` (called by `.hlp_apply_evac_mult_and_blacklist_esi` and `.hlp_write_telemetry`), and `Cave_LoadEngineSettings` (`mov ebx, 0x16` / 22 float configs).
2. **Manual In-Game Validation (User)**:
   - Restart the game to load the updated `Darkest Hour.exe` and `db/mod_settings.ini`, generate `stem_debug.csv`, and inspect `StatusFlags` (`+2` / `0x02` and `+4` / `0x04`), `EvacMult`, and `SalientEvacuationQuota` on coastal provinces and `189 <-> 7003 -> 187`.
   - **STOP and await user approval before proceeding to Stage 4.**

---

### Stage 4: Front-Density Scaling for `BottleneckDefenseBoost` (Item 7)
**Status:** Pending

#### 4.4.1 Why Static `BottleneckDefenseBoost` Fails at Front Extremes
- Currently, `EffectiveBottleneckBoost(B)` (`Step 5E` in `Cave_STEM_UpdateGraphTable` and `Hooks 7B, 8A--8C, 9A` in `CFrontAI::MoveUnitsToFront`) scales `BottleneckDefenseBoost` (`10.0` in mod INI) linearly by `neck_agg_q8[B] / 255.0f`:
  $$\text{EffBoost}_{\text{old}}(B) = \text{BottleneckDefenseBoost} \times \frac{\text{neck\_agg\_q8}[B]}{255.0}$$
- On a small theater front with only `20` total divisions across `15` frontline provinces ($\rho_{\text{front}} = 1.33$ divs/prov), demanding `+10.0` extra divisions at a single bottleneck pulls `50%` of the entire front into one province!
- Conversely, on the 1941 Soviet-German front with `350--500` divisions across `35--45` frontline provinces ($\rho_{\text{front}} \approx 10.0$ divs/prov), `+10.0` divisions at a major operational bottleneck is only `~1.0x` a single average province stack.

#### 4.4.2 Two-Level Front-Density Scaling Formula
We scale `EffectiveBottleneckBoost(B)` by **both** the upstream salient threat (`neck_agg_q8[B]`) **and** the frontline division density ($\rho$), plus a **per-bottleneck maximum front share cap**:

1. **Country-Wide Baseline in `Cave_STEM_UpdateGraphTable` (`Pass 0` & `Step 5E` / `stem_debug.csv`)**:
   - During Pass 0, count:
     - `TotalFrontProvs`: number of friendly frontline provinces (`has_hostile_neighbor == 1` and `dist < 255`).
     - `TotalFrontDivs`: total friendly division count (`div_count` from `+0x48` / `+0xE8000`) on or within `dist <= 2` of the front.
   - Compute $\rho_{\text{country}} = \frac{\text{TotalFrontDivs}}{\max(1,\; \text{TotalFrontProvs})}$ and store in `country_front_density[tag]` (`+0xF7000`).
   - Compute the density multiplier relative to `BottleneckDensityBaseline` (INI default **`3.5` divisions per frontline province**):
     $$\text{DensityMult} = \text{clamp}\!\left(\frac{\rho}{\text{BottleneckDensityBaseline}},\; \text{BottleneckDensityMinScale},\; \text{BottleneckDensityMaxScale}\right)$$
     where default `BottleneckDensityMinScale = 0.25` and `BottleneckDensityMaxScale = 3.00`.
2. **Exact Per-Front Density & Front-Share Cap Inside `CFrontAI::MoveUnitsToFront` (`Hooks 7B, 8A--8C, 9A`)**:
   - Inside `CFrontAI::MoveUnitsToFront`, each independent `CFrontAI` instance (`ebx`) has its exact local division count **`D_front`** (`dword ptr [ebp - 0x60]` in Loop A / Loop B Hooks 8A--8B, `dword ptr [esp + 0x34]` inside Hook 8C) and its exact frontline province count **`N_front_provs`** (`dword ptr [ebx + 0x0C]`, `int32_t`).
   - Using $\rho_{\text{front}} = \frac{D_{\text{front}}}{\max(1,\; N_{\text{front\_provs}})}$, our helper `.hlp_get_density_scaled_boost(pTable, prov_id, D_front, N_front_provs)` computes:
     $$\text{RawBoost}(B) = \text{BottleneckDefenseBoost} \times \frac{\text{neck\_agg\_q8}[B]}{255.0} \times \text{clamp}\!\left(\frac{\rho_{\text{front}}}{\text{BottleneckDensityBaseline}},\; \text{MinScale},\; \text{MaxScale}\right)$$
     and caps it at a maximum fraction of `D_front` (`BottleneckMaxFrontShare`, default **`0.22`** = `22%` of the front's total divisions):
     $$\text{EffBoost}(B) = \min\!\left(\text{RawBoost}(B),\; \text{BottleneckMaxFrontShare} \times D_{\text{front}}\right)$$
3. **Concrete Numerical Examples (with `BottleneckDefenseBoost = 10.0`, `Baseline = 3.5`, `MaxFrontShare = 0.22`)**:
   - **Small 20-division front across 15 provinces** ($\rho_{\text{front}} = 1.33$ divs/prov):
     - $\text{DensityMult} = 1.33 / 3.5 = 0.38$.
     - At `100%` threat (`AggNeckQuota = 1.0`), $\text{EffBoost}(B) = \min(10.0 \times 0.38,\; 0.22 \times 20) = \mathbf{3.8\text{ divisions}}$ (instead of `10.0`!).
   - **Medium 100-division front across 28 provinces** ($\rho_{\text{front}} = 3.57$ divs/prov):
     - $\text{DensityMult} = 3.57 / 3.5 = 1.02$.
     - At `100%` threat, $\text{EffBoost}(B) = \mathbf{10.2\text{ divisions}}$.
   - **Dense 450-division front across 40 provinces** ($\rho_{\text{front}} = 11.25$ divs/prov):
     - $\text{DensityMult} = \min(11.25 / 3.5,\; 3.00) = 3.00$.
     - At `100%` threat, $\text{EffBoost}(B) = \mathbf{30.0\text{ divisions}}$.

#### 4.4.3 New INI Keys for Stage 4
- **`db/mod_settings.ini` (`[FrontAI]` section)**:
  - `BottleneckDensityBaseline = 3.5` (Reference divisions-per-front-province where `BottleneckDefenseBoost` equals `1.0x`; set `<= 0.0` to disable density scaling).
  - `BottleneckDensityMinScale = 0.25` (Minimum density multiplier on very sparse fronts).
  - `BottleneckDensityMaxScale = 3.00` (Maximum density multiplier on ultra-dense fronts).
  - `BottleneckMaxFrontShare = 0.22` (Maximum fraction of a front's total divisions `D_front` that a single bottleneck's boost can demand).

#### 4.4.4 Stage 4 Verification & Stopping Point
1. **Build, Patch Integrity & Static Disassembly Verification**:
   - Rebuild, run `patch_darkest_hour.bat -Verify`, and verify Capstone disassembly of the density-scaling helper and hooks.
2. **Manual In-Game Validation (User)**:
   - Load the 1941 Barbarossa save, save with `Extra debug logs = 1` to generate `stem_debug.csv`, and inspect `FinalAIPrio - AdjAIPrio` on sparse minor/Finnish fronts vs. the main dense Soviet western front.
   - **STOP and report Stage 4 results to the user for approval before proceeding to Stage 5.**

---

### Stage 5: Bottleneck `IsThreatened` Anti-Flicker & Evacuation Commitment Hysteresis (Item 9)
**Status:** Pending

#### 4.5.1 Root Cause of the Cancel-and-Restart Flicker Cycle
During active evacuation of a salient (e.g., `1884 Przemysl` or `209 Bialystok`), three tightly coupled things currently happen when a single fresh division walks into an attacked bottleneck $v$ (e.g., `241 Belz` or `102 Wolkowysk`):
1. **Pass 0 Instant `IsThreatened` Clearance**: The arriving division bumps `FrEff(v)` or briefly pushes `0x004BEBE0` combat progress below the threat threshold for a few hours, flipping `is_threatened[v]` from `1 -> 0` on the next hourly tick.
2. **Pass 1/3 Instant `EvacQuota` Snap-Back**: Because `is_threatened[v]` flipped `1 -> 0`, the upstream salient province $P$ immediately jumps from `F_Paths = 2` (`EvacQuota = 1.000`) to `F_Paths = 3` (`EvacQuota = 0.000`).
3. **Pass 1 Evacuation Registry Instant Slot Clear**: In `Cave_STEM_UpdateAndEvacuate_Internal` (`.uae_p1_noncombat_locked`), the very first hour `quota_q8[P] == 0`, `.uae_p1_noncombat_locked` clears `mov word ptr [ecx + 6], 0` (`locked_dest = 0`)! On that same hour, `CFrontAI::MoveUnitsToFront` sees `quota_q8[P] == 0` and `[slot + 6] == 0`, cancels the evacuating division's in-progress withdrawal march (`0x0050BCA0`), and orders new divisions to march back into $P$. A few hours later, as combat wears down the bottleneck again, `is_threatened[v]` flips back to `1`, restarting the evacuation from scratch (`0%` march progress)!

#### 4.5.2 Three-Layer Anti-Flicker & Hysteresis Architecture
We eliminate this oscillation at all three layers using the persistent hourly countdown arrays `threat_hold_u8[8192]` (`+0xEE000`) and `evac_hold_u8[8192]` (`+0xF0000`):

1. **Layer 1 -- Attacked-Bottleneck `IsThreatened` Hold Timer (`threat_hold_u8[v]` in Pass 0)**:
   - Track the last game-hour timestamp (`dword ptr [0x00893530] + 0x14`) so countdown timers decrement at most once per game hour (not on redundant mid-hour save calls).
   - Whenever raw Pass 0 evaluation marks a province `is_threatened[v] == 1`, set:
     $$\text{threat\_hold\_u8}[v] = \text{ThreatClearanceCooldownHours} \quad (\text{INI default } 36\text{ hours})$$
   - On subsequent hours, if raw Pass 0 evaluation does not mark $v$ threatened, check `threat_hold_u8[v] > 0`:
     - If `threat_hold_u8[v] > 0` **AND** (`dword ptr [pProv(v) + 0x24C] != 0` active defensive combat is still ongoing in $v$, **OR** `raw_threat(v) >= 0.65`):
       - **Hold `is_threatened[v] = 1`**, preserve its threatened status, and set `prov_status_flags[v] |= 0x08` (`STATUS_THREAT_HOLD`)!
     - Only when the timer expires (`threat_hold_u8[v] == 0`) OR active combat has stopped AND raw threat has dropped below `0.65` does `is_threatened[v]` clear to `0`.

2. **Layer 2 -- Evacuation Quota Re-Entry Cooldown (`evac_hold_u8[P]` in Pass 3)**:
   - Whenever a province $P$ has raw `quota_q8[P] >= 64` ($\ge 25\%$ evacuation), set:
     $$\text{evac\_hold\_u8}[P] = \text{EvacReentryCooldownHours} \quad (\text{INI default } 24\text{ hours})$$
   - While `evac_hold_u8[P] > 0` on subsequent hours, if raw `quota_q8[P]` drops to `0` (e.g., because a bottleneck stabilized), do not let `quota_q8[P]` snap immediately to `0` for `CFrontAI` reinforcement checks:
     - Maintain a minimum decaying hold quota `quota_q8[P] = max(raw_quota_q8[P], 32)` (`12.5%`, with `prov_status_flags[P] |= 0x10` `STATUS_EVAC_HOLD`) while `evac_hold_u8[P] > 0`.
     - Because `Hooks 7B, 8A--8C, 9B` treat any province with `quota_q8[P] > 0` as an evacuating salient (blocking Loop A/B from marching new reinforcements into $P$), `CFrontAI` waits until `evac_hold_u8[P]` expires (`24` hours of sustained stability) before marching divisions back into a recently evacuated salient!

3. **Layer 3 -- In-Progress Withdrawal March Commitment (`.uae_p1_noncombat_locked` in Step 6)**:
   - In `Cave_STEM_UpdateAndEvacuate_Internal` (`Pass 1` active evacuation registry validation):
     - If an army slot already has a locked withdrawal destination `dest = word ptr [ecx + 6]` (`dest != 0`) AND the army is currently **still marching toward `dest`** (`.uae_is_marching_to_eax` returns `1`):
     - Even if `quota_q8[src]` drops to `0` (or `prov_status_flags[src] & 0x10` is in cooldown hold), **DO NOT clear `[ecx + 6]` (`locked_dest`) mid-march**, provided `dest` is still friendly-controlled and `quota_q8[dest] < 255`!
     - Keeping `[ecx + 6] = dest` while the unit finishes its current 1-hop withdrawal march guarantees that Hook 9A / Hook 4 (`[slot + 6] != 0`) and `Loop A/B` protect the unit's accumulated movement progress until it arrives at `dest`!

#### 4.5.3 New INI Keys for Stage 5
- **`db/mod_settings.ini` (`[FrontAI]` section)**:
  - `ThreatClearanceCooldownHours = 36` (Hours an attacked bottleneck holds `IsThreatened = 1` against temporary reinforcement blips while combat continues or $T(v) \ge 0.65$; set `0` to disable).
  - `EvacReentryCooldownHours = 24` (Hours a salient province blocks Front AI from marching divisions back in after evacuation clears; set `0` to disable).

#### 4.5.4 Stage 5 Verification & Stopping Point
1. **Build, Patch Integrity & Static Disassembly Verification**:
   - Rebuild, run `patch_darkest_hour.bat -Verify`, and verify Capstone disassembly of `threat_hold_u8`, `evac_hold_u8`, and `.uae_p1_noncombat_locked`.
2. **Manual In-Game Validation (User)**:
   - Run several days on the 1941 Barbarossa save where `241 Belz` / `1884 Przemysl` or `102 Wolkowysk` / `209 Bialystok` are under attack while reinforcements arrive at the neck.
   - Verify in `stem_debug.csv` (`StatusFlags` bits `+8` and `+16`) and in-game that evacuating units complete their withdrawal marches without cancelling/restarting when a reinforcing division enters the neck.
   - **STOP and report Stage 5 results to the user for approval before proceeding to Stage 6.**

---

### Stage 6: Withdrawing to Threatened Bottlenecks & Adjacent `Support Defence` Dispatch (Item 8)
**Status:** Pending

#### 4.6.1 Allowing Threatened Bottlenecks (`IsThreatened == 1`) as Withdrawal Rally Necks
- **Why Threatened Bottlenecks Were Previously Skipped**:
  1. In Step 5C (`.hlp_is_viable_shoulder_eax`), any cut vertex $B$ with `is_threatened[B] != 0` was rejected.
  2. In Pass 3 intermediate rally-neck redirection, a closer cut vertex $N$ (`Dist[N] < Dist[P]`) was only chosen as `neck[P]` if `is_viable_shoulder(N)` returned `1` (which required `is_threatened[N] == 0`).
- **Stage 6 Update**:
  - When a bottleneck/cut-vertex $N$ (`is_cut_vertex[N] == 1`, `Dist[N] < Dist[P]`) is marked `is_threatened[N] == 1`:
    - Provided $N$ still has friendly defenders (`fr_str[N] + inb_str[N] > 0`), $N$ itself has a downstream escape route (`f_paths[N] >= 1` or `neck[N] != 0`), and $N$ is not under full `100%` evacuation (`quota_q8[N] < 255`, OR $N$ is the sole topological bridgehead out of $P$'s component):
    - Allow $N$ to remain a valid withdrawal destination (`neck[P] = N`) for upstream salient provinces $P$ (`Dist[P] > Dist[N]`)!
    - Furthermore, when `is_threatened[N] == 1` and $N$ is the active withdrawal bottleneck for upstream evacuating provinces (`neck_agg_q8[N] > 0`), cap $N$'s own evacuation quota at `quota_q8[N] = 0` while upstream provinces still have friendly troops evacuating through $N$ (or while $N$ is holding as the bridgehead), so the bridgehead defenders and arriving upstream troops stand and hold the neck together!

#### 4.6.2 Dispatching `Support Defence` (`mission_type = 4`) When Adjacent to an Attacked Bottleneck
- **Exact Trigger Conditions in `Cave_STEM_UpdateAndEvacuate_Internal` (`Pass 1` & `Pass 2` non-combat dispatch)**:
  - Suppose army `pArmy` in province `src_prov` ($P$) is selected to withdraw toward destination neck `dest_neck` ($N = \text{neck}[P]$).
  - Check:
    1. `EnableBottleneckSupportDefense == 1` (INI toggle, default `1`),
    2. `src_prov` ($P$) is **directly adjacent** to `dest_neck` ($N$) (`first_step == dest_neck`),
    3. `dest_neck` ($N$) is a bottleneck/shoulder (`is_cut_vertex[N] == 1` or `neck_agg_q8[N] > 0` or `is_threatened[N] == 1`), AND
    4. `dest_neck` ($N$) is **currently under active enemy attack** (`dword ptr [pProv(N) + 0x24C] != 0`, friendly controller).
- **Action When All 4 Conditions Hold**:
  1. Instead of calling `DispatchMoveOrder` (`0x006AAFF0`, `mission_type = 1`), call `.hlp_dispatch_support_defense(pArmy, dest_neck)` which invokes **`CMission::OrderMission` (`0x0050B600`, `ecx = pArmy + 0x260`)** with **`mission_type = 4` (`MISSION_SUPPORT_DEFENCE`)** and `target_prov_id = dest_neck` (using the exact `0x44`-byte stack frame from `CFrontAI::ExecuteTactical` @ `0x006888C0..0x0068892C`).
  2. Record `[slot + 0] = army_type`, `[slot + 2] = army_id`, `[slot + 6] = dest_neck` in the STEM Active Evacuation Registry (`+0x38000`) and set `stem_evac_active[src_prov] = 1` (`+0x30000`).
- **Lifecycle & Recognition of a `Support Defence` Withdrawal Slot**:
  1. **Recognition in `.uae_is_marching_to_eax`**:
     - Update `.uae_is_marching_to_eax(pArmy, target_prov)` so that in addition to checking active movement (`[pArmy + 0x27E] == 1`), it also checks if `[pArmy + 0x264] == 4` (`MISSION_SUPPORT_DEFENCE`) AND `[pArmy + 0x268] == target_prov` AND `[pProv(target_prov) + 0x24C] != 0` (target bottleneck is still under active attack)!
     - While the bottleneck battle continues, `.uae_is_marching_to_eax` returns `1` (`active`), so Pass 1 keeps the unit on `Support Defence` without re-ordering or clearing its slot, and `Hook 4 / Loop B` prevents `CFrontAI` from overwriting the `Support Defence` mission!
  2. **Automatic Transition from `Support Defence` to Physical Move When the Battle Ends**:
     - The moment the enemy attack on `dest_neck` ends (`[pProv(dest_neck) + 0x24C] == 0`, victory!), `.uae_is_marching_to_eax` returns `0` for a non-moving `mission_type == 4` unit.
     - On that very next hourly tick, `.uae_p1_noncombat_locked` sees that the unit is no longer actively supporting an ongoing battle and immediately dispatches a normal **`DispatchMoveOrder` (`0x006AAFF0`)** to `dest_neck` so the division marches physically into the saved bottleneck to complete its withdrawal!

#### 4.6.3 New INI Keys for Stage 6
- **`db/mod_settings.ini` (`[FrontAI]` section)**:
  - `AllowThreatenedBottleneckWithdrawal = 1` (`1` = allow withdrawing into threatened bottlenecks `IsThreatened == 1` that still have friendly defenders and a downstream path; `0` = legacy behavior).
  - `EnableBottleneckSupportDefense = 1` (`1` = use `Support Defence` `mission_type = 4` when withdrawing from a province directly adjacent to an actively attacked bottleneck; `0` = always use normal `Move`).

#### 4.6.4 Stage 6 Verification & Stopping Point
1. **Build, Patch Integrity & Static Disassembly Verification**:
   - Rebuild, run `patch_darkest_hour.bat -Verify`, and verify Capstone disassembly of threatened bottleneck selection and `CMission::OrderMission` (`mission_type = 4`) dispatch.
2. **Manual In-Game Validation (User)**:
   - Load the 1941 Barbarossa save where an active bottleneck (e.g., `102 Wolkowysk`, `241 Belz`, or `181 Pskov`) is under attack while adjacent salient provinces are evacuating toward it.
   - Verify in-game / in memory that adjacent withdrawing units issue **`Support Defence`** (`[pArmy + 0x264] == 4`) into the attacked bottleneck, and transition to a normal move into the bottleneck once the defensive battle is won.
   - **STOP and report Stage 6 results to the user for final validation.**

---

## 5. Summary of New `db/mod_settings.ini` (`[FrontAI]`) Parameters

| Parameter | Default (Code) | Mod INI Value | Stage | Description |
| :--- | :--- | :--- | :--- | :--- |
| `EvacuationBlacklistPriorityThreshold` | `5.0` | `10.0` | Stage 1 | Any province with `front.province_priorities >= threshold` (or `< 0.0`) is blacklisted from STEM evacuation. |
| `OrgWeight` | `0.85` | `0.85` | Stage 2 | Organization multiplier weight in `FrStr`/`EnStr`/`InbStr` (`(1.0 - OrgWeight) + OrgWeight * clamp(Org / max(20.0, eff_max_org), 0.0, 1.0)`). |
| `HardnessWeight` | `0.85` | `3.00` | Stage 2 | Bonus combat power multiplier for division hardness (`1.0 + HardnessWeight * (100 - Softness) / 100`). |
| `ImpassableSupplyQuotaMultiplier` | `0.35` | `0.35` | Stage 3 | Multiplier applied to `SalientEvacuationQuota` when an endangered pocket province connects via an `adj->type == 4` bridgehead to a friendly safe/unthreatened province (`StatusFlags & 0x02`). |
| `PortSupplyQuotaMultiplier` | `0.50` | `0.50` | Stage 3 | Multiplier applied to `SalientEvacuationQuota` when a province has direct coastal sea access (`[pProv + 0x3DC] > 0`, `StatusFlags & 0x04`). |
| `BottleneckDensityBaseline` | `3.5` | `3.5` | Stage 4 | Reference front division density (divisions per frontline province) for `1.0x` `BottleneckDefenseBoost`. |
| `BottleneckDensityMinScale` | `0.25` | `0.25` | Stage 4 | Minimum density scale multiplier for `BottleneckDefenseBoost` on sparse fronts. |
| `BottleneckDensityMaxScale` | `3.00` | `3.00` | Stage 4 | Maximum density scale multiplier for `BottleneckDefenseBoost` on dense fronts. |
| `BottleneckMaxFrontShare` | `0.22` | `0.22` | Stage 4 | Maximum fraction of total front divisions (`D_front`) that a single bottleneck's boost can demand. |
| `ThreatClearanceCooldownHours` | `36` | `36` | Stage 5 | Hours an attacked bottleneck holds `IsThreatened = 1` against temporary reinforcement blips. |
| `EvacReentryCooldownHours` | `24` | `24` | Stage 5 | Hours a salient province blocks Front AI re-entry after evacuation clears. |
| `AllowThreatenedBottleneckWithdrawal` | `1` | `1` | Stage 6 | Allow evacuating units to target a threatened bottleneck (`IsThreatened == 1`) as their intermediate rally neck. |
| `EnableBottleneckSupportDefense` | `1` | `1` | Stage 6 | Issue `Support Defence` (`mission 4`) instead of `Move` when withdrawing from a province adjacent to an attacked bottleneck. |

---

## 6. Future Considerations (Carried Over & New Architectural Topics)

The following items are preserved for future investigation after Phase 2 validation and are not part of Stages 1--6 above:

### 1. Straggler Hostage / Pin-the-Tip Edge Case in Step 5C (Carried Over from Phase 1 `#1`)
- **Mechanism:** In Step 5C (`BottleneckDefenseBoost`), `UpstreamThreat` takes the maximum `SalientEvacuationQuota(P)` across upstream provinces $P$ where `FrStr(P) + InbStr(P) > 0` (including combat-retreating units stamped via `prov_flags |= 0x20`).
- **Potential Edge Case:** If `90%` of a deep salient has already evacuated through bottleneck $B$, but a single slow straggler division remains pinned in combat at the far tip ($P_{\text{tip}}$ with `EvacQuota = 1.0`), `UpstreamThreat` remains `1.0` (`100%` boost at $B$) until that last division escapes or is destroyed.
- **Potential Mitigation:** Weight `UpstreamThreat` by the ratio of remaining upstream friendly strength to a reference corps size (e.g., $\min(1.0,\; \text{UpstreamFriendlyStr}(B) / \text{RefStr})$) so a single 1-division straggler only generates a proportional rescue boost at $B$.

### 2. Post-Arrival Neck-to-Salient "Revolving Door" & Residual Troop Shuffling Watchpoint (Carried Over from Phase 1 `#5`)
- **Mechanism:** Even with Stages 3--5 of Phase 1 and the anti-flicker hysteresis in Stage 5 of Phase 2, `CFrontAI::MoveUnitsToFront` re-evaluates lateral troop balancing across the front.
- **Watchpoint:** Continue monitoring whether units arriving at a neck or adjacent safe province exhibit residual lateral shuffling between neighboring frontline provinces when `ThreatScore` fluctuates below `1.0`.

### 3. Multiplicative vs. Additive/Hybrid `SalientEvacuationQuota` Formulation (Carried Over from Phase 1 `#7`)
- **Mechanism:** Currently, `SalientEvacuationQuota(P)` is purely multiplicative (`D_Width(P) * T_Neck(P) * V_Ret(P)`).
- **Trade-off:** If any single factor is small, the product can be small even when the other two factors are extreme; conversely, when all three are moderate (`0.7 * 0.7 * 0.7 = 0.34`), the product can understate combined risk. A weighted hybrid or additive floor remains an option if future tuning reveals edge cases.

### 4. Multi-Front Separation & Shared-Seam Interior Bottleneck Ownership (`Hook 4` / `0x00694BE0`, Carried Over from Phase 1 `#8`)
- **Mechanism:** `Hook 4` (`0x00682A58`, inside `CFrontAI` setup) injects depth-1 interior bottlenecks (`neck_agg_q8[P] > 0`, `[CProvince + 0x4A8] == 0 or == esi`) into `CFrontAI.front_provs` (`+0x04`).
- **Potential Edge Case:** Before two nearby fronts merge via `0x00693EE0` -> `0x0068A2B0`, an initially empty shared-seam interior bottleneck between two separate fronts is claimed first-come-first-served by whichever front reaches `Hook 4` first. If multi-front scenarios stall for long periods along a seam, garrison-owner tie-breaking may be needed.

### 5. NEW -- Hybrid `CFrontAI` Distribution Mode Combining `reactive`, `defensive`, and `op_defensive` (`0x006843F3..0x00684528`)
- **Problem Statement:** In vanilla Darkest Hour, `CFrontAI::MoveUnitsToFront` (`0x006843F3..0x00684528`) reads `distrib_vs_human` (`[eax + 0x88]`) or `distrib_vs_ai` (`[eax + 0x8C]`) from `eax = [ebp - 0x88]` (`[pCountry + 0x120] + 0x8FC`, the country's `front = { ... }` AI sub-struct) based on `[ebx + 0x124]` (`is_vs_ai`), and branches exclusively (`edi = [ebp - 0x48]`):
  - `0 = even` (`0x006844DB`): Distributes divisions flatly (`1.0f / N_front_provs`), ignoring terrain, enemy stacks, and strategic value.
  - `1 = reactive` (`0x006844E3`, `[ecx + 0x30]` normalized by `[ebp - 0x28]`): Weights desired troop share purely by reactive enemy pressure, ignoring terrain defensibility, forts, and operational depth.
  - `2 = defensive` (`0x00684509`, `[eax + 0x34]` normalized by `[ebp - 0x28]`): Weights desired troop share by defensive terrain/fort/value score, paying less attention to where enemy shock armies are actually massing.
  - `3 = offensive` (`0x006844F1`, `1.0f - [edx + 0x20] / sum`): Weights by offensive target weakness/priority.
  - `4 = op_defensive` (`0x00684518`, `[ecx + 0x14]` integer score divided by `[ebp - 0x28]`): Weights by operational-defensive depth/threat factors, which often under-mans immediate tactical danger spots.
- **Why Mutual Exclusivity Causes Odd AI Behavior:** Because modes `1` (`reactive`), `2` (`defensive`), and `4` (`op_defensive`) are mutually exclusive branches in `0x006843F3..0x00684528`, a country using `defensive` fails to counter enemy armor concentrations; a country using `reactive` piles troops into indefensible plains while neglecting key river/fort lines; and a country using `op_defensive` leaves thin spots on the line.
- **Proposed Future Investigation:** Reverse-engineer the upstream helpers populating `[node + 0x30]` (`reactive`), `[node + 0x34]` (`defensive`), and `[node + 0x14]` (`op_defensive`) on each `CFrontProvince` node (`0x006825E0..0x00683AC0`), and design a configurable **Hybrid Distribution Mode** in `CFrontAI::MoveUnitsToFront` that blends normalized components:
  $$S_{\text{hybrid}}(u) = w_{\text{react}} \cdot S_{\text{reactive}}(u) + w_{\text{def}} \cdot S_{\text{defensive}}(u) + w_{\text{op}} \cdot S_{\text{op\_defensive}}(u)$$
  so the Front AI simultaneously responds to enemy force concentrations (`reactive`), anchors on defensible terrain/forts/VPs (`defensive`), and respects operational depth (`op_defensive`).

### 6. NEW -- Geographic Front-Splitting (Lakes / Interior Gaps) & Cross-Front Division Rebalancing (`0x00693EE0` / `0x00694BE0`)
- **Problem Statement:** Vanilla `CAI::UpdateFronts` (`0x00693EE0` -> `0x0068A2B0`) only merges `CFrontAI` instances when two exposed frontline provinces share a direct walkable land edge. Any small geographic obstacle along the front -- such as `7105 Lake Ilmen` separating `287 Malaya Vishera` and `7075 Parfino` behind friendly interior `7074 Valdaj`, a minor lake/impassable tile, or a shallow Allied salient pinch -- fractures a single continuous theater into multiple isolated `CFrontAI` pools with no ongoing balancing between them.
- **Observed Impact (Live Barbarossa Save):** Even when `186 Krasnogvardeysk` faced `27` German divisions (`NormAIPrio = 8.7`), Lake Ilmen isolated the 4-province Northern Front (`24.0` total divs) from the 14-province Main Front (`187.0` total divs, where `1564 Opocka` facing `20` German divs received `NormAIPrio = 20.8`). Because vanilla `CAI::RequestFrontDivisions` (`0x00694BE0`) gates cross-front transfers on extreme `panic_ratio` (`30.5` in `SOV` AI) and caps requests at `front->prov_count - our_divs` (`4 - 24 <= 0`), the heavily outnumbered Northern Front could never draw surplus divisions from the rest of the same landmass front.
- **Potential Remediation Directions (One or Both Together):**
  1. **Prevent Artificial Front Splits in `CAI::UpdateFronts` (`0x00693EE0` / `0x0068A2B0`):** Allow nearby same-landmass fronts separated only by small geographic obstacles (e.g., 1-2 hop friendly interior bridges like `7074 Valdaj` around lakes, impassable borders, or adjacent water tiles) to merge into a single unified operational front so `Loop A` and `Loop B` distribute divisions proportionally across the whole theater.
  2. **Continuous Enemy-Weighted Cross-Front Rebalancing (`0x00694BE0`):** Supplement or replace vanilla's `1`-division-per-province / `panic_ratio` cross-front gate so same-landmass fronts sharing an active war enemy continuously transfer surplus divisions from low-threat fronts to heavily outnumbered fronts based on actual enemy-to-friendly force ratios.
