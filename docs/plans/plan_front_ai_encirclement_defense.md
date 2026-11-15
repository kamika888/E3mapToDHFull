# Patch 18: Salient Topological Evacuation & Momentum Engine (STEM) - Implementation Status & Reference

**Status**: Realignment & Cleanup Complete (Phases 1-6) | **Binary SHA-256**: `47BC619FFFC3E9FB8D5021378EF42A59C59C964F11799E20B068EACA2532676E`  
**Related Docs**: [Front AI Architecture](../engine/front_ai.md) | [Plans Index](README.md) | [Patcher](../../tools/patch_darkest_hour.bat) | [Settings](../../db/mod_settings.ini)

---

## 1. Executive Summary

Patch 18 (STEM) adds topological encirclement detection and salient evacuation to `CFrontAI` using an hourly articulation-point / BFS graph pass rooted in a dedicated `.mod` cave block (`0x00DCBAB0..0x00DCDAAD`). During Phases 1-6 of the STEM Realignment & Cleanup, the subsystem was rebuilt to remove memory aliasing bugs, decouple unfinished spearhead overrides, restore retail rear-reserve logic (`CFrontAI::ManageRearReserves` @ `0x00681CD0`), dynamically wire neck-threat/org and depot-core settings from `db/mod_settings.ini`, and eliminate an unrelated Patch 1 / Patch 4 crash & `.data` collision discovered during live testing.

Live validation on the Grodno and Crimea fronts confirmed that:
- Allied-access pathing (`CCountry::CanEnterOrTraceSupply` @ `0x0044A690`) and `UseSupplyDepotsAsCores` (`[pProv + 0x270] > 0` / controller capital stockpile) trace supply/escape paths across allied territory as expected.
- Mere enemy presence or weak probing attacks no longer trigger false-positive mass evacuations.
- Heavy attacks on a bottleneck/shoulder (`NeckThreatRatio` / `NeckCollapsingOrgThreshold`) trigger disengagement and evacuation along escape routes.
- **One primary behavioral gap remains open (out of scope for cleanup)**: once a threatened shoulder is captured by the enemy and fighting pauses before the interior province is attacked, evacuation clears and units attempt to re-enter the pocket (see Section 5).

---

## 2. `db/mod_settings.ini` Wiring Audit

### 2.1 `[FrontAI]` & `[Engine]` Configuration Status

| Section | Variable | Current INI | Binary Slot VA | Status | Notes |
| :--- | :--- | :---: | :---: | :--- | :--- |
| `[FrontAI]` | `EnableEncirclementDefense` | `1` | `0x00DCBAB0` | **Wired & Active** | Master gate checked by `0x00DCC885` (`Cave_STEM_HourlyPerCountry`) and evacuation checks. |
| `[FrontAI]` | `SalientNeckWidthThreshold` | `2` | `0x00DCBAB4` | **Wired & Active** | Controls Pass-2 bridge / narrow-neck fallback degree threshold in `Cave_STEM_UpdateGraphTable` (`0x00DCBDD5`). |
| `[FrontAI]` | `UseSupplyDepotsAsCores` | `1` | `0x00DCBABC` | **Wired & Active** | When `1`, accessible provinces (`0x0044A690`) with an active local supply stockpile (`[pProv + 0x270] > 0.0f`) or controller capital stockpile act as BFS escape roots. |
| `[FrontAI]` | `NeckThreatRatio` | `1.5` | `0x00DCBAC0` | **Wired & Active** | Dynamically read by `0x00DCBDD5`; hostile-to-friendly ground combat strength ratio needed to flag a province as threatened (`+0x24000`). |
| `[FrontAI]` | `NeckCollapsingOrgThreshold` | `10.0` | `0x00DCBAC4` | **Wired & Active** | Dynamically read by `0x00DCBDD5` (binary default `30.0`); average friendly defender organization threshold triggering threat flag alongside `NeckThreatRatio`. |
| `[FrontAI]` | `SalientEvacuationQuota` | `0.0` | `0x00DCBACC` | **Pending (Unreferenced)** | Loaded from `db/mod_settings.ini` into `0x00DCBACC`, but not yet referenced by STEM evacuation code. |
| `[FrontAI]` | `BottleneckDefenseBoost` | `3.5` | `0x00DCBAD0` | **Pending (Unreferenced)** | Loaded from `db/mod_settings.ini` into `0x00DCBAD0`, but not yet wired into `CFrontAI` province priority weighting. |
| `[FrontAI]` | `AbortSpearheadOnNeckCollapse` | *removed* | `0x00DCBAB8` | **Scrapped** | INI key removed. Header slot `0x00DCBAB8` retained only for struct alignment; unreferenced by runtime code. |
| `[FrontAI]` | `SpearheadWinningOdds` | *removed* | `0x00DCBAC8` | **Scrapped** | INI key removed. Header slot `0x00DCBAC8` retained only for struct alignment; unreferenced by runtime code. |
| `[Engine]` | `AlwaysShowMovementArrows` | `1` | `0x00DCBAD8` | **Wired & Active** | Loaded by `Cave_LoadEngineSettings` (`0x00DCC80E`); controls forced arrow rendering (`0x00DCC730` / `0x00DCC78E`). |
| `[Engine]` | `AutoNoFog` | `1` | `0x00DCBAE8` | **Wired & Active** | Loaded by `Cave_LoadEngineSettings` (`0x00DCC80E`); applied on scenario/save load (`0x00DCC7C4`) and hourly tick (`0x00DCC8B6`). |
| `[Engine]` | `AutoShowId` | `1` | `0x00DCBAEC` | **Wired & Active** | Loaded by `Cave_LoadEngineSettings` (`0x00DCC80E`); applied on scenario/save load (`0x00DCC7C4`) and hourly tick (`0x00DCC8B6`). |

---

## 3. Realized Hook & Cave Architecture

### 3.1 Active Hooks into Retail `Darkest Hour.exe`

| Retail Address | Target / Cave Function | Role |
| :--- | :--- | :--- |
| `0x005AEDBE` | `Cave_STEM_HourlyAllCountries` (`0x00DCC8B6`) | Hourly AI tick: initializes STEM scratchpad & dispatches `Cave_STEM_HourlyPerCountry` (`0x00DCC885`). |
| `0x00682A58` | `Cave_FrontAI_ManageReservesAndSalients` (`0x00DCC95B`) | Wrapper around retail `CFrontAI::ManageRearReserves` (`0x00681CD0`); executes retail rear-reserve logic cleanly and integrates salient handling. |
| `0x005226C1` | `Cave_DeselectArrows` (`0x00DCC78E`) | Supports `AlwaysShowMovementArrows` when deselected on map. |
| `0x00DCAE55` | `Cave_PostLoadInit` (`0x00DCC7C4`) | Applies `AutoNoFog` and `AutoShowId` from `Cave_LoadEngineSettings` (`0x00DCC80E`). |

### 3.2 Cave Layout (`.mod` Patch 18 Chunk @ `0x00DCBAB0`)

- `0x00DCBAB0..0x00DCBAF0`: Parameter header (strings & loaded INI values; `0x00DCBADC` zeroed, stale `0x00DCBC00..0x00DCBC2B` and `0x00DCBD60..0x00DCBD9F` regions sanitized, `0x00DCBCD7: jmp 0x00DCC80E`).
- `0x00DCBDA0..0x00DCBDD4`: `[Engine]` ASCII key strings.
- `0x00DCBDD5`: `Cave_STEM_UpdateGraphTable` - constructs province graph, scans ground combats for `+0x24000` (`is_threatened`), runs supply/capital BFS, runs Tarjan bridge/articulation pass + Pass-2 `SalientNeckWidthThreshold` bridge check, and sets `+0x30000` evacuation flags.
- `0x00DCC52D`: `Cave_STEM_UpdateAndEvacuate_Internal` - processes per-country evacuation dispatch.
- `0x00DCC730`: `Cave_ShowAllMovingArrows` / `0x00DCC78E`: `Cave_DeselectArrows`.
- `0x00DCC7C4`: `Cave_PostLoadInit` / `0x00DCC80E`: `Cave_LoadEngineSettings`.
- `0x00DCC885`: `Cave_STEM_HourlyPerCountry` / `0x00DCC8B6`: `Cave_STEM_HourlyAllCountries`.
- `0x00DCC95B`: `Cave_FrontAI_ManageReservesAndSalients`.

### 3.3 Hooks & Code Removed During Cleanup

- `0x004E7616` & `0x004E7905`: Removed inline cave hooks that overwrote unit organization / state during combat checks.
- `0x00DCBADC`: Cleared legacy org/hook storage slot.
- `0x006A5790` (and dead spearhead stubs): Removed orphaned spearhead override checks after scrapping `SpearheadWinningOdds` and `AbortSpearheadOnNeckCollapse`.

---

## 4. Issues Addressed During Realignment & Cleanup

1. **Memory Aliasing Between `+0x24000` and `+0x26000` (Phase 1)**: Rebuilt `Cave_STEM_UpdateGraphTable` (`0x00DCBDD5`) with proper stride sizing so province threat flags (`+0x24000`) and attack flags (`+0x26000`) do not alias in scratch memory.
2. **Retail Rear-Reserve Replacement & Org Mutation Bug (Phase 2)**: Restored retail `CFrontAI::ManageRearReserves` (`0x00681CD0`) behind wrapper `0x00DCC95B` at `0x00682A58`, and removed `0x004E7616` / `0x004E7905` org-corruption hooks.
3. **Flawed Spearhead Architecture Removal (Phase 3)**: Completely removed `SpearheadWinningOdds` and `AbortSpearheadOnNeckCollapse` because exempting attacking units would strand breakout stacks when a salient evacuates and allow opponents to bait AI attacks into encirclements.
4. **False-Positive Cut Flag Propagation in `.tarjan_check_cut` (Phase 3A)**: Fixed `.tarjan_check_cut` so articulation/bridge checks only mark a pocket cut when an attacked shoulder (`+0x24000 == 1`) threatens the neck, rather than triggering unconditionally on any neighbor, and removed the redundant second loop.
5. **Hardcoded Threat/Org Formulas & False Evacuation Under Light Attacks (Phase 4)**: Wired `NeckThreatRatio` (`0x00DCBAC0`) and `NeckCollapsingOrgThreshold` (`0x00DCBAC4`) dynamically, fixed unit strength/organization structure offsets and scalar FPU comparisons, and added an active combat guard so non-attacked provinces never trigger `+0x24000 = 1`.
6. **Depot Cores, Allied Territory Blocking, and Multi-Connection Salients (Phase 5)**:
   - Wired `UseSupplyDepotsAsCores` (`0x00DCBABC`) to seed accessible provinces (`CCountry::CanEnterOrTraceSupply` @ `0x0044A690`) having `[pProv + 0x270] > 0.0f` or a supplied controller capital.
   - Replaced strict self-control-only BFS neighbor gating with `CCountry::CanEnterOrTraceSupply` (`0x0044A690`; self/ally/puppet/master/access) and hostile-war filtering (`0x0044B280`) so pockets separated by allied territory keep valid supply/escape paths.
   - Added Pass-2 bridge fallback controlled by `SalientNeckWidthThreshold` (`0x00DCBAB4`).
7. **Unrelated Patch 1 & Patch 4 Crash / `.data` Collision Fix (Session Side-Fix)**:
   - Fixed Patch 1 (`AllowExpForcesToPlayers` @ `0x004CCCB6`): replaced a crashing cave detour with `call [edx+0x1c]; jmp 0x007E2FB3`.
   - Relocated `AllowExpForcesToPlayers` and `AllowPuppetTrade` variables out of retail `.data` (`0x0088077C` / `0x00880780`) to clean `.mod` memory (`0x00DC9FF0` / `0x00DC9FF4`) across Patches 4 and 6.

---

## 5. Remaining Known Issues & Proposed Solution Steps

### Issue 1: Post-Capture Evacuation Cancellation (Crimea `1827 Dzankoj` / Grodno `209` Pattern) - **HIGH PRIORITY**
- **Observed Symptom**:
  - Live Crimea test: While Germany heavily attacked `1827 Dzankoj` (northern approach into Crimea), Soviet forces inside Crimea properly disengaged and withdrew across the Kerch Strait (`254 Kerch`). Once `1827 Dzankoj` fell to Germany and German forces paused before attacking `254 Kerch`, Soviet evacuation cancelled and retreating divisions reversed back into Crimea until `254 Kerch` itself was attacked.
  - Earlier live Grodno test (Phase 3A): Identical pattern when `209 Grodno` was threatened vs. after it fell to Germany.
- **Root Cause**:
  - In `Cave_STEM_UpdateGraphTable` (`.tarjan_check_cut`), `is_cut[edi] = 1` is retained only while `edi` or a pocket child `esi` borders a *friendly-controlled* province with `+0x24000 == 1`.
  - Once the outer shoulder (`1827 Dzankoj` / `209 Grodno`) falls, its controller becomes hostile, so it is no longer evaluated as a friendly threatened node. Until the enemy attacks the next friendly interior node (`254 Kerch` / `102 Wolkowysk`), all friendly nodes in the pocket have `+0x24000 == 0`, clearing `is_cut` and `+0x30000` on the next hourly tick.
- **Proposed Solution Steps** (deferred past current cleanup scope):
  1. **Hostile Chokepoint Breach Detection**: Extend `.tarjan_check_cut` / bridge checks so that if an articulation/bridge node (or narrow bottleneck within `SalientNeckWidthThreshold`) directly borders hostile-controlled territory on an approach vector that cuts or narrows an escape corridor (weighted by adjacent hostile division strength), it remains flagged as threatened/breached rather than requiring active combat on a friendly shoulder.
  2. **Evacuation Hysteresis / Sticky Latch**: Add a per-country or per-province evacuation hysteresis timer/latch on `+0x30000` (or require a safe-threshold margin plus absence of adjacent overwhelming hostile strength for N consecutive ticks) so operational pauses by an advancing attacker do not immediately abort an active withdrawal.
  3. **Targeted Validation**: Re-test both single-corridor peninsulas (`1827 Dzankoj` -> `155 Simferopol` / `254 Kerch`) and multi-province land salients (`209 Grodno` -> `102 Wolkowysk`).

### Issue 2: Post-Evacuation Return Loop & Exterior Reinforcement Inflow
- **Observed Symptom**: Units that finish withdrawing out of a threatened salient, or reserve/front divisions outside the pocket, can be ordered straight back toward the still-dangerous front by `CFrontAI::MoveUnitsToFront` once they sit outside the active `+0x30000` zone (or immediately if `+0x30000` clears).
- **Proposed Solution Steps**:
  1. Prevent `CFrontAI::MoveUnitsToFront` from assigning exterior reinforcements into provinces currently marked `+0x30000 == 1` or reachable only through a collapsing/breached articulation neck.
  2. Pair with Issue 1's hysteresis so evacuated divisions stabilize on fallback front sectors instead of marching back into an active pocket.

### Issue 3: Unwired Settings (`SalientEvacuationQuota`, `BottleneckDefenseBoost`)
- **Current State**: Both keys are loaded from `db/mod_settings.ini` into `0x00DCBACC` and `0x00DCBAD0` at startup, but neither value is consumed by `Cave_STEM_UpdateGraphTable` or `Cave_FrontAI_ManageReservesAndSalients`.
- **Proposed Solution Steps**:
  1. Implement `SalientEvacuationQuota` (fractional threshold controlling whether a delaying screen remains vs. `0.0` full evacuation) after Issue 1 stabilizes.
  2. Implement `BottleneckDefenseBoost` to raise defensive reinforcement weight on un-collapsed neck/shoulder provinces before collapse, while blocking reinforcement once evacuation triggers.

### Issue 4: Retail Caller Gate `0x00682A43` & Combat Defeat Retreat Direction
- **Observed Behavior**:
  - In retail `Darkest Hour.exe`, `0x00682A43` (`test ecx, ecx; jz ...`) skips calling `0x00682A58` (`CFrontAI::ManageRearReserves` / STEM wrapper) if the country's reserve vector is empty, though hourly STEM graph updates still execute via `0x005AEDBE`.
  - Retail combat defeat retreat direction does not consult STEM escape-BFS distances toward supply depots/capital cores, so defeated units can retreat deeper into a closing pocket rather than out through the neck.
- **Proposed Solution Steps**:
  1. Audit defeat-retreat target selection to prefer lower STEM BFS-distance provinces toward cores/depots when an active pocket/threat flag exists.
  2. Evaluate whether any reserve-independent front reallocation in `0x00DCC95B` needs an earlier hook independent of the `0x00682A43` reserve check.

### Issue 5: Future Breakthrough / Spearhead Architecture (On Hold)
- **Current State**: `SpearheadWinningOdds` and `AbortSpearheadOnNeckCollapse` were intentionally removed in Phase 3.
- **Proposed Direction**: Any future offensive breakout protection should model overall corridor width, flank-holding reserve ratio, and supply-line robustness rather than blankly exempting attacking units from evacuation.
