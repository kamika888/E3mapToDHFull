# Darkest Hour -- Garrison AI Architecture & Division Requirement Calculation

## 1. Overview & Architecture

Garrison evaluation, area division quotas, and reinforcement dispatch are managed by `CGarrisonAI::UpdateGarrisons` (`FUN_0068ba50` at virtual address `0x0068BA50`).

The function iterates over all areas belonging to the nation (`[country + 0xE86E]`), determines the division requirements and current deficits for each area, sorts them into a priority dispatch queue, and routes available surplus forces accordingly.

### Runtime Logging
The engine logs its area evaluations at `0x0068CB72` using the internal debug format string at `0x00867E08`:
```text
"Garrison AI: %s: Area %s (%d); nAreaNeed = %d, nDivisions = %d, nAreaLack = %d"
```

Where:
* **`nAreaNeed`** (`[area + 0x5A]`): Total divisions desired for the area.
* **`nDivisions`** (`[area + 0x5E]`): Current friendly divisions stationed in or moving into the area.
* **`nAreaLack`** (`[area + 0x56]`): Net division deficit (`nAreaNeed - nDivisions`), used to sort the AI priority queue (`local_108`) descending.

---

## 2. Step 1: Base Province Counting (C)

For each area $A$, the engine iterates through all member provinces $p \in P_A$:

1. **Controller Check** (`[p + 0x3D8]`):
   * **If controlled by the nation**:
     * The engine checks the terrain movement speed rating via `FUN_004e9500`:
       `*(float *)(*(int *)(p + 0x1DA) + 0x14) != 0.0`
     * Passable land province: **$+1$ to $C$**.
     * Impassable terrain / Terra Incognita / water (`movement == 0.0`): **$+0$ to $C$**.
   * **If not controlled by the nation** (enemy-occupied or allied province inside the area):
     * **$+2$ to $C$** (contested or unowned provinces count double to increase defensive/offensive weight).

2. **Core / National Status Check** (`FUN_004e8ab0(p)`):
   * If any member province is a national/core province of the country, the area is flagged: `has_core_provinces = true`.

$$C = \sum_{p \in P_A, \text{controlled}, \text{passable}} 1 + \sum_{p \in P_A, \text{uncontrolled}} 2$$

---

## 3. Step 2: Emergency Homeland Collapse Check

If the nation is at war (`IsAtWar()` / `FUN_0044beb0() != 0`), the engine evaluates national core territory loss (`FUN_00468560`):
$$\text{CoreLossRatio} = 1.0 - \frac{\text{ControlledCores}}{\text{TotalCores}}$$

If the national Capital province is captured or enemy-occupied, $+0.10$ is added to this ratio.

**Emergency Trigger**:
$$\text{CoreLossRatio} > 0.10 \quad \text{OR} \quad \text{CapitalLost} \quad \text{OR} \quad \text{HomeAreaDivisions} < 1$$

When this trigger fires, for any area that:
1. Has no core provinces (`has_core_provinces == false`), OR
2. Is not the Capital Area and does not directly border an enemy (`is_front_area == false`)

The garrison requirement is set to **ZERO** ($C = 0$). All overseas and rear colonial garrisons are completely abandoned so all forces can be recalled to defend the homeland.

---

## 4. Step 3: Area Type Multipliers & Geometry Modifiers

If the area requirement was not zeroed out by the emergency check, the engine applies base multipliers:

### A. Capital (Home) Area
If the area contains the national capital:
1. **Multiplication**:
   $$C = \text{round}(C \times \text{home\_multiplier}) \quad (\text{token ID } 0x465, \text{default } 0.5)$$
   $$\text{if } C < 1, \quad C = 1$$
2. **Peacetime Cap**:
   If the nation is at peace (`!IsAtWar()`):
   $$\text{if } C > \text{home\_peace\_cap}, \quad C = \text{home\_peace\_cap} \quad (\text{token ID } 0x467)$$
   *(During wartime, `home_peace_cap` is completely bypassed).*

### B. Overseas / Non-Home Areas
1. **Base Multiplier Selection ($M$)**:
   * If any province in the area is specified in `area_multiplier = { <prov_id> = <val> }` (token ID `0x469`): $M = \text{val}$.
   * Otherwise: $M = \text{overseas\_multiplier}$ (token ID `0x466`, default `0.3333`).
2. **Wartime Enemy Border Override**:
   * If the area borders an enemy nation at war (`is_front_area == true`):
     $$M = 1.0 \quad \text{(forced to 1.0, overriding area\_multiplier and overseas\_multiplier)}$$
3. **Small Island Exception**:
   * If the area is a single-province island (`FUN_004e4b60`) with naval distance $< 40.0$ and no explicit `area_multiplier`: $M = 0.0$.
4. **Multiplication**:
   $$C = \text{round}(C \times M)$$
   $$\text{if } C < 1 \text{ and } M > 0.01, \quad C = 1$$
5. **No-Port Pocket Bordering Enemy**:
   * If the area has NO naval base/port (`FUN_004ca453 == 1`) AND borders an enemy:
     $$C = 0 \quad \text{(isolated pocket cannot be supplied or reinforced)}$$
6. **Contiguous Rear Behind Active Front (The $\frac{1}{3}$ Factor)**:
   * If at war, active land front areas exist, and this area has a contiguous overland land path (`FUN_004a4010`) to an active front area with divisions:
     $$C = \left\lfloor \frac{C}{3} \right\rfloor, \quad \text{minimum } 1$$
     *(Troops can march overland directly to the front line, so rear areas directly behind a front need only $\frac{1}{3}$ the peacetime garrison).*

---

## 5. Step 4: Wartime Threat Scaling & The Invisible Factor

Initially:
$$\text{nAreaNeed} = C$$
$$\text{nAreaLack} = C - \text{nCurrentDivisions}$$

When at war and land front areas exist (`0 < count_front_areas`):

### A. Front Areas (`is_front_area == true`)
1. **Border Threat Calculation**:
   The engine scans all enemy provinces bordering our provinces in this area and sums all enemy divisions stationed directly along our border ($\text{EnemyBorderDivisions}$).
   $$\text{BorderDeficit} = 2 \times \text{EnemyBorderDivisions} - \text{nCurrentDivisions}$$
   $$\text{nAreaLack} = \max(\text{nAreaLack},\ \text{BorderDeficit})$$
   *(The AI demands at least $2.0\times$ the enemy force directly on the border).*
2. **War Zone Odds Scaling**:
   If the national Capital Area is NOT directly on an enemy front (homeland safe):
   $$\text{nAreaLack} = \text{round}(\text{nAreaLack} \times \text{war\_zone\_odds}) \quad (\text{token ID } 0x468, \text{default } 2.0)$$
3. **Adjacent Area Floor**:
   If the country is actively targeting this front:
   $$\text{nAreaLack} = \max\left(\text{nAreaLack},\ \left\lfloor \frac{\text{EnemyDivisionsInAdjacentArea}}{2} \right\rfloor\right)$$

### B. Rear Areas (`is_front_area == false`) -- The Invisible Factor
If the country (or an allied faction member) has an active land combat border / troop deficit (`local_52 != 0 || local_e4 != 0`):
$$\mathbf{nAreaNeed = \left\lfloor \frac{C}{2} \right\rfloor}$$
$$\mathbf{nAreaLack = \left\lfloor \frac{C}{2} \right\rfloor - nCurrentDivisions}$$

**This is the "invisible factor" in wartime**: The game engine cuts the required garrison of all rear/non-combat areas in **HALF** ($\div 2$) during an active war to release divisions for the front lines!

---

## 6. Step 5: Reinforcement Priority & Troop Dispatch

Areas are inserted into a priority linked list (`local_108`) sorted descending by `nAreaLack` (`[area + 0x56]`).

* Areas with the largest net division deficit receive reinforcement dispatches first.
* Surplus divisions in areas where `nCurrentDivisions > nAreaNeed` are pooled (`local_70` / `local_68`) and reassigned or loaded onto naval transports for overseas areas.

---

## 7. Step 6: Province-Level Allocation Within the Area

Once `nAreaNeed` is determined for the area as a whole, divisions stationed in the area are distributed among constituent provinces using priority weights calculated in `FUN_0068b4f0` (`[prov + 0x48A]`):

* **Key Point Priority**: `IC * key_point_prio_mult`
* **Beach / Coastal Priority**: `beach` flag weight
* **Border Tensions**: Borders with foreign / hostile nations
* **Capital Province**: High fixed weight for national capital
* **Custom Priority**: Overrides from `province_priorities = { <prov_id> = <prio> }`

Each province receives a share of divisions proportional to its weight fraction:
$$\text{Share}_p = \frac{\text{Priority}_p}{\sum_{k \in P_A} \text{Priority}_k}$$

---

## 8. Summary Formula Matrix

| Scenario | Capital / Home Area Formula | Overseas / Rear Area Formula | Front Area (Borders Enemy) Formula |
| :--- | :--- | :--- | :--- |
| **Peacetime** | $\min(\text{peace\_cap}, \text{round}(P \times \text{home\_mult}))$ | $\text{round}(P \times \text{area\_mult})$ | $N/A$ (No enemy at war) |
| **Wartime (Rear)** | $\left\lfloor \frac{\text{round}(P \times \text{home\_mult})}{2} \right\rfloor$ | $\left\lfloor \frac{\text{round}(P \times \text{area\_mult})}{2} \right\rfloor$ | $N/A$ |
| **Wartime (Rear behind land front)** | $N/A$ (Capital is base) | $\left\lfloor \frac{\lfloor P \times \text{area\_mult} / 3 \rfloor}{2} \right\rfloor$ | $N/A$ |
| **Wartime (Front Area)** | Defends against border threat | Defends against border threat | $\max(P, 2 \times \text{EnemyBorder}) \times \text{war\_zone\_odds}$ |
| **Homeland Emergency (>10% cores lost)** | Defend at all costs | $\mathbf{0}$ (Colonies abandoned) | Defend front line |
