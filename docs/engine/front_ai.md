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
                       |      |      (Hooked by Patch 18 wrapper Cave_FrontAI_ManageReservesAndSalients @ 0x00DCCA5B)
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
| `CFrontAI::ManageRearReserves` | `0x00681CD0` | `__thiscall` | Retail rear-reserve routine. Selects candidate rear-reserve provinces (`+0x12A` / `+0x12E`) and registers reserve unit `TypeId`s in `[this + 0xC8]` (`m_ReserveUnits`). Wrapped by `0x00DCCA5B` at callsite `0x00682A58`. |
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
   - In `0x006829B0`, any assigned front army whose `TypeId` is **not** registered in `[CFrontAI + 0xC8]` (`m_ReserveUnits`) has its movement evaluated against static border quotas. Without registering evacuating units' `TypeId` in `[CFrontAI + 0xC8]` via the `0x00682A58` wrapper (`0x00DCCA5B`), `0x006829B0` (`0x0068416A`) immediately calls `StopMovement` (`0x0050BCA0`) or reassigns the unit back to the border on the very same hour tick, creating an infinite hourly tug-of-war.

---

## 5. Anatomy of Earlier Debugging Pitfalls & Realignment Fixes (Post-Mortem Reference)

| Issue Encountered | Root Cause | Resolution |
|---|---|---|
| **Hooking `0x006A5790` (`CanCommand`) had no effect on Front AI** | `0x006A5790` belongs to `CInvasionAI` (`0x007F4C24`), not `CFrontAI` (`0x007F3868`). | Restored `0x006A5790` to pristine bytes; hooked callsite `0x00682A58` with wrapper `0x00DCCA5B` around retail `CFrontAI::ManageRearReserves` (`0x00681CD0`). |
| **Entire front retreated to Capital (Moscow `175`) on load** | In Tarjan's articulation algorithm, the DFS root (`tin = 1`) trivially satisfies $low[v] \ge tin[root]$ for all children. | Added explicit root guard (`stack_idx == 0`) in `.tarjan_check_cut` so the BFS/DFS root is never marked as a cut-vertex. |
| **Pinned units in combat (Grajewo `6516`) failed to disengage** | Calling `0x00522930` directly leaves the unit attached to `CCombat`; calling `0x004BE920` with `ecx = pCombat` instead of `CLandCombatSide*` hit a no-op slot. | Pass `ecx = [pCombat + 0x84]` (defender side) or `[pCombat + 0x80]` (attacker side) to `0x004BE920`. |
| **Non-combat salient units stood still with 0 Organization** | Zeroing `[pDiv + 0xF4]` or injecting org-mutating hooks (`0x004E7616` / `0x004E7905` / `0x00DCBADC`) corrupted unit organization (`m_fOrganization`). | Never mutate `[pDiv + 0xF4]`; removed `0x004E7616`, `0x004E7905`, and `0x00DCBADC` during Phase 2 cleanup. |
| **Scratchpad `+0x24000` / `+0x26000` flag aliasing & false-positive cuts** | Stride mismatch caused `+0x24000` (`is_threatened`) and `+0x26000` (`is_under_attack`) to alias, and `.tarjan_check_cut` lacked an active-threat shoulder check. | Rebuilt `Cave_STEM_UpdateGraphTable` (`0x00DCBDD5`) in Phases 1 & 3A with clean table offsets, non-attacked guard, and single-pass threatened-shoulder cut check. |
| **Spearhead exemptions left breakout units stranded or baited** | Unfinished spearhead logic (`SpearheadWinningOdds`, `AbortSpearheadOnNeckCollapse`) exempted attacking stacks blindly from evacuation. | Scrapped both INI keys and removed dead spearhead checks in Phase 3; kept alignment header slots unreferenced. |

---

## 6. Current Patch 18 (STEM) Architecture & Hook Pipeline

### 6.1 Active Binary Hooks (`Darkest Hour.exe` + `.mod` Cave @ `0x00DCBAB0..0x00DCCBE2`)
1. **INI Loader Hook (`0x00DCB7E6` -> `0x00DCBC00..0x00DCBC2C` -> `0x00DCC90E`)**:
   - Parses `[FrontAI]` parameters from `db/mod_settings.ini` into `0x00DCBAB0..0x00DCBAD0` (`EnableEncirclementDefense`, `SalientNeckWidthThreshold`, `UseSupplyDepotsAsCores`, `NeckThreatRatio`, `NeckCollapsingOrgThreshold`, plus unreferenced pending slots `SalientEvacuationQuota` `0x00DCBACC` and `BottleneckDefenseBoost` `0x00DCBAD0`).
   - Jumps at `0x00DCBCD7` to `Cave_LoadEngineSettings` (`0x00DCC90E`), loading `[Engine]` flags into `0x00DCBAD8` (`AlwaysShowMovementArrows`), `0x00DCBAE8` (`AutoNoFog`), and `0x00DCBAEC` (`AutoShowId`). (`[0x00DCBAD4]` stores the `g_pGraphTable` scratchpad pointer.)
2. **Post-Scenario Load Hook (`0x00DCAE55` -> `0x00DCC8C4` `Cave_PostLoadInit`)**:
   - Executes upon scenario or savegame load completion to apply `AutoNoFog` (`[0x00DCBAE8] == 1`), `AutoShowId` (`[0x00DCBAEC] == 1`), and `Cave_ShowAllMovingArrows` (`0x00DCC830` when `[0x00DCBAD8] == 1`) without waiting for the first hourly tick.
3. **Movement Arrow Deselect Filter (`0x005226C1` -> `0x00DCC88E` `Cave_DeselectArrows`)**:
   - When `AlwaysShowMovementArrows == 1` (`[0x00DCBAD8]`), prevents `CLandArmy::OnDeselect` from clearing movement/retreat arrows (`0x0040D210` / `0x0040D170`) for actively moving or retreating units.
4. **Hourly Game Loop Hook (`0x005AEDBE` -> `0x00DCC9B6` `Cave_STEM_HourlyAllCountries`)**:
   - Runs every hourly tick: maintains `[Engine]` flags, clears `g_pGraphTable + 0x30000`, and iterates country tags to invoke `Cave_STEM_HourlyPerCountry` (`0x00DCC985`) when `EnableEncirclementDefense == 1` (`[0x00DCBAB0]`).
5. **Front AI Rear-Reserve & Salient Wrapper Hook (`0x00682A58` -> `0x00DCCA5B` `Cave_FrontAI_ManageReservesAndSalients`)**:
   - Wraps retail `CFrontAI::ManageRearReserves` (`0x00681CD0`) rather than replacing it (note: retail caller gate at `0x00682A43` bypasses `0x00682A58` when `[esi + 0x10C]` is empty and `[esi + 0x125] != 0`).
   - Before calling `0x00681CD0`, prunes previous tick's STEM-tagged nodes (`0x5A`) and any retail rear-reserve node (`+0x0F == 0`) whose unit now has an active STEM evacuation slot (`word [slot + 6] != 0`), then temporarily sets `[pArmy + 0x17B] = 2` on evacuating armies in `[CFrontAI + 0xA4]` so `0x00681CD0` treats them as retreating and does not call `StopMovement` (`0x00682950`) or re-order them back into rear-reserve provinces (`0x0068295D`).
   - Immediately after `0x00681CD0`, normalizes retail reserve entries (`+0x0F = 0`), restores `[pArmy + 0x17B] = 0` where `== 2`, and registers all armies with active STEM evacuation slots (`word [slot + 6] != 0`) or located in `[g_pGraphTable + prov + 0x30000] == 1` provinces into `[CFrontAI + 0xC8]` (`m_ReserveUnits`, tagged `0x5A`) so `CFrontAI::MoveUnitsToFront` (`0x006829B0`) and `CFrontAI::PlanAttacks` (`0x00689780`) do not cancel STEM evacuation orders.

### 6.2 Per-Country Graph Analysis & Persistent Evacuation (`0x00DCBDD5` / `0x00DCC52D` / `0x00DCC561`)
1. **Dynamic Threat Scanner (`Cave_STEM_UpdateGraphTable` @ `0x00DCBDD5`)**:
   - Scans ground combats and defending armies to mark `+0x26000` (`is_under_attack`) and evaluate friendly vs. hostile strength/organization against dynamically loaded `NeckThreatRatio` (`0x00DCBAC0`) and `NeckCollapsingOrgThreshold` (`0x00DCBAC4`).
   - Non-attacked provinces (`is_under_attack == 0`) are never marked `+0x24000` (`is_threatened`), preventing false positives during quiet buildups or weak probing attacks.
2. **Escape-Root BFS & Allied Access Pathing**:
   - Seeds BFS from the country's Capital (`[pCountry + 0x117DE]`) and, when `UseSupplyDepotsAsCores == 1` (`0x00DCBABC`), from unthreatened accessible provinces (`CCountry::CanEnterOrTraceSupply` @ `0x0044A690`) holding a local supply stockpile (`[pProv + 0x270] > 0.0f`) or a supplied controller capital.
   - Traverses neighbors passing `CCountry::CanEnterOrTraceSupply` (`0x0044A690`; self/ally/puppet/master/access) across provinces with `threat == 0` (using `0x0044B280` for war-target scanning), recording `[dist:u16, neck:u16, is_cut:u16, parent:u16]` at `g_pGraphTable + prov * 8`.
   - Runs Tarjan articulation/bridge analysis with `.tarjan_check_cut` (cut/evacuation propagates only when an adjacent friendly shoulder node has `+0x24000 == 1`, excluding the BFS root) plus Pass-2 bridge fallback controlled by `SalientNeckWidthThreshold` (`0x00DCBAB4`).
3. **Persistent Evacuation Registry & Unit Dispatch (`Cave_STEM_GetUnitEvacSlot` @ `0x00DCC52D` / `Cave_STEM_UpdateAndEvacuate_Internal` @ `0x00DCC561`)**:
   - Tracks per-unit STEM evacuation state across hourly ticks in `g_pGraphTable + 0x34000..0x3BFFF` (`4,096` 8-byte open-addressed slots `[id:u32, type:u16, dest_prov:u16]`, untouched by per-country or per-hour clears).
   - **Pinned Combat Units (`[pArmy + 0x128] != 0`)**: Inspects safe neighbors (`dist != 0xFFFF`). If the unit can hold an un-cut main front or step to a safe core shoulder, aborts retreat; if all safe exits belong to the collapsing salient (`neck != 0 || is_cut != 0`), flags `+0x30000 = 1`, records `dest_prov` (`neck` if non-zero, else `best_nb`) in the unit's evacuation slot, and dispatches `CLandCombatSide::OrderRetreat` (`0x004BE920`).
   - **Persistent En-Route Check (`[pArmy + 0x128] == 0`)**: Before re-evaluating `neck[prov]`, consults the unit's slot in `g_pGraphTable + 0x34000`. Once the unit reaches `dest_prov` (`prov == dest_prov`), `word [slot + 6]` clears to `0` and normal `CFrontAI` resumes (or starts a new evacuation leg if `dest_prov` itself has `neck != 0`). While `prov != dest_prov` and the unit is actively moving toward `dest_prov` (`[+0x27E] == 1 && [[+0x236]] == dest_prov`, or `[+0x264] == 1 && [+0x268] == dest_prov`), `+0x30000[prov] = 1` stays latched and the march is preserved uninterrupted even if `neck[prov]` changes mid-march or enemy shoulder captures pause combat. If the march stops prematurely before arrival, resumes to `dest_prov` while `dist[dest_prov] != 0xFFFF` (or re-routes via current `neck[prov]`).
   - **Non-Combat Salient Units (`[pArmy + 0x128] == 0` and `neck != 0` and `prov != neck`)**: Flags `+0x30000 = 1`, records `(id, type) -> neck` in the Persistent Evacuation Registry, and, unless already moving to `neck`, issues an overland move order to `neck` via `CAI::DispatchMoveOrder` (`0x006AAFF0`).
   - See [plan_front_ai_encirclement_defense.md](../plans/plan_front_ai_encirclement_defense.md) for remaining known behavioral issues and proposed next-phase solutions.
