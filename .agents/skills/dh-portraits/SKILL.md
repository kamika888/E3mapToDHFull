---
name: dh-portraits
description: >-
    Automated workflow, image processing specs, and database registration conventions for adding or updating Darkest Hour minister and leader portraits.
---

# Darkest Hour Minister & Leader Portraits

This skill provides technical specifications, composition guidelines, and automated tooling for sourcing, processing, formatting, and registering minister and military leader portraits in Darkest Hour.

## Technical Specifications

- **Dimensions:** **36x50** pixels.
- **Target Location:** `gfx/interface/pics/`
- **Format:** 8-bit indexed palette BMP (`Mode P`, 256-color grayscale palette matching `MS355.bmp`).
- **Outline:** **1-pixel white border** around all 4 outer edges (`x=0`, `x=35`, `y=0`, `y=49` are RGB `255, 255, 255` / palette index `255`).

## Composition & Framing Guidelines

- **Face Zoom / Framing:** Portrait photos MUST be cropped in such a way that the individual's face takes up the majority of the photo, anywhere from **60% to 90%** of the frame. Avoid wide full-body or half-body shots where the face is tiny or obscured.
- **Historical Authenticity:** Prefer authentic black-and-white studio portraits or military photographs from the relevant era (1930s–1950s).
- **Source Verification:** Sourced from Wikimedia Commons, Generals.dk, historical archives, or Baike/Wikipedia.
- **Wikimedia Rate-Limiting:** Direct requests to `upload.wikimedia.org` frequently trigger `HTTP 429: Too Many Requests`. Always use standard browser/contact User-Agent headers, query the MediaWiki API for thumbnail URLs, and apply a 1.0s–3.0s delay between sequential downloads.

## Fast Workflow & Tooling

To process an image into a compliant 36x50 BMP portrait:

```bash
python .agents/skills/dh-portraits/scripts/process_portrait.py "<IMAGE_URL_OR_FILE_TITLE>" "<PIC_ID>"
```

### Options:
- **Wikimedia Title:** `python .agents/skills/dh-portraits/scripts/process_portrait.py "File:Example.jpg" "MS357"`
- **Direct Image URL:** `python .agents/skills/dh-portraits/scripts/process_portrait.py "https://generals.dk/content/portraits/Example.jpg" "MS357"`
- **Custom Face Crop:** Pass normalized crop bounds `[LEFT TOP RIGHT BOTTOM]` (0.0–1.0) to zoom into the subject's face (60-90% face area):
  ```bash
  python .agents/skills/dh-portraits/scripts/process_portrait.py "https://example.com/photo.jpg" "MS357" --crop 0.2 0.1 0.7 0.6
  ```

## Database Registration

### 1. Ministers (`db/ministers/*.csv`)
- **Encoding:** All modified CSV files MUST be saved in **`cp1252` (`Latin-1`)** encoding.
- **Format:** Semicolon-delimited line ending with `X`:
  `ID;Role;Name;StartYear;EndYear;RetirementYear;Ideology;Personality;Loyalty;Picturename;X`
- **Picturename:** The filename without `.bmp` extension (e.g. `MS357`). Custom mod portraits use the `MS<number>` prefix (e.g., `MS357`, `MS358`, etc.).
- **ID Assignment:** Use the next sequential unused minister ID in the target country's CSV file (e.g., check `ministers_vic.csv` or `ministers_fra.csv`).

### 2. Leaders (`db/leaders/*.txt`)
- Reference the portrait ID without `.bmp` extension in the leader definition's `picture = ...` block.

