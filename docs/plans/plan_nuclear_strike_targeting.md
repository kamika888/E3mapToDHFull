# Engine Modification Plan: Enhanced AI Nuclear Strike Targeting & Falloff Gate System (Patch 17)

**Document ID**: `plan_nuclear_strike_targeting.md`  
**Target Engine**: Darkest Hour 1.05.2 (32-bit x86 PE, Checksum: `TENE`)  
**Target Executable**: `Darkest Hour.exe` (Image Base: `0x00400000`, Base File Size: `4,730,956` bytes, Patched Size: `4,751,360` bytes)  
**Configuration File**: `db\mod_settings.ini` -> Section `[NuclearAI]`  
**Patcher Integration**: `patch_darkest_hour.bat` -> **Patch 17** (`$PATCH_SHA256 = "5FFC80BC5D7EE574AE0854BCEADFD2AB76608AB5E5371B63F7E2C1EB2EBE3EA6"`)  
**Code Cave Location**: Dedicated `.mod` page 2 at VA `0x00DCB500`-`0x00DCBAA2` (File Offset: `0x00486500`, `1,442` bytes)  
**Status**: IMPLEMENTED & VERIFIED

---

## 1. Executive Summary & Problem Definition

In Darkest Hour retail v1.05.2 (see [Nuclear Strike AI Architecture & Targeting Engine](../engine/nuclear_ai.md)), AI nuclear weapon deployment suffers from severe targeting pathologies:
1. **Occupied Soil, Colonial Territory & Puppet Divergence**: AI nations frequently detonate atomic bombs on occupied enemy territories, puppet colonies, frontline transit provinces, or empty non-core colonial islands (e.g., the United States immediately nuking Palembang `1358` in Indonesia or Japanese-occupied French Indochina) rather than the enemy homeland (Tokyo, Osaka, Hiroshima).
2. **Hidden `+1.0` Base Score Floor (`nukestriketolerance`)**: In `sub_4A52E0` (`0x004A5341`), the engine initializes every enemy-controlled province's base score to `air->nukestriketolerance` (`1.0f` across all vanilla AI files). Even an empty non-core province with `0` IC, `0` VP, `0` divisions, and `0` reactors starts with `1.0` base point, which scales to `~50-60` after multiplying by $\sqrt{\text{Controller Total IC}} \times \text{nukestrikedesirability}$ (`5.0`).
3. **Tactical Division Overweighting**: Enemy troop stacks in frontline hubs (20 to 40 divisions) generate `+10.0` to `+20.0` base points (`0.5` per division), overpowering lightly garrisoned home cities whenever home cities are skipped or out of range.
4. **Random Candidate Skipping**: The mission generator in `sub_66DA10` (`0x0066E3FB`) randomly skips 1 to 10 provinces per iteration while scanning targets in flight range (`rand() % 10 + 1`), bypassing up to 90% of valid targets.
5. **Range Starvation ("Burma / Palembang Syndrome")**: Because the engine lacks a minimum target value threshold (`bestScore` starts at `0.0f`), when enemy homeland cities are out of flight range from the bomber's current base, the AI immediately drops its atomic bomb on the highest-scoring peripheral province in range rather than holding the nuke in reserve or waiting to rebase closer.

### Solution Overview
Patch 17 introduces the **Enhanced AI Nuclear Strike Targeting & Falloff Gate System**:
1. **Externalizes All 6 Hardcoded Engine Constants & Separates Additive `*Weight` vs. Multiplicative `*Multiplier` Parameters**:
   - **Stage 1 -- Additive Base Province Weights (`*Weight`)**: `CoreValueWeight` (`10.0`), `DivisionWeight` (`0.5`), `NuclearReactorWeight` (`20.0`), `ProvinceInstallationWeight` (`0.0`), and `ResourceWeight` (`0.0`). Multiplied by the corresponding provincial attribute and **added** to `baseScore` (which starts at `nukestriketolerance`). `0.0` = disabled/ignored; **any value `> 0.0` increases province priority**.
   - **Stage 2 -- Multiplicative Total Score Scalars (`*Multiplier`)**: `NonBelligerentOwnerMultiplier` (`0.5`), `AlliedOwnerMultiplier` (`0.2`), `PuppetControllerMultiplier` (`0.1`), and `MinorPowerMultiplier` (`0.2`). Multiplied sequentially against the entire running `baseScore`. `1.0` = neutral (no change); **`< 1.0` decreases priority**; **`> 1.0` increases priority**; `0.0` = hard veto.
2. **Puppet Controller Penalty**: Strongly discourages nuking provinces controlled by a puppet state (`PuppetControllerMultiplier`, default `0.1`).
3. **Major Power IC Prioritization**: Replaces compressed square-root IC scaling with configurable linear or super-linear scaling (`ControllerICScalingMode`, `MinorPowerICThreshold`, `MinorPowerMultiplier`), ensuring major industrial powers are prioritized over minors.
4. **Falloff / Minimum Score Threshold Gate ("Save Nukes for Later")**: Enforces `MinTargetScoreThreshold` (default `100.0`) inside `CCountry::EvaluateNukeTargetProvince` (`fn_enhanced_nuke_eval`) prior to outer-loop airbase relocation distance attenuation. If a candidate province's nuclear strike score is below `MinTargetScoreThreshold`, `fn_enhanced_nuke_eval` returns `0.0`, causing the bomber to save its nuke (and either fly conventional missions or rebase to an enabled forward airbase within range of high-value homeland targets).
5. **Installation & Resource Strategic Scoring**:
   - `ProvinceInstallationWeight`: Scores the aggregate military base footprint (`navalBase + airBase + radar + rocketSite`).
   - `ResourceWeight`: Scores total provincial natural resource output (`energy + metal + oil + rare_materials`).

---

## 2. Parameter Inventory & Runtime Memory Table (`0x00DCB500`)

### 2.1 Stage 1: Additive Base Score Weights (`*Weight`)
| Parameter Name | Cave VA | Binary Type | Vanilla Default | Engine Role |
|---|---|---|---|---|
| `CoreValueWeight` | `0x00DCB504` | `float` | `10.0f` | Added per point of `(IC * 0.5 + VP)` if province is a national core of controller (`0x007E4090` in vanilla) |
| `DivisionWeight` | `0x00DCB508` | `float` | `0.5f` | Added per enemy division stationed in province (`0x007E34C0` in vanilla) |
| `NuclearReactorWeight` | `0x00DCB50C` | `float` | `20.0f` | Added per level of Nuclear Reactor (`pProv + 0x1EA`) in province (`0x007E682C` in vanilla) |
| `ProvinceInstallationWeight` | `0x00DCB530` | `float` | `0.0f` | Added per aggregate level of `airBase + navalBase + radar + rocketSite` (`+0x1DE, +0x1E2, +0x1E6, +0x1EE`) |
| `ResourceWeight` | `0x00DCB534` | `float` | `0.0f` | Added per aggregate unit of `rare_materials + metal + energy + oil` (`+0x274, +0x278, +0x27C, +0x280`) |

### 2.2 Stage 2: Multiplicative Total Score Scalars (`*Multiplier`) & IC Scaling
| Parameter Name | Cave VA | Binary Type | Default | Engine Role |
|---|---|---|---|---|
| `NonBelligerentOwnerMultiplier` | `0x00DCB510` | `float` | `0.5f` | Multiplies total score when legal owner (`+0x3D4`) is not at war with attacker (`0x007E34C0` in vanilla) |
| `AlliedOwnerMultiplier` | `0x00DCB514` | `float` | `0.2f` | Multiplies total score when legal owner (`+0x3D4`) is allied with attacker (`0x007E6868` in vanilla) |
| `PuppetControllerMultiplier` | `0x00DCB51C` | `float` | `0.1f` | Multiplies total score when controller (`+0x3D8`) is a puppet (`m_pDiploRelations + 0x3B30 > 0`) |
| `ControllerICScalingMode` | `0x00DCB520` | `int` | `1` | `0` = Vanilla $\sqrt{\text{TotalIC}}$; `1` = Linear ($\text{TotalIC} / 10.0$); `2` = Super-linear ($(\text{TotalIC}/10) \times \sqrt{\text{TotalIC}/10}$) |
| `MinorPowerICThreshold` | `0x00DCB524` | `int` | `40` | Controller Total IC threshold below which `MinorPowerMultiplier` is applied |
| `MinorPowerMultiplier` | `0x00DCB528` | `float` | `0.2f` | Multiplies total score when controller Total IC `< MinorPowerICThreshold` |

### 2.3 Stage 3: Candidate Scanning & Falloff Gate
| Parameter Name | Cave VA | Binary Type | Default | Engine Role |
|---|---|---|---|---|
| `EnableEnhancedNuclearTargeting`| `0x00DCB500` | `int` | `1` | Master switch (`0` = vanilla `sub_4A52E0`, `1` = enhanced Patch 17 evaluator) |
| `CandidateRandomSkipMax` | `0x00DCB518` | `int` | `10` | Modulo divisor for candidate stride (`rand() % Max + 1`; `<= 1` evaluates every province sequentially) |
| `MinTargetScoreThreshold` | `0x00DCB52C` | `float` | `100.0f` | Falloff gate enforced at the end of `fn_enhanced_nuke_eval`: if `finalScore < MinTargetScoreThreshold`, returns `0.0` |

---

## 3. Configuration Specification (`db\mod_settings.ini`)

All targeting parameters are managed in the `[NuclearAI]` section in `db\mod_settings.ini`:

```ini
[NuclearAI]
; Enable Enhanced Nuclear Strike Targeting System:
; 0 = Vanilla retail behavior (hardcoded weights and random province skipping)
; 1 = Enhanced targeting system (recommended)
EnableEnhancedNuclearTargeting = 1

; ==============================================================================
; Part 1: Additive Base Province Weights (*Weight)
;   Base score starts at the AI file's 'nukestriketolerance' (typically 1.0),
;   then adds (attribute * Weight) for each factor below.
;   0.0 = ignored/disabled; any value > 0.0 increases province priority.
; ==============================================================================

; Weight applied to national (core) province strategic value: (IC * 0.5 + VP) * THIS
; Only added if the province is a national core of the enemy controller (non-core
; owned or occupied provinces contribute 0.0 from IC and VP).
; Vanilla default = 10.0
CoreValueWeight = 10.0

; Weight awarded per enemy division stationed in target province: divisions * THIS
; Vanilla default = 0.5 (awards +15.0 base points for a 30-division stack)
DivisionWeight = 0.5

; Weight applied to provincial Nuclear Reactor level (pProv + 490): reactorLevel * THIS
; Vanilla default = 20.0 (awards +120.0 base points for a Level 6 reactor)
NuclearReactorWeight = 20.0

; Weight applied to aggregate military installations (new):
; (navalBaseCurrentSize + airBaseCurrentSize + radarCurrentSize + rocketSiteCurrentSize) * THIS
; Vanilla default = 0.0 (untracked); Recommended = 2.0
ProvinceInstallationWeight = 0.0

; Weight applied to aggregate daily provincial resource production (new):
; (energy + metal + oil + rare_materials) * THIS
; Vanilla default = 0.0 (untracked); Recommended = 0.5
ResourceWeight = 0.0

; ==============================================================================
; Part 2: Total Score Multipliers & Country Scaling (*Multiplier)
;   Multiplied sequentially against the province's total baseScore.
;   1.0 = neutral (no change); < 1.0 = decreases priority; > 1.0 = increases priority;
;   0.0 = hard veto (zeroes out score).
; ==============================================================================

; Multiplier applied when legal province owner is not at war with attacker (e.g. occupied neutral)
; Vanilla default = 0.5
NonBelligerentOwnerMultiplier = 0.5

; Multiplier applied when legal province owner is allied with attacker (e.g. allied soil occupied by enemy)
; Note: Compounds with NonBelligerentOwnerMultiplier (0.5 * 0.2 = 0.1x in vanilla)
; Vanilla default = 0.2
AlliedOwnerMultiplier = 0.2

; Multiplier applied if province controller is a puppet of another nation (new):
; Checks controller puppet status (m_nMasterTag != 0).
; Default = 0.1 (strongly discourages nuking puppet states like French Indochina or Manchukuo; 1.0 = no penalty)
PuppetControllerMultiplier = 0.1

; Controller Total IC Scaling Mode (new):
; Prioritizes major powers over minor nations based on controller's total IC.
; 0 = Vanilla square root scaling: score *= sqrt(TotalIC)
; 1 = Linear IC scaling: score *= TotalIC / 10.0 (heavily favors majors; e.g. 100 IC gives 10x vs 25 IC giving 2.5x)
; 2 = Super-linear scaling: score *= (TotalIC / 10.0) * sqrt(TotalIC / 10.0)
; Vanilla default = 0; Recommended = 1
ControllerICScalingMode = 1

; Minor Power IC Threshold & Penalty Multiplier (new):
; If province controller Total IC is below this threshold, score is multiplied by MinorPowerMultiplier.
; Set MinorPowerICThreshold = 0 to disable.
MinorPowerICThreshold = 40
MinorPowerMultiplier = 0.2

; ==============================================================================
; Part 3: Candidate Scanning & Falloff Gate
; ==============================================================================

; Modulo divisor for candidate province iteration stride: stride = (rand() % Max) + 1
; Vanilla default = 10 (skips 1 to 10 provinces per step, evaluating only ~15% of in-range targets)
; Set to 0 or 1 for sequential exhaustive scanning (evaluates 100% of candidate targets in range)
CandidateRandomSkipMax = 10

; Falloff / Minimum Target Score Gate ("Save Nukes for Later") (new):
; Evaluated inside CCountry::EvaluateNukeTargetProvince after multiplying by 'nukestrikedesirability'.
; If a candidate province's score falls below this threshold, it returns 0.0 so the AI
; holds atomic weapons in reserve rather than wasting them on low-value peripheral provinces
; (e.g. empty non-core colonial provinces scoring ~50 from nukestriketolerance = 1.0 alone).
; Vanilla default = 0.0 (nukes any valid target with score > 0)
; Recommended = 100.0 (ensures atomic weapons are only deployed against high-value strategic sites)
MinTargetScoreThreshold = 100.0
```

---

## 4. Mathematical Comparison: Retail vs. Enhanced (Patch 17)

| Evaluation Step | Tokyo (Retail) | Palembang `1358` (Retail) | Saigon Puppet (Retail) | Tokyo (Patch 17) | Palembang `1358` (Patch 17) | Saigon Puppet (Patch 17) |
|---|---|---|---|---|---|---|
| **Controller** | Japan (120 IC) | Japan (120 IC) | Indochina Puppet (15 IC) | Japan (120 IC) | Japan (120 IC) | Indochina Puppet (15 IC) |
| **Legal Owner** | Japan | Japan (DEI surrender) | France (Allied) | Japan | Japan (DEI surrender) | France (Allied) |
| **Controller Core?** | Yes | No (`0.0`) | Yes (if IDC core) | Yes | No (`0.0`) | Yes (if IDC core) |
| **`nukestriketolerance`**| `1.0` | `1.0` | `1.0` | `1.0` | `1.0` | `1.0` |
| **Core Value Weight** | `(5+15)*10 = +200` | `+0.0` | `(1+2)*10 = +30.0` | `(5+15)*10 = +200` | `+0.0` | `(1+2)*10 = +30.0` |
| **Divisions (`0.5`)** | 1 (`+0.5`) | 0 (`+0.0`) | 20 (`+10.0`) | 1 (`+0.5`) | 0 (`+0.0`) | 20 (`+10.0`) |
| **Base Score (`Stage 1`)**| `201.5` | `1.0` | `41.0` | `201.5` | `1.0` | `41.0` |
| **Puppet Multiplier** | `1.0x` | `1.0x` | `1.0x` (No check) | `1.0x` | `1.0x` | `0.1x` (`PuppetControllerMultiplier`) |
| **Minor Power Penalty**| `1.0x` | `1.0x` | `1.0x` (No check) | `1.0x` | `1.0x` | `0.2x` (`IC < 40`) |
| **Controller IC Scale**| `sqrt(120) = 10.95x`| `sqrt(120) = 10.95x` | `sqrt(15) = 3.87x` | `120 / 10 = 12.0x` | `120 / 10 = 12.0x` | `15 / 10 = 1.5x` |
| **Owner Multipliers** | `1.0x` | `1.0x` (Owner=JAP!) | `0.5 * 0.2 = 0.1x` | `1.0x` | `1.0x` (Owner=JAP!) | `0.5 * 0.2 = 0.1x` |
| **Desirability (`5.0`)**| `x 5.0 = 11,032` | `x 5.0 = 54.8` | `x 5.0 = 79.3` | `x 5.0 = 12,090` | `x 5.0 = 60.0` | `x 5.0 = 0.62` |
| **Threshold Gate** | `> 0.0` (Pass) | **`54.8 > 0.0` (Pass!)** | **`79.3 > 0.0` (Pass!)** | **`12,090 >= 100` (Pass)** | **`60.0 < 100` (REJECTED -> `0.0`)** | **`0.62 < 100` (REJECTED -> `0.0`)** |
| **Outcome** | Targeted if in range | **Nuked immediately from Singapore** | **Nuked from Singapore** | **Rebases to Okinawa & Nukes Japan** | **Held in Reserve** | **Held in Reserve** |

---

## 5. Binary Hooking & Code Cave Layout (Patch 17)

### 5.1 Memory Layout in `.mod` Section (`0x00DCB500`-`0x00DCBAA2`)
* **`0x00DCB500`-`0x00DCB53F` (64 bytes)**: Runtime variables table initialized with defaults and populated on startup from `db\mod_settings.ini`.
* **`0x00DCB540`-`0x00DCB69F` (352 bytes)**: Null-terminated ASCII key strings for `[NuclearAI]`.
* **`0x00DCB6A0` (`fn_read_nuke_float`)**: Helper reading a floating-point key from `[NuclearAI]` via `GetPrivateProfileStringA` + `0x00DCAF49`.
* **`0x00DCB6F0` (`fn_load_nuclear_ai_ini`)**: Chained from Patch 15's INI loader exit (`0x00DCB308`); loads all 14 `[NuclearAI]` settings and returns to `0x007E2DAC`.
* **`0x00DCB800` (`fn_hook_init_score`)**: Hooked at `0x0066E270`; initializes outer loop `bestScore` (`[esp + 0x1C]`) to `0.0f` and returns to `0x0066E278`.
* **`0x00DCB830` (`fn_advance_candidate_stride`)**: Hooked at `0x0066E3FB`; preserves `ECX` across `_rand()` (`0x007A7C0E`) and advances `ESI` by `1` (if `CandidateRandomSkipMax <= 1`) or `(rand() % CandidateRandomSkipMax) + 1`, then reloads `EAX = [esp + 0x24]` and jumps to `0x0066E410`.
* **`0x00DCB860` (`fn_enhanced_nuke_eval`)**: Hooked at `0x004A52E0` (`CCountry::EvaluateNukeTargetProvince`); computes Stage 1 additive weights, Stage 2 country/owner multipliers, multiplies by `nukestrikedesirability`, and enforces `MinTargetScoreThreshold` (`0x00DCB52C`) before returning in `ST(0)`.

### 5.2 Why `MinTargetScoreThreshold` is Enforced Inside `fn_enhanced_nuke_eval` (`0x00DCB860`)
In `CAIPlanAirMarshal::CreateCombatAirMissionPlan` (`sub_66DA10`), the outer loop evaluates candidate targets both from the bomber wing's **current airbase** (e.g., Singapore `1353`) and from **other enabled friendly airbases** (e.g., Okinawa `1193`). When evaluating another airbase (`0x0066E3AA..0x0066E3DC`), `sub_66DA10` divides the returned target score by the relocation distance (`dist * 0.005`) before comparing it against `bestScore` (`[esp + 0x1C]`).

By enforcing `MinTargetScoreThreshold` inside `fn_enhanced_nuke_eval` (`0x00DCB860`) **before** relocation distance attenuation and keeping the outer loop's `bestScore` initialized to `0.0f` (`0x00DCB800`):
1. Low-value peripheral targets in range of Singapore (such as Palembang `1358` scoring `~60.0`) fail `MinTargetScoreThreshold = 100.0` inside `fn_enhanced_nuke_eval` and return `0.0`.
2. High-value homeland targets in range of Okinawa (such as Hiroshima or Tokyo scoring `1,500+`) pass `MinTargetScoreThreshold = 100.0` inside `fn_enhanced_nuke_eval`, survive relocation distance attenuation (`> 0.0`), and win the outer loop--causing the bomber wing at Singapore to automatically rebase to Okinawa and then execute the nuclear strike on Japan.
