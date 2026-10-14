# Reverse Engineering Workflows & Tool Automation

**Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour.exe`  
**Scope**: Dynamic debugging with x32dbg, static analysis with Ghidra, UI automation pitfalls, and binary trampoline instrumentation.

---

## 1. x32dbg Automation (via x64dbg MCP)

### 1.1 Reliable Debugger Launch with Working Directory
Darkest Hour resolves scenario lists, graphics, and database files relative to its current working directory. Always launch `InitDebug` passing the game root directory explicitly as the 3rd argument:

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

### 1.2 Avoiding Window Occlusion
- Default 1024x768 windowed mode spawns at desktop origin `(2, 0)`.
- If x32dbg opens maximized, it occludes the game canvas. Move x32dbg to the right monitor half:
  ```json
  window_management(action="set_bounds", handle="<x32dbg_HWND>", x=1047, y=0, width=870, height=632)
  ```

### 1.3 Inspecting the Hourly Simulation Cycle
- Set a conditional or logging breakpoint on date advancement (`[0x00893530] + 0x14`).
- Use `step_into` / `step_over` to inspect instruction branches.
- Use `x64dbg_registers(action="get_flags")` to inspect Zero Flag (`ZF`), Carry Flag (`CF`), etc., after `cmp` or `test` operations.

---

## 2. Ghidra MCP Static Analysis

- **Decompilation**: Use `decompile_function(address="0x00695520")` to rapidly extract pseudocode and reconstruct control flow.
- **Disassembly**: Use `disassemble_function(address="0x00695520")` to inspect instructions with Ghidra's symbol mapping.
- **Cross-References (XRefs)**: Track callers and data references using `get_xrefs_to` / `get_xrefs_from` to find all access points to internal offsets (e.g. `+0x11862`, `+0x120`).

---

## 3. Windows UI Automation & The DirectDraw Deadlock Trap

> [!CAUTION]
> **The DirectDraw Message Pump Freeze**:
> When `Darkest Hour.exe` is paused by a breakpoint in x32dbg, its Win32 message pump and DirectDraw surface are frozen.
> - **NEVER call `window_management(action="activate")` on a debugger-paused window**. Calling `SetForegroundWindow` on a frozen thread forces Windows to wait for thread message queue synchronization, deadlocking the agent until the 180-second tool timeout expires.
> - To inspect visual state while paused, always use:
>   `screenshot_control(action="capture", annotate=false, outputMode="inline", target="window", windowHandle="<HWND>")`

### 3.1 Static UI Coordinate Reference (1024x768 Windowed Mode)
Window bounds: `[2, 0, 1026, 797]`. Internal canvas: `1024x768`.

- **Main Menu Buttons** ($X = 515$, pitch = $40\text{px}$):
  - Single Player: `(515, 481)`
  - Multiplayer: `(515, 521)`
  - Tutorial: `(515, 441)`
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

## 4. Binary Instrumentation & Splicing Patterns

When modifying compiled code where instructions cannot simply be expanded inline:

### 4.1 Short Jump Splicing (Local Cave)
1. **Identify Instruction to Replace**: Find an instruction of 2 or more bytes that can be relocated.
2. **Locate Alignment Padding**: Check the tail of the function for NOP (`0x90`) or INT3 (`0xCC`) padding before the next 16-byte boundary.
3. **Insert Short Jump**:
   - Write a 2-byte short jump (`EB <disp8>`) to reach the trailing padding cave.
   - Execute the original replaced instruction plus new custom logic inside the cave.
   - Return via another short jump (`EB <disp8>`) to the subsequent instruction.

### 4.2 Near Jump Trampolines (Extended Cave / `.mod` Section)
When extensive logic or large buffers are required:
1. **5-Byte Hook**: Overwrite 5 contiguous bytes with `E9 <disp32>`:
   $$\text{disp32} = \text{CaveTargetAddress} - (\text{HookSiteAddress} + 5)$$
2. **6-Byte Hook with NOP**: If replacing a 6-byte instruction (such as `mov eax, [esi+0x88]`), write `E9 <disp32>` followed by a single `0x90` (NOP) to preserve instruction alignment.
3. **Preserving Calling Context**:
   - Save modified scratch registers (`push eax`, etc.).
   - Execute custom algorithm.
   - Restore scratch registers (`pop eax`, etc.).
   - Execute the original replaced instructions.
   - JMP back to resume point: `E9 <disp32>`.
4. **Validation with Capstone / x32dbg**: Always disassemble the target bytes before running the game to verify correct relative displacement and boundary safety.

