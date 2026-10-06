# Implementation Plan & Summary: Configurable Puppet State Trade via `mod_settings.ini`

## Goal Description
In Darkest Hour, puppet states are hardcoded to disallow trade with any nation other than their master state (e.g., in `TestSave6.eug`, FRA is a puppet of ENG and cannot trade with POL). In the diplomacy window, trade buttons are grayed out with the tooltip `DIPROL_SAT`: *"Puppet states of other nations are not free to do that."* Furthermore, any trade deal established by event or savegame edit involving a puppet and a non-master was hardcoded to 0% effectiveness.

This implementation provides a clean, fully backwards-compatible solution via an external configuration file `mod_settings.ini` without modifying `db/misc.txt` (ensuring 100% compatibility when swapping back to the unpatched `Darkest Hour_original.exe`):

```ini
[Diplomacy]
; Allow Puppet Trade:
; 0 = Vanilla behavior (puppets can only trade with their master)
; 1 = Free trade (puppets can trade with any nation not at war)
; 2 = Free trade with Master Veto (puppets trade freely, but automatically respect master trade embargoes and master war enemies)
AllowPuppetTrade = 2
```

---

## Technical Architecture & Safety

1. **Backwards Compatibility**:
   - `db/misc.txt` remains **completely untouched**. The original vanilla executable will continue to load the mod without syntax errors, buffer shifts, or struct overflows.
2. **Binary Safety & Slack Caves**:
   - Dedicated backup created: `Darkest Hour_backup_pre_puppet_trade.exe`.
   - `.text` code cave at `0x007E2DB0` (240 bytes of contiguous zero slack space up to `0x007E2EA0`).
   - `.data` slack space at `0x00880780` for global variables and string constants.
3. **Dynamic INI Reader**:
   - Reads `mod_settings.ini` at game startup via `GetPrivateProfileIntA` (dynamically resolved using linked `LoadLibraryA` / `GetProcAddress` at IAT entries `[0x007E3054]` / `[0x007E3080]`).
   - Default value is `2` if `mod_settings.ini` is missing.

---

## Detailed Hook Specifications

### 1. `.data` Allocation (`0x00880780`)
- `0x00880780`: `g_nPuppetTradeMode` (DWORD, default 2).
- `0x00880784`: String `"kernel32.dll\0"`
- `0x00880794`: String `"GetPrivateProfileIntA\0"`
- `0x008807B0`: String `"Diplomacy\0"`
- `0x008807C0`: String `"AllowPuppetTrade\0"`
- `0x008807D4`: String `".\%s\mod_settings.ini\0"`
- `0x008807EC`: String `".\mod_settings.ini\0"`

### 2. Startup INI Loader Hook
- Hooked early initialization (`sub_791FE9` at `0x00791FE9` via call at `0x00792BA3`):
  1. Resolves `GetPrivateProfileIntA` from `kernel32.dll`.
  2. Queries active mod folder name; reads `AllowPuppetTrade` from `<mod>\mod_settings.ini` (fallback to `.\mod_settings.ini`).
  3. Stores result in `0x00880780`.

### 3. Master Veto Subroutine (`fn_is_master_hostile` at `0x007E2E4D`)
Evaluates whether a master nation blocks diplomatic trade with a target country. Preserves caller registers and stack alignment across all branches:
1. **Trade Embargo Check**:
   - Calls `0x004A74E0` (`CCountry::HasTradeEmbargoAgainst`, checking `[CCountry + 0x120 + 0x1c0]`).
   - If active, returns `1` (hostile/vetoed).
2. **Tech & AI Embargo Check**:
   - Calls `0x004A7500` (`CCountry::HasTechEmbargoAgainst`, checking `[CCountry + 0x120 + 0x204]`).
   - If active, returns `1` (hostile/vetoed).
3. **War Matrix Relation Check**:
   - Dereferences master's relation array `ecx = [master + 0x12da]`.
   - Checks active war byte at `[ecx + (11 * tag + 11) * 4]`.
   - If non-zero, returns `1` (hostile/vetoed).
4. Returns `0` (clear to trade) if none of the above apply.

### 4. Unified Puppet Trade Verification (`fn_is_puppet_trade_blocked` at `0x007E2DB0`)
- **Mode 0**: Strictly enforces vanilla master-only trade restriction.
- **Mode 1**: Always allows bilateral trade regardless of puppet status (standard war checks apply).
- **Mode 2**: Allows bilateral trade, but checks `fn_is_master_hostile` reciprocally:
  - Actor's Master against Target nation.
  - Target's Master against Actor nation.
  - If either master is hostile/embargoing/at war, trade is blocked.

### 5. Hook Call Sites
- **`0x004A16E9` (Case 0x12 `DIP_OFFER_TA`)** -> Trampoline at `0x007E2EA0`.
- **`0x004A179F` (Case 0x15 `DIP_TRADE`)** -> Trampoline at `0x007E2EC0`.
- **`0x0061D84B` & `0x0061D941` (`CDiplomacyDialog` Tooltips)** -> Trampolines at `0x007E2EE0` / `0x007E2F10`.
- **`0x0067B384` & `0x0067C784` (AI Trade Evaluation)** -> Trampolines at `0x007E2F40` / `0x007E2F60`.
- **`0x0044EB39` (`CalculateTradeEfficiencies`)** -> Trampoline at `0x007E2F90` (eliminates hardcoded 0% puppet trade efficiency).

---

## Summary of Implemented Changes

1. **Configurable Trade Policy via `mod_settings.ini`**:
   - Added support for `AllowPuppetTrade = 0 | 1 | 2` under `[Diplomacy]` in `mod_settings.ini`.
   - Preserves complete backwards compatibility with vanilla Darkest Hour executables.
2. **Dual-Embargo & War Veto Engine Logic**:
   - Identified and resolved the distinction between Trade Embargoes (`0x004A74E0`, `+0x1c0`) and Tech/AI Embargoes (`0x004A7500`, `+0x204`).
   - Implemented `fn_is_master_hostile` with caller register preservation (`ebp`, stack alignment) preventing CTDs from volatile register clobbers.
   - Master veto strictly enforced reciprocally: puppets cannot trade if their master embargoes the target or is at war with the target, nor if the target's master embargoes or is at war with the puppet.
3. **Trade Efficiency Pipeline Fix**:
   - Replaced vanilla hardcoded 0% puppet trade efficiency lock at `0x0044EB39` (`CCountry::CalculateTradeEfficiencies`).
   - Valid trade deals involving puppet states now compute normal land and convoy trade effectiveness.
4. **Unified Automation & Patcher Integration**:
   - Updated `patch_darkest_hour.bat` in both root and `tools/` with Patch 4 support.
   - Script supports `-Apply`, `-Revert`, `-Verify`, and interactive menu modes with full SHA256 integrity checks.

---

## File Deliverables

1. [mod_settings.ini](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/mod_settings.ini):
   - Created in game root and mod folders with `AllowPuppetTrade = 2`.
2. [patch_darkest_hour.bat](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/patch_darkest_hour.bat):
   - Unified multi-patch script managing all 4 game engine fixes.
3. [engine_internals_reference.md](file:///e:/Program%20Files%20(x86)/Steam/steamapps/common/Darkest%20Hour%20A%20HOI%20Game/Mods/E3mapToDHFull/docs/engine_internals_reference.md):
   - Comprehensive technical documentation of the diplomacy, embargo, trade efficiency, and puppet systems.
4. `Darkest Hour.exe` & `Darkest Hour_modified.exe`:
   - Patched executables verified with SHA256 `F1F9CC84C3A6FECDAE587F9C90D48B377CCC4FC9CC020617571DC7B24A41BA7E`.
