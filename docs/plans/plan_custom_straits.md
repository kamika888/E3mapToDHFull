# Patch 6: Configurable & Dynamic Straits System

**Status**: Implemented & Verified  
**Engine**: Darkest Hour 1.05.2 (TENE)  
**Target File**: `Darkest Hour.exe`  
**Patch Category**: Map Mechanics, Scripting Engine & UI Polish  

---

## 1. Overview & Problem Statement

In vanilla Darkest Hour / Europa Engine, naval strait passage logic suffered from severe architectural constraints:
1. **Hardcoded Machine Code Logic**: Vanilla registered only 5 hardcoded straits compiled directly as conditional compare branches in `FUN_004ed1c0` (`0x004ED1C0`): Gibraltar (2430), Suez (2453), Panama (2575), Danish Belts (290), and Bosphorus (397). No other waterway in the world could function as a strait.
2. **Immutability at Runtime**: Strait passage rules could not be altered by events, decisions, or scenario scripting.
3. **Hardcoded Allied-Only Exception**: Only sea province `397` (Bosphorus) supported restricted passage rules (Allied-only), explicitly hardcoded into the movement check function `0x004ED1C0` and UI tooltip formatter `0x005EC5CE`, loading hardcoded string `STRAIT_BOS`. Other straits could not use this rule.
4. **Single-Controller UI Bias**: When multiple land provinces controlled a strait (e.g., Gibraltar and Ceuta), the tooltip only referenced the first province and displayed the flag of whatever country controlled slot 1, even if another land controller was actively blocking the strait.
5. **No Scripted Event Command**: No native command existed to open, close, or toggle strait passage dynamically.

Patch 6 completely redesigns the strait subsystem to support dynamic external configuration (`straits.csv`), multi-controller evaluation, runtime scripting via event commands, natural language UI tooltips, and save-game persistence.

---

## 2. Configuration & Database Specification (`db/straits.csv`)

### 2.1 Unified Configuration Toggle (`db/mod_settings.ini`)
- Section `[Map]`: `EnableCustomStraits = 1` (default `0`).
- When set to `0`: Engine retains vanilla static tables and logic.
- When set to `1`: Dynamic CSV loader, multi-controller transit checks, and runtime scripting hooks are active.

### 2.2 Data File Resolution Hierarchy
1. `map\<current_map>\straits.csv` (e.g. `map\Map_3\straits.csv` for mod-specific map layouts).
2. `db\straits.csv` (mod-wide fallback).
3. Hardcoded baseline table in memory (fallback if no CSV is found).

### 2.3 Database File Format (`straits.csv`)
- Header: `# SeaProv;LandProv1;LandProv2;LandProv3;LandProv4;Type;Name`
- Up to 4 controlling land provinces per strait (unused slots set to `0`).
- Maximum capacity: 64 straits (expanded from 5).
- Types in CSV (aligned 1-to-1 with event command and flag values):
  - `1`: **Always Open** (unconditional free passage for all nations, peace or wartime).
  - `2`: **Closed by Controller** (transit blocked to all non-controllers; controller fleets retain passage).
  - `3`: **Normal Strait** (passage permitted unless at war with any land controller).
  - `4`: **Allied-Only Strait** (passage permitted only to land controllers and wartime allies).
  - `5`: **Montreux Convention Strait** (Black Sea powers peacetime passage; non-Black Sea powers allied at war only).

---

## 3. Runtime Scripting & Dynamic State Machine

Modders can dynamically inspect and modify strait passage rules at runtime using two interchangeable mechanisms:

### 3.1 Native DHFScript Event Command
```dhfscript
command = { type = strait which = <sea_province_id> value = <1/2/3/4/5> }
```
- `which`: Sea province ID of the strait (e.g., `2430` for Gibraltar, `2453` for Suez, `397` for Bosphorus).
- `value`:
  - `1`: **Always Open** (unconditional free passage for all nations, peace or wartime; appends `STRAIT_OPEN`).
  - `2`: **Closed by Controller** (transit blocked to all non-controllers; controller fleets retain passage; appends `STRAIT_CLOSED`).
  - `3`: **Normal Strait** (passage permitted as long as not at war with any controlling land province).
  - `4`: **Allied-Only Strait** (passage permitted only to land controllers and wartime allies; appends `STRAIT_ALLIED_ONLY`).
  - `5`: **Montreux Convention Strait** (Black Sea powers peacetime passage; non-Black Sea powers allied at war only; appends `STRAIT_MONTREUX`).

### 3.2 Global Flag Bridge & Save-Game Persistence
- The command automatically updates the engine's internal global flag `strait_<sea_province_id> = <value>`.
- Modders can also manipulate or query this flag directly:
  ```dhfscript
  # Set or change status:
  command = { type = setflag which = strait_2430 value = 2 }

  # Trigger check:
  trigger = { flag = { which = strait_2430 value = 2 } }
  ```
- **Zero-Loss Save/Load Persistence**: Because the engine natively serializes all global flags into scenario and save files within the `flags = { ... }` block, runtime strait alterations persist across save and load cycles without requiring custom binary save serialization hooks.

---

## 4. Binary Hook Architecture & Memory Layout

Patch 6 injects cooperative hooks across `.text` call sites into dedicated subroutines in the `.mod` section (`0x007E3000`+ / `0x00DC9000`):

```
+-----------------------------------------------------------------------------------+
| .text Call Sites                                                                  |
|                                                                                   |
| 0x007E2DA7: fn_init_straits               --> Reads EnableCustomStraits from INI  |
| 0x0058444F: CSV Loader Hook               --> Calls fn_load_straits_csv           |
| 0x005846B0: IsStraitBlocked Hook          --> Calls fn_custom_strait_check        |
| 0x005342F5: Script Token Lexer Hook (7a)  --> Resolves "strait" token (0x69A)    |
| 0x0053437D: Script Token Direct Hook (7b) --> Resolves "strait" token (0x69A)    |
| 0x0070A5C0: Command Parser Hook (8)       --> Routes 0x69A -> 0x13E opcode        |
| 0x00713861: Command Executor Hook (9)     --> Executes fn_exec_strait_cmd         |
| 0x005EC3F5: UI Blocker Prov Hook (6a)     --> Identifies blocking controller prov |
| 0x005EC47E: UI Prov Names Hook (6b)       --> Formats multi-prov names ("A and B")|
| 0x005EC580: UI Country Deduplication (6c) --> Formats unique blocker nations       |
| 0x005EC5CE: UI Allied Text Hook (6d)      --> Displays STRAIT_ALLIED_ONLY string  |
+-----------------------------------------------------------------------------------+
```

### 4.1 Detailed Hook Specifications

1. **Startup & CSV Loader (`0x007E4400`)**:
   - Called during map initialization at `0x0058444F`.
   - Checks `EnableCustomStraits`. If disabled or file missing, loads default 5-strait table (`tbl_default_straits`).
   - If enabled, parses up to 64 lines from `straits.csv` using custom integer scanner `fn_parse_int`.
   - Stores parsed entries in global array `g_Straits` at `0x007E50C0` (64 entries * 12 bytes = 768 bytes).

2. **Dynamic Passage Evaluation (`0x007E4670`, Call Site `0x005846B0`)**:
   - Replaces vanilla hardcoded loop in `IsStraitBlocked`.
   - First checks if global flag `strait_<sea_prov>` exists via `CScriptParser::GetFlag(ecx=[0x00D77B70], name)`:
     - `1`: Returns `0` (Open).
     - `2`: Returns `1` (Blocked to non-controllers; controller fleets pass).
     - `3`: Evaluates Normal rule against all defined land controllers.
     - `4`: Evaluates Allied-Only rule against all defined land controllers.
     - `5`: Evaluates Montreux Convention rule (peacetime pass for Black Sea powers; wartime allies only for non-Black Sea powers).
     - `0` / missing: Evaluates default rule loaded from CSV.
   - Multi-Controller Precedence: If at least one land controller evaluates to a block, the block takes precedence.

3. **Event Command Token Resolution & Execution**:
   - **Hooks 7a & 7b (`fn_hook_lookup_token` @ `0x005342F5` & `fn_hook_lookup_direct` @ `0x0053437D`)**: Hooked into `CScriptParser::LookupToken` and `LookupTokenDirect`. Evaluates vanilla hash map lookup first, preserving all vanilla tokens completely intact (including `0x699` / `remove_claim_region`), and intercepts unrecognized tokens to resolve keyword `"strait"` as token ID `0x69A`.
   - **Hook 8 (`fn_command_mapper_hook` @ `0x0070A5C0`)**: Maps token `0x69A` to command action opcode `0x13E` in the event compiler switch table.
   - **Hook 9 (`fn_command_executor_hook` @ `0x00713861`)**: Intercepts command dispatch at `0x00713861`. If `eax == 0x13E`, branches to `fn_exec_strait_cmd`:
     - Reads float value from `[esi+8]` and sea prov ID from `[esi+0x0C]`.
     - Formats flag string `"strait_%d"`.
     - Calls `CScriptParser::SetFlag(ecx=[0x00D77B70], name, val)`.

4. **UI Tooltip & Natural Language Grammar Engine**:
   - **Hook 6a (`0x005EC3F5`)**: Queries the current viewer country. If the strait is blocked, iterates all controlling provinces and returns the province ID of the first controller currently at war, ensuring the sidebar flag icon reflects the hostile blocking nation rather than an uninvolved co-controller.
   - **Hook 6b (`0x005EC47E`)**: Iterates all controlling land provinces, retrieves their localized names, and concatenates them with grammatical conjunctions:
     - 1 province: `"Gibraltar"`
     - 2 provinces: `"Gibraltar and Ceuta"`
     - 3+ provinces: `"Gibraltar, Ceuta and Tangier"`
     - Populates localized token `%s` in `STRAIT_CONTROLLER` (*"The controller of %s decides who goes through this strait."*).
   - **Hook 6c (`0x005EC580` / `0x005EC59A`)**: Deduplicates land controllers into unique nations. If all land controllers are held by the same country (e.g., UK holding both sides), the nation is listed only once. If held by multiple countries (e.g., Poland and UK), they are formatted as `"Poland and United Kingdom"` into `STRAIT_BLOCKED` (*"This is possible as long as you are not at war with %s."*).
   - **Hook 6d (`0x005EC5CE` / `0x005F1AD9`)**: Dynamically evaluates runtime strait type and appends dedicated localized explanations from `config/modtext.csv`:
     - **Type 1 (Force Open)**: Appends `STRAIT_OPEN` (*"(The strait controller has declared this strait open to all military vessels and commercial shipping.)"*).
     - **Type 2 (Closed by Controller)**: Appends `STRAIT_CLOSED` (*"(The strait controller has exercised his right to block this strait to all military vessels and cargo.)"*). The controller's own fleets retain passage; all non-controllers are blocked.
     - **Type 3 (Normal Strait)**: Standard passage rules (open if at peace with controllers; no extra suffix).
     - **Type 4 (Allied-Only Strait)**: Appends `STRAIT_ALLIED_ONLY` (*"(Please note that this is an Allied-only strait, and the controller will only allow through allies at war.)"*).
     - **Type 5 (Montreux Convention Strait)**: Appends `STRAIT_MONTREUX` (*"(Please note that this strait is governed by the Montreux Convention: Black Sea powers have passage rights in peacetime, while other nations may only transit if allied to the controller during wartime.)"*).

---

## 5. Patcher Integration

Patch 6 is packaged inside `tools/patch_darkest_hour.bat` under `$PATCH6_CHUNKS`:
- Primary verification signature: `0xE9, 0x55, 0xC1, 0x8D, 0x00` at `0x000ED1C0`.
- Automated binary patching deploys all 7 hooks, `.mod` code caves, and data structures.

