---
name: dh-localization
description: >-
  Specialized workflow and automated tools for managing Darkest Hour localization CSV files (such as config/modtext.csv) and extracting string literals from DHFScript event files. Use whenever inspecting, extracting, migrating, or fixing event names, descriptions, and action texts into localization CSV keys with minimal token overhead and fast execution.
---

# Darkest Hour Localization Skill

This skill provides streamlined tools and protocols for extracting string literals from Darkest Hour event files and synchronizing them into `config/modtext.csv` with zero token waste.

## Fast Workflow

### 1. Scan Event Files for String Literals
Run the extraction script to instantly check any event file for raw string literals, missing CSV keys, or improper quotation:

```bash
python .agents/skills/dh-localization/scripts/extract_strings.py db/events/<EventFile>.txt
```

* For machine-readable output in a single step, add `--json`.

### 2. Preview or Automatically Apply Localization
To automatically migrate string literals to `config/modtext.csv` and replace the strings in the event file with the corresponding `EVT_...` keys:

* **Preview changes (Dry Run)**:
  ```bash
  python .agents/skills/dh-localization/scripts/insert_localization.py db/events/<EventFile>.txt
  ```

* **Apply changes**:
  ```bash
  python .agents/skills/dh-localization/scripts/insert_localization.py db/events/<EventFile>.txt --apply
  ```

### 3. Verify
Run `extract_strings.py` again to confirm that 0 unlocalized strings or missing keys remain.

---

## Key Technical Rules

1. **Encoding**: All localization CSV files MUST be saved in `Latin-1` (`cp1252`).
2. **Line Endings**: MUST preserve Windows `\r\n` (CRLF).
3. **12-Column Schema**:
   `KEY;English;French;Italian;Spanish;German;Polish;Portuguese;Russian;;;X`
   * Copy the English string to all 8 language columns (cols 1..8).
   * Columns 9 and 10 remain empty.
   * Column 11 is `X`.
4. **File Termination**: Localization files must end with `#EOF;;;;;;;;;;;X\r\n`.
5. **Grouping**: Never append at the end of CSV files. Always insert new keys within their matching section header (e.g. `#NewOrderAllied.txt;;;;;;;;;;;X`) and maintain numerical ID sorting.
6. **Max length**: Max length of the event/decision description is 1600 characters. Ideally, keep descriptions closer to 1200 characters, and event name under 40 characters.

## References
* [Localization Format Specifications](./references/format_specs.md)
