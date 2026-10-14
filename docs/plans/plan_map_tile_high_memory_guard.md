# Patch 9: Map Tile High-Memory Signed Comparison Fix (LAA Crash Prevention)

**Status**: Implemented & Verified  
**Engine**: Darkest Hour 1.05.2 (TENE)  
**Target File**: `Darkest Hour.exe` (Virtual Address: `0x004DB0C5`, File Offset: `0x000DB0C5`)  
**Patch Category**: Memory Architecture & Map Stability  

---

## 1. Overview & Motivation

When **Patch 7 (Large Address Aware / LAA)** is active on 64-bit Windows, the operating system kernel allows the Darkest Hour process to allocate heap memory and DirectDraw surfaces in the upper 2 GB virtual address space ($0\text{x}80000000$ to $0\text{xFFFFFFFF}$).

In extended play sessions (such as campaigns progressing into 1941+ with multiple saves/reloads), the off-screen surface wrapper pointer `DAT_00a98460` can be allocated at an address above 2 GB (e.g. `0x9DA1DF00`).

In `FUN_004dafb0` (the map tile boundary unpacker), if any map tile header contains an out-of-bounds boundary reference (such as the 6-bit index overflow in dense province clusters), the engine reads array element `buffer[-4]`, which fetches the pointer `DAT_00a98460` and tests whether it is a valid province ID ($\le 8021$).

Because the original code was compiled with **signed integer comparison (`JLE`)**:
* High-memory addresses ($\ge 0\text{x}80000000$) have bit 31 set and are evaluated as **negative numbers** (e.g. `0x9DA1DF00` = $-1,650,336,000$).
* The comparison `signed(-1,650,336,000) <= 8021` evaluates to **TRUE**.
* The engine bypasses its built-in error recovery clamp (`xor esi, esi`), treats the negative address as a valid province ID, multiplies it by 1202 (`0x4B2`), and crashes with `EXCEPTION_ACCESS_VIOLATION` (`c0000005`) at `0x004DB0DF`.

This patch converts the signed jump `JLE` (`7E 02`) to an unsigned jump `JBE` (`76 02`), restoring the intended safety clamp and making the engine crash-proof against high-address pointers.

---

## 2. Technical Specification & Binary Modification

### 2.1 Call Site & Context (`FUN_004dafb0` @ `0x004DB0B0` - `0x004DB0D0`)

```assembly
004DB0BC: 8B 74 8E F0    mov esi, dword ptr [esi+ecx*4-0x10]  ; Fetch province ID from tile buffer
004DB0C0: 83 E0 0F       and eax, 0xF                         ; Border variant index
004DB0C3: 3B F2          cmp esi, edx                         ; edx = [0x00877690] = MaxProvinces (8021)
004DB0C5: 7E 02          jle 0x004DB0C9                       ; Original: Signed comparison (JLE)
004DB0C7: 33 F6          xor esi, esi                         ; Safe clamp to Province 0
004DB0C9: 8D 0C 76       lea ecx, [esi+esi*2]                 ; Begin province struct offset calculation
```

### 2.2 Truth Table Comparison

| Candidate Value in `ESI` | Meaning | Original `JLE` (`7E 02`) | Patched `JBE` (`76 02`) | Engine Result |
|---|---|---|---|---|
| **$0 \dots 8021$** | Valid Province ID | Jump (Valid) | Jump (Valid) | **Identical**: Renders province border normally |
| **$8022 \dots \text{0x7FFFFFFF}$** | Invalid ID / Low-Memory Pointer | No jump $\rightarrow$ Clamp to 0 | No jump $\rightarrow$ Clamp to 0 | **Identical**: Clamps safely to Province 0 |
| **$\ge \text{0x80000000}$** | High-Memory Pointer (LAA memory) | **Jump (negative!) $\rightarrow$ CRASH** | **No jump $\rightarrow$ Clamp to 0** | **Crash Prevention**: Clamps safely to Province 0 |

### 2.3 Binary Opcode Modification

- **Target Virtual Address**: `0x004DB0C5`
- **File Offset**: `0x000DB0C5`
- **Original Byte**: `0x7E` (`JLE`)
- **Patched Byte**: `0x76` (`JBE`)

---

## 3. Operational Impact & Safety Analysis

1. **Subsystem Isolation**:
   * Instruction `0x004DB0C5` is strictly local to `FUN_004dafb0` (tile unpacking).
   * It has zero interaction with combat, AI, diplomacy, events, scripting, or pathfinding.
2. **Behavior on Province 0**:
   * Immediately following the clamp, instruction `0x004DB0F4` executes `cmp esi, 1; jl 0x004db190`.
   * For Province 0, it skips border drawing entirely and continues to the next tile entry.
   * Terrain color, province textures, unit counters, and map graphics are unaffected.
3. **Universality**:
   * Works synergistically with the map data patch in `lightmap3.tbl`.
   * Serves as a universal engine-level safety net for any present or future map files.

