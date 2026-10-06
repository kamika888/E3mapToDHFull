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


---

## 7. Diplomacy Subsystem & Command Architecture

### 7.1 Deterministic Command Queue & Execution Model
In the Darkest Hour / Europa Engine, multiplayer simulations run under a deterministic lockstep model. Consequently:
- **No Direct State Mutations in UI**: Clicking buttons in the interface does not directly mutate country relations, alliances, or trade treaties.
- **Unified Command Dispatch**: All player actions -- both bilateral pacts (Trade Agreement, Alliance) and unilateral toggles (e.g., `DONTSENDFORCES` [Action 27, Command 340], `CANCEL_MILITARY_ACCESS`, `MOBILIZE`, `RELEASE_PUPPET`) -- are packaged into concrete `CCommand` instances and queued into `CCommandQueue`.
- **Hourly Execution Tick**: On the hourly simulation tick, the queue processes packets identically across all network clients via `CCountry::ExecuteCommand` (`0x004A8C90`), ensuring synchronization without desyncs (OOS).

### 7.2 Catalog of the 28 Hardcoded Diplomatic Actions
The game engine maintains an array of 28 diplomatic actions indexed `0` through `27` (`sub_585B10` at `0x00585B10` and `CCountry::CanPerformDiplomacyAction` at `0x004A1050`). When opening the diplomacy window (`sub_61A...`), the dialog builds its action table from these entries:

| Action ID | Internal Key | In-Game Name | Command ID | UI Status | Engine Functionality & Historical Notes |
|:---|:---|:---|:---|:---|:---|
| **0** | `DIP_DECLARE_WAR` | Declare War | 315 | Active | Standard declaration of war. |
| **1** | `DIP_OFFER_ALLIANCE` | Offer Alliance | 316 | Active | Bilateral alliance offer between two unaligned nations. |
| **2** | `DIP_BRING_TO_ALLIANCE` | Bring to Alliance | 317 | Active | Alliance leader invites a third nation into the existing alliance. |
| **3** | `DIP_JOIN_ALLIANCE` | Join Alliance | 318 | Active | Non-aligned country requests admission into an existing alliance. |
| **4** | `DIP_LEAVE_ALLIANCE` | Leave Alliance | 319 | Active | Peacetime exit from an alliance. |
| **5** | `DIP_BAN_FROM_ALLIANCE` | Ban from alliance | 320 | Active | Alliance leader expels a member nation. |
| **6** | `DIP_INFLUENCE_NATION` | Influence Nation | 321 | Active | Costs money; pulls target domestic policy sliders towards actor. |
| **7** | `DIP_COUP_NATION` | Coup Nation | 322 | **Omitted from Diplo UI** | **Legacy HoI2 action.** In *HoI2: Doomsday*, coups were migrated to the Intelligence/Espionage screen (`SPY_COUP`). Retained in internal enum but not populated in Diplo dialog. |
| **8** | `DIP_ASK_FOR_MILITARY_ACCESS` | Ask for Military Access | 323 | Active | Requests passage through target territory. |
| **9** | `DIP_CANCEL_MILITARY_ACCESS` | Cancel Military Access | 324 | Active | Cancels military access previously granted to target. |
| **10** | `DIP_REVOKE_MILITARY_ACCESS` | Revoke Military Access | 325 | Active | Revokes access actor possesses through target territory. |
| **11** | `DIP_ASSUME_MILITARY_CONTROL` | Assume Military Control | 326 | Active | Transfers operational command of ally divisions to actor. |
| **12** | `DIP_CANCEL_MILITARY_CONTROL` | Relinquish Military Control | -- | Active | Returns operational military control to ally. |
| **13** | `DIP_SEND_EXPEDITIONARY_FORCE` | Send Expeditionary Force | 327 | Active | Transfers selected divisions to ally control. |
| **14** | `DIP_GUARANTEE_INDEPENDENCE` | Guarantee Independence | 328 | Active | Grants CB and mitigates dissent if target is attacked. |
| **15** | `DIP_ANNEX_NATION` | Annex Nation | 329 | Contextual | Available when target is fully occupied (100% of Victory Points controlled). |
| **16** | `DIP_PUPPET_REGIME` | Puppet Regime | -- | **Omitted from Diplo UI** | **Legacy HoI1 action.** Peacetime puppet ultimatum. Superseded in DH by peace negotiations (`Sue for Peace`), liberation, and events. |
| **17** | `DIP_DEMAND_TERRITORY` | Demand Territory | 330 | Active | Demands national claims from target country. |
| **18** | `DIP_TRADE` | Open Negotiations | 331 | Active | Bilateral one-time deal interface (provinces, tech blueprints, stockpiles). |
| **19** | `DIP_OFFER_NON_AGGRESSION` | Offer Non-Aggression Pact | 332 | Active | Proposes bilateral Non-Aggression Pact. |
| **20** | `DIP_CANCEL_NA` | Cancel Non-Aggression Pact | 333 | Contextual | Visible only when an active Non-Aggression Pact exists. |
| **21** | `DIP_OFFER_TA` | Offer Trade Agreement | 334 | Active | Establishes daily recurring resource trade agreement. |
| **22** | `DIP_CANCEL_TA` | Break Trade Agreement | 335 | Contextual | Visible only when an active trade agreement exists with target. |
| **23** | `DIP_CANCEL_PT` | Cancel Peace Treaty | 336 | **Omitted from Diplo UI** | **Engine-only command.** Backend command to break post-war truce early. Not added to UI dialog; truces expire on timers or break via events. |
| **24** | `DIP_SUE_FOR_PEACE` | Sue For Peace | 337 | Contextual | Available when at war with target; opens peace negotiation conditions. |
| **25** | `DIP_RELEASE_PUPPET` | Release Puppet | 338 | Contextual | Visible only when viewing actor own puppet; grants independence. |
| **26** | `LIBERATE_NATION` | Liberate Nation | 339 | Contextual | Releases a sovereign or puppet nation from non-core occupied territory. |
| **27** | `DONTSENDFORCES` | Don't Send Expeditionary Forces | 340 | Contextual | Darkest Hour innovation. One-sided toggle to prevent ally AI spamming units. |

#### Unused Legacy CSV Strings
- `DIP_REQUEST_SPECIFIC_ATTACK` (*"Request Specific Attack"*, `text.csv` line 694) and `DIP_OFFER_LEND_LEASE` (*"Offer Lend Lease"*, `text.csv` line 697) are pre-release HoI2 text entries. They have **zero references** in `Darkest Hour.exe` and were never compiled into executable logic.

### 7.3 Embargo Architecture & Runtime Representation
Darkest Hour contains a complete internal trade and technology embargo subsystem:
- **Country Data Offsets**:
  - `[Country + 288 + 448]`: Hash/set of active technology embargoes.
  - `[Country + 288 + 516]`: Hash/set of active trade embargoes.
- **Validation Functions**:
  - `CCountry::HasTechEmbargoAgainst(tag)`: `sub_4A74E0` (`0x004A74E0`), checks tech embargo set.
  - `CCountry::HasTradeEmbargoAgainst(tag)`: `sub_4A7500` (`0x004A7500`), checks trade embargo set.
- **Trade Deal Checks**: `sub_5FE2F0` and tooltip generator `0x0061C950` explicitly call `sub_4A7500`. If an embargo is active between either party, the trade option is blocked with tooltip string `DIPROL_TRADE_EMBARGO` (*"We or they are currently under a trade embargo"*).
- **Event Command Pipeline**: Scripted event command `type = embargo which = TAG where = TAG value = X` is deserialized as `CExecuteEventEffectCommand` (Command ID 278, Sub-effect 330) and executed in `CCountry::ExecuteEmbargoCommand` (`0x00494B90` / `0x00494C41`).

### 7.4 Puppet Trade Mechanics & Master Relationships
- **Master Tag Resolution**:
  - Actor master tag: `*(*(Country_Actor + 0x12da) + 0x3b30)` (returns `0` if independent).
  - Target master tag: `*(*(Country_Target + 0x12da) + 0x3b30)` (returns `0` if independent).
- **Engine Trade Blocks (Vanilla)**:
  - `CCountry::CanPerformDiplomacyAction`:
    - Case `0x12` (`DIP_OFFER_TA` at `0x004A16CC`): Rejects action if either party is a puppet and the other party is not their master.
    - Case `0x15` (`DIP_TRADE` at `0x004A1782`): Performs identical master-only verification.
  - Tooltip Handler (`0x0061D84B` / `0x0061D941`): Jumps to `0x0061DA73` to display `DIPROL_SAT` (*"Puppet states of other nations are not free to do that"*).
  - AI Trade Evaluations (`0x0067B384` and `0x0067C78A`): AI evaluates puppet status and rejects proposing trades to non-masters.

### 7.5 Trade Efficiency Pipeline & Puppet Restrictions
- **Trade Efficiency Table (`m_TradeEfficiency`)**:
  - Located at offset `+0xF4EE` within `CCountry` (`float m_TradeEfficiency[344]`).
  - Represents direct trade efficiency ($0.0$ to $1.0$) between the country and each target country tag.
  - Calculated for all active countries at scenario start (`0x00485E5B`) and during daily country updates (`0x004832C3`) inside `CCountry::CalculateTradeEfficiencies` (`0x0044E800`).
- **Hardcoded Puppet Zero-Efficiency Block (Vanilla)**:
  - In `CCountry::CalculateTradeEfficiencies` (`0x0044EB23` to `0x0044EB66`):
    - Initializes target efficiency to $0.0f$ (`0x0044EB27`).
    - At `0x0044EB39`: Checks if actor is a puppet (`test al, al`). If target is not actor's master (`cmp [esp+0x3c], edi`), jumps to `0x0044F49B` (skipping route calculation and leaving efficiency at $0.0f$).
    - At `0x0044EB4F`: Checks if target is a puppet. If actor is not target's master, jumps to `0x0044F49B` (leaving efficiency at $0.0f$).
  - Consequently, in vanilla any trade agreement involving a puppet and a non-master was mathematically locked to 0% efficiency, even if established by event or save-file edit.
- **Consumers of Trade Efficiency**:
  - **Trade Dialog UI** (`0x0060646F` / `0x00647BC0`): Averages actor and target efficiency `(eff1 + eff2) * 0.5 * 100.0%` and displays string `TA_EFF_EST` (*"Estimated Effectiveness: %.2f%%"*).
  - **Trade Deal Creation** (`0x00781F4F`): Initializes deal efficiency `[CTradeDeal + 0x46]` from `(eff1 + eff2) * 0.5`.
  - **Daily Trade Deal Updates** (`0x0058A870`): Iterates all active deals and updates `[CTradeDeal + 0x46]` from current country efficiencies.
  - **Daily Deliveries**: Resource amounts transferred each hour/day are multiplied by deal efficiency `[CTradeDeal + 0x46]`.
- **Configurable Hook (`0x0044EB39`)**:
  - Replaces the 51-byte hardcoded check with a call to `fn_is_puppet_trade_blocked` (`0x007E2DB0`).
  - When allowed (Mode 1, or Mode 2 without embargo), execution jumps to `0x0044EB6C` to calculate normal land-transit or sea/convoy efficiency.
  - When blocked (Mode 0, or Mode 2 with master embargo), execution jumps to `0x0044F49B` (efficiency stays $0.0f$).
