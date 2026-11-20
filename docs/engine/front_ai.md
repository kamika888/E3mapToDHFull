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
                       |      +--> Step 1: 0x00682A58 -> 0x00681CD0: CFrontAI::ManageRearReserves()
                       |      |      ([0x00682A43] skips call if [CFrontAI + 0x10C] is empty and [+0x125] != 0)
                       |      |      (Hooked by Patch 18 wrapper Cave_FrontAI_ManageReservesAndSalients @ 0x00DCE55A)
                       |      |      - Retail: stages rear-reserve candidates ([CFrontAI + 0x12A] / +0x12E)
                       |      |        and appends reserve unit TypeIds to [CFrontAI + 0xC8]
                       |      |      - STEM: prunes retail nodes entering STEM Evacuation Mode, shields
                       |      |        evacuating armies ([+0x17B] = 2) during 0x00681CD0, restores [+0x17B],
                       |      |        and exempts evacuating/salient units in [CFrontAI + 0xC8] (tag 0x5A)
                       |      |
                       |      +--> Step 2 ("Loop A"): Interior-to-Border Push (0x00683C1D..0x00684207)
                       |      |      - Operates on non-reserve armies (not in [CFrontAI + 0xC8]) sitting in
                       |      |        non-border interior provinces (CFrontAI::IsFrontProvince == 0 @ 0x00683CA2)
                       |      |      - Stops non-conforming interior marches, builds adjacent border candidate
                       |      |        list ([ebp - 0x58], falling back to [CFrontAI + 0x04] @ 0x00684069),
                       |      |        ranks candidates by raw (en_str - fr_str) @ 0x00684088 (ignoring quotas),
                       |      |        falls back to head of [CFrontAI + 0x04] @ 0x00684117 if edi == 0,
                       |      |        and dispatches forward march via 0x006AAFF0 @ 0x0068418D
                       |      |      - STEM Stage 2: gates/scales candidates by (1 - Q) and AdjustedPriority
                       |      |        at 0x00683EB6, 0x00684088, 0x006840F6, and fallback 0x00684131
                       |      |
                       |      +--> Step 3 ("Loop B"): Border-to-Border Quota Rebalancing (0x00684482..0x0068536C)
                       |             - Computes border shares S(u) across [CFrontAI + 0x04] and target divisions
                       |               N(u) = S(u) * D_front ([ebp - 0x60])
                       |             - Builds under-strength receivers (0x006844E0..0x006845B8) and over-strength
                       |               donors (0x006846CF..0x0068478D & helper 0x006851D0)
                       |             - STEM Stage 2: caches norm_prio_f32[u] and scales S(u) by (1 - Q(u)) at
                       |               0x00684551, 0x0068470D, and 0x0068526A
                       |             - Stops excess/mismatched marches (0x0050BCA0) and dispatches via 0x006AAFF0
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
| `+0xFC` | `float` | `sum(w30)` across front provinces (`reactive` denominator) |
| `+0x100` | `uint32` | `sum(friendly_nbs)` across front provinces (`op_defensive` denominator) |
| `+0x104` | `float` | `sum(en_str)` across front provinces (`offensive` denominator) |
| `+0x108` | `float` | `sum(w34)` across front provinces (`defensive` denominator) |
| `+0x124` | `uint8` | `vs_human` flag (`1` if any front enemy is human-controlled, selecting `[CAI_FrontPrefs + 0x8C]` `distrib_vs_human`; `0` selects `[+0x88]` `distrib_vs_ai`) |
| `+0x125` | `uint8` | Hold-in-place / disable reserve withdrawal flag |
| `+0x126` | `uint32` | Hourly front tick counter |
| `+0x12A` | `CIntList` | `m_RearReserveCandidateProvinces`: interior rear-reserve candidate provinces evaluated by `0x00681CD0` |
| `+0x12E` | `ListNode*` | `m_SelectedRearReserveProvinces`: selected rear-reserve destination province list populated by `0x00681CD0` |

### 2.2 `CFrontProvince` Descriptor & AI Preference Offsets
Each node in `[CFrontAI + 0x04]` points to a per-province front descriptor populated during `0x006829B0`, and `CAI_FrontPrefs` is located at `[pCountry + 0x120] + 0x8FC` (`+0x20`: crossing threat multiplier `1.2`, `+0x88`: `distrib_vs_ai`, `+0x8C`: `distrib_vs_human`, `+0x94`: `province_priorities`):

| Offset | Type | Description |
|---|---|---|
| `+0x04` | `int32` | Province ID |
| `+0x0C` | `int32` | Total friendly/allied divisions assigned to or arriving at this province |
| `+0x10` | `int32` | Stationary non-retreating front-eligible division count |
| `+0x14` | `int32` | Count of adjacent accessible non-hostile (friendly/allied) provinces (`op_defensive` numerator) |
| `+0x18` | `float` | Effective friendly combat strength defending this province |
| `+0x20` | `float` | `en_str`: weighted adjacent hostile combat strength facing this province |
| `+0x2C` | `float` | `def`: static defense score (`land_fort * 5.0 + terrain_bonus`) |
| `+0x30` | `float` | `w30`: reactive threat-adjusted weight (`en_str / (1.0 + 0.01 * def)`) |
| `+0x34` | `float` | `w34`: static strategic/economic value weight (`defensive` numerator) |
| `+0x40` | `uint8` | Narrow-connection boost flag (`friendly_nbs < 2`, doubles weight at `0x00683880` when interior backup applies) |
| `+0x42` | `uint8` | Unused by retail (zeroed by `0x006AF940`); stamped `0x5B` by Patch 18 `Hook 4` on injected interior bottleneck nodes (`0` on native/promoted frontline nodes) |
| `+0x8D` | `uint8` | Guard flag excluding province from quota reinforcement when bordering only zero-infrastructure enemy provinces (`0x004E9440`) or itself having zero infrastructure (`0x004E9500`) |

---

## 3. Subsystem Function Directory

| Routine | Virtual Address | Calling Conv. | Description |
|---|---|---|---|
| `CFrontAI::Execute` | `0x006811B0` | `__thiscall` | Master hourly front evaluation entry point. Calls `0x006829B0` and `0x006853C0`. |
| `CFrontAI::MoveUnitsToFront` | `0x006829B0` | `__thiscall` | Evaluates border quotas, calls `ManageRearReserves` via `0x00682A58` (when gated pass at `0x00682A43` succeeds), stops non-conforming marches (`0x0050BCA0`), and dispatches reinforcement moves (`0x006AAFF0`). |
| `CFrontAI::ManageRearReserves` | `0x00681CD0` | `__thiscall` | Retail rear-reserve routine. Selects candidate rear-reserve provinces (`+0x12A` / `+0x12E`) and registers reserve unit `TypeId`s in `[this + 0xC8]` (`m_ReserveUnits`). Wrapped by `0x00DCE55A` at callsite `0x00682A58`. |
| `CFrontAI::IsFrontProvince` | `0x006813E0` | `__thiscall` | Returns `1` if the given province ID belongs to this front's border province list. |
| `CFrontAI::ExecuteTactical` | `0x006853C0` | `__thiscall` | Coordinates active combat management (`0x00685ED0`) and offensive attack planning (`0x00689780`). |
| `CFrontAI::ManageCombat` | `0x00685ED0` | `__thiscall` | Evaluates ongoing battles on the front for reinforcement or tactical retreat. |
| `CFrontAI::PlanAttacks` | `0x00689780` | `__thiscall` | Plans and initiates frontline attacks into adjacent enemy provinces. |
| `CFrontAI::IsPassiveFront` | `0x006A8720` | `__thiscall` | Checks `[pCountry + 0x34AC + tag]`; returns `0` during active war so `0x006829B0` executes hourly. |
| `CAI::UpdateFronts` | `0x00693EE0` | `__thiscall` | Reconciles `[CCountryAI + 0x278]` fronts against current war borders (`[CCountry + 0xE880]`), removes interior provinces (`0x00694074`), splits fronts (`0x00680D50`), merges adjacent fronts (`0x0068A2B0`), and assigns idle units. Hooked at entry by `Hook 10` (`0x00DCECC1`). |
| `CFrontAI::MergeFront` | `0x0068A2B0` | `__thiscall` | Folds an adjacent front's province list and army list into a unified front during `0x00693EE0`. |
| `CAI::RequestFrontDivisions` | `0x00694BE0` | `__thiscall` | Handles urgent panic-ratio reinforcement pulls (`"%s: Front %s urgently requests %d more divisions."`), reassigning idle garrison or eligible donor-front units (`0x00695297`). |

---

## 4. Retail Engine Behavior: Why Multi-Province Salients Are Not Evacuated

Reverse-engineering `0x00681CD0` (`CFrontAI::ManageRearReserves`) and `0x006829B0` (`CFrontAI::MoveUnitsToFront`) reveals why retail Darkest Hour lacks multi-province salient evacuation:

1. **Local Quotas Only & No Topological Neck Detection**:
   - Retail `CFrontAI::ManageRearReserves` (`0x00681CD0`) manages rear-reserve staging rather than topological pocket evacuation, and `CFrontAI::MoveUnitsToFront` (`0x006829B0`, including `0x006831D0` - `0x00684526`) weights border province quotas using local immediate-neighbor scoring rather than global cut-vertex / articulation-point analysis.
   - Consequently, a multi-province salient (connected internally with degree $\ge 2$, but joined to the main interior only through a narrow neck/shoulder pair) continues receiving border allocations unless external evacuation tracking exempts those units.
2. **Aggressive `StopMovement` Override (`0x0068416A`)**:
   - In `0x006829B0`, any assigned front army whose `TypeId` is **not** registered in `[CFrontAI + 0xC8]` (`m_ReserveUnits`) has its movement evaluated against static border quotas. Without registering evacuating units' `TypeId` in `[CFrontAI + 0xC8]` via the `0x00682A58` wrapper (`0x00DCE55A`), `0x006829B0` (`0x0068416A`) immediately calls `StopMovement` (`0x0050BCA0`) or reassigns the unit back to the border on the very same hour tick, creating an infinite hourly tug-of-war.

### 4.1 Retail Front Distribution Modes (`distrib_vs_ai` / `distrib_vs_human`) & Terrain Effects
Reverse-engineering `0x006829B0` and the `.ai` serializer (`0x006BFBE2..0x006C023C`) establishes the exact enum mapping and quota calculation used when `[CFrontAI + 0x124]` selects `[CAI_FrontPrefs + 0x88]` (`distrib_vs_ai`) vs `[+0x8C]` (`distrib_vs_human`):

| Enum | `.ai` Mode | Quota Share Formula (`0x006844E0..0x00684529`) | Terrain Influence | Empty-Prov Floor (`deficit = 1`) |
| :---: | :--- | :--- | :--- | :--- |
| `0` | `even` | $\frac{1}{\text{N\_front}}$ (equal split) | None on quota | **Yes** (`0x00684592`: forces `deficit = 1` when `divs == 0`) |
| `1` | `reactive` | $\frac{\text{w30}}{\sum \text{w30}}$, $\text{w30} = \frac{\text{en\_str} \cdot (\text{2 if capital})}{1.0 + 0.01 \cdot \text{def}}$ | **Double** (`en_str` attack mod + `def` divider) | **No** (truncated `0` stays `0`) |
| `2` | `defensive` | $\frac{\text{w34}}{\sum \text{w34}}$ (`100 + VP*10 + IC + resources + area/cap`) | None | **No** |
| `3` | `offensive` | $1.0 - \frac{\text{en\_str} \cdot (\text{2 if capital})}{\sum \text{en\_str}}$ | **Indirect** via `en_str` (lower enemy attack effectiveness raises `1 - en_str/sum`) | **No** |
| `4` | `op_defensive` | $\frac{\text{friendly\_nbs}}{\sum \text{friendly\_nbs}}$ (`[+0x14]`) | None | **No** |

All shares are further multiplied by any `province_priorities` entry (`[CAI_FrontPrefs + 0x94]`, `0x00684529`).

**How Terrain Enters `reactive` (`1`) and `offensive` (`3`):**
- **Numerator `en_str` (`+0x20`, affects `reactive` and `offensive`)**: Inside `0x006829B0` (`0x00683306..0x0068349E`), each adjacent hostile division is scored via `CDivision::vtbl[+0x2c]` (`0x005005B0`). That helper multiplies by the attacker's weather modifier (`0x0044D5B0`) and terrain attack modifier into the target province (`0x0044D660([targetProv + 0x254])`), and `0x006829B0` multiplies by `[CAI_FrontPrefs + 0x20]` (`1.2` on `PID 66240`) when `0x004E79B0` reports `conn_type == 1` or `2`. Difficult defensive terrain (such as `Marsh`) lowers incoming `en_str` directly (e.g., on live `PID 66240`, `6` German divs yield `0.1610` against `7335 Augustów` (`Marsh`) vs `0.3600` against `1875 ?om?a` (`Plains`)).
- **Denominator `def` (`+0x2C`, `reactive` only)**: `0x00682C17..0x00682C79` sets `def = land_fort * 5.0 + terrain_bonus`:
  - `Clear` / `Plains` (`0`), `Desert` (`3`), `Urban` (`7`): `+0.0`
  - `Hills` (`5`): `+20.0` (`divide by 1.20`)
  - `Forest` (`1`): `+25.0` (`divide by 1.25`)
  - `Marsh` (`4`): `+40.0` (`divide by 1.40`)
  - `Mountain` (`2`): `+45.0` (`divide by 1.45`)
  - `Jungle` (`6`): `+50.0` (`divide by 1.50`)
- **Empty-Province Truncation Cliff (`0x0068457C..0x0068459A`)**: Retail converts `(target_share - current_share) * total_front_divs` using `call 0x7A5EEC` (`__ftol()`, truncating toward zero) and only bumps an empty province (`divs == 0`) from `0` to `1` when `distrib_mode == 0` (`even`, `0x00684592: test edi, edi; jne 0x684fee`). Thus in `reactive` (`1`) — and likewise `defensive` (`2`) / `op_defensive` (`4`) — any empty province whose target quota falls strictly under `1.0` division receives `0` reinforcement pulls (`6516 Grajewo` = `0.93`, `7335 Augustów` = `0.67` on a `13`-division front). Unassigned incoming armies (`0x00684088`, active in all modes) additionally rank front provinces by `en_str - fr_str` (`[+0x20] - [+0x18]`), again preferring `Plains` over `Marsh`.

### 4.2 Internal Structure of `CFrontAI::MoveUnitsToFront` (`0x006829B0`): Loop A vs. Loop B vs. `ManageRearReserves` (`0x00681CD0`)
`CFrontAI` separates rear-area staging (`0x00681CD0`) from active front reinforcement (`0x006829B0`), and `0x006829B0` itself executes **two distinct assignment loops** over non-reserve armies (every army in `[CFrontAI + 0xA4]` whose `TypeId` is absent from `[CFrontAI + 0xC8]`):

| Routine / Phase | Address Range | Target Units | Decision Criterion | Why Stage 2 Needs Hooks |
| :--- | :--- | :--- | :--- | :--- |
| **`CFrontAI::ManageRearReserves`** | `0x00681CD0` (called at `0x00682A58`) | Idle/reserve candidates in interior provinces (`+0x12A` / `+0x12E`) | Pulls reserves back to staged rear-reserve provinces and inserts their `TypeId` into `[CFrontAI + 0xC8]` so Loop A/B/attacks leave them alone. | Wrapped by `Cave_FrontAI_ManageReservesAndSalients` so evacuating salient units are shielded (`+0x17B = 2`) and added to `[+0xC8]` (`0x5A`). |
| **`MoveUnitsToFront` — Loop A (Interior-to-Border Push)** | `0x00683C1D..0x00684207` (scoring `0x00684088`, fallback `0x00684117`) | Non-reserve armies currently standing in **interior** (non-border) provinces (`CFrontAI::IsFrontProvince` @ `0x006813E0` returns `0` at `0x00683CA2`, not in combat). | **Ignores Loop B's quota shares $S(u)$ and distribution modes.** Stops incompatible marches, gathers adjacent border candidates in `[ebp - 0x58]` (or falls back to `[CFrontAI + 0x04]` at `0x00684069`), picks the candidate maximizing raw `en_str - fr_str` (`[esi + 0x20] - [esi + 0x18]` at `0x00684088`), or falls back to the head of `[CFrontAI + 0x04]` at `0x00684117`, then orders a move (`0x006AAFF0`). | Without Loop A hooks, interior armies (including divisions that just arrived at a locked evacuation neck such as `102 Wolkowysk`) ignore Loop B's `AdjustedPriority = 0` and immediately walk back into evacuating salient tips whenever `en_str - fr_str` looks higher than safe borders. STEM Stage 2/3 hooks: `0x00683C9D` (interior neck garrison hold), `0x00683EB6`, `0x00684088` (incl. bottleneck attraction), `0x006840F6`, `0x00684131`. |
| **`MoveUnitsToFront` — Loop B (Border-to-Border Quota Rebalancing)** | `0x00684482..0x0068536C` (Site 1 `0x00684551`, Site 2 `0x0068470D`, Site 3 `0x006851D0` @ `0x0068526A`) | Border provinces in `[CFrontAI + 0x04]` and non-reserve armies assigned to border provinces (executed only when `total_front_divs` `[ebp - 0x60] > 0`). | Computes mode-specific normalized share $S(u)$ (`even`, `reactive`, `defensive`, `offensive`, `op_defensive`) $\times$ `province_priorities` and target divisions $N(u) = S(u) \times D_{\text{front}}$. Receiver loop (`0x006844E0..0x006845B8`) computes deficit (with `even`-mode `deficit = 1` floor at `0x0068459A`); donor paths (`0x006846CF..0x0068478D` and `0x006851D0`) compute excess divisions available for transfer (`+0x6A` urgency ordering). | Caches unadjusted `norm_prio_f32[u] = S(u) * D_front` (`+0x58000`) and scales $S(u) \leftarrow S(u) \cdot (1 - Q(u))$ at all three share sites (`0x00684551`, `0x0068470D`, `0x0068526A`) so evacuating provinces stop pulling reinforcements, suppress `even`-mode empty-province `deficit = 1` when $N_{\text{adj}} < 1.0$, and donate surplus outward. |

Because Loop A executes **before** Loop B inside every hourly `0x006829B0` call and selects targets by raw `(en_str - fr_str)` rather than $S(u) \times D_{\text{front}}$, Stage 2 gates **both** loops:
- **Loop A** rejects fully evacuating provinces ($Q = 1.0$), rejects partially evacuating candidates already at or above `AdjustedPriority`, and down-scales partial candidates' `(en_str - fr_str)` attractiveness toward `(1 - Q)` (for negative `(en_str - fr_str)`, dividing by `(1 - Q)` makes the candidate more negative rather than pulling it upward toward `0.0`), while also blocking the `0x00684117` fallback if the list head has $Q > 0$.
- **Loop B** caches `NormalFrontAIPriority` into `norm_prio_f32` (`+0x58000`) at Site 1 (`0x00684551`), replaces `S(u)` with `S(u) * (1 - Q(u))` across Site 1 (`0x00684551`), Site 2 (`0x0068470D`), and Site 3 (`0x0068526A` in `0x006851D0`), and zeroes `S(u)` whenever `Q == 1.0` or `(Q > 0 && S_adj * D_front < 1.0)` so `0x00684568` jumps to `0x00684FEA` instead of triggering `even`-mode's `deficit = 1` bump at `0x0068459A`.

---

### 4.3 Multi-Front Organization, Merging & Inter-Front Reinforcement (`0x00693EE0` / `0x00694BE0`)

In retail Darkest Hour, each continuous connected strip of exposed land-border provinces forms one `CFrontAI` object listed in `[CCountryAI + 0x278]` (and `[pCountry + 0xE86E]`). Two fronts remain separate unless `CAI::UpdateFronts` (`0x00693EE0`) connects them through a shared **exposed frontline** province (`0x0068A2B0`) — interior provinces never bridge separate fronts in vanilla.

- **Independent Front Pools & Staggered Execution**:
  Each `CLandArmy` stores its assigned front pointer at `CArmy + 0x1F4` (`pFront + 0x12`), and each `CProvince` stores a single back-pointer at `CProvince + 0x4A8` (`pFront`). Each front ticks on its own schedule and runs `Loop A` / `Loop B` only over its **own** `[CFrontAI + 0x04]` provinces and `[CFrontAI + 0xA4]` armies. There is **no continuous cross-front rebalancing** merely because one front is somewhat thinner (e.g., `2:1` vs `1:1`) than another.
- **Emergency Cross-Front Pulls ("Urgent Requests", `0x006839F5..0x00683C10` -> `0x00694BE0`)**:
  A front only requests divisions from outside its own pool when **all** of these hold:
  1. Front age `[CFrontAI + 0x126] > 10` and request cooldown `[CFrontAI + 0xF8] >= 1` (`+0x124` / `+0x125` non-zero).
  2. `enemy_divs ([CFrontAI + 0xFC]) / our_divs >= panic_ratio` (`[CAI_FrontPrefs + 0x68]` `panic_ratio_vs_ai` or `[+0x6C]` `panic_ratio_vs_human`, default `3.5` in `db/mod_settings.ini` / `ai/default.ai`).
  3. Request volume is `max(2, floor(our_divs * 0.25))`, capped at **`front->prov_count - our_divs`** — so once a front already has at least `1` division per province (`our_divs >= prov_count`), `0x00694BE0` returns immediately without pulling from other fronts.
- **Donor Front Guardrails (`0x00694D58..0x00695190`)**:
  `CAI::RequestFrontDivisions` (`0x00694BE0`) scans non-moving, non-retreating land units on the same landmass (`[CProvince + 0x482]` match). Unassigned/garrison units (`+0x1F4 == 0`) are preferred; another front (`donor_front`) can donate a unit **only** if all of these pass:
  1. `donor_front` age `[+0x126] >= 120` hours (`0x78`).
  2. `donor_strength >= 1.25 * requesting_front_strength` (`0x006896B0`, counting assigned + inbound units).
  3. Leaving the unit behind still keeps `donor_divs - unit_divs >= donor_prov_count` (and `>= 2` if coastal at `0x004ED260`).
  4. Post-donation odds check (`0x00695020..0x00695068`): `donor_enemy_divs / (donor_divs - unit_divs)` must remain better than `req_enemy_divs / req_divs`.
- **Front Merging & Stage 3 Interior Bottleneck Cleanup (`Hook 10` @ `0x00693EE0`)**:
  Because `CProvince + 0x4A8` holds a single `CFrontAI*`, injecting an interior bottleneck (`+0x42 = 0x5B`) via `Hook 4` would block vanilla front merging if `CProvince + 0x4A8` stayed populated across `0x00693EE0`, and when two separate fronts border the same empty interior bottleneck (such as `102 Wolkowysk` between Northern and Southern fronts before a pocket closes), whichever front executes `Hook 4` first claims `CProvince + 0x4A8` (if the other front owns the armies there, `Hook 9A` holds them at the required minimum while `Loop B` on that other front cannot reinforce the province above what arrived). `Hook 10` cleans all `+0x42 == 0x5B` nodes at entry to `0x00693EE0` whenever `[pFront + 0x9E] == 0` so vanilla `0x0068A2B0` merges fronts cleanly once the bottleneck reaches the frontline.
---

## 5. Anatomy of Earlier Debugging Pitfalls & Realignment Fixes (Post-Mortem Reference)

| Issue Encountered | Root Cause | Resolution |
|---|---|---|
| **Hooking `0x006A5790` (`CanCommand`) had no effect on Front AI** | `0x006A5790` belongs to `CInvasionAI` (`0x007F4C24`), not `CFrontAI` (`0x007F3868`). | Restored `0x006A5790` to pristine bytes; hooked callsite `0x00682A58` with wrapper `0x00DCE55A` around retail `CFrontAI::ManageRearReserves` (`0x00681CD0`). |
| **Entire front retreated to Capital (Moscow `175`) on load** | In Tarjan's articulation algorithm, the DFS root (`tin = 1`) trivially satisfies $low[v] \ge tin[root]$ for all children. | Superseded Tarjan in `Cave_STEM_UpdateGraphTable` (`0x00DCBDD5`) with a Local $K$-Hop Frontline Search + Per-Province Vertex-Disjoint Path Search. |
| **Pinned units in combat (Grajewo `6516`) failed to disengage** | Calling `0x00522930` directly leaves the unit attached to `CCombat`; calling `0x004BE920` with `ecx = pCombat` instead of `CLandCombatSide*` hit a no-op slot. | Pass `ecx = [pCombat + 0x84]` (defender side) or `[pCombat + 0x80]` (attacker side) to `0x004BE920`. |
| **Non-combat salient units stood still with 0 Organization** | Zeroing `[pDiv + 0xF4]` or injecting org-mutating hooks (`0x004E7616` / `0x004E7905` / `0x00DCBADC`) corrupted unit organization (`m_fOrganization`). | Never mutate `[pDiv + 0xF4]`; removed `0x004E7616`, `0x004E7905`, and `0x00DCBADC` during Phase 2 cleanup. |
| **Scratchpad `+0x24000` / `+0x26000` flag aliasing & false-positive cuts** | Stride mismatch caused `+0x24000` (`is_threatened`) and `+0x26000` (`is_under_attack`) to alias, and `.tarjan_check_cut` lacked an active-threat shoulder check. | Rebuilt `Cave_STEM_UpdateGraphTable` (`0x00DCBDD5`) with non-overlapping scratchpad arrays and direct safe-path counting up to `SalientNeckWidthThreshold`. |
| **Spearhead exemptions left breakout units stranded or baited** | Unfinished spearhead logic (`SpearheadWinningOdds`, `AbortSpearheadOnNeckCollapse`) exempted attacking stacks blindly from evacuation. | Scrapped both spearhead INI keys; reused slot `0x00DCBAB8` (`0x00DCBB30`) for `SalientSearchDepth`. |
| **Stale STEM evacuations persisted across savegame reload** | `Cave_PostLoadInit` (`0x00DCCB62`) did not clear `g_pGraphTable + 0x30000..+0x3BFFF` when loading a save without restarting the process. | Added a `48 KB` (`0x3000` dwords) zeroing pass in `Cave_PostLoadInit` (`0x00DCCB62`) whenever `[0x00DCBAD4] != 0`. |
| **Access violation on `REB` (`0x157`) after multiple reloads** | Non-AI `CCountry` / `CRebelCountry` (`0x007E5934`) allocates only `0x13C84` bytes, so reading `[pCountry + 0x13C84]` reads 4 bytes past heap object bounds into recycled heap data after reloads. | Verified `CAI_Country` vtable (`0x007F66CC` / `0x007E5464`) and `CAI` vtable (`0x007F3D54`) in both `Cave_STEM_HourlyPerCountry` (`0x00DCCC3D`) and `Cave_STEM_UpdateGraphTable` (`0x00DCBDD5`) before reading `+0x13C84`. |
| **Level-component grouping masked coastal/shoulder bottlenecks** | Merging laterally connected `dist >= cur_d` frontline provinces (`3280`+`3281`, `7335`+`102`) let adjacent wide sectors mask narrow bottlenecks on individual provinces. | Replaced level-component aggregation with direct per-province vertex-disjoint path counting from each frontline province (including `is_threatened == 1`). |
| **Greedy Option B blocking caused false-positive evacuations (`3274 Kowel`)** | Greedy shortest-path blocking sent `3274 -> 503 -> 562 -> 225`, sealing off `3395` and reporting `2/3` instead of `3/3` paths, causing a `3274 <-> 503` shuttle with `MoveUnitsToFront`. | Replaced Option B with Option C (split-node residual vertex-disjoint max-flow) in `Cave_STEM_UpdateGraphTable` (`0x00DCBDD5`) and cleared stale `evac_slot` in `Cave_STEM_UpdateAndEvacuate_Internal` when `neck[prov] == 0`. |

---

## 6. Current Patch 18 (STEM) Architecture & Hook Pipeline

### 6.1 Active Binary Hooks (`Darkest Hour.exe` + `.mod` Cave @ `0x00DCBAB0..0x00DCEC5F`, `.mod` Size `32 KB`)
1. **INI Loader Hook (`0x00DCB7E6` -> `0x00DCBC30..0x00DCBCD7` -> `0x00DCE3AC`)**:
   - Parses `[FrontAI]` parameters from `db/mod_settings.ini` into `0x00DCBAB0..0x00DCBAD0` (`EnableEncirclementDefense`, `SalientNeckWidthThreshold`, `SalientSearchDepth` at `0x00DCBAB8` / key `0x00DCBB30` default `5`, `UseSupplyDepotsAsCores`, `NeckThreatRatio`, `NeckCollapsingOrgThreshold`, `SalientEvacuationQuota` slot `0x00DCBACC`, and `BottleneckDefenseBoost` `0x00DCBAD0`).
   - Jumps at `0x00DCBCD7` to `Cave_LoadEngineSettings` (`0x00DCE711`), loading `[Engine]` flags into `0x00DCBAD8` (`AlwaysShowMovementArrows`), `0x00DCBAE8` (`AutoNoFog`), and `0x00DCBAEC` (`AutoShowId`). (`[0x00DCBAD4]` holds the `0xC0000`-byte `g_pGraphTable` scratchpad pointer.)
2. **Post-Scenario Load Hook (`0x00DCAE55` -> `0x00DCE6AD` `Cave_PostLoadInit`)**:
   - Zeroes `g_pGraphTable + 0x30000..+0xBFFFF` (`0x24000` dwords / `576 KB`, clearing active flags, persistent evacuation slots, quotas, cached normal priorities, and debug telemetry) on scenario or savegame load, then applies `AutoNoFog`, `AutoShowId`, and `Cave_ShowAllMovingArrows` (`0x00DCE619`).
3. **Movement Arrow Deselect Filter (`0x005226C1` -> `0x00DCE677` `Cave_DeselectArrows`)**:
   - Preserves movement/retreat arrows across deselection when `AlwaysShowMovementArrows == 1` (`0x00DCBAD8`).
4. **Hourly Game Loop Hook (`0x005AEDBE` -> `0x00DCE80A` `Cave_STEM_HourlyAllCountries`)**:
   - Maintains `[Engine]` flags, allocates `0xC0000` (`768 KB`) for `g_pGraphTable`, zeroes hourly transient buffers (`+0x30000..+0x31FFF`, `+0x40000..+0x57FFF`, `+0x80000..+0xBFFFF`, while preserving `+0x58000..+0x5FFFF` `norm_prio_f32` across ticks for Loop A & telemetry), and calls `Cave_STEM_HourlyPerCountry` (`0x00DCE7BF`) -> `Cave_STEM_UpdateAndEvacuate_Internal` (`0x00DCE3BE`) when `EnableEncirclementDefense == 1`.
5. **Front AI Rear-Reserve, Salient & Interior Bottleneck Wrapper Hook (`0x00682A58` -> `0x00DCE8D9` `Cave_FrontAI_ManageReservesAndSalients`)**:
   - Prunes evacuating units from `[CFrontAI + 0xC8]`, sets `[pArmy + 0x17B] = 2` around retail `CFrontAI::ManageRearReserves` (`0x00681CD0`), restores `[pArmy + 0x17B] = 0`, and exempts active STEM evacuating units in `[CFrontAI + 0xC8]` (tag `0x5A`).
   - Prunes stale injected interior nodes (`+0x42 = 0` when promoted by `0x006813E0`), then injects adjacent interior bottleneck provinces (`neck_q8 > 0`, `evac_q8 == 0`, `[CProvince + 0x4A8] == 0` or `== esi`, tagged `+0x42 = 0x5B`) into `[CFrontAI + 0x04]` so Loop B includes them as redistribution targets.
6. **Save-Game Telemetry Hook (`0x004301D7` -> `0x00DCEF0A` `Cave_STEM_SaveGameHook`)**:
   - Refreshes `Cave_STEM_UpdateGraphTable` (`0x00DCC1E9`) in read-only mode after save serialization completes and dumps semicolon-delimited `stem_debug.csv` (including Stage 2 `NormPrio` and `AdjPrio`).
7. **Stage 2 & 3 Front AI Hooks inside `CFrontAI::MoveUnitsToFront` (`0x006829B0`) & `CAI::UpdateFronts` (`0x00693EE0`)**:
   - **Pass 1 Zero-Enemy Guard Skip (`0x006836D5` -> `0x00DCEC7D` `Cave_FrontAI_Pass1SetNoLandEnemyFlag`)**: Prevents retail from stamping `+0x8D = 1` (`no_land_enemy`) onto injected interior bottleneck provinces.
   - **Pre-`UpdateFronts` Injected-Node Cleanup (`0x00693EE0` -> `0x00DCECC1` `Cave_FrontAI_PreUpdateFrontsCleanInjected`)**: Guards against busy `[pFront + 0x9E] != 0`, then removes injected `+0x42 == 0x5B` `CFrontProvince` entries, resets `[CProvince + 0x4A8] = 0`, and deletes those `CFrontProvince` instances before vanilla `0x00693EE0` evaluates sector merges (`0x0068A2B0`).
   - **Loop A Interior Bottleneck Garrison Hold (`0x00683C9D` -> `0x00DCED64` `Cave_FrontAI_LoopAIsFrontOrHeldNeck`)**: Wraps `0x006813E0`; holds stationary interior bottleneck units while `(fr_eff_str - army_str) < BottleneckDefenseBoost * Q_agg` and deducts surplus armies as they release.
   - **Loop A Candidate Attraction (`0x00DCEEBC`) & Loop B Border Neck Boost (`0x00DCF01B`, `0x00DCF103`, `0x00DCF1A8`)**: Adds `BottleneckDefenseBoost * Q_agg` (`Q_agg` aggregated in Step 5E via `BottleneckQuotaAggregation` at `0x00DCBADC`) to frontline bottleneck shares `S(B)` and under-strength Loop A candidate attractiveness.
   - **Loop A Adjacent Candidate Gate (`0x00683EB6` -> `0x00DCEE3D` `Cave_FrontAI_LoopAAdjCheck`)**: Wraps `0x004E9500`, excluding adjacent border candidates where `Q == 1.0` (`q8 >= 255`) or `0 < Q < 1.0` with `divs >= AdjustedPriority`.
   - **Loop A Candidate Scoring & Gate (`0x00684088` -> `0x00DCEEBC` `Cave_FrontAI_LoopACheckCand` & `0x006840F6` -> `0x00DCEFBF` `Cave_FrontAI_LoopAStoreBest`)**: Rejects `Q == 1.0` or already-saturated partial candidates, scales `(en_str - fr_str)` attractiveness toward `(1 - Q)` (dividing negative scores by `(1 - Q)` so evacuating provinces lose to safe ones), and stores the scaled winning score.
   - **Loop A Fallback Head Check (`0x00684131` -> `0x00DCEFCA` `Cave_FrontAI_LoopAFallbackCheck`)**: Wraps `0x004E9500` on the `edi == 0` fallback (`0x00684117`), refusing to march interior armies into a list head whose `quota_q8 > 0`.
   - **Loop B Border Receiver Quota Cache & Scaling (`0x00684551` -> `0x00DCF01B` `Cave_FrontAI_ScaleReceiverShare`)**: Caches unscaled `NormalFrontAIPriority = S(u) * D_front` into `norm_prio_f32` (`+0x58000`), scales `S(u)` by `(1 - Q(u))` (forcing `S(u) = 0.0` when `Q == 1.0` or `Q > 0 && S_adj * D_front < 1.0` to suppress `even`-mode's `deficit = 1` floor at `0x0068459A`), and syncs `NormPrio` / `AdjPrio` via `Cave_STEM_SyncTelemetryPrio` (`0x00DCE23B`).
   - **Loop B Donor Share Scaling (`0x0068470D` -> `0x00DCF103` `Cave_FrontAI_ScaleDonorShare2` & `0x0068526A` -> `0x00DCF1A8` `Cave_FrontAI_ScaleDonorShare3`)**: Scales `S(u)` in both donor evaluation paths so excess divisions in evacuating salients can be donated outward.

### 6.2 Per-Country Graph Analysis, Dynamic Quota & Persistent Evacuation (`0x00DCC193` / `0x00DCE025` / `0x00DCE059`)
1. **Active-Front Gate & Table Initialization (`Cave_STEM_UpdateGraphTable` @ `0x00DCC1E9`)**:
   - Verifies AI `CCountry` vtables (`0x007F66CC` / `0x007E5464`), `!IsAtPeace` (`0x006A8720`), `CAI` vtable (`0x007F3D54`), and `[pCAI + 0x278]` active fronts (`m_EnemyFrontProvinces > 0`).
   - Initializes GraphTable (`+0x00000..+0x0FFFF`), zeroes scratch buffers (`+0x10000..+0x2FFFF`), sets `min_org_q8` (`+0x46000`) to `0xFF`, and zeroes `+0x60000..+0x7FFFF` (`fr_eff_str`, `en_eff_str`, `inbound_fr_str`, `raw_hostile_str`).
2. **Dynamic Threat Scanner & Unit Presence (`+0x24000`, `+0x26000`, `+0x28000 & 0x20`)**:
   - Stamps `prov_flags |= 0x20` on any non-empty friendly/allied land army location **before** skipping combat-retreating units (`[+0x17B] != 0`), then computes `fr_eff_str_f32` (`+0x60000`), `min_org_q8` (`+0x46000`), `inbound_fr_str_f32` (`+0x70000`), `raw_hostile_str_f32` (`+0x78000`), and `is_threatened` (`+0x24000`) / `en_eff_str_f32` (`+0x68000`).
3. **Local $K$-Hop Frontline Search (`SalientSearchDepth` @ `0x00DCBAB8`)**:
   - Expands inward up to $K$ hops through unthreatened accessible provinces (`CCountry::CanEnterOrTraceSupply` @ `0x0044A690`), seeds Core / Depot / $K$-horizon roots (`dist = 0`), and runs Pass-1 Safe BFS.
4. **Option C Residual Max-Flow, Downstream Cut Contraction & Continuous Quota (`Step 5A` / `5B` / `5C`)**:
   - **Step 5A**: Runs Option C split-node augmenting-path BFS once per `dist > 0` strip province plus `is_threatened == 1` sources, extracting the exact residual minimum cut $C_{\text{raw}}(P)$ from `+0x26000` / `+0x2C000` (`optc_vis[2v] == pass_id && optc_vis[2v+1] != pass_id`).
   - **Step 5B**: Contracts intermediate corridor bottlenecks in increasing `dist` order (`MAX_CONTRACT_STEPS = 8`), enforces the Natural Geography Gate (`F_Exp == 0 && !is_threatened => Q = 0.0`), and computes `quota_q8[P]` from `D_Width * T_Neck * V_Ret` (`VP` at `[CProvince + 0x19E]`, `IC` at `[*(prov + 0x1CA) + 0x14]`).
   - **Step 5C & Pass-2 Neck Lock**: Scans `+0x1C000` (and Pass-2 BFS queue) in reverse descending `dist` order prior to chaining: whenever an evacuating province $P$ (`quota_q8[P] > 0`) contains friendly/allied units (`prov_flags & 0x20 != 0`), locks each dependency neck $N$ with `Dist[N] < Dist[P]` to `quota_q8[N] = 0, neck[N] = 0`, keeping bottleneck provinces held until upstream salients clear (and naturally stopping `.chain_necks_start` at $N$).
   - Writes per-province telemetry via `.hlp_write_telemetry` and `Cave_STEM_SyncTelemetryPrio` (`0x00DCE23B`).
5. **Persistent Evacuation Registry & Unit Dispatch (`Cave_STEM_GetUnitEvacSlot` @ `0x00DCE38A` / `Cave_STEM_UpdateAndEvacuate_Internal` @ `0x00DCE3BE`)**:
   - Dispatches `CLandCombatSide::OrderRetreat` (`0x004BE920`) for pinned combat units and `CAI::DispatchMoveOrder` (`0x006AAFF0`) for non-combat salient units, preserving active evacuation marches in `g_pGraphTable + 0x34000..0x3BFFF` until reaching `dest_prov` or `neck[prov] == 0`.
   - See [plan_stem_strategic_defense.md](../plans/plan_stem_strategic_defense.md) and [plan_front_ai_encirclement_defense.md](../plans/plan_front_ai_encirclement_defense.md) for active implementation stages and roadmap.
