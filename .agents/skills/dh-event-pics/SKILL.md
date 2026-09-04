---
name: dh-event-pics
description: >-
    Automated workflow for fetching, resizing, cropping, and templating event pictures for Darkest Hour. Use when adding or replacing event or decision pictures.
---

# Darkest Hour Event Pictures

This skill provides a streamlined tool and best practices for sourcing and processing event images to meet the mod's technical and historical requirements.

## Fast Workflow

1. **Identify:** Read the event/decision including the localization and determine what historical subject or event the picture should depict, and for which country this event will fire.
2. **Find & Verify Source:** 
   - Search across diverse sources (Wikimedia Commons, historical archives, baike/wikipedia, google images, etc).
   - **Acceptable Media:**
     - Primary: Authentic historical photographs from the relevant era/conflict.
     - Secondary (acceptable when photos are absent or low quality): Period artwork, contemporary propaganda posters/paintings, historical maps, and monument sculptures.
   - **Avoid:** Modern photographs (e.g. modern buildings, contemporary tourists, modern military units), out-of-period imagery, corrupted solid color images, and low-relevance generic search matches.
3. **Process:** Run the processing script to fetch the image from a URL, local file, or Wikimedia file title, resize/crop it, apply the appropriate template overlay, and save it to `gfx/events_pics/`:
   * For regular event pictures:
   ```bash
   python .agents/skills/dh-event-pics/scripts/process_event_pic.py "<IMAGE_URL_OR_FILE_TITLE>" "<FILENAME_NO_EXT>"
   ```
   * For decision pictures:
   ```bash
   python .agents/skills/dh-event-pics/scripts/process_event_pic.py "<IMAGE_URL_OR_FILE_TITLE>" "decision_<FILENAME_NO_EXT>" --decision
   ```
   * For vertical portraits requiring top alignment, pass `--crop-y` (0.0=top, 0.5=center/default, 1.0=bottom):
   ```bash
   python .agents/skills/dh-event-pics/scripts/process_event_pic.py "<URL_OR_TITLE>" "<NAME>" --crop-y 0.05
   ```
   * For narrow portraits where cropping would cut off the chin or forehead, use `--pad`:
   ```bash
   python .agents/skills/dh-event-pics/scripts/process_event_pic.py "<URL_OR_TITLE>" "<NAME>" --pad
   ```
4. **Reference:** Update the event/decision with `picture = "<FILENAME_NO_EXT>"` or `decision_picture = "decision_<FILENAME_NO_EXT>"`.
5. **Visual Verification:** 
   - Visually inspect generated BMPs using `view_file` or generate a local HTML inspection gallery (`gallery.html`) to ensure correct composition, no head-clipping, and authentic period feel.
   - Verify BMP file exists in `gfx/events_pics/`, is uncompressed 24-bit BMP, and has exact dimensions (**400x232** for events, **224x48** for decisions).

## Best Practices & Composition Guidelines

- **Portraits & Aspect Ratio (400x232 = ~1.72:1):**
  - Avoid tight headshots or extreme close-ups, as a wide landscape slice through a narrow face will cut off either the forehead or the chin.
  - Prefer medium/half-length shots, seated poses at desks, podium speeches, or environmental/press photographs with generous margin around the head.
  - If only a narrow vertical portrait exists, use `--pad` to preserve the complete head and shoulders with a subtle neutral blurred backdrop instead of over-zooming.
- **Historical Event Priority:** For death, resignation, or crisis events, prioritize photographs of actual historical moments (lying-in-state, funeral corteges, courtroom trials, treaty signings, crisis protests) over static individual portraits where they exist.
- **Strict Subject Verification:** Verify names, dates, and historical roles to avoid confusing historical figures with modern namesakes or similarly named landmarks/buildings.

## Technical Requirements

- Event pictures: **400x232** BMP; template: `gfx/events_pics/template.png`.
- Decision pictures: **224x48** BMP; template: `gfx/events_pics/decision_template.png`.
- The processing script handles cropping, resizing, and template application. Do not duplicate this logic manually.
- **Distinguishing Decisions from Regular Events:**
  - **Decisions** (events with a nested `decision = { ... }` block) require **both** `picture = "..."` and `decision_picture = "..."`.
  - **Regular events** (events without a `decision = { ... }` block) **only** use `picture = "..."` and must **not** include a `decision_picture`.
- **Distinct Image Sources:** `picture` and `decision_picture` generally should **not** be sourced from the exact same image. Wherever possible, find and use distinct source images for the event picture and the decision picture to provide varied visuals.
- **Decision Banner Framing (224x48):** Due to the extreme wide aspect ratio (~4.67:1), prefer wide landscape scenes, maps, lines of soldiers, banners, reliefs, or insignia. Avoid tall vertical portraits unless a horizontal crop slice is visually coherent.

## Wikimedia Commons Rate-Limiting Best Practice

Direct downloads from `upload.wikimedia.org` frequently trigger `HTTP 429: Too many requests`.
- Pass Wikimedia titles directly (e.g. `File:Example.jpg`) to `process_event_pic.py`, which automatically queries the MediaWiki API for the pre-cached 800px edge thumbnail.
- Always include a custom `User-Agent: DHModdingTool/1.0 (contact@email.com)` header.
- Add a 1.0s–1.5s delay between sequential automated downloads.