# Patch 6 Extension: Montreux Convention Black Sea Naval Trade Prohibition

**Status**: Implemented & Verified  
**Engine**: Darkest Hour 1.05.2 (TENE)  
**Target File**: `Darkest Hour.exe` (File Offset: `0x001FD41C`, Virtual Address: `0x005FD41C`, Cave: `0x00DCA100`)  
**Patch Category**: Diplomacy & Naval Trade Restrictions  

---

## 1. Overview & Historical Motivation

Under the **Montreux Convention Regarding the Regime of the Straits (1936)**, strict limitations were placed on the naval composition of Black Sea powers and the transit of warships. A fundamental pillar of this convention is that non-Black Sea powers cannot transfer warships into the Black Sea, nor can Black Sea powers acquire or sell naval vessels across the straits from external powers.

In vanilla Darkest Hour, the diplomatic **Open Negotiations** (Trade) screen allows any two nations at peace to trade military units (including capital ships, submarines, and transports), provided they have diplomatic relations. This enabled ahistorical exploits, such as Romania or Bulgaria purchasing large battle fleets from Germany or Italy, circumventing the Montreux regime.

This engine modification integrates an automated, bilateral naval trade filter directly into the diplomacy unit-selection interface.

---

## 2. Diplomatic Rule: Exclusive OR (XOR) Prohibition

The trade prohibition operates on an **Exclusive OR (XOR)** principle based on national status:

$$\text{Prohibit Naval Trade} \iff \text{IsBlackSeaPower}(\text{Buyer}) \neq \text{IsBlackSeaPower}(\text{Seller})$$

| Buyer | Seller | Trade Permitted? | Rationale |
|---|---|---|---|
| Black Sea Power | Non-Black Sea Power | **PROHIBITED** | External warship acquisition into Black Sea blocked |
| Non-Black Sea Power | Black Sea Power | **PROHIBITED** | Warship sale from Black Sea to external power blocked |
| Black Sea Power | Black Sea Power | **PERMITTED** | Intra-Black Sea naval transfers permitted (e.g. Turkey <-> USSR) |
| Non-Black Sea Power | Non-Black Sea Power | **PERMITTED** | Standard foreign naval trade proceeds normally (e.g. UK <-> France) |

### Non-Naval Units
- **Land Units** (Types `0` to `11`): Always tradeable regardless of Black Sea status.
- **Air Units** (Types `12` to `20`, and `32`): Always tradeable regardless of Black Sea status.

---

## 3. Country Identification via `local_flags`

Rather than relying on hardcoded tag lists (e.g., `TUR`, `SOV`, `BUL`, `ROM`), the engine dynamically inspects the country's local script flags:

```dhfscript
local_flags = {
    black_sea_power = 1
}
```

- Any country with `black_sea_power = 1` in its `local_flags` (defined in scenario files or toggled via `set_local_flag` in events) is dynamically treated as a Black Sea power.
- If a nation loses its Black Sea coastline or signs a treaty modifying its status, clearing or setting the local flag immediately alters trade behavior without executable changes.

---

## 4. Binary Hook Architecture & Memory Layout

### 4.1 Hook Site (`0x005FD41C`, File Offset `0x001FD41C`)
Inside `FUN_005fce40` (the diplomacy dialog function populating available units for the trade offer list):
- Replaces 6 bytes (`mov eax, [esi + 0x88]`) with:
  ```x86asm
  005FD41C: E9 DF CC 7C 00    jmp 0x00DCA100                ; Jump to Black Sea Trade Cave
  005FD421: 90                nop
  ```

### 4.2 Code Cave Implementation (`0x00DCA100`, File Offset `0x00485100`)
Located in the `.mod` section across 136 bytes:

```x86asm
; Preserve working registers
00DCA100: 50                   push eax
00DCA101: 51                   push ecx
00DCA102: 52                   push edx

; 1. Check Division Type (Naval = 21..31)
00DCA103: 8B 46 14             mov eax, [esi + 0x14]         ; eax = division type
00DCA106: 83 F8 15             cmp eax, 21                   ; type < 21?
00DCA109: 7C 75                jl allowed                    ; land / air -> allow trade
00DCA10B: 83 F8 1F             cmp eax, 31                   ; type > 31?
00DCA10E: 7F 70                jg allowed                    ; non-naval -> allow trade

; 2. Resolve Buyer and Seller Country Structs
00DCA110: 8B 4D EC             mov ecx, [ebp - 0x14]         ; ecx = Buyer Country*
00DCA113: 8B 55 E8             mov edx, [ebp - 0x18]         ; edx = Seller Country*

; 3. Query local_flag "black_sea_power" on Buyer
00DCA116: 52                   push edx                      ; save Seller
00DCA117: 68 00 A0 DC 00       push 0x00DCA000               ; "black_sea_power\0"
00DCA11C: 81 C1 3E 18 01 00    add ecx, 0x1183E              ; ecx = Buyer local_flags map
00DCA122: E8 59 B1 8F FF       call 0x006C5280               ; LookupFlag(map, name)
00DCA127: 85 C0                test eax, eax
00DCA129: 0F 95 C2             setne dl                      ; dl = Buyer is BSP (0 or 1)
00DCA12C: 59                   pop ecx                       ; restore Seller to ecx
00DCA12D: 52                   push edx                      ; save dl (Buyer status)

; 4. Query local_flag "black_sea_power" on Seller
00DCA12E: 68 00 A0 DC 00       push 0x00DCA000               ; "black_sea_power\0"
00DCA133: 81 C1 3E 18 01 00    add ecx, 0x1183E              ; ecx = Seller local_flags map
00DCA139: E8 42 B1 8F FF       call 0x006C5280               ; LookupFlag(map, name)
00DCA13E: 85 C0                test eax, eax
00DCA140: 0F 95 C0             setne al                      ; al = Seller is BSP (0 or 1)
00DCA143: 5A                   pop edx                       ; edx = Buyer is BSP

; 5. Evaluate XOR Condition
00DCA144: 38 C2                cmp dl, al                    ; dl == al?
00DCA146: 74 38                je allowed                    ; both BSP or neither BSP -> allow

; 6. Prohibited: Skip Division
00DCA148: 5A                   pop edx
00DCA149: 59                   pop ecx
00DCA14A: 58                   pop eax
00DCA14B: E9 4D 34 83 FF       jmp 0x005FD59D                ; jump directly to next loop iteration

; 7. Allowed: Resume Vanilla Code
allowed:
00DCA150: 5A                   pop edx
00DCA151: 59                   pop ecx
00DCA152: 58                   pop eax
00DCA153: 8B 86 88 00 00 00    mov eax, [esi + 0x88]         ; restored original instruction
00DCA159: E9 C4 32 83 FF       jmp 0x005FD422                ; resume vanilla trade list builder
```

---

## 5. Covered Naval Unit Division Types

| Type ID | Internal Name | Description |
|---|---|---|
| `21` | `battleship` | Dreadnoughts and Super-Heavy Battleships |
| `22` | `light_cruiser` | Light Cruisers |
| `23` | `heavy_cruiser` | Heavy Cruisers |
| `24` | `battlecruiser` | Fast Capital Battlecruisers |
| `25` | `destroyer` | Destroyer Flotillas |
| `26` | `carrier` | Fleet Aircraft Carriers |
| `27` | `escort_carrier` | Escort Aircraft Carriers |
| `28` | `submarine` | Conventional Submarines |
| `29` | `nuclear_submarine` | Nuclear Submarines |
| `30` | `transport` | Naval Transports / Landing Craft |
| `31` | `light_carrier` | Light / Commando Aircraft Carriers |

---

## 6. Patcher Integration

This subsystem is integrated directly into `patch_darkest_hour.bat` and `tools/patch_darkest_hour.bat` under `$PATCH6_CHUNKS`:
- File Offset: `0x001FD41C` (6 bytes hook)
- File Offset: `0x00485100` (136 bytes code cave)
- Automatically applied and verified alongside the Custom Straits System.

