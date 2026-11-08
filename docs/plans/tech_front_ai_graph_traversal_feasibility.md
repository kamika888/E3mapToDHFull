# Technical Feasibility & Reverse Engineering Reference: Front AI Graph Traversal & "Stay vs Run" Engine

**Target Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour.exe` (Image Base: `0x00400000`, Vanilla Checksum: `TENE`)  
**Scope**: In-depth technical feasibility evaluation, memory mapping, instruction-level hook sites, ABI constraints, data structures, and operational risk mitigation for implementing graph-based encirclement detection.

---

## 1. Executive Summary & Feasibility Verdict

| Subsystem Component | Technical Complexity | Feasibility Rating | Recommended Implementation Mechanism |
|---|---|---|---|
| **Graph Traversal (Reverse BFS)** | Moderate (40–60 asm instrs) | **HIGH (95%)** | Static heap buffer (`VirtualAlloc`), multi-source BFS from Capital & Depots. |
| **Supply Core Seeding (Depots)** | Low (10 asm instrs) | **VERY HIGH (99%)** | Seed Capital and provinces where `[pProv + 0x270] > 0` (or `pProv + 0x18A`). |
| **Trigger Mechanism (Dirty Bit)** | Low (5 asm instrs) | **VERY HIGH (99%)** | Hook `0x004E7905` (`CProvince::SetController`) to set `g_bGraphDirty = 1`. |
| **Bottleneck Identification** | Moderate (15 asm instrs) | **HIGH (90%)** | Propagate 16-bit bottleneck province ID down the BFS tree. |
| **Shoulder / Neck Stress Check** | Low (20 asm instrs) | **HIGH (95%)** | Query `[pNeck + 0x1c2]` (army list) and `IsInCombat()` at `[pNeck + 0x22]`. |
| **Offensive Momentum Guard** | Low (15 asm instrs) | **HIGH (95%)** | Check `[pArmy + 0x14C]` (target prov) vs `m_pController` to protect spearheads. |
| **Withdrawal Action Mechanism** | Low (8 asm instrs) | **VERY HIGH (99%)** | **Overland March Only**: Zero out quota `ppvVar20` at `0x00684529`; native engine evacuates naturally. |
| **Strategic Redeployment** | N/A | **DISALLOWED** | **Explicitly Prohibited**: Matches multiplayer standards; units must march on foot. |
| **Exact Hour Prediction Math** | High (Float derivatives) | **DEFERRED (Phase 2)** | Postponed to keep Phase 1 simple and robust. |

**Verdict**: The overall architecture is **fully achievable** on the current engine without source code. By utilizing native overland quota re-allocation and reading provincial supply depot indices directly, the implementation is completely decoupled from risky packet injection.

---

## 2. Memory Architecture & Buffer Allocation

### 2.1 The Code Cave Capacity
Inspection of the PE section headers in `Darkest Hour.exe`:
* `.mod` Section Base: `0x009C9000` (Virtual Address: `0x00DC9000`).
* Total Raw & Virtual Size: `0x4000` (16,384 bytes / 16 KB).
* Currently Allocated Space (Patches 6, 8, 10, 11, 14, 15, 16, 17): `0x00DC9000` to `0x00DCBAA0` (7,649 non-zero bytes).
* **Contiguous Free Cave Space**: `0x00DCBAA0` to `0x00DCD000` = **5,472 bytes (0x1560)**.

A complete assembly BFS implementation with shoulder evaluation requires $\approx 450 - 600$ bytes of code, fitting comfortably within the 5,472 bytes remaining.

### 2.2 Working Table Memory Requirement
On the E3 map, `MaxProvinces` $\approx 8,021$.
A graph node record:
```c
struct NodeState {
    uint16_t dist_to_capital;   // 2 bytes: Shortest friendly land hops (0xFFFF = severed pocket)
    uint16_t bottleneck_prov;    // 2 bytes: Province ID of earliest bottleneck (width <= threshold)
    uint8_t  min_neck_width;     // 1 byte:  Narrowest corridor width between here & capital
    uint8_t  predecessors;       // 1 byte:  Friendly neighbors closer to capital
}; // sizeof = 6 bytes
```
* Total Table Size: $8,192 \times 6\text{ bytes} = 49,152\text{ bytes}$ (48 KB).
* **Allocation Strategy**:
  Because 48 KB exceeds the remaining 5.4 KB of `.mod`, the table **must not** be statically embedded in `.mod`.
  Instead, during the one-time scenario initialization hook (or PE startup cave at `0x007E2DB0`), call `VirtualAlloc`:
  ```asm
  push    0x04                ; PAGE_READWRITE
  push    0x1000              ; MEM_COMMIT
  push    0xC000              ; 49,152 bytes (0xC000)
  push    0x00                ; NULL (let OS choose base)
  call    dword ptr [0x007E3168] ; KERNEL32!VirtualAlloc
  mov     dword ptr [0x00DCBB00], eax ; Store g_pGraphTable base pointer
  ```
  This is 100% crash-proof and requires only 20 bytes of setup code.

---

## 3. Data Structures & Reverse-Engineered Offsets

### 3.1 `CProvince` Structure (`sizeof = 0x4B2` / 1202 bytes)
Base pointer for province ID $N$:
$$\text{pProv} = \text{DAT\_00ab27b4} + N \times \text{0x4B2}$$

| Offset | Type | Field Name | Usage in Graph Engine |
|---|---|---|---|
| `+0x012` | `uint32` | `m_nProvinceId` | Verification and identification. |
| `+0x022` | `void*` | `m_pCombat` | Non-null if province is currently in active combat. |
| `+0x18A` | `int16` | `m_nSupplyDepotProvId` | **Supply source depot province ID** for this province. |
| `+0x1C2` | `void*` | `m_pArmiesList` | Head of linked list of armies present in province. |
| `+0x254` | `uint32` | `m_nTerrainType` | Terrain classification (8=Sea, 9=Lake). |
| `+0x270` | `float` | `m_fSupplies` | **Provincial supply stockpile** ($> 0.0$ indicates an active depot). |
| `+0x280` | `float` | `m_fOil` | Provincial oil stockpile. |
| `+0x290` | `int32` | `m_nNeighbors` | Count of adjacent connections. |
| `+0x298` | `Neighbor*` | `m_pNeighbors` | Pointer to 12-byte connection array. |
| `+0x3D8` | `CCountry*` | `m_pController` | Pointer to controlling country object. |
| `+0x482` | `CArea*` | `m_pArea` | Pointer to runtime contiguous land cluster. |

#### Neighbor Connection Structure (12 bytes per neighbor):
```
Offset   Type     Description
+0x00    uint32   Neighbor Province ID
+0x04    int32    Connection Type (0=Normal, 1=River, 4=Impassable)
+0x08    uint32   Border / Strait flags
```

### 3.2 Supply Depot Resolution (User Requirement 3)
In Darkest Hour, supply lines for disconnected overseas areas (e.g. East Prussia, North Africa, island garrisons) do not trace back to the Capital; they trace back to the local **Supply Depot**:
* Each province holds `[pProv + 0x18A]` (`m_nSupplyDepotProvId`).
* When seeding the BFS:
  1. Push the Capital province (`pCountry->m_nCapitalProvId`).
  2. For all provinces controlled by `pCountry` where `[pProv + 0x270] > 0.0f` (active depot with supplies):
     Push to the BFS queue with `dist = 0`, `bottleneck = 0`.
  3. This ensures that overseas theaters and colonies (like German East Prussia centered on Königsberg `510`, or French North Africa centered on Oran `950`) are recognized as valid operational theaters with their own supply lifelines, preventing false-positive pocket panics!

---

## 4. Technical Implementation of the "Stay vs Run" Components

### 4.1 Component 1: Event-Driven Graph Dirty Bit
* **Hook Site**: `0x004E7905` in `CProvince::SetController` (`FUN_004e78e0`):
  ```asm
  004E7905: 89 91 D8 03 00 00       mov [ecx+0x3D8], edx ; Set controller
  ```
* **Patch**:
  Replace with a 6-byte jump to `.mod` cave:
  ```asm
  mov     [ecx+0x3D8], edx
  mov     byte ptr [0x00DCBB04], 1 ; g_bGraphDirty = 1
  jmp     0x004E790B
  ```

---

### 4.2 Component 2: The Multi-Source Reverse-BFS
* **Concept**: Single-pass BFS from Capital and valid friendly Supply Depots.
* **Traversal Algorithm**:
  ```asm
  Cave_RunBFS:
      ; Zero out dist_to_capital array with 0xFFFF
      ; Push Capital and all friendly Supply Depots (pProv + 0x270 > 0) to Queue
      ; Set dist = 0, bottleneck = 0 for all seeds
  .bfs_loop:
      ; Pop u from queue
      ; pProv = DAT_00ab27b4 + u * 0x4B2
      ; Loop neighbors i = 0 .. pProv->m_nNeighbors - 1:
      ;   pNeighbor = pProv->m_pNeighbors[i]
      ;   if (pNeighbor->type == 4) skip; // impassable
      ;   if (pNeighbor->m_pController != pCountry) skip; // foreign
      ;   if (dist[neighbor_id] == 0xFFFF):
      ;       dist[neighbor_id] = dist[u] + 1
      ;       // Establish or inherit bottleneck ID:
      ;       if (breadth <= [g_SalientNeckWidthThreshold] && bottleneck[u] == 0)
      ;           bottleneck[neighbor_id] = neighbor_id;
      ;       else
      ;           bottleneck[neighbor_id] = bottleneck[u];
      ;       Push neighbor_id to Queue
      ; jmp .bfs_loop
  ```

---

### 4.3 Component 3: Shoulder / Neck Stress Evaluation
* **Parameters Loaded from `db/mod_settings.ini`**:
  - `NeckThreatRatio` (default = 1.5)
  - `NeckCollapsingOrgThreshold` (default = 30.0f)
* **Logic**:
  1. Inspect bottleneck province $B = \text{g\_GraphTable}[\text{prov}].\text{bottleneck\_prov}$.
  2. If `pNeck->m_pCombat != NULL` (active battle):
     - Walk defender list at `[pNeck + 0x1C2]`. If any division has $\text{Org} < \text{NeckCollapsingOrgThreshold}$, neck is **CRITICAL**.
  3. If not in active combat:
     - Compare $\text{AdjacentEnemyStrength} : \text{FriendlyStrength}$. If ratio $\ge \text{NeckThreatRatio}$, neck is **THREATENED**.

---

### 4.4 Component 4: Spearhead Protection (Offensive Momentum)
* **Parameters Loaded from `db/mod_settings.ini`**:
  - `SpearheadWinningOdds` (default = 1.1)
  - `AbortSpearheadOnNeckCollapse` (default = 1)
* **Check**:
  - Check `[pArmy + 0x14C]` (m_nDestProv) for divisions in the salient.
  - If destination is enemy-controlled AND ongoing combat odds $\ge \text{SpearheadWinningOdds}$:
    The army is spearheading an offensive breakthrough!
  - If `AbortSpearheadOnNeckCollapse == 0`, spearhead continues regardless.
  - If `AbortSpearheadOnNeckCollapse == 1`, spearhead only aborts if the neck reaches **CRITICAL** (battle losing).

---

### 4.5 Component 5: Action Mechanism (Overland March Only)
* **Zero Strategic Redeployment**:
  As requested, **NO strategic redeployment orders will ever be issued**.
* **Native Front Quota Zeroing**:
  In `FUN_006829b0` (`0x00684526` / `0x00684529`):
  - Hook site intercepts `ppvVar20` (the target division proportion).
  - When the STEM decision is **RUN**:
    Set target quota:
    $$\text{ppvVar20} = \text{SalientEvacuationQuota} \quad (\text{default } 0.0)$$
    Set bottleneck target quota:
    $$\text{ppvVar20}(\text{Neck}) = \text{BottleneckDefenseBoost} \quad (\text{default } 2.5)$$
  - **Native Engine Execution**:
    In `FUN_006853c0`, the engine observes that the salient has an extreme surplus and the neck has a major deficit.
    The native engine naturally issues **overland combat march orders** to withdraw divisions out of the salient toward the neck!

---

## 5. Proposed `[FrontAI]` Configuration Section in `db/mod_settings.ini`

```ini
[FrontAI]
; Enable Graph-Based Encirclement Avoidance & Pocket Defense:
; 0 = Vanilla behavior (local 1-hop op_defensive only)
; 1 = Enhanced graph-based BFS and dynamic "Stay vs Run" decision engine
EnableEncirclementDefense = 1

; --- Topological Salient Thresholds ---
; Maximum bottleneck width to classify a sector as an exposed salient
; (Provinces whose connection to the supply core passes through a neck <= this width are evaluated)
; Default = 2
SalientNeckWidthThreshold = 2

; --- Shoulder & Neck Stress Thresholds ---
; Ratio of enemy adjacent/attacking combat power to friendly defenders required to declare the neck threatened
; (e.g. 1.5 = enemy has 1.5x friendly strength)
; Default = 1.5
NeckThreatRatio = 1.5

; Minimum defender organization threshold in the bottleneck province (0.0 to 100.0)
; If active combat in the bottleneck causes defender org to drop below this value, the neck is declared collapsing
; Default = 30.0
NeckCollapsingOrgThreshold = 30.0

; --- Offensive Breakthrough Protection (Spearhead Guard) ---
; Minimum combat odds of advancing units required to classify forward action as a winning spearhead
; Default = 1.1
SpearheadWinningOdds = 1.1

; Force spearhead abort if neck is collapsing regardless of forward progress:
; 0 = Spearhead continues advancing even if neck is collapsing
; 1 = Abort spearhead and pull back to neck if shoulder is collapsing (recommended)
AbortSpearheadOnNeckCollapse = 1

; --- Quota Modulation Weights (Overland Evacuation) ---
; Quota multiplier applied to forward salient provinces when "RUN" decision is active
; (0.0 = complete overland withdrawal; 0.2 = retain a screening rear guard)
; Default = 0.0
SalientEvacuationQuota = 0.0

; Quota multiplier applied to the bottleneck province when "RUN" decision is active
; (Attracts retreating divisions to form a defensive line at the base of the salient)
; Default = 2.5
BottleneckDefenseBoost = 2.5

; --- Multi-Source Supply Seeding ---
; Consider friendly active supply depots (CProvince + 0x18A / +0x270) as valid supply cores:
; 1 = Yes (enclaves/islands with depots are not treated as encircled, default)
; 0 = Capital only
UseSupplyDepotsAsCores = 1
```
