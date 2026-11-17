# Darkest Hour Front AI Architecture & Evaluation Engine

**Target Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour.exe` (Image Base: `0x00400000`, Vanilla Checksum: `TENE`)  
**Scope**: In-memory architecture of Front AI (`CFrontAI`), hourly front distribution and tactical evaluation loops, retail rear-reserve staging (`0x00681CD0`), and the Patch 18 Salient Topological Evacuation & Momentum Engine (STEM).

---

## 1. Retail Subsystem Architecture Overview

Front AI is the operational land theater commander in Darkest Hour. Unlike `CGarrisonAI` (`0x0068BA50`, which manages rear-area quotas, homeland defense ratios, and partisan suppression) or `CInvasionAI` (`0x006A6DF0` / vtable `0x007F4C24`, which manages overseas amphibious invasions and naval staging), `CFrontAI` (vtable `0x007F3868`) governs active land border fronts between nations.

```
[Country Object] (Base: [0x0089CAD8 + tag * 4])
       |
       +--> +0x13C84: CAI Controller Subsystem (ecx for CAI::DispatchMoveOrder @ 0x006AAFF0)
       |
       +--> +0xE86E: Active Fronts Linked List Head (CFrontAI* objects, vtable: 0x007F3868)
                       |
                       v
               0x006811B0: CFrontAI::Execute()
                       |
                       +--> 0x006A8720: IsPassiveFront() (checks [pCountry + 0x34AC + enemyTag])
                       |      (Returns 0 during active war -> proceeds to 0x006829B0 every hour)
                       |
                       +--> 0x006829B0: CFrontAI::MoveUnitsToFront()
                       |      |
                       |      +--> [0x00682A43]: skips 0x00682A58 call if reserve vector is empty
                       |      +--> 0x00682A58 -> 0x00681CD0: CFrontAI::ManageRearReserves()
                       |      |      (Hooked by Patch 18 wrapper Cave_FrontAI_ManageReservesAndSalients @ 0x00DCCBB6)
                       |      |      - Retail: stages rear-reserve candidates ([CFrontAI + 0x12A] / +0x12E)
                       |      |        and appends reserve unit TypeIds to [CFrontAI + 0xC8]
                       |      |      - STEM: prunes retail nodes entering STEM Evacuation Mode, shields
                       |      |        evacuating armies ([+0x17B] = 2) during 0x00681CD0, restores [+0x17B],
                       |      |        and exempts evacuating/salient units in [CFrontAI + 0xC8] (tag 0x5A)
                       |      |
                       |      +--> 0x00682AD1 / 0x00682D5C / 0x0068416A / 0x00685086:
                       |             - Computes border province troop quotas (reactive / defensive / op_defensive)
                       |             - Skips any army whose TypeId is in [CFrontAI + 0xC8]
                       |             - Calls StopMovement (0x0050BCA0) on moving armies not matching front quotas
                       |             - Dispatches front redistribution moves via 0x006AAFF0
                       |
                       +--> 0x006853C0: CFrontAI::ExecuteTactical()
                              |
                              +--> 0x00685ED0: CFrontAI::ManageCombat()
                              +--> 0x00689780: CFrontAI::PlanAttacks() (also skips units in [CFrontAI + 0xC8] @ 0x00689C8C)
```

---

## 2. In-Memory Data Structures

### 2.1 `CFrontAI` Structure
Retrieved from the linked list at `pCountry + 0xE86E`. Vtable: `0x007F3868`.

| Offset | Type | Description |
|---|---|---|
| `+0x00` | `void*` | Vtable (`0x007F3868`) |
| `+0x04` | `ListNode*` | Head of front border province descriptors list (`[[node] + 4]` = province ID) |
| `+0x12` | `struct` | Embedded country/tag query subobject (`0x006A9D50`) |
| `+0x1C` | `Country*` | Pointer to owning `Country` object |
| `+0x9E` | `uint8` | Active evaluation flag |
| `+0xA4` | `ListNode*` | Head of assigned `CLandArmy*` linked list for this front |
| `+0xC8` | `CIdList` | `m_ReserveUnits`: linked list of `TypeId` records exempted from border-quota reassignment by `0x006829B0` / `0x00689780` (`Clear` at `[vtable + 0x10]`, `Contains` at `[vtable + 0x24]`, `Insert` at `0x0049A190`, `Remove` at `0x0049A230`; used by both retail `ManageRearReserves` and STEM salient exemptions) |
| `+0x124` | `uint32` | Front distribution mode (`0` = default, `1` = `reactive`, `2` = `defensive`, `3` = `op_defensive`) |
| `+0x125` | `uint8` | Hold-in-place / disable reserve withdrawal flag |
| `+0x126` | `uint32` | Hourly front tick counter |
| `+0x12A` | `CIntList` | `m_RearReserveCandidateProvinces`: interior rear-reserve candidate provinces evaluated by `0x00681CD0` |
| `+0x12E` | `ListNode*` | `m_SelectedRearReserveProvinces`: selected rear-reserve destination province list populated by `0x00681CD0` |

---

## 3. Subsystem Function Directory

| Routine | Virtual Address | Calling Conv. | Description |
|---|---|---|---|
| `CFrontAI::Execute` | `0x006811B0` | `__thiscall` | Master hourly front evaluation entry point. Calls `0x006829B0` and `0x006853C0`. |
| `CFrontAI::MoveUnitsToFront` | `0x006829B0` | `__thiscall` | Evaluates border quotas, calls `ManageRearReserves` via `0x00682A58` (when gated pass at `0x00682A43` succeeds), stops non-conforming marches (`0x0050BCA0`), and dispatches reinforcement moves (`0x006AAFF0`). |
| `CFrontAI::ManageRearReserves` | `0x00681CD0` | `__thiscall` | Retail rear-reserve routine. Selects candidate rear-reserve provinces (`+0x12A` / `+0x12E`) and registers reserve unit `TypeId`s in `[this + 0xC8]` (`m_ReserveUnits`). Wrapped by `0x00DCCBB6` at callsite `0x00682A58`. |
| `CFrontAI::IsFrontProvince` | `0x006813E0` | `__thiscall` | Returns `1` if the given province ID belongs to this front's border province list. |
| `CFrontAI::ExecuteTactical` | `0x006853C0` | `__thiscall` | Coordinates active combat management (`0x00685ED0`) and offensive attack planning (`0x00689780`). |
| `CFrontAI::ManageCombat` | `0x00685ED0` | `__thiscall` | Evaluates ongoing battles on the front for reinforcement or tactical retreat. |
| `CFrontAI::PlanAttacks` | `0x00689780` | `__thiscall` | Plans and initiates frontline attacks into adjacent enemy provinces. |
| `CFrontAI::IsPassiveFront` | `0x006A8720` | `__thiscall` | Checks `[pCountry + 0x34AC + tag]`; returns `0` during active war so `0x006829B0` executes hourly. |

---

## 4. Retail Engine Behavior: Why Multi-Province Salients Are Not Evacuated

Reverse-engineering `0x00681CD0` (`CFrontAI::ManageRearReserves`) and `0x006829B0` (`CFrontAI::MoveUnitsToFront`) reveals why retail Darkest Hour lacks multi-province salient evacuation:

1. **Local Quotas Only & No Topological Neck Detection**:
   - Retail `CFrontAI::ManageRearReserves` (`0x00681CD0`) manages rear-reserve staging rather than topological pocket evacuation, and `CFrontAI::MoveUnitsToFront` (`0x006829B0`, including `0x006831D0` - `0x00684526`) weights border province quotas using local immediate-neighbor scoring rather than global cut-vertex / articulation-point analysis.
   - Consequently, a multi-province salient (connected internally with degree $\ge 2$, but joined to the main interior only through a narrow neck/shoulder pair) continues receiving border allocations unless external evacuation tracking exempts those units.
2. **Aggressive `StopMovement` Override (`0x0068416A`)**:
   - In `0x006829B0`, any assigned front army whose `TypeId` is **not** registered in `[CFrontAI + 0xC8]` (`m_ReserveUnits`) has its movement evaluated against static border quotas. Without registering evacuating units' `TypeId` in `[CFrontAI + 0xC8]` via the `0x00682A58` wrapper (`0x00DCCBB6`), `0x006829B0` (`0x0068416A`) immediately calls `StopMovement` (`0x0050BCA0`) or reassigns the unit back to the border on the very same hour tick, creating an infinite hourly tug-of-war.

---

## 5. Anatomy of Earlier Debugging Pitfalls & Realignment Fixes (Post-Mortem Reference)

| Issue Encountered | Root Cause | Resolution |
|---|---|---|
| **Hooking `0x006A5790` (`CanCommand`) had no effect on Front AI** | `0x006A5790` belongs to `CInvasionAI` (`0x007F4C24`), not `CFrontAI` (`0x007F3868`). | Restored `0x006A5790` to pristine bytes; hooked callsite `0x00682A58` with wrapper `0x00DCCBB6` around retail `CFrontAI::ManageRearReserves` (`0x00681CD0`). |
| **Entire front retreated to Capital (Moscow `175`) on load** | In Tarjan's articulation algorithm, the DFS root (`tin = 1`) trivially satisfies $low[v] \ge tin[root]$ for all children. | Superseded Tarjan in `Cave_STEM_UpdateGraphTable` (`0x00DCBDD5`) with a Local $K$-Hop Frontline Search + Per-Province Vertex-Disjoint Path Search. |
| **Pinned units in combat (Grajewo `6516`) failed to disengage** | Calling `0x00522930` directly leaves the unit attached to `CCombat`; calling `0x004BE920` with `ecx = pCombat` instead of `CLandCombatSide*` hit a no-op slot. | Pass `ecx = [pCombat + 0x84]` (defender side) or `[pCombat + 0x80]` (attacker side) to `0x004BE920`. |
| **Non-combat salient units stood still with 0 Organization** | Zeroing `[pDiv + 0xF4]` or injecting org-mutating hooks (`0x004E7616` / `0x004E7905` / `0x00DCBADC`) corrupted unit organization (`m_fOrganization`). | Never mutate `[pDiv + 0xF4]`; removed `0x004E7616`, `0x004E7905`, and `0x00DCBADC` during Phase 2 cleanup. |
| **Scratchpad `+0x24000` / `+0x26000` flag aliasing & false-positive cuts** | Stride mismatch caused `+0x24000` (`is_threatened`) and `+0x26000` (`is_under_attack`) to alias, and `.tarjan_check_cut` lacked an active-threat shoulder check. | Rebuilt `Cave_STEM_UpdateGraphTable` (`0x00DCBDD5`) with non-overlapping scratchpad arrays and direct safe-path counting up to `SalientNeckWidthThreshold`. |
| **Spearhead exemptions left breakout units stranded or baited** | Unfinished spearhead logic (`SpearheadWinningOdds`, `AbortSpearheadOnNeckCollapse`) exempted attacking stacks blindly from evacuation. | Scrapped both spearhead INI keys; reused slot `0x00DCBAB8` (`0x00DCBB30`) for `SalientSearchDepth`. |
| **Stale STEM evacuations persisted across savegame reload** | `Cave_PostLoadInit` (`0x00DCC9EB`) did not clear `g_pGraphTable + 0x30000..+0x3BFFF` when loading a save without restarting the process. | Added a `48 KB` (`0x3000` dwords) zeroing pass in `Cave_PostLoadInit` (`0x00DCC9EB`) whenever `[0x00DCBAD4] != 0`. |
| **Access violation on `REB` (`0x157`) after multiple reloads** | Non-AI `CCountry` / `CRebelCountry` (`0x007E5934`) allocates only `0x13C84` bytes, so reading `[pCountry + 0x13C84]` reads 4 bytes past heap object bounds into recycled heap data after reloads. | Verified `CAI_Country` vtable (`0x007F66CC` / `0x007E5464`) and `CAI` vtable (`0x007F3D54`) in both `Cave_STEM_HourlyPerCountry` (`0x00DCCAC6`) and `Cave_STEM_UpdateGraphTable` (`0x00DCBDD5`) before reading `+0x13C84`. |
| **Level-component grouping masked coastal/shoulder bottlenecks** | Merging laterally connected `dist >= cur_d` frontline provinces (`3280`+`3281`, `7335`+`102`) let adjacent wide sectors mask narrow bottlenecks on individual provinces. | Replaced level-component aggregation with direct per-province vertex-disjoint path counting from each frontline province (including `is_threatened == 1`). |

---

## 6. Current Patch 18 (STEM) Architecture & Hook Pipeline

### 6.1 Active Binary Hooks (`Darkest Hour.exe` + `.mod` Cave @ `0x00DCBAB0..0x00DCCC3D`)
1. **INI Loader Hook (`0x00DCB7E6` -> `0x00DCBC30..0x00DCBCD7` -> `0x00DCCA4F`)**:
   - Parses `[FrontAI]` parameters from `db/mod_settings.ini` into `0x00DCBAB0..0x00DCBAD0` (`EnableEncirclementDefense`, `SalientNeckWidthThreshold`, `SalientSearchDepth` at `0x00DCBAB8` / key `0x00DCBB30` default `5`, `UseSupplyDepotsAsCores`, `NeckThreatRatio`, `NeckCollapsingOrgThreshold`, plus unreferenced pending slots `SalientEvacuationQuota` `0x00DCBACC` and `BottleneckDefenseBoost` `0x00DCBAD0`).
   - Jumps at `0x00DCBCD7` to `Cave_LoadEngineSettings` (`0x00DCCA4F`), loading `[Engine]` flags into `0x00DCBAD8` (`AlwaysShowMovementArrows`), `0x00DCBAE8` (`AutoNoFog`), and `0x00DCBAEC` (`AutoShowId`). (`[0x00DCBAD4]` stores the `g_pGraphTable` scratchpad pointer.)
2. **Post-Scenario Load Hook (`0x00DCAE55` -> `0x00DCC9EB` `Cave_PostLoadInit`)**:
   - Executes upon scenario or savegame load completion: zeroes `g_pGraphTable + 0x30000..+0x3BFFF` (`48 KB`, clearing both active salient flags and persistent unit evacuation slots when `[0x00DCBAD4] != 0`), then applies `AutoNoFog` (`[0x00DCBAE8] == 1`), `AutoShowId` (`[0x00DCBAEC] == 1`), and `Cave_ShowAllMovingArrows` (`0x00DCC957` when `[0x00DCBAD8] == 1`).
3. **Movement Arrow Deselect Filter (`0x005226C1` -> `0x00DCC9B5` `Cave_DeselectArrows`)**:
   - When `AlwaysShowMovementArrows == 1` (`[0x00DCBAD8]`), prevents `CLandArmy::OnDeselect` from clearing movement/retreat arrows (`0x0040D210` / `0x0040D170`) for actively moving or retreating units.
4. **Hourly Game Loop Hook (`0x005AEDBE` -> `0x00DCCB11` `Cave_STEM_HourlyAllCountries`)**:
   - Runs every hourly tick: maintains `[Engine]` flags, clears `g_pGraphTable + 0x30000` (`8,192` bytes), and iterates country tags to invoke `Cave_STEM_HourlyPerCountry` (`0x00DCCAC6`) when `EnableEncirclementDefense == 1` (`[0x00DCBAB0]`).
5. **Front AI Rear-Reserve & Salient Wrapper Hook (`0x00682A58` -> `0x00DCCBB6` `Cave_FrontAI_ManageReservesAndSalients`)**:
   - Wraps retail `CFrontAI::ManageRearReserves` (`0x00681CD0`) rather than replacing it (note: retail caller gate at `0x00682A43` bypasses `0x00682A58` when `[esi + 0x10C]` is empty and `[esi + 0x125] != 0`).
   - Before calling `0x00681CD0`, prunes previous tick's STEM-tagged nodes (`0x5A`) and any retail rear-reserve node (`+0x0F == 0`) whose unit now has an active STEM evacuation slot (`word [slot + 6] != 0`), then temporarily sets `[pArmy + 0x17B] = 2` on evacuating armies in `[CFrontAI + 0xA4]` so `0x00681CD0` treats them as retreating and does not call `StopMovement` (`0x00682950`) or re-order them back into rear-reserve provinces (`0x0068295D`).
   - Immediately after `0x00681CD0`, normalizes retail reserve entries (`+0x0F = 0`), restores `[pArmy + 0x17B] = 0` where `== 2`, and registers all armies with active STEM evacuation slots (`word [slot + 6] != 0`) or located in `[g_pGraphTable + prov + 0x30000] == 1` provinces into `[CFrontAI + 0xC8]` (`m_ReserveUnits`, tagged `0x5A`) so `CFrontAI::MoveUnitsToFront` (`0x006829B0`) and `CFrontAI::PlanAttacks` (`0x00689780`) do not cancel STEM evacuation orders.

### 6.2 Per-Country Graph Analysis & Persistent Evacuation (`0x00DCBDD5` / `0x00DCC6D0` / `0x00DCC704`)
1. **Active-Front Gate & Clean Table Initialization (`Cave_STEM_UpdateGraphTable` @ `0x00DCBDD5`)**:
   - Exits immediately if `CCountry` vtable is not an AI country (`0x007F66CC` / `0x007E5464`, excluding `0x13C84`-byte `CRebelCountry` and `CHumanCountry`), `CCountry::IsAtPeace` (`0x006A8720`) returns non-zero, `CAI` (`[pCountry + 0x13C84]`) is null or lacks vtable `0x007F3D54`, or `[pCAI + 0x278]` has no active `CFrontAI*` with `m_EnemyFrontProvinces.Count()` (`[pFront + 0x118]`) `> 0`.
   - Initializes all `8,192` 8-byte graph entries (`+0x00000..+0x0FFFF`) cleanly to `dist = 0xFFFF, neck = 0, is_cut = 0, parent = 0` and zeroes scratchpad buffers `+0x10000..+0x2FFFF` (`128 KB`).
2. **Dynamic Threat Scanner (`+0x24000` / `+0x26000`)**:
   - Scans friendly/allied ground combats (`0x004BEBE0`) and advancing hostile armies (`CCountry::IsAtWarWith` @ `0x0044B280`, `+0x264 != 0 && +0x17B == 0`) against dynamically loaded `NeckThreatRatio` (`0x00DCBAC0`) and `NeckCollapsingOrgThreshold` (`0x00DCBAC4`), marking `+0x24000` (`is_threatened`) and `+0x26000` (`has_defenders`).
3. **Local $K$-Hop Frontline Search (`SalientSearchDepth` @ `0x00DCBAB8`)**:
   - Marks threatened friendly provinces (`+0x24000 == 1`), unthreatened `[pFront + 0x04]` frontline entries (`[CFrontProvince* + 0x04]`), and unthreatened accessible neighbors of threatened provinces as exposed frontline seeds (`prov_flags |= 1` in `+0x28000`; unthreatened seeds start with `fdist_plus_1 = 1` in `+0x14000`).
   - Expands inward via bounded BFS (`0..K` hops when `SalientSearchDepth > 0`, or `0x7FFF` unlimited when `SalientSearchDepth <= 0`, i.e., `-1`) through unthreatened accessible provinces (`CCountry::CanEnterOrTraceSupply` @ `0x0044A690`). Threatened provinces remain excluded (`in_safe_bfs == 0`, `dist == 0xFFFF`) from transit.
   - Seeds **Safe Rear Roots (`dist = 0`)** in the reached strip: Capital (`[pCountry + 0x117DE]`) and active Supply Depots (`[0x00DCBABC] == 1` with `[pProv + 0x270] > 0.0f` or supplied controller capital) receive `prov_flags |= 6` (`in_safe_bfs | is_core_root`); $K$-hop horizon provinces (`fdist == K`) with at least one unvisited unthreatened accessible neighbor beyond $K$ receive `prov_flags |= 2` (`in_safe_bfs`).
   - Runs **Pass-1 Local Safe BFS** from `dist == 0` roots strictly within the unthreatened reached strip (`fdist_plus_1 != 0`), recording `dist`, `parent`, and `in_safe_bfs` (`+0x28000 |= 2`).
4. **Per-Province Independent Path Search (`1..W` Paths) & Pass-2 Bridge Fallback**:
   - Seeds the evaluation queue (`+0x1C000`, marked visited in `+0x18000`) with every exposed province `P` (`prov_flags & 1 != 0`) that is either in the safe subgraph (`prov_flags & 2 != 0 && dist > 0`) or threatened (`+0x24000 == 1`).
   - For each `P`, blocks `P` (`+0x2A000`) and runs up to $W = \text{SalientNeckWidthThreshold}$ (`0x00DCBAB4`) shortest-path BFS passes (`+0x2E000` queue, `+0x2C000` per-pass visited, `+0x2A000` per-province blocked, `+0x20000` predecessor `optb_prev` reserved for Option C) through any safe neighbor (`prov_flags & 2 != 0`) toward `dist == 0`, stopping early once `W` vertex-disjoint safe paths are found. Intermediate vertices and non-core horizon roots are blocked per pass; Capital/Depot core roots (`prov_flags & 4 != 0`) remain unblocked.
   - On Pass 1 (`paths_found == 0`), the traceback identifies `first_hop` (`optb_prev[first_hop] == P`) and stores it in `parent[P]` (setting `dist[P] = dist[first_hop] + 1` if `P` was threatened with `dist == 0xFFFF`), so even threatened sources without a Pass-1 parent derive their evacuation step directly from their first safe route.
   - If `1 <= paths_found < W`, sets `neck[P] = parent[P]` (`first_hop`) and enqueues `P`'s un-evaluated safe neighbors (`dist > 0`) into `+0x1C000` so interior pocket provinces behind a narrow/collapsing front are also evaluated. Once the evaluation queue drains, chains `neck[P]` along `parent` through consecutive failing provinces to the first safe ancestor (`neck == 0`) and sets `is_cut[neck[P]] = 1`.
   - Finally, **Pass-2 Bridge Fallback** expands across threatened friendly bridges (`+0x24000 == 1`, bounded to `fdist_plus_1 != 0 || +0x24000 == 1`) to evacuate `0`-safe-path soft-cut pockets.
5. **Persistent Evacuation Registry & Unit Dispatch (`Cave_STEM_GetUnitEvacSlot` @ `0x00DCC6D0` / `Cave_STEM_UpdateAndEvacuate_Internal` @ `0x00DCC704`)**:
   - Tracks per-unit STEM evacuation state across hourly ticks in `g_pGraphTable + 0x34000..0x3BFFF` (`4,096` 8-byte open-addressed slots `[id:u32, type:u16, dest_prov:u16]`, untouched by per-country or per-hour clears and reset on scenario/savegame load by `0x00DCC9EB`).
   - **Pinned Combat Units (`[pArmy + 0x128] != 0`)**: Checks whether `neck[prov] != 0` with a valid adjacent 1-hop `parent[prov]` (`first_hop`); if so, flags `+0x30000 = 1`, records `neck[prov]` in the unit's evacuation slot, and dispatches `CLandCombatSide::OrderRetreat` (`0x004BE920`) toward `parent[prov]`.
   - **Persistent En-Route Check (`[pArmy + 0x128] == 0`)**: Before re-evaluating `neck[prov]`, consults the unit's slot in `g_pGraphTable + 0x34000`. Once the unit reaches `dest_prov` (`prov == dest_prov`), `word [slot + 6]` clears to `0` and normal `CFrontAI` resumes (or starts a new evacuation leg if `dest_prov` itself has `neck != 0`). While `prov != dest_prov` and the unit is actively moving toward `dest_prov` (`[+0x27E] == 1 && [[+0x236]] == dest_prov`, or `[+0x264] == 1 && [+0x268] == dest_prov`), `+0x30000[prov] = 1` stays latched and the march is preserved uninterrupted even if `neck[prov]` changes mid-march or enemy shoulder captures pause combat. If the march stops prematurely before arrival, resumes to `dest_prov` while `dist[dest_prov] != 0xFFFF` (or re-routes via current `neck[prov]`).
   - **Non-Combat Salient Units (`[pArmy + 0x128] == 0` and `neck != 0` and `prov != neck`)**: Flags `+0x30000 = 1`, records `(id, type) -> neck` in the Persistent Evacuation Registry, and, unless already moving to `neck`, issues an overland move order to `neck` via `CAI::DispatchMoveOrder` (`0x006AAFF0`).
   - See [plan_front_ai_encirclement_defense.md](../plans/plan_front_ai_encirclement_defense.md) for remaining known behavioral issues and proposed next-phase solutions.
