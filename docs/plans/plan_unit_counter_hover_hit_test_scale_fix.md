# Implementation Plan: Unit Counter Hover Hit-Test Effective Scale Fix (Patch 13)

## Goal Description
Fix the recurring `EXCEPTION_ACCESS_VIOLATION` (`0xC0000005`) crash at `0x00406100` (`FUN_004060b0` / `0x004170C0`) that occurs when scrolling the map or hovering the mouse cursor over unit counters at map zoom levels $\ge 1$.

### Background & Mechanics
During map scrolling or mouse movement, `FUN_00652570` loops through all visible unit counters on screen to test whether the cursor is hovering over a counter (for selection, tooltips, or highlight state). For each counter, it calls the sprite hit-test method `0x004170C0`.

1. **Visual Scale Calculation**:
   Unit counters have a scale offset bias of $-1$ (`[counter + 0x82] = -1`), which prevents them from shrinking at Zoom 1 so they remain readable to the player.
   $$\text{effective\_scale} = \max(0, \text{scale\_bias} + \text{zoom})$$
   * At Zoom 0: $\max(0, -1 + 0) = 0$ ($1\times$ scale, $32 \times 34\text{ px}$)
   * At Zoom 1: $\max(0, -1 + 1) = 0$ ($1\times$ scale, $32 \times 34\text{ px}$)
   * At Zoom 2: $\max(0, -1 + 2) = 1$ ($0.5\times$ scale, $16 \times 17\text{ px}$)
   * At Zoom 3: $\max(0, -1 + 3) = 2$ ($0.25\times$ scale, $8 \times 8.5\text{ px}$)

2. **The Vanilla Engine Bug**:
   The bounding box check (`0x0041712b` - `0x00417161`) correctly uses `effective_scale` to verify if the cursor is within the counter's screen boundaries. However, in the subsequent per-pixel transparency sampling block (`0x00417178` - `0x00417185`), the original code mistakenly ignores `effective_scale` and shifts local coordinates by the **global map `zoom` level directly**:
   ```x86asm
   00417176  sub  edi, ecx                  ; EDI = mouseY - screen_top (local Y: 0..33)
   00417178  mov  ecx, dword ptr [00a98464] ; ECX = Global Zoom Level (e.g. 1) <-- BUG!
   0041717e  shl  edi, cl                   ; EDI = local Y << zoom (e.g. 29 << 1 = 58)
   00417189  push edi                       ; Push Y = 58
   00417194  call 004060b0                  ; Call Surface->IsPixelTransparent(X, Y)
   ```

3. **Buffer Overrun & Crash**:
   Because the counter texture surface is only $34$ pixels tall, sampling at $Y = 58$ causes `GetPixelAddress` (`FUN_00409090`) to compute a pointer $31{,}830$ bytes past the end of the DirectDraw surface buffer ($58 \times 1312 + 342 = 76{,}438$ bytes, vs buffer size of $44{,}608$ bytes). Under Large Address Aware (LAA), this out-of-bounds offset crosses into uncommitted virtual memory (`0x58E15AA6`), triggering an instant Access Violation crash.

---

## User Review Required

> [!IMPORTANT]
> **Zero Code Caves / In-Place Register Reallocation**
> Earlier in `0x004170C0`, register `EDI` already computes and holds `effective_scale`. At line `0x0041714B`, the compiler needlessly reused `EDI` to hold `mouseY`, while register `EBX` (which previously held `screen_right`) became completely dead and unused.
> 
> By switching `mouseY` to use `EBX`, `EDI` naturally retains `effective_scale` throughout the entire function. At line `0x00417178`, we replace the 6-byte global zoom load with `mov ecx, edi; shl ebx, cl; nop; nop; nop; nop`.
> 
> **Benefits**:
> * Exactly preserves all 73 bytes of the routine without shifting any instruction boundaries or relative jumps.
> * Requires **zero code caves**, zero far jumps, and zero external relocations.
> * Mathematically restores true 1:1 pixel transparency testing for counters at Zoom 1, 2, and 3.

---

## Open Questions

None. The root cause is completely diagnosed at the byte level, and the in-place fix fits directly within existing instruction space.

---

## Proposed Changes

### Engine Binary & Patch Scripts

#### [MODIFY] [`Darkest Hour.exe`](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Darkest%20Hour.exe)
* **File Offset**: `0x0001714B` (Virtual Address: `0x0041714B` to `0x00417189`)
* **Byte Count**: 73 bytes (12 specific byte modifications, zero displacement)

```x86asm
; --- Before (Vanilla Darkest Hour v1.05.2) ---
0041714B: 8B 7C 24 20        mov  edi, dword ptr [esp+0x20]   ; EDI clobbers effective_scale
0041714F: 3B F9              cmp  edi, ecx                    ; cmp mouseY, screen_top
00417151: 7D 0C              jge  0x0041715F
... [return 0 exit block]
0041715F: 3B F8              cmp  edi, eax                    ; cmp mouseY, screen_bottom
00417161: 7C 0C              jl   0x0041716F
... [return 0 exit block]
0041716F: 8A 46 68           mov  al, byte ptr [esi+0x68]
00417172: 84 C0              test al, al
00417174: 75 33              jnz  0x004171A9
00417176: 2B F9              sub  edi, ecx                    ; EDI = mouseY - top
00417178: 8B 0D 64 84 A9 00  mov  ecx, dword ptr [00A98464]   ; ECX = Global Zoom Level (BUG)
0041717E: D3 E7              shl  edi, cl                     ; EDI = local Y << zoom (OVERFLOW)
00417180: 8B 46 62           mov  eax, dword ptr [esi+0x62]
00417183: 2B D5              sub  edx, ebp
00417185: D3 E2              shl  edx, cl
00417187: 8B C8              mov  ecx, eax
00417189: 57                 push edi                         ; Push Y (58 > 34)

; --- After (Patched: Patch 13) ---
0041714B: 8B 5C 24 20        mov  ebx, dword ptr [esp+0x20]   ; Load mouseY into dead register EBX
0041714F: 3B D9              cmp  ebx, ecx                    ; cmp mouseY, screen_top
00417151: 7D 0C              jge  0x0041715F                  ; (branch target unchanged)
... [return 0 exit block]
0041715F: 3B D8              cmp  ebx, eax                    ; cmp mouseY, screen_bottom
00417161: 7C 0C              jl   0x0041716F                  ; (branch target unchanged)
... [return 0 exit block]
0041716F: 8A 46 68           mov  al, byte ptr [esi+0x68]
00417172: 84 C0              test al, al
00417174: 75 33              jnz  0x004171A9                  ; (branch target unchanged)
00417176: 2B D9              sub  ebx, ecx                    ; EBX = mouseY - top
00417178: 8B CF              mov  ecx, edi                    ; ECX = effective_scale (from EDI!)
0041717A: D3 E3              shl  ebx, cl                     ; EBX = local Y << effective_scale
0041717C: 90 90 90 90        nop; nop; nop; nop               ; Padding (exact 8-byte preservation)
00417180: 8B 46 62           mov  eax, dword ptr [esi+0x62]
00417183: 2B D5              sub  edx, ebp
00417185: D3 E2              shl  edx, cl                     ; EDX = local X << effective_scale
00417187: 8B C8              mov  ecx, eax
00417189: 53                 push ebx                         ; Push Y (bounded within 0..33)
```

#### Byte Diff Summary:
* Offset `0x0001714C`: `7C` $\rightarrow$ `5C`
* Offset `0x00017150`: `F9` $\rightarrow$ `D9`
* Offset `0x00017160`: `F8` $\rightarrow$ `D8`
* Offset `0x00017177`: `F9` $\rightarrow$ `D9`
* Offset `0x00017179` - `0x0001717F`: `0D 64 84 A9 00 D3 E7` $\rightarrow$ `CF D3 E3 90 90 90 90`
* Offset `0x00017189`: `57` $\rightarrow$ `53`

---

#### [MODIFY] [`tools/patch_darkest_hour.bat`](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/tools/patch_darkest_hour.bat) & [`patch_darkest_hour.bat`](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/patch_darkest_hour.bat)
* Add definition for **Patch 13: Unit Counter Hover Hit-Test Effective Scale Fix**:
  * `$SIG13_OFFSET = 0x0001714B`
  * `$ORIG13_SIG`: Original 73 bytes
  * `$PATCH13_SIG`: Patched 73 bytes
* Include Patch 13 in `$PATCH_CHUNKS` and verification status checks.
* Update help, banner, and summary output.

---

### Documentation

#### [NEW] [`docs/plans/plan_unit_counter_hover_hit_test_scale_fix.md`](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/plan_unit_counter_hover_hit_test_scale_fix.md)
* Comprehensive documentation covering the mathematical analysis, register lifecycle, assembly diff, and verification data.

#### [MODIFY] [`docs/plans/README.md`](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/plans/README.md) & [`docs/engine_internals_reference.md`](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/engine_internals_reference.md)
* Register Patch 13 in the engine patch catalog and subsystem reference tables.

---

## Verification Plan

### Automated Tests
1. **Binary Offset and Disassembly Verification**:
   Verify with Python that all modified offsets match their intended opcodes:
   ```powershell
   python -c "
   with open('Darkest Hour.exe', 'rb') as f:
       f.seek(0x0001714B)
       data = f.read(73)
       assert data[:4] == bytes.fromhex('8b5c2420')
       assert data[0x2d:0x35] == bytes.fromhex('8bcfd3e390909090')
       assert data[0x3e:0x3f] == bytes.fromhex('53')
       print('Patch 13 verification successful!')
   "
   ```
2. **Patcher Script Self-Verification**:
   Run the updated batch patcher in verify mode:
   ```powershell
   .\patch_darkest_hour.bat -Verify
   ```

### Manual Verification
1. **Debugger Resume & Counter Hover**:
   * Detach/resume or restart game under x32dbg with the patched executable.
   * Load the 1936 scenario / save game.
   * Scroll across the map at Zoom Level 1, 2, and 3 directly over dense unit counter stacks (e.g. southern China, Europe, Soviet borders).
   * Hover the mouse cursor specifically over the lower half of unit counters.
   * Verify that:
     1. No `EXCEPTION_ACCESS_VIOLATION` occurs.
     2. Unit selection, tooltip boxes, and hover highlights display immediately and smoothly.
     3. Normal map scrolling operates without stutter or memory faults.
