# Darkest Hour Engine Architecture & Reverse Engineering Reference

**Target Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour.exe` (Size: `4,730,956` bytes, Image Base: `0x00400000`, Vanilla Checksum: `TENE`)  
**Scope**: Master architectural index, memory navigation hub, and documentation directory for Darkest Hour engine internals, vanilla simulation models, and custom binary modifications.

---

## Document Organization & Structure

To ensure modularity and clean separation between unmodified retail mechanics and custom modding innovations, the technical documentation is divided into two primary directories:

```
docs/
+-- engine_internals_reference.md   <-- Master Index & Navigation Hub (This File)
+-- engine/                         <-- Vanilla Engine Architecture Reference
|   +-- README.md                   <-- Category Index & Guide Map
|   +-- architecture_and_memory.md  <-- PE sections, alignment, checksum, simulation tick
|   +-- data_structures.md          <-- Global tables, country enum, in-memory structs
|   +-- subsystems_and_calling.md   <-- MSVC ABI, calling conventions, key function directory
|   +-- reverse_engineering_tools.md<-- x32dbg, Ghidra, UI automation, code caves
|   +-- garrison_ai.md              <-- UpdateGarrisons formulas, threat scaling, quotas
|   +-- diplomacy.md                <-- 28 diplo actions, queue model, embargoes, trade eff
|   +-- straits.md                  <-- The 5 hardcoded straits, single-controller, Bosphorus exception
+-- plans/                          <-- Custom Engine Modifications & Binary Patches
|   +-- README.md                   <-- Master Patch Catalog & Verification Matrix
|   +-- plan_unit_control_transfer.md   <-- Patch 1: Peacetime Front Leader Recognition
|   +-- plan_garrison_overseas_dispatch.md <-- Patch 2: Garrison AI Overseas Dispatch
|   +-- plan_wartime_rear_area_cap.md   <-- Patch 3: Garrison AI Rear Area Cap & Cave Restore
|   +-- plan_puppet_trade.md            <-- Patch 4: Configurable Puppet Trade & Master Veto
|   +-- plan_checksum_sync.md           <-- Patch 5: Checksum Sync for mod_settings.ini
|   +-- plan_custom_straits.md          <-- Patch 6: Configurable Dynamic Straits System
|   +-- plan_black_sea_naval_trade.md   <-- Patch 6 Ext: Montreux Naval Trade Prohibition
|   +-- plan_large_address_aware.md     <-- Patch 7: Large Address Aware (LAA) 4GB Flag
|   +-- plan_scenario_memory_leak_patch.md <-- Patch 8: Scenario Unload Deallocation Cave
```

---

## 1. Vanilla Engine Reference Library (`docs/engine/`)

The [`docs/engine/`](engine/README.md) directory documents the unmodified retail behavior, runtime memory models, and execution architecture of Darkest Hour 1.05.2:

| Modular Guide | Focus Area | Key Topics Covered |
|---|---|---|
| **[`architecture_and_memory.md`](engine/architecture_and_memory.md)** | Binary Architecture | PE section mapping (`.text`, `.rdata`, `.data`, `.rsrc`), checksum generation (`FUN_0042E3D0`), 16-byte function alignment, local code caves, and simulation tick loops. |
| **[`data_structures.md`](engine/data_structures.md)** | Data Structures & Tables | Pointer arrays (`DAT_00DC0FD4`, `DAT_0089CAD8`, `pDateStruct`), universal Country Tags enum, `Country`, `CGarrisonAI`, `CFront`, `CArmy`, and singly-linked list traversal. |
| **[`subsystems_and_calling.md`](engine/subsystems_and_calling.md)** | Subsystems & Calling ABI | MSVC x86 ABI rules (caller-saved `EAX/ECX/EDX` vs callee-saved `EBX/ESI/EDI/EBP`), `__thiscall`/`__cdecl`/`__fastcall`, and directory of 21+ key engine routines. |
| **[`reverse_engineering_tools.md`](engine/reverse_engineering_tools.md)** | Debugging & Tool Workflows | x32dbg automation via x64dbg MCP, Ghidra MCP static workflows, the DirectDraw desktop deadlock trap, static 1024x768 UI coordinates, and trampoline splicing. |
| **[`garrison_ai.md`](engine/garrison_ai.md)** | Garrison AI Mechanics | In-depth formulas for `CGarrisonAI::UpdateGarrisons` (`0x0068BA50`), emergency homeland collapse triggers, wartime threat scaling, the rear-area / 2 "invisible factor", and province priority allocation. |
| **[`diplomacy.md`](engine/diplomacy.md)** | Diplomacy Subsystem | Deterministic command queue, complete catalog of all 28 hardcoded diplomatic actions, embargo storage offsets (`+0x1C0`, `+0x204`), vanilla puppet trade constraints, and the bilateral trade efficiency pipeline (`m_TradeEfficiency`). |
| **[`straits.md`](engine/straits.md)** | Naval Straits (Vanilla) | The 5 hardcoded vanilla straits in machine code (`FUN_004ed1c0`), single-controller limitation, province 397 (Bosphorus) exception, and engine limitations. |

---

## 2. Custom Engine Modifications & Binary Patches (`docs/plans/`)

All custom behavioral modifications, binary hooks, and engine enhancements compared to the retail release are isolated in [`docs/plans/`](plans/README.md).

### Master Patch Matrix

| Patch # | Feature | Hook Site | Cave Location | Configuration Key | Plan Document |
|---|---|---|---|---|---|
| **Patch 1** | Peacetime Front Leader Recognition | `0x004CCB2C` (`0x000CCCB6`) | `0x007E2FB3` | `AllowExpForcesToPlayers` | [`plan_unit_control_transfer.md`](plans/plan_unit_control_transfer.md) |
| **Patch 2** | Garrison AI Overseas Dispatch | `0x00695593` (`0x00295593`) | `0x007E2FCA` | `AllowExpForcesToPlayers` | [`plan_garrison_overseas_dispatch.md`](plans/plan_garrison_overseas_dispatch.md) |
| **Patch 3** | Garrison AI Wartime Rear Area Cap | `0x006955E5` (`0x002955E5`) | Inline (11 bytes) | N/A | [`plan_wartime_rear_area_cap.md`](plans/plan_wartime_rear_area_cap.md) |
| **Patch 4** | Configurable Puppet Trade & Master Veto | `0x004A16E9`, `0x004A179F` | `0x007E2DB0` - `0x007E2F90` | `AllowPuppetTrade` | [`plan_puppet_trade.md`](plans/plan_puppet_trade.md) |
| **Patch 5** | Checksum Sync for `mod_settings.ini` | `0x0042E710` (`0x0002E710`) | Inline (72 bytes) | Automatic | [`plan_checksum_sync.md`](plans/plan_checksum_sync.md) |
| **Patch 6** | Configurable Dynamic Straits System | `0x0058444F`, `0x005846B0` | `0x007E4400` / `0x00DC9000` | `EnableCustomStraits` | [`plan_custom_straits.md`](plans/plan_custom_straits.md) |
| **Patch 6 Ext** | Montreux Naval Trade Prohibition | `0x005FD41C` (`0x001FD41C`) | `0x00DCA100` (.mod cave) | `local_flags = { black_sea_power = 1 }` | [`plan_black_sea_naval_trade.md`](plans/plan_black_sea_naval_trade.md) |
| **Patch 7** | Large Address Aware (LAA) Flag | PE Header `0x00000116` | Bit `0x20` | N/A (PE Flag) | [`plan_large_address_aware.md`](plans/plan_large_address_aware.md) |
| **Patch 8** | Scenario Memory Leak Deallocation Cave | `0x0070287B` (`0x0030287B`) | `0x00DCA000` (.mod cave) | Automatic | [`plan_scenario_memory_leak_patch.md`](plans/plan_scenario_memory_leak_patch.md) |

### Automated Patcher Script
All patches above are bundled into the automated deployment script:
- Root Deployment Script: `patch_darkest_hour.bat`
- Mod Tools Script: [`tools/patch_darkest_hour.bat`](../tools/patch_darkest_hour.bat)

---

## 3. Quick Reference: Core Global Pointers

For rapid lookup during debugging sessions in x32dbg or Ghidra:

```c
// Human vs AI status array (1 = Human, 0 = AI):
int is_human = *(int*)(0x00DC0FD4 + country_tag * 4);

// Country structure base pointer:
Country* pCountry = *(Country**)(0x0089CAD8 + country_tag * 4);

// Simulation date structure base pointer:
uint8_t* pDate = *(uint8_t**)(0x00893530) + 0x14;
// pDate[0] = Hour (0..23)
// pDate[1] = Day (0..29)
// pDate[2] = Month (0..11)
// pDate[4..5] = Year (e.g. 1936)

// Active UI formatted clock string:
const char* clock_str = (const char*)0x00D0B68C; // "H:00 Month D, YYYY"

// Checksum accumulator:
uint32_t checksum_accum = *(uint32_t*)0x00893644;
```
