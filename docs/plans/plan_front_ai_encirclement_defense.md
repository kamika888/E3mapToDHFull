# Engine Modification Plan: Front AI Graph Traversal & "Stay vs Run" Encirclement Defense System (Patch 18)

**Document ID**: `plan_front_ai_encirclement_defense.md`  
**Target Engine**: Darkest Hour 1.05.2 (32-bit x86 PE, Checksum: `TENE`)  
**Target Executable**: `Darkest Hour.exe` (Image Base: `0x00400000`, Base File Size: `4,730,956` bytes, Patched Size: `4,751,360` bytes)  
**Configuration File**: `db\mod_settings.ini` -> Section `[FrontAI]`  
**Patcher Integration**: `patch_darkest_hour.bat` -> **Patch 18**  
**Code Cave Location**: Dedicated `.mod` page 2 at VA `0x00DCBAA0`-`0x00DCBF80` (File Offset: `0x00486AA0`, $\approx 1,248$ bytes)  
**Status**: APPROVED / IMPLEMENTATION STAGE

---

## 1. Executive Summary & Problem Definition

In Darkest Hour retail v1.05.2 (and Hearts of Iron II/III/IV generally), the Front AI suffers from a chronic inability to detect, prevent, or react to operational encirclements:
1. **The 1-Hop Neighbor Blind Spot (`op_defensive`)**:
   As reverse-engineered in `FUN_006829b0` (`0x006831D0` - `0x00684526`), the only vanilla anti-encirclement tool, `distrib_vs_human = op_defensive`, calculates troop quotas purely from immediate 1-hop friendly adjacent connections over total front escape connections ($A_i / \sum A$). In any multi-province pocket or salient, interior provinces share connections with each other ($\ge 2$), completely blinding the AI to the fact that the entire sector's connection to the national supply core has narrowed to a single bottleneck.
2. **The "Reactive" Pinning Trap**:
   In 99% of country AI files, `distrib_vs_human = reactive`. Under `reactive`, the AI strives to match enemy troop concentrations directly facing it across the border. When a player fixes the forward line with a weak infantry pinning screen and sends armored pincers around the flanks, the AI divisions remain paralyzed in place, staring at the pinning screen until the trap snaps shut.
3. **The Breakthrough / False-Positive Paradox**:
   If an engine modification were to rely solely on topological constriction (e.g. `min_neck_width <= 2`), the AI would abort its own armored breakthrough drives, because an advancing spearhead naturally forms a 1- or 2-province wide salient. Similarly, naturally constricted choke points (such as the Perekop isthmus into Crimea, or Denmark/Jutland) would be abandoned even if heavily fortified and completely secure.
4. **The E3 Map Granularity Multiplier**:
   On the E3 map (`Map_3`), depth from the frontline to the interior is three times greater than on the vanilla map. When an enemy punches through the front line, the spearheads operate in vast empty rear space managed by `CGarrisonAI` (which slashes rear quotas by $\frac{1}{3}$ and $\frac{1}{2}$ during war), while the Front AI divisions remain pinned on the border.

### Solution Overview
Patch 18 introduces the **Front AI Graph Traversal & "Stay vs Run" Encirclement Defense System (STEM)**:
1. **Multi-Source Reverse Breadth-First Search (BFS)**:
   - Evaluates global graph connectivity from the national Capital **and active provincial supply depots** (`CProvince + 0x18A` / `+0x270`) through friendly land territory.
   - For every front province, maps its shortest path distance, its narrowest corridor bottleneck width (`min_neck_width`), and the province ID of its bottleneck shoulder ($B$).
   - Overseas enclaves and colonies with their own supply depots (e.g., German East Prussia at Königsberg `510`, French North Africa at Oran `950`) are treated as valid supply bases, preventing false-positive pocket panics.
2. **The Multi-Factor "Stay vs Run" Decision Switch (STEM)**:
   - **Topological Gate**: Activates only if `min_neck_width <= SalientNeckWidthThreshold` (default `2`).
   - **Shoulder / Neck Stress Check**: Evaluates bottleneck province $B$. If $B$ is in active combat with defender organization $< \text{NeckCollapsingOrgThreshold}$ (default $30\%$) or enemy force ratio $\ge \text{NeckThreatRatio}$ (default $1.5\times$), the neck is declared **THREATENED** or **COLLAPSING**.
   - **Offensive Momentum Guard**: Inspects advancing divisions in the salient (`[pArmy + 0x14C]`). If units are attacking into enemy territory with winning combat odds ($\ge \text{SpearheadWinningOdds}$), the offensive is protected (`STAY & ADVANCE`), preventing the AI from aborting its own breakthroughs.
3. **Overland-Only March Evacuation**:
   - Explicitly bars strategic redeployment from threatened salients (matching competitive multiplayer standards).
   - Operates by modulating front quotas at `0x00684529` in `FUN_006829b0`: sets forward salient quota to `SalientEvacuationQuota` (`0.0`) and bottleneck quota to `BottleneckDefenseBoost` (`2.5`).
   - The native Paradox front manager (`FUN_006853c0`) observes a massive surplus at the tip and deficit at the base, naturally issuing **overland combat march orders** to withdraw units out of the salient toward the base.
4. **Complete INI Externalization**:
   - All weights, thresholds, and modes are exposed under `[FrontAI]` in `db\mod_settings.ini`.

---

## 2. Parameter Inventory & Runtime Memory Table (`0x00DCBAA0`)

| Parameter Name | Cave VA | Binary Type | Default | Engine Role |
|---|---|---|---|---|
| `EnableEncirclementDefense` | `0x00DCBAA0` | `int` | `1` | Master toggle (`0` = vanilla 1-hop `op_defensive`, `1` = Patch 18 STEM engine) |
| `SalientNeckWidthThreshold` | `0x00DCBAA4` | `int` | `2` | Max bottleneck width to classify a sector as an exposed salient |
| `NeckThreatRatio` | `0x00DCBAA8` | `float` | `1.5f` | Ratio of adjacent/attacking enemy power to friendly defenders to declare neck threatened |
| `NeckCollapsingOrgThreshold` | `0x00DCBAAC` | `float` | `30.0f` | Minimum defender org in bottleneck province below which neck is declared collapsing |
| `SpearheadWinningOdds` | `0x00DCBAB0` | `float` | `1.1f` | Minimum combat odds of advancing units required to classify action as a winning spearhead |
| `AbortSpearheadOnNeckCollapse`| `0x00DCBAB4` | `int` | `1` | `1` = Abort spearhead and pull back to neck if shoulder is collapsing; `0` = continue advance |
| `SalientEvacuationQuota` | `0x00DCBAB8` | `float` | `0.0f` | Quota multiplier applied to forward salient provinces when "RUN" decision is active |
| `BottleneckDefenseBoost` | `0x00DCBABC` | `float` | `2.5f` | Quota multiplier applied to the bottleneck province when "RUN" decision is active |
| `UseSupplyDepotsAsCores` | `0x00DCBAC0` | `int` | `1` | `1` = Seed BFS with Capital and friendly supply depots (`pProv + 0x18A` / `+0x270`); `0` = Capital only |
| `g_pGraphTable` | `0x00DCBAC4` | `pointer` | `Dynamic` | Base pointer to 48 KB graph node array allocated via `VirtualAlloc` |
| `g_bGraphDirty` | `0x00DCBAC8` | `byte` | `1` | Flag set to `1` by `CProvince::SetController` (`0x004E7905`); triggers BFS re-run |

---

## 3. Configuration Specification (`db\mod_settings.ini`)

All encirclement avoidance parameters are managed under `[FrontAI]` in `db\mod_settings.ini`:

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

---

## 4. Hook Architecture & Call Sites

### 4.1 Hook 1: Event-Driven Graph Invalidation (`0x004E7905`)
* **Routine**: `CProvince::SetController` (`FUN_004e78e0`).
* **Original Code**:
  ```asm
  004E7905: 89 91 D8 03 00 00       mov [ecx+0x3D8], edx
  ```
* **Patch**:
  Intercepts controller changes to set `g_bGraphDirty = 1` (`0x00DCBAC8`), ensuring graph traversal only re-runs when territorial boundaries change.

### 4.2 Hook 2: Dynamic Quota Intercept (`0x00684526` / `0x00684529`)
* **Routine**: `CFront::UpdateDistribution` (`FUN_006829b0`).
* **Original Code**:
  ```asm
  00684526: D8 35 ...               fdiv dword ptr [local_2c]
  0068452C: 8B 8D ...               mov ecx, [ebp - ...]
  ```
* **Patch**:
  Jumps to `.mod` cave `fn_stem_eval_quota`.
  - If `g_bGraphDirty == 1`, runs `fn_run_bfs` for the current country.
  - Queries `g_GraphTable` for province ID (`[local_44 + 4]`).
  - Evaluates the "Stay vs Run" switch:
    - If **RUN**: Overwrites target ratio `ppvVar20` with `SalientEvacuationQuota` (`0.0f`).
    - If **STAY**: Leaves native quota unchanged.
  - Returns to `0x0068452C`.

---

## 5. Verification & Test Scenarios

### 5.1 Test Scenarios in `scenarios/`
1. **`scenarios/test_pincer_encirclement.eug`**:
   - Bialystok salient with 12 Soviet divisions pinned by 3 German infantry divisions.
   - German armored columns attacking northern (Grodno) and southern (Brest) shoulders.
   - **Verification**: Soviet divisions disengage from Bialystok and march overland to Minsk before the pocket seals.
2. **`scenarios/test_offensive_breakthrough.eug`**:
   - German motorized corps advancing into Soviet territory near Vitebsk (1-province wide spearhead).
   - **Verification**: Panzers receive `STAY & ADVANCE` and continue advancing toward Smolensk without aborting.

### 5.2 Automated Tests
- Run `tools/patch_darkest_hour.bat -Verify` to validate signatures and section alignment.
