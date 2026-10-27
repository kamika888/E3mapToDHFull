# Darkest Hour Engine Modifications & Patch Plans Index

This directory contains comprehensive architectural documentation, reverse engineering specifications, and binary patch plans for all custom engine modifications introduced compared to the retail release of **Darkest Hour 1.05.2 (checksum TENE)**.

---

## Patch Catalog & Master Matrix

| Patch # | Feature Name | Primary Call Site / Hook | Code Cave / Target | Config Key (`db/mod_settings.ini`) | Documentation |
|---|---|---|---|---|---|
| **Patch 1** | Peacetime Front Leader Recognition | `0x004CCB2C` (`0x000CCCB6`) | `0x007E2FB3` | `AllowExpForcesToPlayers` | [`plan_unit_control_transfer.md`](plan_unit_control_transfer.md) |
| **Patch 2** | Garrison AI Overseas Dispatch | `0x00695593` (`0x00295593`) | `0x007E2FCA` | `AllowExpForcesToPlayers` | [`plan_garrison_overseas_dispatch.md`](plan_garrison_overseas_dispatch.md) |
| **Patch 3** | Garrison AI Rear Area Cap & Cave Restore | `0x006955E5` (`0x002955E5`) | `0x006955E5` (Inline) | N/A | [`plan_wartime_rear_area_cap.md`](plan_wartime_rear_area_cap.md) |
| **Patch 4** | Configurable Puppet Trade & Master Veto | `0x004A16E9`, `0x004A179F` | `0x007E2DB0` - `0x007E2F90` | `AllowPuppetTrade` | [`plan_puppet_trade.md`](plan_puppet_trade.md) |
| **Patch 5** | Checksum Sync for `mod_settings.ini` | `0x0042E710` (`0x0002E710`) | Inline (72 bytes) | Automatic | [`plan_checksum_sync.md`](plan_checksum_sync.md) |
| **Patch 6** | Configurable Dynamic Straits System | `0x0058444F`, `0x005846B0` | `0x007E4400` / `0x00DC9000` | `EnableCustomStraits` | [`plan_custom_straits.md`](plan_custom_straits.md) |
| **Patch 6 Ext** | Black Sea Naval Trade Prohibition | `0x005FD41C` (`0x001FD41C`) | `0x00DCA100` (.mod cave) | `local_flags = { black_sea_power = 1 }` | [`plan_black_sea_naval_trade.md`](plan_black_sea_naval_trade.md) |
| **Patch 7** | Large Address Aware (LAA) Flag | PE Header `0x00000116` | Characteristics bit `0x20` | N/A (PE Flag) | [`plan_large_address_aware.md`](plan_large_address_aware.md) |
| **Patch 8** | Scenario Unload Event Deallocation Cave | `0x0070287B` (`0x0030287B`) | `0x00DCA000` (.mod cave) | Automatic | [`plan_scenario_memory_leak_patch.md`](plan_scenario_memory_leak_patch.md) |
| **Patch 9** | Map Tile High-Memory Signed Comparison Fix | `0x004DB0C5` (`0x000DB0C5`) | `0x000DB0C5` (Inline 1 byte) | Automatic | [`plan_map_tile_high_memory_guard.md`](plan_map_tile_high_memory_guard.md) |
| **Patch 10** | Silent Events for Player Countries | `0x007123CB` (`0x003123CB`) | `0x00DCA200` (.mod cave) | `flag = "ENGINE:SILENT_EVENT"` | [`plan_silent_events.md`](plan_silent_events.md) |
| **Patch 11** | Allied Territory Garrison AI | `0x0068D8B9`, `0x0068C18E`, `0x00693CBD` | `0x00DCA188` - `0x00DCAF90` | `EnableAlliedGarrison`, `GarrisonLandConnectedMultiplier`, `GarrisonWartimeMultiplier` | [`plan_allied_garrison_ai.md`](plan_allied_garrison_ai.md) |

---

## Detailed Plan Summaries

### 1. [Peacetime Front Leader Recognition](plan_unit_control_transfer.md)
Enables human-controlled allied nations to be recognized as Front Leaders during peacetime. Removes the vanilla restriction that prevented human soil from hosting an allied front commander, allowing allied expeditionary forces to transfer operational control to the player on home territory.

### 2. [Garrison AI Overseas Dispatch](plan_garrison_overseas_dispatch.md)
Hooks `CGarrisonAI::FindAlliedFrontNeedingTroops` to permit AI countries (e.g. United Kingdom) to dispatch homeland garrison reserves overseas to defend human allies (e.g. France), while respecting the player's diplomatic refusal toggle (`dont_want_exp_forces`).

### 3. [Garrison AI Wartime Rear Area Cap](plan_wartime_rear_area_cap.md)
Restores and optimizes garrison evaluation logic, capping excessive homeland reserve hoarding during wartime to free up divisions for frontline and overseas theater deployment.

### 4. [Configurable Puppet Trade & Master Veto](plan_puppet_trade.md)
Adds the `AllowPuppetTrade` configuration key with three distinct operational modes:
- `0`: Vanilla master-only trade restriction.
- `1`: Free trade for puppets.
- `2`: Free trade with bilateral Master Veto (puppets respect master trade embargoes, tech embargoes, and war enemies).

### 5. [Checksum Synchronization](plan_checksum_sync.md)
Relocates configuration to `db/mod_settings.ini` and hooks the startup checksum routine (`FUN_0042E3D0`) so any configuration changes alter the four-letter checksum, natively preventing multiplayer desynchronization.

### 6. [Configurable Dynamic Straits System](plan_custom_straits.md)
Replaces the 5 hardcoded vanilla straits with an extensible CSV database (`straits.csv`, up to 64 straits), multi-controller transit checks, a native DHFScript `strait` event command, global flag state persistence, and dynamic natural language UI tooltips.

### 7. [Black Sea Naval Trade Prohibition](plan_black_sea_naval_trade.md)
Enforces the Montreux Convention regime on naval vessel acquisitions in the diplomacy trade interface using Exclusive OR (XOR) logic for nations flagged with `local_flags = { black_sea_power = 1 }`.

### 8. [Large Address Aware (LAA)](plan_large_address_aware.md)
Sets bit `0x0020` in the PE file header, unlocking up to 4 GB of virtual address space on 64-bit systems to eliminate memory exhaustion crashes during heavy scenario loading.

### 9. [Scenario Memory Leak Patch](plan_scenario_memory_leak_patch.md)
Injects an event list deallocation cave at scenario teardown (`0x0070287B`), preventing event and decision memory leaks when returning to the main menu or reloading saves.

### 10. [Map Tile High-Memory Signed Comparison Fix](plan_map_tile_high_memory_guard.md)
Patches the signed comparison branch `JLE` (`7E 02`) to unsigned `JBE` (`76 02`) in `FUN_004dafb0` (`0x004DB0C5`), preventing out-of-bounds pointer underruns in high virtual memory ($\ge 0\text{x}80000000$) from bypassing validation and dereferencing invalid province structures.

### 11. [Silent Events for Player-Controlled Countries](plan_silent_events.md)
Executes scripted maintenance events silently in the background for human players without displaying modal dialog windows or pausing the simulation, using the positive trigger marker `OR = { flag = "ENGINE:SILENT_EVENT" random = 100 }` to ensure 100% graceful dual compatibility with unmodified retail binaries.

### 12. [Allied Territory Garrison AI](plan_allied_garrison_ai.md)
Enables AI countries to station, reinforce, and withdraw troops inside allied and military-access territory based on `country_priorities`, `province_priorities`, and `area_multiplier`. Implements a multi-area allied iterator, configurable land-connected and wartime multipliers (`GarrisonLandConnectedMultiplier`, `GarrisonWartimeMultiplier`), destination-aware en-route overland unit counting, foreign surplus capital repatriation, target-aware army distribution and peacetime repatriation filters, and Phase 4 overseas maritime transport dispatch with `CInvasionAI` dangling-pointer protection.

---

## Automated Deployment

All modifications documented above are compiled into the automated deployment script:
- Mod Root: [`tools/patch_darkest_hour.bat`](../../tools/patch_darkest_hour.bat)
- Game Root: `patch_darkest_hour.bat`

