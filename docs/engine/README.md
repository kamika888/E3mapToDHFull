# Darkest Hour Engine Architecture & Reverse Engineering Reference Library

**Target Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour.exe` (Size: `4,730,956` bytes, Image Base: `0x00400000`, Vanilla Checksum: `TENE`)  
**Scope**: Authoritative reference library documenting the unmodified retail engine architecture, memory layouts, simulation subsystems, calling conventions, and reverse engineering workflows.

---

## Modular Category Guides

This reference library is divided into specialized modular guides:

### 1. [Binary Format & Memory Model](architecture_and_memory.md)
* PE file structure, vanilla sections (`.text`, `.rdata`, `.data`, `.rsrc`), custom injected `.mod` section, and virtual memory mapping.
* Checksum calculation pipeline and executable universality across mods.
* MSVC compiler ABI, 16-byte function alignment, and code cave discovery patterns.
* Simulation tick architecture (hourly loop and midnight daily update).

### 2. [Core Data Structures & Global Tables](data_structures.md)
* Primary engine pointer tables (`DAT_00dc0fd4`, `DAT_0089cad8`, `pDateStruct`, `TokenTable`).
* Universal internal Country Tags enumeration compiled into `FUN_004ab800`.
* In-memory structure definitions: `Country`, `CGarrisonAI`, `CFront`, `CArmy`, and `Date/Time`.
* Singly-linked list traversal patterns used across simulation objects.

### 3. [Subsystems & Calling Conventions](subsystems_and_calling.md)
* Standard MSVC x86 ABI: Caller-saved (`EAX`, `ECX`, `EDX`) vs Callee-saved (`EBX`, `ESI`, `EDI`, `EBP`, `ESP`).
* Calling conventions in the engine: `__thiscall`, `__cdecl`, `__stdcall`, `__fastcall`.
* Comprehensive directory of core engine routines, virtual addresses, parameter signatures, and purposes.

### 4. [Reverse Engineering Workflows & Automation](reverse_engineering_tools.md)
* Dynamic debugging workflows in x32dbg via the x64dbg MCP.
* Static analysis with Ghidra MCP (decompilation, xref analysis, function tagging).
* Windows UI automation pitfalls and avoiding the DirectDraw message pump deadlock trap.
* Static UI coordinate reference for 1024x768 windowed execution.
* Binary instrumentation patterns: short jumps, 5-byte near jumps, and code cave trampolines.

### 5. [Garrison AI Architecture & Formulas](garrison_ai.md)
* Detailed mathematical breakdown of `CGarrisonAI::UpdateGarrisons` (`0x0068BA50`).
* Base province counting, emergency homeland defense collapse check, and geometry modifiers.
* Wartime threat scaling: front area enemy border concentration and the rear-area "invisible factor" ($\div 2$).
* Reinforcement dispatch priority queue and province-level allocation within areas.

### 6. [Diplomacy Subsystem & Command Architecture](diplomacy.md)
* Deterministic command queue and packet serialization model (`CCountry::ExecuteDiplomacyAction`).
* Complete catalog and analysis of all 28 hardcoded diplomatic actions and unused legacy strings.
* Embargo data structures (`+0x1C0`, `+0x204`) and verification routines.
* Vanilla puppet trade restrictions and the 0.0 - 1.0 bilateral trade efficiency pipeline (`m_TradeEfficiency`).

### 7. [Naval Straits Subsystem (Vanilla)](straits.md)
* The 5 hardcoded vanilla straits in machine code (Gibraltar, Suez, Panama, Danish Belts, Bosphorus).
* Movement evaluation pipeline in `IsStraitBlocked` (`FUN_004ed1c0` @ `0x004ED1C0`).
* Province 397 (Bosphorus) hardcoded allied-only exception and single-controller limitations.

### 8. [Map & Lightmap Engine](map_and_lightmap_engine.md)
* Coordinate system, $32 \times 32$ tile grid, and $29,952 \times 11,520$ E3 map dimensions.
* Zoom level indexing (`DAT_00a98464`), `lightmap1.tbl` to `lightmap4.tbl` scale factors.
* Binary archive layout, 16-bit header word packing, and 6-bit province reference bitfield.
* Root cause specification of the 60-entry tile header limit and access violation crash at `0x004DB0DF`.
* Complete mod audit of 17 failing tiles in `lightmap3.tbl`.

---

## Custom Engine Modifications & Patch Plans

For custom engine modifications, binary hooks, and behavioral patches introduced compared to retail release, consult the dedicated plans in:
* **[Custom Modifications & Patch Plans Index](../plans/README.md)**

