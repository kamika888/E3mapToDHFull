# Engine Modification Plan: Front AI Graph Traversal & Salient Evacuation Engine (Patch 18 / STEM)

**Document ID**: `plan_front_ai_encirclement_defense.md`  
**Target Engine**: Darkest Hour 1.05.2 (32-bit x86 PE, Checksum: `TENE`)  
**Target Executable**: `Darkest Hour.exe` (Image Base: `0x00400000`, Base File Size: `4,730,956` bytes, Patched Size: `4,751,360` bytes)  
**Configuration File**: `db\mod_settings.ini` -> Sections `[FrontAI]` and `[Engine]`  
**Patcher Integration**: `patch_darkest_hour.bat` -> **Patch 18**  
**Code Cave Location**: Dedicated `.mod` page 2/3 at VA `0x00DCBAB0`-`0x00DCCBA0` (File Offset: `0x00486AB0`, `3,374` / `4,336` bytes total)  
**Status**: IMPLEMENTED (V2 BASELINE) / UNDER REVIEW

---

## 1. Executive Summary & Problem Definition

In Darkest Hour retail v1.05.2, `CFrontAI` (`0x006811B0`) suffers from structural limitations when defending multi-province salients against armored pincer attacks:
1. **1-Hop Neighbor Blind Spot (`0x00681CD0` & `op_defensive`)**:
   - Retail `CFrontAI::ManageSalientUnits` (`0x00681CD0`, called from `CFrontAI::MoveUnitsToFront` at `0x00682A58`) only identifies border provinces that individually possess a single friendly neighbor (`[CFrontAI + 0x12E]`), pulls at most 2 border-tip divisions back by 1 hop into an adjacent border province, and registers only those 2 units in `[CFrontAI + 0xC8]` (`m_SalientEvacuatingUnits`).
   - Similarly, `distrib_vs_human = op_defensive` (`0x006831D0` - `0x00684526`) weights province quotas strictly by immediate 1-hop friendly connections ($A_i / \sum A$). In any multi-province pocket (such as the Bialystok salient: `7335`, `6516`, `1875`, `6515`, `505`), interior and border provinces connect to one another ($\ge 2$ neighbors), blinding the AI to a narrow bottleneck neck (`102` Wolkowysk) at the base of the salient.
2. **The Pinning & `StopMovement` Trap**:
   - Under `reactive` distribution, `CFrontAI::MoveUnitsToFront` (`0x006829B0`) matches enemy troop stacks directly across the border and calls `StopMovement` (`0x0050BCA0` at `0x0068416A`) on any moving front army whose `TypeId` is not registered in `[CFrontAI + 0xC8]`.
   - Meanwhile, divisions pinned in combat inside a salient (e.g., Grajewo `6516`) remain locked in battle until encircled and destroyed.

---

## 2. Parameter Inventory & Runtime Memory Table (`0x00DCBAB0`)

| Parameter Name | Cave VA | Binary Type | Default | Current Implementation Status |
|---|---|---|---|---|
| `EnableEncirclementDefense` | `0x00DCBAB0` | `int` | `1` | **ACTIVE**: Master toggle (`0` = vanilla, `1` = STEM enabled). Checked at `0x00DCC712` & `0x00DCC74F`. |
| `SalientNeckWidthThreshold` | `0x00DCBAB4` | `int` | `2` | **LOADED ONLY (UNREFERENCED)**: Loaded from INI at `0x00DCBC57`; Tarjan DFS currently checks width-1 cut-vertices (`is_cut == 1`) in the safe subgraph. |
| `AbortSpearheadOnNeckCollapse`| `0x00DCBAB8` | `int` | `1` | **LOADED ONLY (UNREFERENCED)**: Loaded at `0x00DCBC6F`, not yet evaluated in cave. |
| `UseSupplyDepotsAsCores` | `0x00DCBABC` | `int` | `1` | **LOADED ONLY (UNREFERENCED)**: Loaded at `0x00DCBC87`; BFS currently seeds only from Capital (`[pCountry + 0x117DE]`). |
| `NeckThreatRatio` | `0x00DCBAC0` | `float` | `1.5f` | **LOADED ONLY (UNREFERENCED)**: Loaded at `0x00DCBC96`, not yet evaluated in cave. |
| `NeckCollapsingOrgThreshold` | `0x00DCBAC4` | `float` | `30.0f` | **LOADED ONLY (UNREFERENCED)**: Loaded at `0x00DCBCA5`, not yet evaluated in cave. |
| `SpearheadWinningOdds` | `0x00DCBAC8` | `float` | `1.1f` | **ACTIVE**: Loaded at `0x00DCBCB4`; used at `0x00DCBE77` as the attacker combat odds threshold ($\frac{W}{1+W}$) via `CCombat::GetAttackerWinFraction` (`0x004BEBE0`) to flag defending provinces as threatened (`+0x25000 = 1`). |
| `SalientEvacuationQuota` | `0x00DCBACC` | `float` | `0.0f` | **LOADED ONLY (UNREFERENCED)**: Loaded at `0x00DCBCC3`; superseded by direct `0x006AAFF0` dispatch. |
| `BottleneckDefenseBoost` | `0x00DCBAD0` | `float` | `3.5f` | **LOADED ONLY (UNREFERENCED)**: Loaded at `0x00DCBCD2`; superseded by direct `0x006AAFF0` dispatch. |
| `g_pGraphTable` | `0x00DCBAD4` | `pointer` | `Dynamic` | **ACTIVE**: Base pointer to 256 KB (`0x40000` bytes) working buffer allocated via `VirtualAlloc`. |
| `AlwaysShowMovementArrows` | `0x00DCBAD8` | `int` | `0` (`1` in INI) | **ACTIVE**: `[Engine]` setting; renders movement/retreat arrows for all moving units and prevents deselect clearing at `0x005226C1`. |
| `g_nHourlyCounter` | `0x00DCBADC` | `uint32` | `0` | **WRITE-ONLY (LEGACY)**: Incremented at `0x00DCBD60`, `0x00DCBD80`, and `0x00DCC6E6`; never read. |
| `AutoNoFog` | `0x00DCBAE8` | `int` | `0` (`1` in INI) | **ACTIVE**: `[Engine]` setting; sets `[0x00D610DC] = 1` and `[pPlayerCountry + 0x21E90] = 1` on load and hourly. |
| `AutoShowId` | `0x00DCBAEC` | `int` | `0` (`1` in INI) | **ACTIVE**: `[Engine]` setting; sets `[0x00D610E8] = 1` on load and hourly. |

### `g_pGraphTable` (`[0x00DCBAD4]`, `0x40000` bytes) Layout
- `+0x00000 .. +0x0FFFF`: Per-province 8-byte graph records (`prov_id * 8`):
  - `+0x00` (`uint16`): `dist` — BFS hop distance from Capital (`0xFFFF` = unreachable / excluded from Safe Subgraph)
  - `+0x02` (`uint16`): `neck` — Province ID of nearest upstream articulation point (`0` = main body / no bottleneck)
  - `+0x04` (`uint16`): `is_cut` — `1` if province is a Tarjan articulation point (cut-vertex) in the Safe Subgraph
  - `+0x06` (`uint16`): `parent` — BFS parent province ID
- `+0x10000 .. +0x13FFF`: BFS queue (`uint16` province IDs)
- `+0x14000 .. +0x17FFF`: Tarjan DFS discovery time `tin[prov]` (`uint16`)
- `+0x18000 .. +0x1BFFF`: Tarjan DFS low-link value `low[prov]` (`uint16`)
- `+0x1C000 .. +0x23FFF`: Explicit Tarjan DFS call stack (`[prov:u16, nb_idx:u16]` per frame)
- `+0x25000 .. +0x25FFF`: `is_threatened[prov]` (`uint8`, `1` = province excluded from Safe Subgraph)
- `+0x26000 .. +0x26FFF`: `is_holding[prov]` (`uint8`, `1` = friendly defender holding province)
- `+0x30000 .. +0x31FFF`: `is_evacuating[prov]` (`uint8`, `1` = active STEM salient province during current hour; read by `Cave_FrontAI_ManageSalients` to populate `[CFrontAI + 0xC8]`)

---

## 3. Hook Architecture & Call Sites

| Hook ID | Call Site VA (File Offset) | Target Cave VA | Purpose & Status |
|---|---|---|---|
| **Hook 1** | `0x00DCB7E6` (`0x004867E6`) | `0x00DCBC00` -> `0x00DCC5FA` | Chains from Patch 17 INI loader to load `[FrontAI]` and `[Engine]` settings from `db\mod_settings.ini`. |
| **Hook 2A** | `0x004E7616` (`0x000E7616`) | `0x00DCBD60` | **OBSOLETE / CANDIDATE FOR REMOVAL**: Increments unused counter `[0x00DCBADC]` on combat occupation. |
| **Hook 2B** | `0x004E7905` (`0x000E7905`) | `0x00DCBD80` | **OBSOLETE / CANDIDATE FOR REMOVAL**: Increments unused counter `[0x00DCBADC]` in `CProvince::SetController`. |
| **Hook 3** | `0x005AEDBE` (`0x001AEDBE`) | `0x00DCC6A2` | Hourly game loop hook after `AdvanceDate(1)`. Runs `Cave_STEM_HourlyAllCountries`. |
| **Hook 4** | `0x00681CD0` (`0x00281CD0`) | `0x00DCC74D` | Redirects `CFrontAI::ManageSalientUnits` to `Cave_FrontAI_ManageSalients`, registering all armies in `[g_pGraphTable + prov + 0x30000] == 1` into `[CFrontAI + 0xC8]`. |
| **Hook 5** | `0x005226C1` (`0x001226C1`) | `0x00DCC57A` | `AlwaysShowMovementArrows` deselect filter inside `CLandArmy::OnDeselect`. |
| **PostLoad**| `0x00DCAE55` (`0x00485E55`) | `0x00DCC5B0` | Chains from Patch 12 scenario-load hook (`FUN_0042E9B0` exit) to apply `AutoNoFog`, `AutoShowId`, and `AlwaysShowMovementArrows` immediately upon load. |
