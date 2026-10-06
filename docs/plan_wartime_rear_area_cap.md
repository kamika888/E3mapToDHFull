# Research Notes: Rear Area Garrisons & Homeland Emergency Mechanic (Shelved)

## Status: Shelved / Archived

The investigation into a proposed `wartime_rear_area_cap` binary patch has been shelved. Empirical testing demonstrated that the initial premise - that the game unconditionally forces all non-frontline areas to a maximum of 1 division whenever a war front exists - was incorrect. The original 3-patch baseline in `patch_darkest_hour.bat` has been fully restored and verified.

---

## 1. Empirically Confirmed Engine Mechanics

### A. The "Capital Homeland Emergency" Mechanic (`FUN_0068ba50` @ `0x0068C5AF` - `0x0068C5CB`)
During reverse-engineering of `CGarrisonAI::UpdateGarrisons`, an emergency homeland defense check was identified:
* At the start of garrison distribution, the AI checks whether the nation's capital / home area contains at least one division (`capital_area->current_divisions`).
* If `current_divisions == 0` in the capital area, an emergency flag is activated (`local_51 = 1`).
* When active, overseas garrison requirements are suppressed to zero (`nAreaNeed = 0`), flagging all units in peripheral / overseas areas as surplus to be shipped home or reassigned.
* In testing with `TestSave5`, England initially had 0 divisions stationed in the British Isles, which triggered this emergency mode and caused the AI to immediately evacuate all 12 divisions from Dunkirk.
* As soon as Britain had at least 1 division in its home area, this emergency mode deactivated, and Dunkirk garrisons were calculated normally.

### B. Overseas Multiplier Behavior in Vanilla
* When the capital is garrisoned, an isolated overseas area (such as Dunkirk #43 in `TestSave5`, separated from frontline areas) directly respects the AI configuration parameter:
  ```text
  garrison = {
      overseas_multiplier = 4.0
  }
  ```
* Under vanilla engine code (without any binary modifications), adjusting `overseas_multiplier` directly influenced the number of divisions England retained in Dunkirk rather than reducing them to 0 or capping them at 1.

---

## 2. Retracted Assumptions

* **Hardcoded Rear Area Cap at `0x0068C81D`**:
  Earlier disassembly noted an instruction sequence (`MOV ESI, 1` / `MOV [EBP - 0x2c], ESI`) occurring when `front_areas_count > 0` and `is_front_area == 0`. It was hypothesized that this was a universal cap forcing all rear areas to 1 division during war.
  Empirical in-game testing disproved this hypothesis; rear overseas areas retain divisions according to their configured multipliers under standard war conditions. The exact execution criteria and scope of `0x0068C81D` were misunderstood and do not operate as an unconditional global rear-area cap.
* Consequently, the proposed `wartime_rear_area_cap` lexer/parser/engine patch (formerly Fix 4) was discarded.

---

## 3. Current Hypotheses for Rear Area Garrison Depletion

The original problem observed in extended campaigns - where rear areas (e.g. Sardinia) gradually lose their garrison over time - remains under observation, with several alternative explanations:

1. **Invasion AI Siphoning (`CAIInvasionMinister` / `CAITransportMinister`)**:
   * The AI's invasion subsystem periodically draws available divisions from coastal and peripheral areas to assemble invasion forces or staging task forces.
   * If an invasion succeeds or is called off, these divisions may not be repatriated to their original posts.
2. **War Zone Priority Allocation**:
   * Because active war zones (`war_zone_odds`) take top priority for military distribution, divisions displaced from their original posts (or new production) are directed toward frontlines rather than being returned to rear garrisons.
3. **Specific Area Definition / Sea Zone Interaction**:
   * Whether an area is classified as an overseas area, frontline-adjacent, or home-adjacent may depend on dynamic naval connectivity and controlled ports.

---

## 4. Current State

* **Executable & Scripts**:
  * `patch_darkest_hour.bat` is restored to the clean 3-patch baseline:
    - Fix 1: Front Leader Recognition (`0x006939F0` & `0x00693BC0`)
    - Fix 2: AI Homeland Expedition Dispatch (`0x00447360`)
    - Fix 3: Diplomatic `dont_want_exp_forces` Respect (`0x00489AE0`)
  * `Darkest Hour.exe` and `Darkest Hour_original.exe` match pristine checksum `7A1AE8BB802377B6C9EC808F420ACE58475D1816464390422CF97AD450A51EB4`.
  * `Darkest Hour_modified.exe` matches clean patched checksum `1DB5DC08A644080CDACF56B103F91B3C696DBF5FCB83723E671B9A51814CD98E`.
* **Test Saves**:
  * `TestSave5.eug` has been restored to its original state.