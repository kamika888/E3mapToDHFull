# Darkest Hour Engine Architecture & Reverse Engineering Reference

**Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour.exe` (Size: `4,730,956` bytes, Image Base: `0x00400000`)  
**Scope**: Comprehensive reference covering engine runtime architecture, memory structures, global tables, key subsystems, debugging workflows, and binary instrumentation practices.

---

## 1. Engine Binary & Execution Model

### 1.1 Executable Universality & Checksum Architecture
- **Single Executable for All Configurations**: The physical binary `Darkest Hour.exe` is identical regardless of which mod or scenario is launched (e.g., *Darkest Hour Full*, *Darkest Hour Light*, *E3mapToDHFull*). Mod folders provide data, scripts, and interface overrides, while the core simulation engine remains constant.
- **Lightweight Debugging Target**: *Darkest Hour Light* (vanilla baseline checksum `TENE`) is optimal for debugging because its reduced database footprint loads in ~3–5 seconds under a debugger, compared to 30–60 seconds for large mods.
- **The Checksum Mechanism**:
  - The four-letter checksum displayed in the main menu (e.g., `TENE`) is calculated exclusively over script databases (`db/`, `map/`, events, scenario definitions).
  - **The checksum does NOT hash `Darkest Hour.exe`**.
  - Any binary patch, hook, or code modification to `Darkest Hour.exe` preserves the original checksum completely, avoiding multiplayer desync flags or launcher mismatch warnings caused by executable changes.

### 1.2 Binary Layout & Memory Mapping
- **Compiler**: Microsoft Visual C++ (MSVC), 32-bit x86 Little-Endian.
- **PE Headers**:
  - `ImageBase`: `0x00400000`
  - `.text` Section: Virtual Address `0x00401000` – `0x007E3000` (Raw Offset: `0x00001000`, Size: `4,071,424` bytes)
  - Formula: $\text{Virtual Address} = \text{File Offset} + \text{0x00400000}$ (valid throughout the entire `.text` section).
- **Function Alignment & Code Caves**:
  - MSVC aligns functions to 16-byte boundaries. Functions that do not fill their 16-byte block terminate with **1 to 15 bytes of `0x90` (NOP) or `0xCC` (INT3) padding**.
  - These alignment bytes reside within the mapped PE image and can be safely utilized as code caves for jumps, hooks, and local logic extensions without displacing surrounding code.

---

## 2. Core Global Data Tables & Pointers

| Global Identifier | Virtual Address | Description | Access Pattern |
|---|---|---|---|
| `DAT_00dc0fd4` | `0x00DC0FD4` | **IsHuman Controller Array** | `*(int*)(0x00DC0FD4 + tag * 4)`<br>`1` = Human player, `0` = AI |
| `DAT_0089cad8` | `0x0089CAD8` | **Country Pointer Table** | `*(Country**)(0x0089CAD8 + tag * 4)`<br>Returns base pointer to country object |
| `pDateStruct` | `0x00893530` | **Engine Time & Date Pointer** | `[0x00893530] + 0x14`<br>Base of 6-byte runtime date struct |
| `szClockBuffer` | `0x00D0B68C` | **UI Formatted Clock String** | ASCII string: `"H:00 Month D, YYYY"` |
| `TokenTable` | `0x0084FA64` | **Scenario Parser Token Table** | Maps token strings to token IDs (e.g. `0x52E` = `dont_want_exp_forces`) |

### Global Country Tags (Internal Engine Enum)
Country tags are **not** dynamically assigned per scenario; they are defined as a global, hardcoded internal enumeration compiled directly into the executable's tag registration function (`FUN_004ab800`). When the game initializes, `FUN_004ab800` builds the global hash/lookup table mapping 3-letter ASCII tags to 32-bit integers.

**These integer IDs are identical across ALL scenarios, save games, and mods:**
- `0`: `---` (None / No country / Rebel)
- `1`: `ENG` (United Kingdom)
- `2`: `FRA` (France)
- `3`: `GER` (Germany)
- `4`: `HOL` (Netherlands)
- `5`: `POR` (Portugal)
- `6`: `ITA` (Italy)
- `7`: `SOV` (Soviet Union)
- `8`: `SPA` (Nationalist Spain)
- `9`: `SWE` (Sweden)
- `10`: `TUR` (Turkey)
- `11`: `JAP` (Japan)
- `12`: `CHI` (Nationalist China)
- `13`: `POL` (Poland)
- `14`: `NOR` (Norway)
- `15`: `BEL` (Belgium)
- `16`: `DEN` (Denmark)
- `17`: `SCH` (Switzerland)
- `18`: `CUB` (Cuba)
- `19`: `GRE` (Greece)
- `20`: `BUL` (Bulgaria)

-.etc

## 3. Runtime Data Structure Layouts

### 3.1 `Country` Structure
Base pointer retrieved from `DAT_0089cad8[tag]`:

```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x0000         void*               Virtual Method Table (vtable)
+0x0006         int32 (dword)       Country Tag (e.g. 1=GER, 2=FRA, 3=ENG)
+0x000A         void*               Country name / identity metadata
+0x0120         CAI*                AI Controller Subsystem pointer
                +0xB8               CAI::m_diplomacy / Foreign Minister module
                [[+0x120]+0xB8]+24  Virtual method: IsAtWar / CanCooperate(target_tag)
+0x3350         CAlliance*          Alliance container pointer
                +0x22               Pointer to alliance member container
                [[+0x3350]+0x22]+4  Head node of ally country tags linked list
+0xE86E         FrontNode*          Head of active Fronts linked list (CFront*)
+0x11862        uint8[] (byte[])    dont_want_exp_forces boolean array
                                    *(byte*)(Country + 0x11862 + target_tag)
                                    1 = refuses expeditionary forces from target_tag
                                    0 = accepts expeditionary forces
```

#### Linked List Traversal Pattern (Alliance & Fronts)
Darkest Hour uses standard singly-linked list nodes across its simulation objects:
```c
struct ListNode {
    void* pItem;        // +0x00: Pointer to object (or integer tag)
    void* pUnk;         // +0x04: Context/back-pointer
    ListNode* pNext;    // +0x08: Pointer to next node (NULL at tail)
};
```

---

### 3.2 `CGarrisonAI` Structure
The garrison evaluator object passed as `this` (`ecx`) into `FUN_00695520` and `FUN_0068ba50`:

```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x00           void*               Vtable
+0x0A           Country*            Pointer to owning Country object (e.g. UK)
+0x10..+0x40    int32 / float       Garrison ratios, homeland defense requirements
```

- **Tag Query Helper (`FUN_006a9d50`)**:
  ```c
  int __fastcall CGarrisonAI::GetTag(CGarrisonAI* this) {
      return *(int*)(*(int*)(this + 0x0A) + 0x06);
  }
  ```

---

### 3.3 `CFront` (Front Object) Structure
Represents an active front or border segment:

```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x00           void*               Vtable
+0x52           int32               Front Requirement / Deficit Flag (>0 needs troops)
+0x56..+0x80    ProvinceList        Provinces along front and adjacent enemy provinces
```

- **Validation Routine (`FUN_004ca33c`)**: Verifies whether the front is active and valid for garrison operations.
- **Deficit Computation (`FUN_00695380`)**: Calculates net division deficit against enemy front concentration. Returns integer deficit (>0 indicates reinforcements required).

---

### 3.4 `CArmy` (Corps / Army Group) Structure
Represents a land unit counter on the map:

```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x00           void*               Vtable
+0x10           int32               Unit ID (e.g. 200010)
+0x14           char[]              Army Name (e.g. "BEF Corps")
+0x298          int32               Target Province ID (e.g. 41 = Le Havre; 0 = none)
+0x29C          List*               Movement Route / Waypoint List
```

- When an overseas mission is assigned by `FUN_00696ef0`, `[CArmy + 0x298]` is written with the port province ID, prompting the transport minister to schedule naval lift.

---

### 3.5 Engine Time & Date Structure
Located at `[0x00893530] + 0x14`:

```
Byte Offset     Type        Format / Meaning
--------------------------------------------------------------------------------------
+0x00           uint8       Hour of day (0x00 .. 0x17 = 0:00 to 23:00)
+0x01           uint8       Day of month (0-indexed: 0x00 = 1st, 0x03 = 4th, etc.)
+0x02           uint8       Month of year (0-indexed: 0x00 = Jan, 0x06 = July)
+0x03           uint8       Flags / Tick state
+0x04..0x05     uint16      Year (little-endian: 0x0790 = 1936)
```

---

## 4. Key Subsystems & Calling Conventions

### 4.1 Calling Conventions & Register Preservation Rules
- **Standard MSVC x86 ABI**:
  - **Scratch / Caller-Saved**: `EAX`, `ECX`, `EDX` (can be modified freely inside hooks).
  - **Non-Volatile / Callee-Saved**: `EBX`, `ESI`, `EDI`, `EBP`, `ESP` (MUST be preserved across calls and hooks).
  - `__thiscall`: `ECX` contains the `this` pointer; parameters are pushed right-to-left on the stack; callee cleans the stack (`ret N`).
  - `__fastcall`: `ECX` and `EDX` contain first two parameters; remaining on stack.

---

### 4.2 Key Function Directory

| Routine | Virtual Address | Calling Conv. | Purpose |
|---|---|---|---|
| `Front::GetLeadingCountry` | `0x004CCB2C` | `__thiscall` | Evaluates which nation controls a front; governs peacetime transfer of control |
| `FUN_00695520` | `0x00695520` | `__fastcall` | `CGarrisonAI::FindAlliedFrontNeedingTroops`; traverses allies and identifies troop deficit |
| `FUN_0068BA50` | `0x0068BA50` | `__thiscall` | `CGarrisonAI::UpdateGarrisons`; hourly/daily top-level garrison dispatch logic |
| `FUN_00696EF0` | `0x00696EF0` | `__thiscall` | `CAITransportMinister::DispatchArmy`; assigns target port, transport booking, and march orders |
| `FUN_006939F0` | `0x006939F0` | `__thiscall` | Real-time unit control transfer between allied nations when stationed on foreign soil |
| `FUN_006A9D50` | `0x006A9D50` | `__fastcall` | `CGarrisonAI::GetTag`; helper extracting donor country tag from `this + 0x0A` |
| `FUN_004CA33C` | `0x004CA33C` | `__thiscall` | Front validation predicate |
| `FUN_00695380` | `0x00695380` | `__thiscall` | Front strength deficit calculation |
| `FUN_00588A70` | `0x00588A70` | `__thiscall` | Scenario & save game parser for diplomatic relationship blocks |

---

## 5. Tool Use & Reverse Engineering Workflows

### 5.1 x32dbg Automation (via x64dbg MCP)

#### 1. Reliable Debugger Launch with Working Directory
Darkest Hour resolves scenario lists and database files relative to its current working directory. Always launch `InitDebug` passing the game directory explicitly as the 3rd argument:
```json
{
  "ServerName": "x64dbg",
  "ToolName": "x64dbg_command",
  "Arguments": {
    "action": {
      "action": "execute",
      "command": "InitDebug \"E:\\Program Files (x86)\\Steam\\steamapps\\common\\Darkest Hour A HOI Game\\Darkest Hour.exe\", \"\", \"E:\\Program Files (x86)\\Steam\\steamapps\\common\\Darkest Hour A HOI Game\""
    }
  }
}
```

#### 2. Avoiding Window Occlusion
- Default 1024x768 windowed mode spawns at desktop origin `(2, 0)`.
- If x32dbg opens maximized, it occludes the game canvas. Move x32dbg to the right monitor half:
  `window_management(action="set_bounds", handle="<x32dbg_HWND>", x=1047, y=0, width=870, height=632)`

#### 3. Inspecting the Hourly Simulation Cycle
- Set a conditional or logging breakpoint on date advancement (`[0x00893530] + 0x14`).
- Use `step_into` / `step_over` to inspect instruction branches.
- Use `x64dbg_registers(action="get_flags")` to inspect Zero Flag (`ZF`), Carry Flag (`CF`), etc., after `cmp` or `test` operations.

---

### 5.2 Ghidra MCP Integration
- **Decompilation**: Use `decompile_function(address="0x00695520")` to rapidly extract pseudocode and reconstruct control flow.
- **Disassembly**: Use `disassemble_function(address="0x00695520")` to inspect instructions with Ghidra's symbol mapping.
- **Cross-References (XRefs)**: Track callers and data references using `get_xrefs_to` / `get_xrefs_from` to find all access points to internal offsets (e.g. `+0x11862`, `+0x120`).

---

### 5.3 Windows UI Automation & The DirectDraw Deadlock Trap

> [!CAUTION]
> **The DirectDraw Message Pump Freeze**:
> When `Darkest Hour.exe` is paused by a breakpoint in x32dbg, its Win32 message pump and DirectDraw surface are frozen.
> - **NEVER call `window_management(action="activate")` on a debugger-paused window**. Calling `SetForegroundWindow` on a frozen thread forces Windows to wait for thread message queue synchronization, deadlocking the agent until the 180-second tool timeout expires.
> - To inspect the visual state while paused, always use:
>   `screenshot_control(action="capture", annotate=false, outputMode="inline", target="window", windowHandle="<HWND>")`

#### Static UI Coordinate Reference (1024x768 Windowed Mode)
Window bounds: `[2, 0, 1026, 797]`. Internal canvas: `1024x768`.

- **Main Menu Buttons** ($X = 515$, pitch = $40\text{px}$):
  - Tutorial: `(515, 441)`
  - Single Player: `(515, 481)`
  - Multiplayer: `(515, 521)`
  - Exit: `(515, 601)`
- **Saved Games List** ($X = 112$):
  - Row 1 (`autosave`): `Y = 538`
  - Row 2 (`oldautosave`): `Y = 558`
  - Row 3 (`TestSave`): `Y = 578`
  - Row 4 (`TestSave2`): `Y = 598`
  - Row 5 (`TestSave3`): `Y = 618`
- **Country Selection Banners**:
  - France: `(315, 140)`
  - Germany: `(387, 140)`
- **Action Buttons**:
  - START (bottom-right): `(937, 745)`
  - Dismiss Scenario Briefing: Send key `Enter` via `keyboard_control` (or click `386, 511`).

---

### 5.4 Binary Instrumentation & Splicing Pattern
When modifying compiled code where instructions cannot simply be expanded in-line:
1. **Identify Unused Code or Slots**: Find dead calls (e.g. unused return values) or check logic being replaced.
2. **Locate Compiler Alignment Padding**: Check the tail of the function for NOP (`0x90`) caves before the next function boundary.
3. **Short Jump Splicing**:
   - Execute register setup in the primary function body.
   - Use a 2-byte short jump (`EB <disp8>`) to reach the trailing NOP cave.
   - Perform extended comparison or conditional branching inside the cave.
   - Branch back to the appropriate continuation target (`75 <disp8>` / `EB <disp8>`).
4. **Validation with Capstone**: Always disassemble the patched binary via Capstone before running to confirm byte alignment and relative jump offsets.


---

---

## 6. Garrison AI Mechanics & Area Division Requirement Formulas
Garrison evaluation, area quotas, and reinforcement dispatch are handled primarily in `CGarrisonAI::UpdateGarrisons` (`FUN_0068ba50` at virtual address `0x0068BA50`).

The detailed mathematical formulas, wartime scaling modifiers (including the rear-area $\div 2$ reduction and land-contiguous $\div 3$ reduction), enemy border threat calculations (`war_zone_odds`), and province-level distribution mechanics are documented in:
* **[Garrison AI Reference](file:///e:/Program%20Files%20%28x86%29/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/garrison_ai_reference.md)** (`docs/garrison_ai_reference.md`)

### Summary of Key Engine Identifiers & Offsets
* **Core Function**: `CGarrisonAI::UpdateGarrisons` (`0x0068BA50`)
* **Debug String**: `0x00867E08` (`"Garrison AI: %s: Area %s (%d); nAreaNeed = %d, nDivisions = %d, nAreaLack = %d"`)
* **Area Structure Fields**:
  * `[area + 0x56]`: `nAreaLack` (division deficit sorting priority queue `local_108` descending)
  * `[area + 0x5A]`: `nAreaNeed` (desired total divisions)
  * `[area + 0x5E]`: `nDivisions` (current stationed + inbound friendly divisions)
* **AI Tokens & Offsets (`local_12c`)**:
  * `0x465`: `home_multiplier` (`[local_12c + 0x68]`, default `0.5`)
  * `0x466`: `overseas_multiplier` (`[local_12c + 0x6C]`, default `0.3333`)
  * `0x467`: `home_peace_cap` (`[local_12c + 0x70]`)
  * `0x468`: `war_zone_odds` (`[local_12c + 0x64]`, default `2.0`)
  * `0x469`: `area_multiplier` list (`[local_12c + 0x78]`)
