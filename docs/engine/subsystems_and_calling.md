# Darkest Hour Subsystems & Calling Conventions

**Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour.exe`  
**Scope**: Calling conventions, register preservation rules, ABI requirements, and core engine routine directory.

---

## 1. Calling Conventions & Register Preservation Rules

Darkest Hour is compiled with Microsoft Visual C++ for 32-bit x86 Little-Endian architecture. Understanding register preservation is critical when analyzing code or constructing hooks.

### 1.1 Standard Register Roles (x86 MSVC ABI)
- **Scratch / Caller-Saved Registers**: `EAX`, `ECX`, `EDX`
  - Any function or hook may freely overwrite these registers.
  - If a caller requires these values across a call, it must push them to the stack beforehand.
- **Non-Volatile / Callee-Saved Registers**: `EBX`, `ESI`, `EDI`, `EBP`, `ESP`
  - **MUST** be preserved across all function calls and hooks.
  - If modified within a hook or subroutine, they must be saved (`push`) upon entry and restored (`pop`) prior to return or jump back.
  - Violating register preservation on `EBX`, `ESI`, or `EDI` causes immediate simulation corruption, heap crashes, or desynchronizations.

### 1.2 Calling Conventions Used in Darkest Hour

| Calling Convention | `this` Pointer | Argument Order | Stack Cleanup | Usage in Engine |
|---|---|---|---|---|
| `__thiscall` | `ECX` | Right-to-Left on Stack | Callee (`ret N`) | Primary C++ member functions (Country, Army, Front, Dialogs) |
| `__cdecl` | None | Right-to-Left on Stack | Caller (`add esp, N`) | C runtime functions (`sprintf`, `fopen`), variable-arg methods |
| `__stdcall` | None | Right-to-Left on Stack | Callee (`ret N`) | Win32 API callbacks, Windows subsystem imports |
| `__fastcall` | `ECX`, `EDX` | In registers, rest on Stack | Callee (`ret N`) | Optimized internal AI helpers (`CGarrisonAI::FindAlliedFront...`) |

---

## 2. Key Engine Function Directory

| Routine | Virtual Address | Calling Conv. | Class / Module | Purpose |
|---|---|---|---|---|
| `Front::GetLeadingCountry` | `0x004CCB2C` | `__thiscall` | `CFront` | Evaluates which nation controls a front; governs peacetime transfer of control |
| `CanPerformDiplomacyAction` | `0x004A1110` | `__thiscall` | `CCountry` | Master validation switch evaluating whether a diplomatic action is legal |
| `ExecuteDiplomacyAction` | `0x0049ED10` | `__thiscall` | `CCountry` | Dispatches and executes confirmed diplomatic action packets |
| `CalculateTradeEfficiencies` | `0x0044E800` | `__thiscall` | `CCountry` | Calculates daily 0.0 - 1.0 bilateral trade efficiency for all countries |
| `IsStraitBlocked` | `0x005846B0` | `__cdecl` | Map / Naval | Evaluates whether a naval passage / strait is impassable to a nation |
| `CScriptParser::LookupToken` | `0x005342C0` | `__thiscall` | `CScriptParser` | Main scenario/event lexer resolving text tokens into integer token IDs |
| `LookupTokenDirect` | `0x00534350` | `__thiscall` | `CScriptParser` | Fast direct token lookup |
| `CScriptParser::GetFlag` | `0x00533C50` | `__thiscall` | `CScriptParser` | Queries runtime value of an engine global flag (`[0x00D77B70]`) |
| `CScriptParser::SetFlag` | `0x00533CD0` | `__thiscall` | `CScriptParser` | Sets or alters runtime value of an engine global flag |
| `HasTradeEmbargoAgainst` | `0x004A74E0` | `__thiscall` | `CCountry` | Checks if actor has an active trade embargo against target (`+0x1C0`) |
| `HasTechEmbargoAgainst` | `0x004A7500` | `__thiscall` | `CCountry` | Checks if actor has an active tech embargo against target (`+0x204`) |
| `FindAlliedFrontNeedingTroops`| `0x00695520` | `__fastcall` | `CGarrisonAI` | Traverses allied countries to identify front reinforcement deficits |
| `UpdateGarrisons` | `0x0068BA50` | `__thiscall` | `CGarrisonAI` | Top-level hourly/daily garrison evaluation and division quota dispatch |
| `CAITransportMinister::DispatchArmy` | `0x00696EF0` | `__thiscall` | `CAITransport` | Schedules transport lift, boarding orders, and port navigation for armies |
| `TransferUnitControl` | `0x006939F0` | `__thiscall` | Unit Manager | Performs real-time unit operational handover to host allied territory |
| `CGarrisonAI::GetTag` | `0x006A9D50` | `__fastcall` | `CGarrisonAI` | Helper extracting donor country tag from `[this + 0x0A] + 0x06` |
| `Front::IsValid` | `0x004CA33C` | `__thiscall` | `CFront` | Validates whether a front is active and suitable for reinforcement |
| `Front::CalcDeficit` | `0x00695380` | `__thiscall` | `CFront` | Calculates numerical division deficit relative to opposing enemy forces |
| `CScriptParser::LookupFlag` | `0x006C5280` | `__cdecl` | `CScriptParser` | Queries associative `local_flags` map (`Country + 0x1183E`) |
| `Checksum::CalcTotal` | `0x0042E3D0` | `__cdecl` | Checksum | Iterates ~35 core files and accumulates global 4-letter checksum |
| `Checksum::CalcFile` | `0x0042E2C0` | `__cdecl` | Checksum | Computes signed byte sum of an individual database file |

