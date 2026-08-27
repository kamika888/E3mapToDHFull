# Darkest Hour Localization File Format & Specifications

## CSV Structure & Column Definitions

Darkest Hour loads localization files from the `config/` directory. All 18 standard CSV files plus custom mod CSVs (such as `modtext.csv`) are parsed by the engine.

### Row Schema

Each localization entry is a semicolon-delimited row containing **12 columns**:

| Column Index | Field | Description | Standard Mod Default |
|---|---|---|---|
| 0 | `Key` | Unique identifier (e.g. `EVT_2003295_NAME`) | Uppercase by convention |
| 1 | `English` | English text string | English string |
| 2 | `French` | French translation | Copied English string |
| 3 | `Italian` | Italian translation | Copied English string |
| 4 | `Spanish` | Spanish translation | Copied English string |
| 5 | `German` | German translation | Copied English string |
| 6 | `Polish` | Polish translation | Copied English string |
| 7 | `Portuguese` | Portuguese translation | Copied English string |
| 8 | `Russian` | Russian translation | Copied English string |
| 9 | `Extra` | Unused in standard DH | Empty |
| 10 | `Extra` | Unused in standard DH | Empty |
| 11 | `Terminator` | Line termination marker | Always `X` |

### Raw Row Example
```csv
EVT_2003295_NAME;Percentages Agreement;Percentages Agreement;Percentages Agreement;Percentages Agreement;Percentages Agreement;Percentages Agreement;Percentages Agreement;Percentages Agreement;;;X
```

### Critical CSV Requirements
1. **Line Endings**: Must use Windows CRLF (`\r\n`).
2. **Encoding**: Must be saved in `Latin-1` / `Windows-1252` (`cp1252`) encoding.
3. **File Terminator**: Every localization CSV must end with `#EOF;;;;;;;;;;;X\r\n`.
4. **Section Organization**: Entries in `config/modtext.csv` are organized under section headers (e.g. `#NewOrderAllied.txt;;;;;;;;;;;X`) and sorted numerically by event ID within that section.
5. **No End-of-File Appending**: Never append new keys at the end of the file; always place them within their corresponding file/ID group.

---

## DHFScript Key Naming Conventions

* **Event Title**: `EVT_<ID>_NAME`
* **Event Description**: `EVT_<ID>_DESC`
* **Action Names**: `EVT_<ID>_ACTA`, `EVT_<ID>_ACTB`, `EVT_<ID>_ACTC`, etc.
* **Decision Title**: `EVT_<ID>_NAME` (or `DEC_<ID>_NAME`)
* **Decision Description**: `EVT_<ID>_DESC` (or `DEC_<ID>_DESC`)

### Common Engine Keys (Do Not Treat as Missing)
* `AI_EVENT` (Used as a placeholder name for AI-only events)
* `ACTION_NAME_OK`, `ACTION_NAME_ACCEPT`, `ACTION_NAME_DECLINE`, `ACTION_NAME_DAMN`, `ACTION_NAME_HURRAH`, `ACTION_NAME_GREAT`, `ACTION_NAME_EXCELLENT`, `ACTION_NAME_REFUSE`, `ACTION_NAME_COUP_FAILS`, `ACTION_NAME_COUP_SUCCEEDS`
