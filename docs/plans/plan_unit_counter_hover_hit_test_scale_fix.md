# Patch 13: Unit Counter Hover Hit-Test Effective Scale Fix (Map Scroll Crash Fix)

**Status**: Implemented (binary + patcher), pending in-game soak test  
**Engine**: Darkest Hour 1.05.2 (TENE)  
**Target File**: `Darkest Hour.exe` (Virtual Address: `0x0041714B` - `0x00417193`, File Offset: `0x0001714B`, 73 bytes)  
**Patch Category**: Map UI Stability (vanilla engine bug)  

---

## 1. Overview & Motivation

While scrolling the map or moving the mouse over unit counters at zoom level 1 or higher, the game can crash with `EXCEPTION_ACCESS_VIOLATION` (`c0000005`) at `0x00406100` (`mov al, byte ptr [eax]`).

This is a **vanilla engine bug**. It is unrelated to the `lightmap3.tbl` clamp or Patch 9. The faulty bytes are identical in `Darkest Hour_original.exe`.

### Observed crash state (x32dbg)

| Item | Value |
|---|---|
| Crash EIP | `0x00406100` in `FUN_004060b0` (surface pixel transparency test) |
| Faulting address | `EAX = 0x58E15AA6` (unmapped) |
| Surface (`ESI`) | `0x5E313D98`: width `0x520` (1312), height `0x22` (34), pitch `0x520` |
| Pixel requested | `X = 342`, `Y = 58` (Y is past the 34-pixel surface height) |
| Zoom (`[0x00A98464]`) | `1` |
| Counter scale bias (`[counter+0x82]`) | `-1` |

### Call stack

```
0x00406100  FUN_004060b0      Surface::IsPixelOpaque(x, y)   -> vtable+0x04 GetPixelAddress (FUN_00409090)
0x00417199  0x004170C0        Unit counter sprite hit-test (vtable+0x20 of counter sprite, vtable 0x007E3738)
0x00652A06  FUN_00652570      Map hover / selection dispatch: loops all countries' unit lists (DAT_0089CAD8, +0x4508)
0x00654B47  map window message handler (mouse move)
```

---

## 2. Root Cause

### 2.1 Counter sprite scale

Unit counter sprites (constructor `FUN_00416730`, vtable `0x007E3738`) store a scale bias at `+0x82`. Counters use `-1` so they do not shrink at zoom 1. Draw code (`0x00416FED`) and the hit-test bounding box both use:

$$\text{effective\_scale} = \max(0,\ \text{bias} + \text{zoom})$$

| Zoom | effective_scale | On-screen counter size |
|---|---|---|
| 0 | 0 | 32 x 34 |
| 1 | 0 | 32 x 34 |
| 2 | 1 | 16 x 17 |
| 3 | 2 | 8 x 8 |

In `0x004170C0`, `EDI` gets `effective_scale` at `0x004170EB`-`0x004170FD`. The screen bounding box (`0x0041712B`-`0x00417161`) is computed correctly as `size >> effective_scale`.

### 2.2 The defect

When the mouse is inside the bounding box, the routine converts the local screen offset back into texture coordinates. Vanilla shifts by the **global zoom** instead of `effective_scale`:

```assembly
00417176: 2B F9              sub  edi, ecx                  ; EDI = mouseY - top      (0..33 at zoom 1)
00417178: 8B 0D 64 84 A9 00  mov  ecx, [0x00A98464]         ; ECX = global zoom       <-- BUG
0041717E: D3 E7              shl  edi, cl                   ; Y   = localY << zoom    (up to 66)
00417183: 2B D5              sub  edx, ebp                  ; EDX = mouseX - left
00417185: D3 E2              shl  edx, cl                   ; X   = localX << zoom    (up to 62)
...
0041718A: 8B 7E 56           mov  edi, [esi+0x56]           ; frame width (32)
0041718D: 0F AF 7E 52        imul edi, [esi+0x52]           ; * frame index (e.g. 9)
00417191: 03 FA              add  edi, edx                  ; X = frame*32 + localX
00417194: E8 17 EF FE FF     call 0x004060B0                ; IsPixelOpaque(X, Y), no bounds check
```

If the cursor is on the lower half of a counter (`localY >= 17` at zoom 1), Y comes out at 34 or more. `FUN_004060b0` passes it straight to `GetPixelAddress` (`base + x*bpp + y*pitch`) and dereferences it. In the crash:

$$58 \times 1312 + 342 = 76{,}438 \text{ bytes} \quad\text{vs. buffer size}\quad 34 \times 1312 = 44{,}608 \text{ bytes}$$

X is wrong in the same way: it can sample a neighbouring frame in the counter strip. That is harmless memory-wise, but hover detection on the right half of counters is wrong too.

### 2.3 Why it is intermittent

* It only happens at zoom 1 or higher, with the cursor over the lower half of a counter (zoom 1). At zoom 2/3 it is over a larger share of the counter.
* The bad read is only about 30 KB past the end of the surface. Whether that lands in committed memory depends on heap layout. With LAA (Patch 7) the address space is larger and sparser, so the page after a surface is more often unmapped. That makes the latent vanilla bug fatal more often. LAA does not cause it.

---

## 3. Fix: In-Place Register Reallocation (No Code Cave)

At `0x0041714B` vanilla reloads `mouseY` into `EDI`, which destroys `effective_scale`. Meanwhile `EBX` (screen right edge) is dead after the X test at `0x0041713B`. It is callee-saved and restored by the epilogue `pop ebx`.

The patch:
1. Loads `mouseY` into `EBX` instead of `EDI`, so `EDI` keeps `effective_scale`.
2. Replaces the 6-byte global zoom load with `mov ecx, edi` (2 bytes). The shift becomes `shl ebx, cl`, padded with 4 NOPs.
3. Pushes `EBX` as the Y argument.

All instruction boundaries and branch targets are unchanged. The only branches into the range (`0x0041713D`, `0x0041714C`, `0x00417151`, `0x00417161`) land on unchanged instruction starts.

```assembly
; --- Patched ---
0041714B: 8B 5C 24 20        mov  ebx, [esp+0x20]           ; mouseY -> EBX (was EDI)
0041714F: 3B D9              cmp  ebx, ecx                  ; vs top
00417151: 7D 0C              jge  0x0041715F
0041715F: 3B D8              cmp  ebx, eax                  ; vs bottom
00417161: 7C 0C              jl   0x0041716F
0041716F: 8A 46 68           mov  al, [esi+0x68]
00417172: 84 C0              test al, al
00417174: 75 33              jnz  0x004171A9
00417176: 2B D9              sub  ebx, ecx                  ; localY
00417178: 8B CF              mov  ecx, edi                  ; CL = effective_scale
0041717A: D3 E3              shl  ebx, cl                   ; Y = localY << effective_scale
0041717C: 90 90 90 90        nop x4
00417180: 8B 46 62           mov  eax, [esi+0x62]
00417183: 2B D5              sub  edx, ebp
00417185: D3 E2              shl  edx, cl                   ; X uses effective_scale too
00417187: 8B C8              mov  ecx, eax
00417189: 53                 push ebx                       ; Y (was push edi)
```

### 3.1 Byte diff (file offsets)

| File Offset | Original | Patched |
|---|---|---|
| `0x0001714C` | `7C` | `5C` |
| `0x00017150` | `F9` | `D9` |
| `0x00017160` | `F8` | `D8` |
| `0x00017177` | `F9` | `D9` |
| `0x00017179` - `0x0001717F` | `0D 64 84 A9 00 D3 E7` | `CF D3 E3 90 90 90 90` |
| `0x00017189` | `57` | `53` |

### 3.2 Bounds guarantee after patch

Because `localY < (34 >> s)`, it follows that `localY << s < 34`. Likewise `localX << s < 32`. Every sampled pixel stays inside the counter's own frame.

---

## 4. Operational Impact & Safety

1. **Scope**: Only `0x004170C0` (unit counter sprite hit-test, vtable slot `+0x20`) is changed. `FUN_004060b0` itself is untouched. Its only other caller is the generic sprite hit-test at `0x00415C00` (call at `0x00415C8D`).
2. **Behavior**: At zoom 0, `effective_scale == zoom == 0`, so the result is identical to vanilla. At zoom 1-3, hover/selection now tests the correct pixel of the correct frame. Clicking and hovering counters becomes accurate instead of reading random memory.
3. **Known limitation**: The bounding box also folds in the sprite's base shift `[+0x0E]`, but the texture mapping (vanilla and patched alike) does not. It was `0` on the crashing counter, and counters appear to always use 0.
4. **Multiplayer**: UI-only. No game state, checksum, or simulation impact.

---

## 5. Verification

* **Static**: The patcher `-Verify` reports `Sig13Patch` for the active exe. The 73 bytes at `0x0001714B` match `$PATCH13_SIG`.
* **In-game**: At zoom 1, 2 and 3, sweep the cursor slowly across the lower half of counters in dense stacks (China, Europe, Soviet border) while scrolling. Expect no AV at `0x00406100`, and hover highlight/selection should line up with the visible counter.
