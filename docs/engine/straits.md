# Darkest Hour Naval Straits Subsystem (Vanilla Engine)

**Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour_original.exe` / `Darkest Hour.exe`  
**Primary Routine**: `IsStraitBlocked` (`FUN_004ed1c0` at `0x004ED1C0`, File Offset: `0x000ED1C0`)  
**Scope**: Native retail straits architecture, the 5 hardcoded straits, single-controller limitation, province 397 allied-only exception, and UI tooltip generation.

---

## 1. Overview & Vanilla Architecture

In the unmodified retail release of Darkest Hour (`Darkest Hour_original.exe`), naval passage through strategic chokepoints is **not** managed by a data file or dynamic table. Instead, it is governed by **five hardcoded conditional branches** compiled directly into machine code inside `FUN_004ed1c0` (`0x004ED1C0`).

When a naval formation or convoy plans movement through a sea province, the pathfinder calls `IsStraitBlocked(CProvince* prov, Country* country)`:
- If the sea province matches one of the five hardcoded IDs, the engine queries the current controller of a single hardcoded land province and tests diplomatic status.
- Any sea province not matching one of the five hardcoded IDs falls through and is unconditionally treated as open, passable water (`return 0`).

---

## 2. The 5 Hardcoded Vanilla Straits

Disassembly of the vanilla evaluation function at `0x004ED1C0`:

```x86asm
; IsStraitBlocked(CProvince* prov, Country* country)
004ED1C0: 8B 41 12             mov eax, [ecx + 0x12]         ; eax = sea province ID

; 1. Gibraltar (Sea Prov 2430 / 0x097E)
004ED1C3: 3D 7E 09 00 00       cmp eax, 0x97E                ; Sea Prov == 2430?
004ED1C8: 75 25                jne check_suez
004ED1CA: A1 B4 27 AB 00       mov eax, [0x00AB27B4]         ; Province database pointer
004ED1CF: 8B 88 D0 65 06 00    mov ecx, [eax + 0x665D0]      ; Land Prov 348 (Gibraltar) controller
004ED1D5: 85 C9                test ecx, ecx
004ED1D7: 74 79                je passable
004ED1D9: 8B 54 24 04          mov edx, [esp + 4]            ; Target Country*
004ED1DD: 8B 42 06             mov eax, [edx + 6]            ; Target Country tag
004ED1E0: 50                   push eax
004ED1E1: E8 9A E0 F5 FF       call 0x0044B280               ; IsAtWar(controller, target_tag)
004ED1E6: 84 C0                test al, al
004ED1E8: 74 68                je passable
004ED1EA: B0 01                mov al, 1                     ; BLOCKED (return 1)
004ED1EC: C2 04 00             ret 4

; 2. Suez Canal (Sea Prov 2453 / 0x0995)
check_suez:
004ED1EF: 3D 95 09 00 00       cmp eax, 0x995                ; Sea Prov == 2453?
004ED1F4: 75 0D                jne check_panama
004ED1F6: A1 B4 27 AB 00       mov eax, [0x00AB27B4]
004ED1FB: 8B 88 A0 85 10 00    mov ecx, [eax + 0x1085A0]     ; Land Prov 900 (Suez) controller
004ED201: EB D2                jmp 0x004ED1D5                ; Test IsAtWar

; 3. Panama Canal (Sea Prov 2575 / 0x0A0F)
check_panama:
004ED203: 3D 0F 0A 00 00       cmp eax, 0xA0F                ; Sea Prov == 2575?
004ED208: 75 0D                jne check_belts
004ED20A: A1 B4 27 AB 00       mov eax, [0x00AB27B4]
004ED20F: 8B 88 FA 51 10 00    mov ecx, [eax + 0x1051FA]     ; Land Prov 889 (Colon) controller
004ED215: EB BE                jmp 0x004ED1D5                ; Test IsAtWar

; 4. Danish Belts / Oresund (Sea Prov 290 / 0x0122)
check_belts:
004ED217: 3D 22 01 00 00       cmp eax, 0x122                ; Sea Prov == 290?
004ED21C: 75 0D                jne check_bosphorus
004ED21E: A1 B4 27 AB 00       mov eax, [0x00AB27B4]
004ED223: 8B 88 44 68 05 00    mov ecx, [eax + 0x056844]     ; Land Prov 294 (Copenhagen) controller
004ED229: EB AA                jmp 0x004ED1D5                ; Test IsAtWar

; 5. Bosphorus / Dardanelles (Sea Prov 397 / 0x018D)
check_bosphorus:
004ED22B: 3D 8D 01 00 00       cmp eax, 0x18D                ; Sea Prov == 397?
004ED230: 75 20                jne passable                  ; None of the 5 -> Open water
004ED232: A1 B4 27 AB 00       mov eax, [0x00AB27B4]
004ED237: 8B 88 3A 84 07 00    mov ecx, [eax + 0x07843A]     ; Land Prov 409 (Istanbul) controller
004ED23D: 85 C9                test ecx, ecx
004ED23F: 74 11                je passable
004ED241: 8B 54 24 04          mov edx, [esp + 4]
004ED245: 8B 42 06             mov eax, [edx + 6]
004ED248: 50                   push eax
004ED249: E8 42 D4 F5 FF       call 0x0044A690               ; CanCooperate / IsAllied
004ED24E: 84 C0                test al, al
004ED250: 74 98                je 0x004ED1EA                 ; NOT allied -> BLOCKED

passable:
004ED252: 32 C0                xor al, al                    ; PASSABLE (return 0)
004ED254: C2 04 00             ret 4
```

### 2.1 Summary of the 5 Vanilla Straits

| # | Strait Name | Sea Province ID (Hex / Dec) | Controlling Land Province | Passage Rule Enforced |
|---|---|---|---|---|
| **1** | **Gibraltar** | `0x097E` / `2430` | `348` (Gibraltar) | Blocked if at war with controller (`IsAtWar`) |
| **2** | **Suez Canal** | `0x0995` / `2453` | `900` (Suez) | Blocked if at war with controller (`IsAtWar`) |
| **3** | **Panama Canal** | `0x0A0F` / `2575` | `889` (Colon) | Blocked if at war with controller (`IsAtWar`) |
| **4** | **Danish Belts** | `0x0122` / `290` | `294` (Copenhagen) | Blocked if at war with controller (`IsAtWar`) |
| **5** | **Bosphorus** | `0x018D` / `397` | `409` (Istanbul) | Blocked unless allied to controller (`CanCooperate`) |

---

## 3. Movement Check Pipeline Flowchart

```
                 [Naval Movement / Pathfinder Request]
                                   |
                                   v
                       IsStraitBlocked(prov, country)
                                   |
            +----------------------+----------------------+
            |                                             |
   [Sea Prov in {2430, 2453, 2575, 290}]         [Sea Prov == 397?]
            |                                             |
     (Normal Straits)                            (Bosphorus Exception)
            |                                             |
  At war with Land Controller?               Is nation Allied to Turkey?
        /          \                                  /          \
      Yes          No                               Yes          No
       |            |                                |            |
    BLOCKED      Passable                         Passable     BLOCKED
   (Return 1)   (Return 0)                       (Return 0)   (Return 1)
```

---

## 4. The Bosphorus Hardcoded Exception (Province 397)

In the unmodified retail engine, the Bosphorus (`397`) was the **only** strait subject to restricted transit:
1. **Movement Check Branch (`0x004ED249`)**:
   - Calls `0x0044A690` (`CanCooperate / IsAllied`). If the passing nation is not allied to the controller of Istanbul, transit is rejected.
2. **Hardcoded Tooltip Formatter (`0x005EC5CE`)**:
   - Explicitly checked `cmp word ptr [esi+0x00], 0x18D` (`397`).
   - Appended localized string `STRAIT_BOS` (*"Please note that the Bosphorus is an Allied-only strait..."*).
   - No other strait could utilize allied-only behavior or custom localized explanations.

---

## 5. Architectural Limitations of the Vanilla Engine

1. **Strictly 5 Hardcoded Straits**: Only provinces 2430, 2453, 2575, 290, and 397 were recognized. Any other strategic waterway (e.g. Bab el-Mandeb, Strait of Hormuz, Malacca, Kiel Canal, Kerch Strait) could **never** block ships in vanilla, regardless of map scripting.
2. **Single-Controller Limitation**: The engine only inspected a single hardcoded province offset per strait:
   - Gibraltar inspected only province `348` (Gibraltar), completely ignoring `Ceuta`.
   - Suez inspected only province `900` (Suez), completely ignoring `Port Said`.
   - Danish Belts inspected only `294` (Copenhagen), ignoring `Odense` or Swedish territory.
   - Bosphorus inspected only `409` (Istanbul), ignoring `Canakkale` or `Bursa`.
3. **No Scripting Support**: No native commands or triggers existed to open, close, or toggle strait passage dynamically during gameplay.
4. **Immutability**: Rules could not be configured via text files or mod databases.

---

## 6. Dynamic Replacement System (Patch 6)

To completely eliminate these hardcoded constraints, Patch 6 hooks `0x004ED1C0` and replaces the 5 hardcoded branches with a dynamic, table-driven architecture:
- Loads definitions from `db/straits.csv` and `map/<Map>/straits.csv`.
- Expands capacity from 5 to **64 straits**.
- Supports up to **4 controlling land provinces** per strait with boolean blocker precedence.
- Introduces native DHFScript `command = { type = strait which = <id> value = <val> }`.
- Integrates natural language multi-province UI tooltip grammar and controller deduplication.

For complete implementation specifications, see:
* **[Patch 6 Plan: Configurable & Dynamic Straits System](../plans/plan_custom_straits.md)**
