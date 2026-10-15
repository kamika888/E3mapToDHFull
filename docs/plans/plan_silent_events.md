# Patch 10: Silent Events for Player-Controlled Countries (Zero Popup Execution)

**Status**: Implemented & Verified  
**Engine**: Darkest Hour 1.05.2 (TENE)  
**Target File**: `Darkest Hour.exe`  
- Hook Sites: `0x007123CB`, `0x0070F3A1`, `0x007333FF`, `0x007334D5`  
- Code Cave: `0x00DCA200` (File Offset: `0x00485200` in `.mod` section)  
**Patch Category**: Scripting Engine & UI Automation  

---

## 1. Overview & Motivation

In Darkest Hour, many complex gameplay systems rely on scripted background events (e.g., periodic civilian oil consumption calculation, GDP scaling, dynamic partisan checks, supply convoys).

Because most event commands and triggers require country-level scope to function, they must fire for the specific country being modified. When that country happens to be human-controlled:
1. Vanilla Europa Engine forces a **modal popup dialog window** to appear.
2. The simulation automatically **pauses**.
3. The human player must manually click an action button to dismiss the dialog.

For frequent maintenance events, these constant popups disrupt gameplay. The goal of **Patch 10** is to enable **silent execution**:
- In the **custom patched binary**, player events marked with the `ENGINE:SILENT_EVENT` trigger execute automatically in the background (Action A is selected, or `ai_chance` weighted probabilities are rolled) with **zero UI dialogs**, **zero simulation pauses**, and **zero player input required**, while updating game state and recording the event in savegame history.
- In the **unmodified retail binary (`Darkest Hour.exe`)**, the exact same event executes normally as a standard event with its real localized title and description, producing **zero syntax errors**, **zero savedebug.txt warnings**, and **zero crashes**.

---

## 2. DHFScript Scripting Convention

To achieve guaranteed dual compatibility without deceiving other modders or breaking retail simulation logic, the silent event directive uses a positive `OR` trigger with a guaranteed 100% retail fallback:

```text
event = {
    id = 30000
    random = no
    persistent = yes

    trigger = {
        # Actual gameplay conditions:
        local_flag = AllInit

        # Engine silent directive with guaranteed retail fallback:
        OR = {
            flag = "ENGINE:SILENT_EVENT"
            random = 100
        }
    }

    date = { day = 1 month = january year = 1936 }
    offset = 4
    deathdate = { day = 29 month = december year = 1963 }

    name = "EVT_OIL_RECALCULATION"
    desc = "EVT_OIL_RECALCULATION_DESC"
    style = 2

    action = {
        name = "ACTION_OK"
        command = { type = oilpool value = -50 }
    }
}
```

### Why this pattern works:
* **In Retail `Darkest Hour.exe`**:
  - The engine's lexer parses `flag = "ENGINE:SILENT_EVENT"` as an unknown/unset flag (evaluates to `false`).
  - The second line `random = 100` always evaluates to `true`.
  - Because they are enclosed in an `OR = { ... }` block, the trigger evaluates to `true`.
  - The event fires normally with full localized text.
* **In Patched `Darkest Hour.exe`**:
  - The flag parser detects the `"ENGINE:SILENT_EVENT"` string token and flags the event as silent (`m_bSilent = 1`).
  - When the event triggers for the human player, the dispatcher suppresses the dialog window and executes the action silently in the background.

---

## 3. Reverse Engineering & Engine Internals

### 3.1 Event Dispatch Pipeline (`FUN_00712310`)
When an event triggers (Message Type `0x00A0`), `CEvent::HandleMessage` (`0x00712310`) checks if the target country matches the local player:

```assembly
007123C2: 8B 47 24          mov eax, [edi+0x24]       ; EAX = Event Target CCountry*
007123C5: 8B 0D 90 CA D0 00 mov ecx, [0x00D0CA90]    ; ECX = Local Player CCountry*
007123CB: 3B C1             cmp eax, ecx
007123CD: 74 2A             jz  0x007123F9            ; Jump to Player Dialog Popup Path
007123CF: 85 C0             test eax, eax
007123D1: 0F 85 81 00 00 00 jnz 0x00712458            ; Jump to AI Path
```

### 3.2 The `CCountry::IsAi()` Dispatch Trap
In vanilla, the AI path at `0x00712458` verifies whether the country is AI-controlled:
```assembly
00712465: 8B 4F 24          mov ecx, [edi+0x24]
00712468: 8B 01             mov eax, [ecx]
0071246A: FF 50 1C          call dword ptr [eax+0x1C] ; CCountry::IsAi()
0071246D: 84 C0             test al, al
0071246F: 75 1D             jnz 0x0071248E            ; IF AI -> Proceed to Action Resolution
...
00712488: 0F 85 58 02 00 00 jnz 0x007126E6            ; NON-AI COUNTRY ABORTS AND EXITS!
```
If a human player event is diverted to `0x00712458`, `IsAi()` returns `0`, causing the engine to abort immediately at `0x00712488`.

### 3.3 The Native Action Resolution Routine (`0x0071248E`)
At `0x0071248E`, the engine performs action calculation and network dispatching:
1. `0x0071248E`: `mov ecx, edi; call 0x007120b0` (`CEvent::CalculateAction`).
   - If 1 valid action: selects Action A (index 0).
   - If multiple valid actions: rolls `ai_chance` weighted probabilities.
2. `0x00712495` - `0x00712585`: Allocates message packet `0x84` containing the chosen action index, country tag, and event ID.
3. `0x0071258E`: Calls `0x00565ca0` to dispatch packet `0x84`.
4. Delivery of packet `0x84` invokes `0x00711c60` (`CEvent::ExecuteAction`):
   - Executes all commands.
   - Updates resources and game state.
   - Records the event into savegame `history = { ... }` via `0x004e9370`.

---

## 4. Binary Modifications & Code Cave

### 4.1 Hook Sites

| Address | Original Bytes | Patched Bytes | Purpose |
|---|---|---|---|
| `0x0070F3A1` | `8B E9 89 44 24 14` | `E9 6A AE 6B 00 90` | Event Loader: Records `CEvent*` currently being parsed to `g_pCurrentLoadingEvent`. |
| `0x007333FF` | `5F 5E 5D 5B C2 04 00` | `E9 2C 6E 69 00 90 90` | Bare Flag Trigger Parser (`flag = "..."`): Inspects flag string. |
| `0x007334D5` | `5F 5E 5D 5B C2 04 00` | `E9 56 6D 69 00 90 90 90 90` | Structured Flag Trigger Parser (`flag = { which = ... }`): Inspects flag string. |
| `0x007123CB` | `3B C1 74 2A` | `E9 A0 7E 6B 00 90` | Event Dispatcher: Diverts silent player events directly to `0x0071248E`. |

### 4.2 Cave Assembly (`0x00DCA200` / File Offset `0x00485200`)

```assembly
; Data storage:
0x00DCA200: dd 0 ; g_pCurrentLoadingEvent
0x00DCA204: 12 bytes zero padding

; Cave 1: Record Currently Loading Event (0x00DCA210)
Cave_RecordLoadingEvent:
    mov [0x00DCA200], ecx
    mov ebp, ecx
    mov [esp+0x14], eax
    jmp 0x0070F3A7

; Cave 2: Intercept Flag Name (0x00DCA230)
Cave_CheckFlagName:
    cmp dword ptr [ebp+0x12], 0x49474E45   ; "ENGI"
    jne ExitFlagCheck
    mov eax, [ebp+0x16]
    cmp eax, 0x533A454E                    ; "NE:S" (ENGINE:S)
    je PrefixMatch
    cmp eax, 0x535F454E                    ; "NE_S" (ENGINE_S)
    jne ExitFlagCheck
PrefixMatch:
    cmp dword ptr [ebp+0x1A], 0x4E454C49   ; "ILEN" (ILENT)
    jne ExitFlagCheck
    mov eax, [0x00DCA200]
    test eax, eax
    jz ExitFlagCheck
    mov byte ptr [eax+0x23BF], 1           ; Set CEvent::m_bSilent = 1
ExitFlagCheck:
    xor eax, eax
    pop edi
    pop esi
    pop ebp
    pop ebx
    ret 4

; Cave 3: Dispatcher Check (0x00DCA270)
Cave_EventDispatchCheck:
    cmp eax, ecx
    jne NotPlayerCountry
    cmp byte ptr [edi+0x23BF], 1
    je IsSilentEvent
NormalPlayerEvent:
    jmp 0x007123F9                         ; Spawns modal dialog popup
IsSilentEvent:
    jmp 0x0071248E                         ; Action Calc (0x007120b0) + Packet 0x84 Dispatch
NotPlayerCountry:
    test eax, eax
    jmp 0x007123D1                         ; Retail AI path
```

---

## 5. Verification & Testing Results

1. **Patched Executable (`Darkest Hour.exe`)**:
   - Silent event triggers on scheduled date without popup window.
   - Simulation continues running without pausing.
   - Supplies and dissent changes apply immediately.
   - Event ID is properly recorded in savegame `history = { ... }`.
   - Normal player events without `ENGINE:SILENT_EVENT` continue to pop up normally.
2. **Retail Pristine Executable (`Darkest Hour_original.exe`)**:
   - Both events pop up as standard dialogs.
   - Localized titles and descriptions display correctly.
   - `savedebug.txt` records zero errors or unknown trigger warnings.

