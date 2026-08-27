---
name: dh-event-pics
description: >-
    Automated workflow for fetching, resizing, cropping, and templating event pictures for Darkest Hour. Use when adding or replacing event or decision pictures.
---

# Darkest Hour Event Pictures

This skill provides a streamlined tool for processing event images to meet the mod's technical requirements.

## Fast Workflow

1. **Identify:** Read the event/decision including the localization and determine what historical subject or event the picture should depict, and for which country this event will fire.
2. **Find:** Use a range of sources to locate an appropriate image. Do not always pick the first thing that shows up on Wikimedia Commons or Google images. Try to find images with a similar aspect ratio as per target requirements in order to minimize cropping. Inspect the actual image when possible rather than just reading the description. 
3. **Process:** Run the processing script to fetch the image from a URL, resize/crop it, apply the appropriate template overlay, and save it to `gfx/events_pics/`:
  * For regular event pictures:
  ```bash
  python .agents/skills/dh-event-pics/scripts/process_event_pic.py "<IMAGE_URL>" "<FILENAME_NO_EXT>"
  ```
  * For decision pictures:
  ```bash
  python .agents/skills/dh-event-pics/scripts/process_event_pic.py "<IMAGE_URL>" "decision_<FILENAME_NO_EXT>" --decision
  ```
4. **Reference:** Update the event/decision with `picture = "<FILENAME_NO_EXT>"` or `decision_picture = "decision_<FILENAME_NO_EXT>"`.
5. **Verify:** Confirm the output exists in `gfx/events_pics/`, is BMP, and has the correct dimensions.

## Technical Requirements

- Event pictures: **400×232** BMP; template: `gfx/events_pics/template.png`.
- Decision pictures: **224×48** BMP; template: `gfx/events_pics/decision_template.png`.
- The processing script handles cropping, resizing, and template application. Do not duplicate this logic manually.
- For multiple pictures, process them consistently and verify the resulting files and references.
- **Distinguishing Decisions from Regular Events:** A decision is an event with a nested `decision = { ... }` block.
  - **Decisions** require **both** `picture = "..."` and `decision_picture = "..."`.
  - **Regular events** (events without a `decision = { ... }` block) **only** use `picture = "..."` and must **not** include a `decision_picture`.
- **Distinct Image Sources:** `picture` and `decision_picture` generally should **not** be sourced from the exact same image. Wherever possible, find and use distinct source images for the event picture and the decision picture to provide varied visuals.
- Multiple events **may** reuse the same picture where appropriate, but use this option sparingly. Always try to find distinct images for separate events, even if they are sharing the same name/description, but fire for different countries.