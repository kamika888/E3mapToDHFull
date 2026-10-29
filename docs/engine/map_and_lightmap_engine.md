# Map & Lightmap Engine Architecture (Europa Engine / Darkest Hour)

**Target Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour.exe` (Image Base: `0x00400000`, Checksum: `TENE`)  
**Scope**: In-depth specification of the map rendering pipeline, lightmap binary table format, coordinate mapping, zoom level indexing, and the hardcoded 60-entry tile header limit.

---

## 1. Map Coordinates & Tile Dimensions

Darkest Hour renders maps using a tiled grid system. Each tile is uniformly $32 \times 32$ pixels.

### Dimension Reference
* **Vanilla Map**: $18,432 \times 7,680$ pixels ($576 \times 240$ tiles = 138,240 tiles).
* **E3 Map (`Map_3`)**: $29,952 \times 11,520$ pixels ($936 \times 360$ tiles = 336,960 tiles).

```
Full Map Dimensions (E3): 29,952 (W) x 11,520 (H)
Tile Size: 32 x 32 pixels
Grid Dimensions: 936 tiles (columns) x 360 tiles (rows)
```

---

## 2. Zoom Levels & Lightmap Files

The engine manages zoom levels via the global variable `DAT_00a98464` (`0x00A98464`).  
Although the engine memory structure has slots for 5 zoom levels (`lightmap1.tbl` to `lightmap5.tbl`), in Darkest Hour (and specifically with the E3 map), **4 zoom levels are effectively active in-game (Levels 0 through 3)**; `lightmap5.tbl` is a legacy HoI2 asset.

| In-Game Zoom | Engine `DAT_00a98464` | File Name | Scale | Grid Size (E3) | Total Tiles | Index Size |
|---|---|---|---|---|---|---|
| **Max In (0)** | `0` | `lightmap1.tbl` | 1:1 | $936 \times 360$ | 336,960 | 1,347,840 bytes |
| **Step 1** | `1` | `lightmap2.tbl` | 1:2 | $468 \times 180$ | 84,240 | 336,960 bytes |
| **Step 2 (Mid)** | `2` | `lightmap3.tbl` | 1:4 | $234 \times 90$ | 21,060 | 84,240 bytes |
| **Max Out (3)** | `3` | `lightmap4.tbl` | 1:8 | $117 \times 45$ | 5,265 | 21,060 bytes |
| *(Unused)* | `4` | `lightmap5.tbl` | 1:16 | $58 \times 22$ | 1,276 | 5,104 bytes |

---

## 3. Binary Structure of `lightmapX.tbl`

Each `lightmapX.tbl` file is an independent binary archive containing:

```
+-------------------------------------------------------------+
| Index Table: uint32[num_tiles]                              |
| (Byte offsets from data start to each tile record)          |
+-------------------------------------------------------------+
| uint32: Total Data Block Byte Size                          |
+-------------------------------------------------------------+
| Tile Data Block:                                            |
|   Tile 0: [Header Words...] [Pixel / Palette Run Data...]   |
|   Tile 1: [Header Words...] [Pixel / Palette Run Data...]   |
|   ...                                                       |
|   Tile N: ...                                               |
+-------------------------------------------------------------+
```

### Tile Header Word Format
Each tile begins with a sequence of 16-bit little-endian words (`uint16`):
* **Province IDs**: Words $\le \text{MaxProvinces}$ (`[0x00877690]`, typically 8021 for E3). These define the provinces whose territory appears in this $32 \times 32$ tile.
* **Boundary Definitions**: Words $> \text{MaxProvinces}$ ($> 8021$). These define border pixels, rivers, and province outlines within the tile.

#### Boundary Word Bitmask Layout
```
 15    14   13              8   7                           0
+----+----+-------------------+-------------------------------+
|TERM|FLAG| Province Reference|  Sub-pixel / Border Property  |
| 1b | 1b |      6 bits       |            8 bits             |
+----+----+-------------------+-------------------------------+
```
* **Bit 15 (`0x8000`)**: Loop Terminator bit. Set on the final word of the tile's header list.
* **Bit 14 (`0x4000`)**: Boundary entry indicator flag.
* **Bits 8–13 (`0x3F00`)**: 6-bit **Biased Province Index**:
  $$\text{encoded\_ref} = (\text{province\_index\_in\_tile} + 4) \ \& \ 0x3F$$
* **Bits 0–7 (`0x00FF`)**: Boundary line classification, styling, and sub-pixel coordinate offsets.

---

## 4. Tile Decoding Pipeline & The 60-Entry Limit

### Decoding Logic (`FUN_004dafb0` @ `0x004DAFB0`)
The engine reads the tile header into a flat global scratch buffer at `DAT_00aa4320` (`0x00AA4320`, base `0x00A98470`):

```c
// Decompiled from FUN_004dafb0:
do {
    DAT_00aa7324++;
    word = read_uint16();
    buffer[DAT_00aa7324] = ((word >> 8) & 0x7F) << 8 | (word & 0xFF);
} while ((word & 0x8000) == 0);
```

When evaluating boundary entries:
```c
if (entry_value > MaxProvinces) {
    int ref_index = (entry_value >> 8) & 0x3F;
    int eff_index = ref_index - 4;  // <-- Engine reverses bias
    int province_id = buffer[eff_index];
    
    // Bounds check bug in engine:
    if (province_id <= MaxProvinces) {  // JLE (signed comparison)
        // Look up province structure:
        Province* prov = ProvinceArrayBase + (province_id * 0x4B2);
        int val = prov->field_290;      // Offending instruction
    }
}
```

### The 60-Entry Overflow Crash Mechanics
Because the reference field in the binary format is strictly **6 bits** ($0 \dots 63$):
1. **Valid Range**: $0 \dots 59$ (since $59 + 4 = 63$).
2. **Overflow**: If a tile header has a province placed at index **$\ge 60$**:
   $$\text{encoded\_ref} = (60 + 4) \ \& \ 0x3F = 64 \ \& \ 0x3F = \mathbf{0}$$
3. **Negative Indexing**: During playback, the engine reverses the bias:
   $$\text{eff\_index} = 0 - 4 = \mathbf{-4}$$
4. **Buffer Underrun**: `buffer[-4]` accesses memory 16 bytes before `0x00A98470`, hitting the global pointer `DAT_00a98460` (the DirectDraw surface structure pointer, e.g. `0x9B909E00`).
5. **Signed Comparison Defect & LAA Intermittency**:
   ```assembly
   004DB0C3: cmp esi, edx   ; edx = 8021 (MaxProvinces)
   004DB0C5: jle 0x004db0c9 ; signed jump if <= 8021
   004DB0C7: xor esi, esi   ; clamp to province 0 (skipped if negative!)
   ```
6. **Access Violation**: The engine treats `0x9B909E00` as a valid province ID, computes an out-of-bounds pointer (`base + 0x9B909E00 * 0x4B2 = 0x7985DC04`), and crashes at `0x004DB0DF: mov edx, [ecx + 0x290]` (`c0000005`).

### 4.1 Why the Crash is Intermittent (The LAA High-Memory Variable)

The reason this crash does **not** reproduce on a clean scenario startup or in a standard 32-bit environment without Large Address Aware (LAA) is due to pointer sign interpretation:

1. **Standard 32-Bit / Fresh Startup State (No Crash)**:
   * By default (or early in a game session), all heap and surface allocations reside in low virtual memory ($0\text{x}00000000$ to $0\text{x}7FFFFFFF$, $< 2\text{ GB}$).
   * Pointers in low memory (e.g. `0x0A714D80` = $+175,197,568$) have bit 31 cleared and are **positive** signed 32-bit integers.
   * When `buffer[-4]` fetches `DAT_00a98460`, `ESI` is positive and vastly greater than 8021:
     $$\text{ESI} = 175,197,568 > 8021$$
   * The signed comparison `JLE` evaluates to **FALSE**.
   * The engine executes `004DB0C7: xor esi, esi`, clamping `ESI` to **Province 0**.
   * **Result**: The engine silently absorbs the map overflow and recovers without crashing!

2. **LAA Extended Play Session State (Fatal Crash)**:
   * When **Patch 7 (Large Address Aware)** is active on 64-bit Windows, the operating system allows user-mode allocations in the upper 2 GB range ($0\text{x}80000000$ to $0\text{xFFFFFFFF}$).
   * After prolonged gameplay (such as the 1941 state where the crash occurred), surface reallocations or heap fragmentation push `DAT_00a98460` into the high address space (e.g. `0x9B909E00`).
   * Any address $\ge 0\text{x}80000000$ has bit 31 set, making it a **negative** signed integer in two's complement:
     $$\text{0x9B909E00} = \mathbf{-1,685,021,184}$$
   * The engine compares:
     $$-1,685,021,184 \le 8021 \quad (\mathbf{TRUE})$$
   * `JLE` jumps directly to `004DB0C9`, **bypassing the `xor esi, esi` clamp**!
   * The negative address is multiplied by `0x4B2`, resulting in an invalid pointer and an immediate `c0000005` access violation.

This explains why the defect can lie dormant across countless normal test sessions and only strikes intermittently during deep, memory-heavy campaigns with LAA enabled.

---

## 5. Mod Audit (`Map_3` Status)

Automated inspection of all four active lightmap files in `map/Map_3/` reveals:
* `lightmap1.tbl` (Zoom 0): Max tile header words = 42 (0 bad tiles).
* `lightmap2.tbl` (Zoom 1): Max tile header words = 63, all provinces $< 60$ (0 bad tiles).
* `lightmap4.tbl` (Zoom 3): Max tile header words = 30 (0 bad tiles).
* **`lightmap3.tbl` (Zoom 2)**: **17 tiles exceed the 60-entry limit** due to high province density.

### Bad Tiles in `lightmap3.tbl`
| Tile ID | Grid ($T_x, T_y$) | Full Map Coordinates | Region | Word Count |
|---|---|---|---|---|
| 3874 | (130, 16) | $X=16640, Y=2048$ | Central / Eastern Europe | 76 |
| 4100 | (122, 17) | $X=15616, Y=2176$ | Northern Germany (Hamburg/Kiel/Lübeck) | 62 |
| 4567 | (121, 19) | $X=15488, Y=2432$ | Western / Central Europe | 77 |
| 4799 | (119, 20) | $X=15232, Y=2560$ | France / Rhineland | 68 |
| 4806 | (126, 20) | $X=16128, Y=2560$ | Bohemia / Silesia (Katowice/Ostrava/Brno) | 83 |
| 5507 | (125, 23) | $X=16000, Y=2944$ | Italy / Alps / Balkans | 70 |
| 5975 | (125, 25) | $X=16000, Y=3200$ | Balkans / Greece | 71 |
| 5976 | (126, 25) | $X=16128, Y=3200$ | Balkans / Greece | 68 |
| 5979 | (129, 25) | $X=16512, Y=3200$ | Aegean / Western Anatolia | 71 |
| 5993 | (143, 25) | $X=18304, Y=3200$ | Ukraine / Black Sea | 71 |
| 6227 | (143, 26) | $X=18304, Y=3328$ | Crimea / Sea of Azov | 74 |
| 6229 | (145, 26) | $X=18560, Y=3328$ | North Caucasus / Kuban | 68 |
| 6446 | (128, 27) | $X=16384, Y=3456$ | Eastern Mediterranean | 78 |
| 6447 | (129, 27) | $X=16512, Y=3456$ | Cyprus / Levant Coast | 64 |
| 6682 | (130, 28) | $X=16640, Y=3584$ | Palestine / Sinai | 72 |
| 7652 | (164, 32) | $X=20992, Y=4096$ | Kashmir / Punjab (Dharmsala/Jammu/Amritsar) | 63 |
| 7861 | (139, 33) | $X=17792, Y=4224$ | Egypt / Red Sea | 79 |

---

## 6. Remediation Strategies

1. **Asset-Level Clamping (Implemented & Verified)**:
   * **Status**: Implemented on `map/Map_3/lightmap3.tbl` (original backed up as `lightmap3.tbl.bak`).
   * **Action**: All 72 boundary entries across the 17 tiles that had wrapped indices ($0 \dots 3$, pointing before the buffer) were clamped to reference field value `4` (Province index 0 of the respective tile).
   * **Verification**: Re-scanned all 21,060 tiles in `lightmap3.tbl`; bad tile count reduced from **17 to 0**. The buffer underrun is fully eliminated at the asset level without requiring executable modifications.

2. **Binary Engine Fix (Implemented & Verified - Patch 9)**:
   * **Status**: Implemented on `Darkest Hour.exe` at `0x004DB0C5` (file offset `0x000DB0C5`).
   * **Opcode Patch**: Changed `7E 02` (`JLE 0x004DB0C9` - signed) to `76 02` (`JBE 0x004DB0C9` - unsigned).
   * **Result**: Any out-of-bounds pointer in high address space ($\ge 0\text{x}80000000$) is interpreted as unsigned $> 8021$, executing `xor esi, esi` and safely falling back to province 0 instead of crashing. Fully integrated into the automated patcher script.

---

## 7. Unit Counter Sprites & Mouse Hover Hit-Testing

Separate from tile rendering, the map window hit-tests unit counters on every mouse move or scroll.

### Call chain
* `FUN_00652570`: map hover/selection dispatch. It loops over every country slot in `DAT_0089CAD8` (`0x0089CAD8`-`0x0089D038`) and each country's unit list at `+0x4508`. For each unit it calls the counter sprite's vtable `+0x20` (sprite pointer at unit `+0x15A` / `+0x15E`).
* `0x004170C0`: unit counter sprite hit-test (sprite vtable `0x007E3738`, constructor `FUN_00416730`). It projects the unit's map position to the screen (`FUN_004d8ba0`), tests the screen bounding box, then samples the sprite surface for transparency.
* `FUN_004060b0`: surface pixel test (`8bpp`: byte != 0 means opaque; `16bpp`: compared to color key `DAT_0088CEE8`). It has **no bounds check** and calls `GetPixelAddress` (`FUN_00409090`: `base + x*[+0x0C] + y*[+0x18]`).

### Counter sprite fields (relative to sprite object)
| Offset | Meaning |
|---|---|
| `+0x0E` | base scale shift (0 for counters) |
| `+0x52` | current frame index in the counter strip |
| `+0x56` | frame width (32) |
| `+0x62` | surface pointer (surface `+0x04` width, `+0x08` height, `+0x18` pitch) |
| `+0x82` | scale bias vs. map zoom (`-1` for counters, so they stay full size at zoom 1) |
| `+0x86` / `+0x8A` | map X / Y position |

### Effective scale
$$\text{effective\_scale} = \max(0,\ [+0x82] + \text{zoom})$$
The counter draw path (`0x00416FED`) also adds `[+0x0E]` and caps at 4. The result is full-size counters (32 x 34) at zoom 0 and 1, half size at zoom 2, and quarter size at zoom 3.

### Vanilla defect (fixed by Patch 13)
The bounding box uses `effective_scale`, but the texture-coordinate conversion at `0x00417178` shifted by the raw global zoom (`[0x00A98464]`). At zoom 1 or higher, the lower half of a counter maps to rows past the 34-pixel surface, giving an out-of-bounds read and an intermittent AV at `0x00406100`. See [`plan_unit_counter_hover_hit_test_scale_fix.md`](../plans/plan_unit_counter_hover_hit_test_scale_fix.md).
