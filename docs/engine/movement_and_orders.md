# Darkest Hour Land Movement, Orders & Pathfinding Subsystem

**Target Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour.exe` (Image Base: `0x00400000`, Vanilla Checksum: `TENE`)  
**Scope**: In-memory unit representation (`CLandArmy`), mission control (`CMissionController`), province memory structures (`CProvince`), the movement dispatch and pathfinding pipeline, and actionable instructions for issuing move orders via live memory manipulation.

---

## 1. Subsystem Architecture Overview

Movement in Darkest Hour operates through a multi-tiered pipeline connecting high-level AI directives, intermediate order validation, the A* pathfinder, graphical map representation, and the low-level discrete event scheduler:

```
[CAI Subsystem] (pAI: [pCountry + 0x13C84])
       |
       v
0x006AAFF0: CAI::DispatchMoveOrder(pArmy, pTargetProvince, 0)
       |
       v
0x006AABA0: CAI::ProcessOrderMove(pArmy, pTargetProvince, &stackOrder, 0)
       |
       +--> 0x0051A4C0: CanMove / Combat Check (m_bMoving == 0 && !IsInCombat)
       +--> 0x0051B230: GetCurrentProvince (ecx = pArmy) -> pCurrentProvince
       |
       v
0x00431220: COrderMove::Execute(pArmy, pCurrentProvince, pTargetProvince)
       |
       +--> 0x00431BB0: ValidateRoute (Adjacency & impassable checks)
       +--> A* Pathfinding: Calculates travel duration, terrain friction & ETA
       +--> 0x00893768: Event Priority Heap Enqueue (schedules arrival tick)
       |
       v
0x00523250: CLandArmy::StartMoving()
       |
       +--> Sets m_bMoving = 1 (pArmy + 0x17B)
       +--> Updates Map Counter Animation ([pArmy + 0x15A]->SetAnimation("march"))
       +--> Plays March Sound (ID 0x19)
       |
       v
0x00522650: CLandArmy::UpdateMovementArrow()
       |
       +--> 0x00522380: Injects waypoint nodes into Map Renderer (0x00D12B40)
```

---

## 2. Core Data Structure Memory Layouts

### 2.1 `CLandArmy` (Army / Corps Instance)
Virtual method table at `0x007E85C0`. Size: `0x320` bytes.

| Offset | Type | Field Name | Description |
|---|---|---|---|
| `+0x000` | `void*` | `vtable` | Points to `0x007E85C0` (`CLandArmy` vtable) |
| `+0x004` | `char*` | `m_szName` | Pointer to null-terminated ASCII unit name (e.g. `"29-ya Motorizovannaya Diviziya"`) |
| `+0x00C` | `uint16_t` | `m_curProv` | Current province ID where army is stationed |
| `+0x010` | `void*` | `m_pDivisionList` | Head of linked list containing child division objects |
| `+0x018` | `uint16_t` | `m_idType` | Unit ID type field (e.g. `10848` / `0x2A60`) |
| `+0x01A` | `uint16_t` | `m_idNumber` | Unit ID sequential number (e.g. `9` / `0x0009`) |
| `+0x028` | `void*` | `IsLandArmy` | Virtual call (`+0x28`): returns `1` for land armies (`0x00509C90`) |
| `+0x11C` | `struct` | `m_CombatState` | Combat controller structure (`+0x00`: vtable `0x007E8B04`, `+0x0C`: combat active flag) |
| `+0x15A` | `void*` | `m_pMapSprite` | Pointer to map counter / graphical sprite representation |
| `+0x17B` | `uint8_t` | `m_bMoving` | **Movement State Byte**: `1` = actively marching, `0` = stationary / idle |
| `+0x17E` | `uint8_t` | `m_bArrowDirty` | Movement arrow redraw flag (`1` = needs graphics update) |
| `+0x1F0` | `void*` | `m_pMovementPath` | Path node container |
| `+0x22E` | `void*` | `m_WaypointVtable` | Points to `0x007EAAD0` (waypoint container vtable) |
| `+0x230` | `void*` | `m_pWaypoints` | Active waypoint list pointer |
| `+0x238` | `uint16_t` | `m_nWaypointCount`| Number of pending waypoints in path queue |
| `+0x240` | `uint16_t` | `m_startProv` | Starting province ID of the current move leg |
| `+0x248` | `Country*` | `m_pCountry` | Base pointer to owning `Country` object (`[pArmy + 0x248]`) |
| `+0x260` | `struct` | `m_MissionCtrl` | Embedded `CMissionController` structure (`0x60` bytes) |
| `+0x264` | `uint32_t` | `m_missionType` | Mission type in controller: `1` = `MOVE`, `0` = `NONE` |
| `+0x268` | `uint32_t` | `m_targetProv` | Target province ID in controller |
| `+0x26C` | `float` | `m_speedFactor` | Movement speed scalar (`1.0f` = `0x3F800000`) |
| `+0x270` | `uint32_t` | `m_startDate` | Packed start date timestamp |
| `+0x27E` | `uint16_t` | `m_activeMission`| Active execution mission type (`1` = `MOVE`) |
| `+0x282` | `uint16_t` | `m_destProv` | Destination province ID |

---

### 2.2 `CMissionController` (Embedded at `pArmy + 0x260`)
Virtual method table at `0x007E8754`. Manages AI and player mission directives.

```
Offset from Army  Internal Offset  Type        Description
--------------------------------------------------------------------------------------
+0x260            +0x00            void*       Vtable (0x007E8754)
+0x264            +0x04            uint32_t    Mission Type: 0=None, 1=Move, 2=Attack...
+0x268            +0x08            uint32_t    Target Province ID
+0x26C            +0x0C            float       Speed Multiplier (standard 1.0f = 0x3F800000)
+0x270            +0x10            uint32_t    Mission Start Date / Time
+0x27C            +0x1C            uint16_t    Mission Active Flag (1 = active)
+0x27E            +0x1E            uint16_t    Active Mission Code (1 = MOVE)
+0x282            +0x22            uint16_t    Destination Province ID
```

---

### 2.3 `CProvince` Structure
All provinces are stored in a contiguous array in the engine heap.

- **Base Pointer**: `*(uint32_t*)0x00AB27B4`
- **Structure Stride**: `0x4B2` (1,202 bytes)
- **Direct Address Formula**:
  $$\text{Address}(ID) = \text{prov\_base} + ID \times \text{0x4B2}$$

| Offset | Type | Field Name | Description |
|---|---|---|---|
| `+0x000` | `void*` | `vtable` | Province object virtual table |
| `+0x00C` | `uint16_t` | `m_ownerTag` | Country ID of legal owner |
| `+0x00E` | `uint16_t` | `m_controllerTag` | Country ID of current military controller |
| `+0x012` | `uint16_t` | `m_provinceId` | Province numerical ID |
| `+0x180` | `uint8_t` | `m_bBlocked` | Impassable / closed border flag (`1` = blocked) |
| `+0x254` | `uint32_t` | `m_terrainType` | Terrain classification (`8` = Sea, `9` = Ocean) |
| `+0x290` | `uint32_t` | `m_nNeighborCount`| Count of adjacent neighbors |
| `+0x298` | `void*` | `m_pNeighbors` | Pointer to adjacency array (12 bytes per record) |
|          | `+0x00` | `uint32_t` | Neighbor Province ID |
|          | `+0x04` | `uint32_t` | Border Type (0 = normal, 1 = river...) |
|          | `+0x08` | `uint32_t` | Distance / Connection Flags |
| `+0x471` | `uint8_t` | `m_bDirectSea` | Direct sea access flag |

---

## 3. Subsystem Function Directory

| Routine | Virtual Address | Calling Conv. | Arguments | Description |
|---|---|---|---|---|
| `CAI::DispatchMoveOrder` | `0x006AAFF0` | `__thiscall` | `(pArmy, pTargetProv, 0)` (`ecx = pAI`) | Master AI move order entry point. Prepares order stack, validates army state, and dispatches. |
| `CAI::ProcessOrderMove` | `0x006AABA0` | `__thiscall` | `(pArmy, pTargetProv, &order, 0)` | Validates movement legality, calls pathfinder, updates waypoint queue. |
| `COrderMove::Execute` | `0x00431220` | `__thiscall` | `(pArmy, pCurProv, pTargetProv)` (`ecx = &order`) | Runs A* pathfinding, computes travel time, schedules tick in priority heap `0x00893768`. |
| `COrderMove::ValidateRoute` | `0x00431BB0` | `__stdcall` | `(pArmy, pCurProv, pTargetProv)` | Route and adjacency validator. |
| `CLandArmy::CanMoveTo` | `0x005091C0` | `__thiscall` | `(uint32_t targetProvId)` (`ecx = pArmy`) | Fast adjacency query. Returns `1` if target province is a legal neighbor. |
| `CLandArmy::CanEnterTerrain` | `0x005216C0` | `__thiscall` | `(CProvince* pTargetProv)` (`ecx = pArmy`) | Validates if all units in division list can traverse target terrain. |
| `CLandArmy::StartMoving` | `0x00523250` | `__thiscall` | None (`ecx = pArmy`) | Sets `m_bMoving = 1`, triggers sprite march animation, plays march sound. |
| `CLandArmy::StopMoving` | `0x005232B0` | `__thiscall` | None (`ecx = pArmy`) | Clears `m_bMoving = 0`, resets map counter state to stationary. |
| `CLandArmy::UpdateMovementArrow` | `0x00522650` | `__thiscall` | None (`ecx = pArmy`) | Traverses waypoints and draws red directional movement arrow on map. |
| `GetProvince` | `0x004E9370` | `__cdecl` | `(uint32_t provId)` | Returns pointer `prov_base + provId * 0x4B2`. |
| `CLandArmy::GetCurrentProvince`| `0x0051B230` | `__thiscall` | None (`ecx = pArmy`) | Returns `GetProvince(pArmy->cur_prov)`. |

---

## 4. Instructions: Issuing Move Orders via Live Memory Manipulation

To order an army to move without restarting the game, patching disk executables, or desynchronizing simulation state, the move order must be dispatched on the **main engine thread** within the active game loop.

### 4.1 Prerequisites & Pointer Discovery
1. **Find Army Object (`pArmy`)**:
   Scan memory for the army's name string or traverse the country's army list starting from `Country* pCountry = *(Country**)(0x0089CAD8 + tag * 4)`.
2. **Resolve Target Province (`pTargetProvince`)**:
   ```python
   prov_base = *(uint32_t*)0x00AB27B4
   pTargetProvince = prov_base + target_prov_id * 0x4B2
   ```
3. **Resolve AI Subsystem Pointer (`pAI`)**:
   ```python
   pAI = *(uint32_t*)(pCountry + 0x13C84)
   ```

---

### 4.2 Injection Mechanism (Clean Main-Thread Hook)

The game loop contains a continuously executed message pump hook at `0x007902E4`:
```assembly
0x007902E4: 6A 00                push 0
0x007902E6: 8B 0D 48 33 D1 00    mov  ecx, dword ptr [0x00D13348]
0x007902EC: E8 EF 06 F4 FF       call 0x006D09E0
```

By temporarily setting `EIP` of the main thread (while paused in x32dbg) to an allocated memory page, the injection runs synchronously in the main thread's execution context.

#### Complete Assembly Injection Stub
```assembly
; --- Save CPU Context ---
pushad
pushfd

; --- Step 1: Dispatch Master AI Move Order ---
push 0                       ; arg3: flags (0)
push <pTargetProvince>       ; arg2: target province pointer
push <pArmy>                 ; arg1: army pointer
mov  ecx, <pAI>              ; this: AI controller pointer
mov  edx, 0x006AAFF0         ; CAI::DispatchMoveOrder
call edx

; --- Step 2: Ensure Controller State & Start Marching ---
mov  ecx, <pArmy>
mov  dword ptr [ecx + 0x264], 1              ; mission_type = MOVE (1)
mov  dword ptr [ecx + 0x268], <targetProvId> ; target_prov
mov  dword ptr [ecx + 0x26C], 0x3F800000     ; speed_factor = 1.0f

; Call StartMoving (sets m_bMoving = 1, activates sprite)
mov  eax, 0x00523250
call eax

; Call UpdateMovementArrow (renders arrow on map)
mov  ecx, <pArmy>
mov  eax, 0x00522650
call eax

; --- Step 3: Restore CPU Context ---
popfd
popad

; --- Step 4: Displaced Game Loop Instructions & Return ---
push 0
mov  ecx, dword ptr [0x00D13348]
push 0x007902EC              ; Return site
ret
```

---

### 4.3 Step-by-Step Execution Protocol (x32dbg / Python)

1. **Pause Main Thread at Game Loop**:
   - Set a software breakpoint at `0x007902E4`.
   - The breakpoint hits immediately (executed every render frame).
2. **Allocate Executable Memory**:
   - Call `VirtualAllocEx(hProcess, NULL, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)`.
3. **Write Machine Code Stub**:
   - Assemble the stub above using target pointers (`pArmy`, `pTargetProvince`, `pAI`).
   - Write bytes into the allocated page using `WriteProcessMemory`.
4. **Redirect Execution**:
   - Set a singleshot breakpoint at `0x007902EC` (the return site).
   - Delete the breakpoint at `0x007902E4`.
   - Set register `EIP` = base address of allocated stub.
5. **Resume Execution**:
   - Resume debugger (`F9` / `run`).
   - The main thread executes the stub, completes the move order, and halts at `0x007902EC`.
6. **Resume Normal Play**:
   - Delete breakpoint at `0x007902EC`.
   - Resume debugger (`F9`).
   - The game continues running normally with the move order in full effect.

---

### 4.4 Verification Checklist

After executing the injection, verify the following fields in memory:

| Field | Address / Offset | Expected Value | Meaning |
|---|---|---|---|
| `m_bMoving` | `[pArmy + 0x17B]` | `1` | Division is actively in motion |
| `m_targetProv` | `[pArmy + 0x268]` | `<targetProvId>` | Target province recorded in controller |
| `m_destProv` | `[pArmy + 0x282]` | `<targetProvId>` | Final destination recorded |
| `m_missionType` | `[pArmy + 0x264]` | `1` | Mission type is set to `MOVE` |
| `m_pWaypoints` | `[pArmy + 0x230]` | Non-zero pointer | Waypoint queue is populated |
| Hourly Tick | `[0x00893530] + 0x14` | Date advances | Time step decrements travel distance |
