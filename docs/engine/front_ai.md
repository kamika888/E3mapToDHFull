# Darkest Hour Front AI Architecture & Evaluation Engine

**Target Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour.exe` (Image Base: `0x00400000`, Vanilla Checksum: `TENE`)  
**Scope**: In-memory architecture of Front AI (`CFront`, `CFrontAI`), front evaluation loops, unit assignment algorithms, periodic scheduling, and root-cause analysis of salient encirclement passivity.

---

## 1. Subsystem Architecture Overview

Front AI is the operational theater commander in Darkest Hour. Unlike `CGarrisonAI` (which handles rear-area quotas, homeland defense ratios, and partisan suppression), Front AI governs active border contacts between nations at war or under hostile tension.

The subsystem operates through a hierarchy of linked structures:

```
[Country Object] (Base: [0x0089CAD8 + tag * 4])
       |
       +--> +0x0120: CAI Controller Subsystem (vtable: 0x007F3D54)
       |               +--> CAI::DispatchMoveOrder (0x006AAFF0)
       |
       +--> +0xE86E: Front List Head (singly-linked list of CFront*)
                       |
                       +--> Node 0: CFront* (vtable: 0x007E7D34) -> [Border Provinces, Opposing Tag, Assigned Armies]
                       +--> Node 1: CFront*
                       +--> Node N: ...

[CFrontAI Controller] (vtable: 0x007F6220)
       |
       v
0x006A6DF0: CFrontAI::Update()
       |
       +--> 0x006A6DFF: Checks war state & opposing enemy presence
       |
       v
0x006A6E15: Periodic Evaluation Gate
       |
       +--> 0x006A6A20: CFrontAI::EvaluateArmies()
       |       |
       |       +--> Iterates assigned armies ([this + 0x94])
       |       +--> Checks army province: [pArmy + 0x0C]
       |       +--> Validates terrain entry: 0x005216C0 (CanEnterTerrain)
       |       +--> Dispatches move orders:
       |               - 0x006A5971: Front reinforcement / shift
       |               - 0x006A5F61: Frontline attack / advance
       |               - 0x006A6D83: Flank support / redeploy
       |               All call: 0x006AAFF0 (CAI::DispatchMoveOrder)
       |
       +--> 0x006AE0D0: Reschedules next evaluation:
               Interval = 12 + (rand() % 8) hours
```

---

## 2. In-Memory Data Structures

### 2.1 `CFront` Structure
Base pointer retrieved from the linked list at `pCountry + 0xE86E`.  
Virtual method table at `0x007E7D34`.

```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x00           void*               Vtable (0x007E7D34)
+0x04           void*               Internal state container (vtable: 0x007E4B04)
+0x18           void*               Front node vtable (0x007E7C08)
+0x28           void*               Front segment descriptor (vtable: 0x007E6EAC)
+0x3C           void*               Province list container (vtable: 0x007E8AB0)
+0x44           uint16              Count of provinces comprising this front segment
+0x52           int32               Front Reinforcement Deficit (>0 indicates troop shortage)
+0x8C           uint32              Owning Country Tag (e.g. 7 = SOV)
+0x94           uint32              Opposing Enemy Country Tag (e.g. 3 = GER)
+0x98           uint32              Secondary opposing tag / allied border tag
+0xD8           Country*            Pointer to owning Country object ([0x0DF2D020])
```

#### Traversal Example: Enumerating Fronts of a Country
```c
struct ListNode {
    void*     pItem;   // +0x00: CFront*
    void*     pUnk;    // +0x04
    ListNode* pNext;   // +0x08: Next node or NULL
};

ListNode* pCurr = *(ListNode**)(pCountry + 0xE86E);
while (pCurr != NULL) {
    CFront* pFront = (CFront*)pCurr->pItem;
    uint32_t ownerTag = *(uint32_t*)((uint8_t*)pFront + 0x8C);
    uint32_t enemyTag = *(uint32_t*)((uint8_t*)pFront + 0x94);
    uint16_t provCount = *(uint16_t*)((uint8_t*)pFront + 0x44);
    // Process front...
    pCurr = pCurr->pNext;
}
```

---

### 2.2 `CFrontAI` Controller
Virtual method table at `0x007F6220`. Embedded in the AI subsystem.

```
Vtable Offset   Virtual Address     Method
--------------------------------------------------------------------------------------
+0x00           0x0066F7D0          CFrontAI::Destructor
+0x18           0x006A6870          CFrontAI::Init
+0x2C           0x006A9E50          CFrontAI::Reset
+0x34           0x006A6DF0          CFrontAI::Update (Master periodic evaluation entry)
```

---

## 3. Subsystem Function Directory

| Routine | Virtual Address | Calling Conv. | Description |
|---|---|---|---|
| `CFrontAI::Update` | `0x006A6DF0` | `__thiscall` | Master periodic entry point. Checks war state, invokes evaluation loop, and schedules next evaluation tick. |
| `CFrontAI::EvaluateArmies` | `0x006A6A20` | `__thiscall` | Core decision loop. Iterates assigned armies (`[this + 0x94]`), checks province threat/balance, and dispatches move orders. |
| `CFrontAI::ScheduleTick` | `0x006AE0D0` | `__thiscall` | Schedules the next evaluation tick. Generates randomized delay: `12 + (rand() % 8)` hours. |
| `Front::DispatchReinforce`| `0x006A5971` | `__thiscall` | Dispatches move order to shift division along front line to reinforce deficit province. |
| `Front::DispatchAttack` | `0x006A5F61` | `__thiscall` | Dispatches offensive attack/advance order into adjacent enemy province. |
| `Front::DispatchFlank` | `0x006A6D83` | `__thiscall` | Dispatches flank support or redeployment order to adjacent friendly front province. |
| `CFront::CalcDeficit` | `0x00695380` | `__thiscall` | Calculates division deficit relative to enemy strength directly facing front. |
| `CFront::IsValid` | `0x004CA33C` | `__thiscall` | Validates whether front is active and legal for operational commands. |

---

## 4. Root-Cause Analysis: Salient Encirclement Blindness

During blitzkrieg operations (such as the historical or simulated Białystok pocket), AI divisions stationed in deep forward salients frequently exhibit complete passivity, refusing to pull back even as enemy armored pincers sever their rear supply lines.

Reverse engineering the engine reveals the three structural causes of this behavior:

### 4.1 Cause 1: Static Border Defense Quota Model
- Front AI treats every front as a set of border provinces facing an opposing nation.
- Under standard `reactive` or `defensive` distribution modes, Front AI calculates troop requirements purely to match the enemy divisions directly facing each province across the border.
- In the Białystok salient, the 5 forward Soviet divisions (in Augustow, Bialystok, Bielsk Podlaski, Lomza) face German divisions across the East Prussian and Polish demarcation lines.
- To Front AI, these divisions are **successfully fulfilling their border defense quota**. It sees enemy troops on the other side and concludes that withdrawing would create a front deficit.

### 4.2 Cause 2: Zero Topological / Graph Awareness
- Front AI possesses **no graph traversal or bottleneck detection routines**.
- It does not trace connectivity from forward provinces back to the capital or provincial supply depots.
- When enemy motorized divisions seize the shoulders of the salient (e.g. Grodno `209`, Wolkowysk `102`, Brzesc Litewski `505`), Front AI treats those breakthrough provinces as belonging to adjacent or rear sectors.
- It has no analytical concept of a "pocket neck", "salient width", or "impending encirclement".

### 4.3 Cause 3: The 12-to-20 Hour Evaluation Lag
- Unlike combat and movement (which tick hourly), Front AI evaluation (`0x006A6DF0`) is gated by `0x006AE0D0`:
  $$\text{Interval} = 12 + (\text{rand}() \pmod 8) \quad \text{hours}$$
- Even if a front condition changes drastically, Front AI only evaluates its division assignments once every 12 to 20 in-game hours.
- A fast armored breakthrough can traverse a province and snap a pocket shut before Front AI even executes a single re-evaluation cycle.

---

## 5. Anatomy of Previous Failed Fixes (Post-Mortem)

Understanding why earlier patching attempts failed is essential for future development:

| Attempted Mechanism | Intended Role | Actual Runtime Reality (Why It Failed) |
|---|---|---|
| **Hook at `0x00681269`** | Intercept front AI evaluation loop | **Dead code**. Dynamic breakpoint tracing in x32dbg proved this hook had a **hit count of 0**. The active front execution path never passed through this branch during wartime because `IsAtWar()` (`0x006A8720`) bypasses `0x0068XXXX` entirely. |
| **Hook at `0x0042F6C0`** | Hourly Country Loop dispatch | **Scenario loader, not hourly tick**. Reverse-engineering `FUN_0042efb0` proved this country loop only runs once during scenario initialization (`INIT_PROVINCES`, `INIT_SCENARIO`, `INIT_SCRIPT`). It never runs during live gameplay. |
| **Call to `0x005091C0`** | Issue retreat / move orders | **Read-only query**. `0x005091C0` is `CLandArmy::CanMoveTo(provId)`. It merely checks if `provId` is an adjacent neighbor and returns 0 or 1 in `AL`. It issues no orders, alters no state, and touches no queues. |
| **Missing Pipeline State** | Initiate division march | Movement requires a 5-step execution sequence: (1) `CAI::DispatchMoveOrder` (`0x006AAFF0`), (2) `m_missionType = 1` (`+0x264`), (3) `m_targetProv = target` (`+0x268`), (4) `CLandArmy::StartMoving` (`0x00523250`), and (5) `CLandArmy::UpdateMovementArrow` (`0x00522650`). Omitting any step leaves units stationary. |

---

## 6. Correct Blueprint for Encirclement Defense Modifications

To implement working anti-encirclement logic in the engine:

1. **Target the Real Front Evaluation Loop**:
   Hook `CFrontAI::EvaluateArmies` at `0x006A6A20` or its caller `0x006A6DF0`. This is the verified live execution path where Front AI evaluates assigned armies.
2. **Perform Graph Traversal (BFS / DFS)**:
   Trace friendly land connectivity from forward front provinces back to the national capital or nearest friendly supply depot. Compute bottleneck width (`min_neck_width`).
3. **Trigger Evacuation via Valid Move Dispatch**:
   When `min_neck_width <= 2` and the bottleneck province is threatened or in combat, override the border quota and dispatch an immediate move order to the bottleneck using the verified 3-step pipeline:
   ```assembly
   ; 1. Dispatch move order via AI dispatcher
   push 0
   push pBottleneckProvince
   push pArmy
   mov  ecx, pAI
   call 0x006AAFF0

   ; 2. Ensure mission controller fields
   mov  dword ptr [pArmy + 0x264], 1      ; MOVE
   mov  dword ptr [pArmy + 0x268], bottleneckProvId
   mov  dword ptr [pArmy + 0x26C], 0x3F800000 ; 1.0f

   ; 3. Activate movement execution & map arrow
   mov  ecx, pArmy
   call 0x00523250                       ; StartMoving
   mov  ecx, pArmy
   call 0x00522650                       ; UpdateMovementArrow
   ```

---

## 7. Working Implementation: Patch 18 (STEM) & Live Verification

The complete working Encirclement Defense System (Patch 18) was verified and deployed using the following architecture:

### 7.1 Architecture & Hook Pipeline
1. **Hourly Tick Hook at `0x005AEDBE`** (`FUN_005aec40`):
   Dispatched immediately after `AdvanceDate(1)` (`0x0042CF30`) on every single in-game hour:
   ```assembly
   0x005AEDBE: call 0x00DCC44D  ; Cave_STEM_HourlyAllCountries
   0x005AEDC3: nop
   0x005AEDC4: nop
   0x005AEDC5: mov esi, eax
   0x005AEDC7: nop
   0x005AEDC8: nop
   0x005AEDC9: nop
   ```
2. **All-Country Dispatcher at `0x00DCC44D`** (in `.mod` code cave):
   Increments hourly generation counter (`inc dword ptr [0x00DCBADC]`) and iterates through country tags `0` to `0x157`. For each nation with an active AI (`pAI != NULL`, skipping human player `[0x00D0CA90]`), it invokes `Cave_STEM_HourlyHook`:
   ```assembly
   0x00DCC44D: pushal
   0x00DCC44E: pushfd
   0x00DCC44F: inc dword ptr [0x00DCBADC]
   0x00DCC455: xor esi, esi
   0x00DCC457: call Cave_STEM_HourlyHook
   0x00DCC45C: inc esi
   0x00DCC45D: cmp esi, 0x158
   0x00DCC463: jl 0x00DCC457
   0x00DCC465: popfd
   0x00DCC466: popal
   0x00DCC467: push 0x0C
   0x00DCC469: mov eax, 0x007A635C ; operator new
   0x00DCC46E: call eax
   0x00DCC470: add esp, 4          ; Balance argument
   0x00DCC473: ret
   ```
3. **Graph Topology, Threat Scanner & Two-Pass Exit Analysis (`0x00DCBDA0`)**:
   - **Active Threat Scanner**: Scans friendly armies. If an army is actively defending in combat (`[edi + 0x128] != 0`), its province is marked threatened in the threat table (`[pGraph + prov + 0x25000] = 1`).
   - **Safe Graph BFS & Tarjan DFS**: Runs BFS and Tarjan's bridge algorithm from national capital/depots strictly across *unthreatened* friendly provinces. When a salient shoulder enters combat (e.g. Grodno `209` under attack), Grodno is excluded from the safe graph, immediately turning the remaining corridor (Wołkowysk `102`) into an articulation point (`is_cut = 1`, `neck = 102`) days before the shoulder falls.
   - **Pass 2 (Breakout Gateways)**: If all exits are under attack or collapsed (e.g. simultaneous assaults on both shoulders), Pass 2 identifies threatened provinces directly bordering safe rear provinces as breakout gateways, routing pocket divisions toward the best gateway rather than stranding them.
4. **Discriminative Move vs. Retreat Order Dispatch**:
   Divisions in the pocket are evaluated against their calculated neck gateway:
   - **Units in Active Combat (`[edi + 0x128] != 0`)**: Dispatches a tactical disengagement retreat to the bottleneck via `0x004BE920` (`CCombat::OrderRetreat`).
   - **Units Not in Combat (`[edi + 0x128] == 0`)**: Aborts existing stationary/patrol orders via `0x0050BCA0` and dispatches a clean operational march order to the bottleneck via `0x006AAFF0` (`CAI::DispatchMoveOrder`).
   - Indiscriminate drawing of global map retreat vectors (`0x00523250` / `0x00522650`) is completely removed, preserving standard fog-of-war counter icons.

### 7.2 Verification Results
- **Move vs. Retreat**: Verified in live memory that unengaged infantry and motorized divisions in the Białystok pocket receive standard move orders rather than combat retreat states.
- **Map Vector Elimination**: Confirmed zero visible grey arrows rendered across the map when viewing opposing AI movements as Germany.
- **Early Trigger on Shoulder Attack**: Verified that as soon as Grodno is attacked, the safe topology instantly designates Wołkowysk (`102`) as the sole articulation neck, initiating evacuation days before panzers can close the corridor.
- **Simultaneous Neck Assault (Pass 2)**: Tested against simultaneous attacks on both Grodno and Wołkowysk; pocket divisions successfully designated breakout vectors rather than locking into passive idle states.
