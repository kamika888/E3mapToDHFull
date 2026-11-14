# Darkest Hour Front AI Architecture & Evaluation Engine

**Target Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour.exe` (Image Base: `0x00400000`, Vanilla Checksum: `TENE`)  
**Scope**: In-memory architecture of Front AI (`CFrontAI`), hourly front distribution and tactical evaluation loops, retail salient management (`0x00681CD0`), and the Patch 18 Salient Topological Evacuation & Momentum Engine (STEM).

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
                       |      +--> 0x00681CD0: CFrontAI::ManageSalientUnits()
                       |      |      - Populates [CFrontAI + 0x12A] (m_SalientProvinces)
                       |      |      - Populates [CFrontAI + 0xC8]  (m_SalientEvacuatingUnits TypeId list)
                       |      |      - Retail only pulls <= 2 single-connection tip units back by 1 hop
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
| `+0xC8` | `CIdList` | `m_SalientEvacuatingUnits`: linked list of 6-byte `TypeId` (`[type:u16, id:u32]`) records of armies currently evacuating a salient (`Clear` at `[vtable + 0x10]`, `Contains` at `[vtable + 0x24]`, `Insert` at `0x0049A190`) |
| `+0x124` | `uint32` | Front distribution mode (`0` = default, `1` = `reactive`, `2` = `defensive`, `3` = `op_defensive`) |
| `+0x125` | `uint8` | Hold-in-place / disable salient withdrawal flag |
| `+0x126` | `uint32` | Hourly front tick counter |
| `+0x12A` | `CIntList` | `m_SalientProvinces`: interior friendly provinces adjacent to salient border provinces |
| `+0x12E` | `ListNode*` | Head of list of front border provinces having only 1 friendly connection |

---

## 3. Subsystem Function Directory

| Routine | Virtual Address | Calling Conv. | Description |
|---|---|---|---|
| `CFrontAI::Execute` | `0x006811B0` | `__thiscall` | Master hourly front evaluation entry point. Calls `0x006829B0` and `0x006853C0`. |
| `CFrontAI::MoveUnitsToFront` | `0x006829B0` | `__thiscall` | Evaluates border quotas, calls `ManageSalientUnits` (`0x00681CD0`), stops non-conforming marches (`0x0050BCA0`), and dispatches reinforcement moves (`0x006AAFF0`). |
| `CFrontAI::ManageSalientUnits` | `0x00681CD0` | `__thiscall` | Retail salient withdrawal routine. Identifies 1-connection border tips (`+0x12E`), orders up to 2 units to step back 1 hop, and registers their `TypeId` in `[this + 0xC8]`. |
| `CFrontAI::IsFrontProvince` | `0x006813E0` | `__thiscall` | Returns `1` if the given province ID belongs to this front's border province list. |
| `CFrontAI::ExecuteTactical` | `0x006853C0` | `__thiscall` | Coordinates active combat management (`0x00685ED0`) and offensive attack planning (`0x00689780`). |
| `CFrontAI::ManageCombat` | `0x00685ED0` | `__thiscall` | Evaluates ongoing battles on the front for reinforcement or tactical retreat. |
| `CFrontAI::PlanAttacks` | `0x00689780` | `__thiscall` | Plans and initiates frontline attacks into adjacent enemy provinces. |
| `CFrontAI::IsPassiveFront` | `0x006A8720` | `__thiscall` | Checks `[pCountry + 0x34AC + tag]`; returns `0` during active war so `0x006829B0` executes hourly. |

---

## 4. Retail Engine Behavior: Why Multi-Province Salients Are Never Evacuated

Reverse-engineering `0x00681CD0` (`CFrontAI::ManageSalientUnits`) and `0x006829B0` (`CFrontAI::MoveUnitsToFront`) reveals the exact mechanisms of retail Darkest Hour's salient handling:

1. **1-Hop Local Degree Blindness (`+0x12E` & `op_defensive`)**:
   - Retail `CFrontAI` only flags a border province in `[this + 0x12E]` if that individual province has a single friendly neighbor, and `op_defensive` (`0x006831D0` - `0x00684526`) weights province quotas solely by immediate 1-hop friendly neighbor count ($A_i / \sum A$).
   - In any multi-province salient (such as the 5-province Bialystok salient: Augustow `7335`, Grajewo `6516`, Lomza `1875`, Bielsk Podlaski `6515`, Bialystok `505`), the interior and border provinces connect to one another ($\ge 2$ friendly neighbors), blinding the retail engine to the fact that the entire salient is connected to the Soviet interior through a narrow neck (Wolkowysk `102`) flanked by exposed shoulders (Grodno `209` and Brzesc Litewski `503`).
2. **The 2-Unit, 1-Step Cap in `0x00681CD0`**:
   - Even when `0x00681CD0` triggers on narrow tips, it selects at most 2 units, cancels any multi-province path back to the neck, and issues a **1-step** move into an adjacent border province (`7335 -> 209` or `1875 -> 6515`).
3. **Aggressive `StopMovement` Override (`0x0068416A`)**:
   - In `0x006829B0`, any assigned front army whose `TypeId` is **not** registered in `[CFrontAI + 0xC8]` (`m_SalientEvacuatingUnits`) has its movement evaluated against static border quotas. If an external routine orders a salient unit to march to the neck (`102`) without registering its `TypeId` in `[CFrontAI + 0xC8]`, `0x006829B0` (`0x0068416A`) immediately calls `StopMovement` (`0x0050BCA0`) or reassigns the unit back to the border on the very same hour tick, creating an infinite hourly tug-of-war.

---

## 5. Anatomy of Earlier Debugging Pitfalls (Post-Mortem Reference)

| Issue Encountered | Root Cause in Retail Binary | Resolution |
|---|---|---|
| **Hooking `0x006A5790` (`CanCommand`) had no effect on Front AI** | `0x006A5790` belongs to `CInvasionAI` (vtable `0x007F4C24`), not `CFrontAI` (vtable `0x007F3868`). | Restored `0x006A5790` to pristine bytes and hooked `CFrontAI::ManageSalientUnits` at `0x00681CD0` to populate `[CFrontAI + 0xC8]`. |
| **Entire front retreated to Capital (Moscow `175`) on load** | In Tarjan's articulation algorithm, the DFS root (`tin = 1`) trivially satisfies $low[v] \ge tin[root]$ for all children. Marking the root as `is_cut = 1` caused `.neck_propagate` to assign `neck = 175` to every province on the map. | Added explicit root guard (`stack_idx == 0`) in `.tarjan_check_cut` so the BFS/DFS root is never marked as a cut-vertex. |
| **Attack odds check (`SpearheadWinningOdds`) ignored or failed to detect defensive battles** | Checked `[pCombat + 0x40]` (confusing `CCombat` with `CLandCombatSide`) instead of `[[pCombat + 0x78] + 0x12]` (battle province ID on `CCombat`). | Read `[[pCombat + 0x78] + 0x12]` to verify the army is defending its province before calling `CCombat::GetAttackerWinFraction` (`0x004BEBE0`). |
| **Pinned units in combat (Grajewo `6516`) failed to disengage** | Calling `0x00522930` directly leaves the unit attached to `CCombat`; calling `0x004BE920` with `ecx = pCombat` instead of `ecx = [pCombat + 0x84]` (`CLandCombatSide*`) hit `CCombat`'s no-op virtual slot `+0x5C` (`0x004BD460`) instead of `CLandCombatSide::RetreatUnit` (`0x004BE280`). | Pass `ecx = [pCombat + 0x84]` (defender side) or `[pCombat + 0x80]` (attacker side) to `0x004BE920`. |
| **Non-combat salient units stood still with 0 Organization** | Zeroing `[pDiv + 0xF4]` (mistaken for attack cooldown) before calling `0x006AAFF0` wiped `m_fOrganization` (`20.4 -> 0.0`). `CArmy::CanMove` (`0x0051A4C0`) requires average `[pDiv + 0xF4] >= 1.0` (`[0x007E7828]`) in friendly territory, so it rejected every move order with error code `3`. | Never zero `[pDiv + 0xF4]`. |

---

## 6. Current Patch 18 (STEM) Architecture & Hook Pipeline

### 6.1 Active Binary Hooks
1. **INI Loader Hook (`0x00DCB7E6` -> `0x00DCBC00` -> `0x00DCC5FA`)**:
   - Reads `[FrontAI]` parameters into `0x00DCBAB0` - `0x00DCBAD0` and allocates the 256 KB `g_pGraphTable` buffer (`[0x00DCBAD4]`) via `VirtualAlloc`.
   - Chains to `Cave_LoadEngineSettings` (`0x00DCC5FA`), which reads `[Engine]` debugging flags from `db\mod_settings.ini`:
     - `AlwaysShowMovementArrows` (`[0x00DCBAD8]`)
     - `AutoNoFog` (`[0x00DCBAE8]`)
     - `AutoShowId` (`[0x00DCBAEC]`)
2. **Post-Scenario Load Hook (`0x00DCAE55` -> `0x00DCC5B0` `Cave_PostLoadInit`)**:
   - Executes immediately upon scenario or savegame load completion (`FUN_0042E9B0` exit) to apply `AutoNoFog` (`[0x00D610DC] = 1` and `[pPlayerCountry + 0x21E90] = 1`), `AutoShowId` (`[0x00D610E8] = 1`), and `Cave_ShowAllMovingArrows` (`0x00DCC53E`) without waiting for the first hourly tick.
3. **Movement Arrow Deselect Filter (`0x005226C1` -> `0x00DCC57A` `Cave_DeselectArrows`)**:
   - When `AlwaysShowMovementArrows = 1`, prevents `CLandArmy::OnDeselect` from clearing movement/retreat arrows (`0x0040D210` / `0x0040D170`) for actively moving or retreating units.
4. **Hourly Game Loop Hook (`0x005AEDBE` -> `0x00DCC6A2` `Cave_STEM_HourlyAllCountries`)**:
   - Runs at the start of every hourly tick after `AdvanceDate(1)`:
     - Maintains `AutoNoFog`, `AutoShowId`, and `Cave_ShowAllMovingArrows`.
     - Clears the per-province active salient flag array at `g_pGraphTable + 0x30000` (`8,192` bytes).
     - Iterates all country tags `0..0x157`; for each AI-controlled country (`[pCountry + 0x13C84] != 0` and `pCountry != [0x00D0CA90]`), invokes `Cave_STEM_UpdateAndEvacuate_Internal` (`0x00DCC2DB`).
5. **Front AI Salient Exemption Hook (`0x00681CD0` -> `0x00DCC74D` `Cave_FrontAI_ManageSalients`)**:
   - Replaces retail `CFrontAI::ManageSalientUnits` when `EnableEncirclementDefense == 1`:
     - Clears `[CFrontAI + 0x12A]` and `[CFrontAI + 0xC8]`.
     - Iterates `[CFrontAI + 0xA4]` (all armies assigned to the front); for any army stationed in a province flagged with `[g_pGraphTable + prov + 0x30000] == 1`, inserts its `TypeId` (`[pArmy + 0x18]`) into `[CFrontAI + 0xC8]` via `0x0049A190` so `CFrontAI::MoveUnitsToFront` (`0x006829B0`) and `CFrontAI::PlanAttacks` (`0x00689780`) do not cancel or override STEM evacuation orders.

### 6.2 Per-Country Graph Analysis & Evacuation (`0x00DCBDA0` / `0x00DCC2DB`)
1. **Threat Scanner (`0x00DCBDA0`)**:
   - Scans friendly armies (`[pCountry + 0x4508]`):
     - If defending in combat (`[pArmy + 0x128] != 0` and `[[pCombat + 0x78] + 0x12] == prov`), calls `CCombat::GetAttackerWinFraction` (`0x004BEBE0`) and compares attacker win fraction $p$ against $\frac{W}{1 + W}$ where $W = \text{SpearheadWinningOdds}$ (`[0x00DCBAC8]`, default `1.1`, threshold $\approx 0.5238$).
     - If $p \ge \text{Threshold}$, marks the province threatened (`[g_pGraphTable + prov + 0x25000] = 1`); otherwise marks it as holding (`+0x26000 = 1`).
   - Scans moving/attacking armies of other countries targeting friendly-controlled provinces (`[pArmy + 0x13A]`) and marks undefended target provinces as threatened (`+0x25000 = 1`).
2. **Safe Subgraph BFS & Tarjan Articulation Point Detection**:
   - Runs BFS from the Capital (`[pCountry + 0x117DE]`) across friendly-controlled provinces with `threat == 0`, recording `[dist:u16, neck:u16, is_cut:u16, parent:u16]` at `g_pGraphTable + prov * 8`.
   - Runs iterative Tarjan DFS over the Safe Subgraph to identify articulation points (`is_cut = 1`, excluding the BFS root).
   - Propagates the nearest articulation point ID (`neck`) down the BFS tree (`.neck_propagate`).
3. **Unit Evacuation Dispatch (`0x00DCC2DB`)**:
   - **Pinned Combat Units (`[pArmy + 0x128] != 0`)**: Scans adjacent friendly provinces in the Safe Subgraph (`dist != 0xFFFF`). If any safe neighbor lies on the main front (`neck == 0 && is_cut == 0`, e.g., Lida `210` behind Grodno `209`), aborts retreat so the shoulder defender holds its ground. If all safe neighbors belong to the salient/neck (`neck != 0 || is_cut != 0`, e.g., Bialystok `505` behind Grajewo `6516`), selects the safe neighbor with minimum `dist`, flags `+0x30000 = 1`, and dispatches `CLandCombatSide::OrderRetreat` (`0x004BE920`).
   - **Non-Combat Salient Units (`[pArmy + 0x128] == 0` and `neck != 0` and `prov != neck`)**: Flags `+0x30000 = 1`, checks if already marching to `neck` (`[[pArmy + 0x236]] == neck` or `[pArmy + 0x268] == neck`), and if not, dispatches an overland move order to `neck` via `CAI::DispatchMoveOrder` (`0x006AAFF0`).
