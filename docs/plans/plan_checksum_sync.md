# Patch 5: Checksum Synchronization & Configuration Relocation (db/mod_settings.ini)

**Status**: Implemented & Verified  
**Engine**: Darkest Hour 1.05.2 (TENE)  
**Target File**: `Darkest Hour.exe` (File Offset: `0x0002E710`, Virtual Address: `0x0042E710`)  
**Patch Category**: Multiplayer Integrity & Configuration Architecture  

---

## 1. Overview & Motivation

In vanilla Darkest Hour, configuration files located outside standard script directories (such as in the mod root) are not included in the engine's startup database hashing routine. When introducing custom gameplay toggles (such as `AllowPuppetTrade` and `AllowExpForcesToPlayers`), storing settings in an unhashed root file created a serious multiplayer desynchronization risk:
- Two players could join the same multiplayer session with conflicting settings (e.g., one allowing puppet trade and one blocking it), leading to desyncs, ghost trades, and crashes.
- To guarantee multiplayer integrity, custom configuration must be integrated into the engine's native 4-letter checksum pipeline (`TENE`).

This patch implements a dual solution:
1. **Configuration Relocation**: Relocates `mod_settings.ini` into the `db/` directory (`db/mod_settings.ini`), adhering to standard database resolution hierarchy.
2. **Inline Checksum Hashing**: Hooks the engine's checksum accumulator (`FUN_0042E3D0`) to include `db/mod_settings.ini` in the global database hash. Any modification to settings immediately alters the 4-letter checksum displayed in the main menu, natively preventing desyncs.

---

## 2. Configuration Relocation Architecture

### 2.1 File Resolution Hierarchy
The engine resolves configuration paths through a multi-tier fallback:
1. `.\Mods\<ActiveMod>\db\mod_settings.ini` (active mod override).
2. `.\db\mod_settings.ini` (game root fallback).

### 2.2 Path Buffers & Memory Layout (.data Section)
At `0x00880750` in the `.data` section, dedicated format strings and path buffers are allocated:

| Virtual Address | File Offset | Content / Format String | Usage |
|---|---|---|---|
| `0x008807D4` | `0x004807D4` | `".\\%s\\db\\mod_settings.ini\0"` | Mod-specific path format string |
| `0x008807F0` | `0x004807F0` | `".\\db\\mod_settings.ini\0"` | Game root fallback path |
| `0x00880810` | `0x00480810` | `"db\\mod_settings.ini\0"` | Relative path passed to `FUN_0042E2C0` |
| `0x00880830` | `0x00480830` | `char[128]` formatted buffer | Buffer pre-populated and passed to `GetPrivateProfileIntA` |

The sequential INI loader at `0x007E2D30` passes `0x00880830` directly into `GetPrivateProfileIntA`.

---

## 3. Engine Checksum Pipeline Architecture

### 3.1 Checksum Calculation (`FUN_0042E3D0` @ `0x0042E3D0`)
`FUN_0042E3D0` is the top-level checksum calculator executed during game boot:
1. Clears the global 32-bit checksum accumulator: `DAT_00893644 = 0`.
2. Iterates over ~35 core database files (`db\building_costs.txt`, `db\country.csv`, `db\misc.txt`, brigade files, `db\mission_eff.csv`, etc.).
3. Calls native file hashing routine `FUN_0042E2C0(const char* rel_path)` for each file.
4. Accumulates returned integer sums: `DAT_00893644 += FUN_0042E2C0(...)`.
5. Converts `DAT_00893644` into four uppercase ASCII letters:
   $$\text{Char}_0 = (S \pmod{26}) + \text{'A'}$$
   $$\text{Char}_1 = ((S \gg 4) \pmod{26}) + \text{'A'}$$
   $$\text{Char}_2 = ((S \gg 8) \pmod{26}) + \text{'A'}$$
   $$\text{Char}_3 = ((S \gg 12) \pmod{26}) + \text{'A'}$$
6. Formats the string into `DAT_00893648` as `"Darkest Hour v 1.05.2 (%s)"`.

### 3.2 Native File Checksum Routine (`FUN_0042E2C0` @ `0x0042E2C0`)
- Signature: `int __cdecl FUN_0042E2C0(const char* rel_path)`
- Logic:
  - If a mod is active (`DAT_00DC3A00 != 0`), attempts `fopen("%s\\%s", mod_path, rel_path)`.
  - If not found or no mod, falls back to `fopen(rel_path, "rb")`.
  - Reads file byte-by-byte via `fread` and sums all byte values into a signed 32-bit integer.
  - Returns `0` if the file does not exist.

---

## 4. Binary Hook Specification

### 4.1 Inline Hook Location
The hook is installed at the tail of `FUN_0042E3D0` across 72 bytes (`0x0042E710` - `0x0042E758`, file offset `0x0002E710`). It fits completely inline without requiring jumps to external code caves.

### 4.2 Disassembly of Patched Hook
```x86asm
0042E710: 68 68 B1 83 00       push 0x83B168                 ; "db\ministers\minister_personalities.txt"
0042E715: 01 05 44 36 89 00    add [0x00893644], eax         ; accumulate policy_effects.csv sum
0042E71B: E8 A0 FB FF FF       call 0x0042E2C0               ; hash minister personalities
0042E720: 68 54 B1 83 00       push 0x83B154                 ; "db\mission_eff.csv"
0042E725: 01 05 44 36 89 00    add [0x00893644], eax         ; accumulate minister personalities sum
0042E72B: E8 90 FB FF FF       call 0x0042E2C0               ; hash mission_eff.csv
0042E730: 68 10 08 88 00       push 0x00880810               ; "db\mod_settings.ini"
0042E735: 01 05 44 36 89 00    add [0x00893644], eax         ; accumulate mission_eff.csv sum
0042E73B: E8 80 FB FF FF       call 0x0042E2C0               ; hash db\mod_settings.ini
0042E740: 83 C4 20             add esp, 0x20                 ; clean up 8 stacked arguments (32 bytes)
0042E743: 01 05 44 36 89 00    add [0x00893644], eax         ; accumulate db\mod_settings.ini sum
0042E749: BE 1A 00 00 00       mov esi, 0x1A                 ; restore divisor 26 for modulo conversion
0042E74E: A1 44 36 89 00       mov eax, [0x00893644]         ; eax = total checksum
0042E753: 8B C8                mov ecx, eax                  ; ecx = total checksum
0042E755: 90 90 90             nop * 3
0042E758: CDQ                                                ; native modulo division begins
0042E759: F7 FE                idiv esi
```

---

## 5. Checksum Verification Matrix

| Game State | Configuration (`db/mod_settings.ini`) | Checksum | Result |
|---|---|---|---|
| Unmodified Retail | N/A (Vanilla baseline) | `TENE` | Retail match |
| Patched Engine | `AllowPuppetTrade = 2`, `AllowExpForcesToPlayers = 1` | `EGNR` | Modded match |
| Patched Engine | `AllowPuppetTrade = 2`, `AllowExpForcesToPlayers = 0` | `DGNR` | Modded match |
| Any Desync Attempt | Modified values or missing INI file | Diverges | Prevented |

---

## 6. Integration in Patcher (`tools/patch_darkest_hour.bat`)

Patch 5 is registered in the automated patcher script with verification signature:
```powershell
# Patch 5: Checksum Sync for db\mod_settings.ini (FUN_0042E3D0 @ 0x0042E710)
$PATCH5_OFFSET = 0x0002E710
$PATCH5_SIG = [byte[]]@(0x68, 0x68, 0xB1, 0x83, 0x00, 0x01, 0x05, 0x44, 0x36, 0x89, 0x00, 0xE8, 0xA0, 0xFB, 0xFF, 0xFF)
```

