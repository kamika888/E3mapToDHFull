# Graphics & UI Rendering Performance Optimization (Patches A + B; Future Options C + D)

**Status**: Patches A + B Implemented & Validated; Options C + D Documented for Future Reference  
**Engine**: Darkest Hour 1.05.2 (checksum `TENE`)  
**Target File**: `Darkest Hour.exe` (Image Base: `0x00400000`, `.mod` section `0x00DC9000` - `0x00DD9000`)  
**Hook Sites**: `Hooks 15-20` (`0x00404CA7`, `0x00405B85`, `0x00406160`, `0x004066F0`, `0x0040671F`, `0x0040674D`, `0x00409040`, `0x0040D787`, `0x0040FF00`)  
**Code Cave Range**: `0x00DD2BB0` - `0x00DD2EC9` (file offsets `0x0048DBB0` - `0x0048DEC9`, bundled in `$PATCH18_CHUNKS`)  
**Patched Binary SHA256**: `47EA7FDF3ADF9A926A1ED05E1C5A2FE08873D60D4E25B4CDFB7862A5DA770061` (`4,800,512` bytes)  
**Patch Category**: Map & UI Rendering Performance (Zero Gameplay / Checksum Impact)

---

## 1. Overview & Motivation

Even when the game clock is completely paused (zero hourly simulation work), the retail Darkest Hour UI exhibits noticeable frame-rate degradation, delayed input response, and jagged map scrolling as global unit counts grow toward mid- and late-game campaigns. Enabling global movement arrow rendering via `[Engine] AlwaysShowMovementArrows = 1` makes this degradation severe immediately from scenario start in 1936.

Reverse engineering of the retail frame loop (`WinMain` @ `0x007942B2` -> in-game loop `FUN_007901B0` -> `(*DAT_0088eba8 + 0x34)()` `RenderAll` @ `0x0040FF00` -> `Present` @ `0x00583F10`) identified four distinct architectural bottlenecks:

1. **Patch A (Implemented)**: Redundant per-triangle and per-sprite DirectDraw `GetSurfaceDesc` + `Lock` + `Unlock` COM round-trips on `DDSCAPS_SYSTEMMEMORY` (`type == 1`) surfaces.
2. **Patch B (Implemented)**: Zero viewport frustum culling in `CArrow::Draw` (`0x0040D770`) combined with broken clip-before-cull ordering in `CSurface::DrawTriangle` (`0x00404C50`).
3. **Option / Patch C (Future Option)**: Four full-world entity/province linear scans per mouse-hover query in `FUN_00652570` calling `CSprite::HitTest` (`0x004170C0`).
4. **Option / Patch D (Future Option)**: Windowed 16-bit primary-surface `Lock` + CPU scanline `memcpy` + `Unlock` presentation overhead under Windows 10/11 DWM (`0x00583F10` -> `0x00407A00`), addressable via an external DirectDraw wrapper (`cnc-ddraw` or `DDrawCompat`).

In-game testing confirmed that **Patches A + B alone** restore smooth UI responsiveness even in late-game campaigns with `AlwaysShowMovementArrows = 1` enabled. Patches C and D are preserved in Section 5 as ready-to-use options if ever needed in the future.

---

## 2. Patch A: DirectDraw `DDSCAPS_SYSTEMMEMORY` Lock/Unlock Elimination (`Hooks 15-18D`)

### 2.1 Retail Engine Bottleneck

Every software drawing primitive in the retail engine wraps its pixel writes in `CSurface::Lock` (`0x00408F70`) and `CSurface::Unlock` (`0x00409040`):

* `CSurface::DrawTriangle` (`0x00404C50` -> `0x00404F90` / `0x004050A0` / `0x00405170`) locks and unlocks the backbuffer (`DAT_00bd1bac`) on **every single triangle** (50+ triangles per movement arrow, thousands per frame).
* Software sprite blitters (such as `FUN_00406C00` 8bpp->16bpp counter/icon blitting) lock and unlock **both** the source sprite surface and the destination backbuffer on every sprite draw.
* When `[surface + 0x254] == 0` (unlocked), `CSurface::Lock` (`0x00408F70`) zeroes a 108-byte `DDSURFACEDESC` on the stack, calls `IDirectDrawSurface::GetSurfaceDesc` (`vtbl + 0x58`), and calls `IDirectDrawSurface::Lock` (`vtbl + 0x64`); `CSurface::Unlock` (`0x00409040`) then calls `IDirectDrawSurface::Unlock` (`vtbl + 0x80`) and clears `[surface + 0x20]` (`lpSurface`) and `[surface + 0x254]`.

An audit of all 27 surface-creation call sites (`0x004010A0` and `0x00401060`) established that `CSurface` tracks its surface class at `[this + 0x238]`:

| `[this + 0x238]` (`type`) | DirectDraw Caps | Engine Usage |
|---|---|---|
| `0` | `DDSCAPS_VIDEOMEMORY` | Hardware mouse cursor (`0x0058434D` / `0x00584396`) |
| `1` | `DDSCAPS_OFFSCREENPLAIN \| DDSCAPS_SYSTEMMEMORY` (`0x840`) | Backbuffer (`DAT_00bd1bac`), terrain cache (`DAT_00a98460`), and all BMP sprites, unit counters, fonts, and UI elements (`0x00415FD0`) |
| `2` | `DDSCAPS_PRIMARYSURFACE` | Windowed/fullscreen front surface (`DAT_00bd1bb0`) |

For `type == 1` (`DDSCAPS_SYSTEMMEMORY`) surfaces, the pixel buffer is a fixed user-mode heap allocation whose `lpSurface` pointer never moves after creation. Moreover, `CSurface::Lock` (`0x00408F77`) **already** contains a 4-instruction fast path when `[ebx + 0x254] != 0`:

```assembly
00408F77: 8B 83 54 02 00 00  mov  eax, [ebx + 0x254]   ; lock flag
00408F7D: 85 C0              test eax, eax
00408F7F: 74 09              je   0x00408F8A           ; slow COM GetSurfaceDesc + Lock
00408F81: 8B 43 20           mov  eax, [ebx + 0x20]    ; cached lpSurface
00408F84: 5E                 pop  esi
00408F85: 5B                 pop  ebx
00408F86: 83 C4 6C           add  esp, 0x6C
00408F89: C3                 ret
```

### 2.2 Critical Pitfall Avoided: Unbalanced Retail `Lock` Calls

Converting `CSurface::Lock` / `CSurface::Unlock` to naive `lock_count++` / `lock_count--` reference counting would **break** the engine because retail Darkest Hour contains multiple intentionally unbalanced lock paths on `type == 1` surfaces:

1. **`FUN_00406C00` (8bpp -> 16bpp sprite blitter)**: Calls `Lock(src)` and `Lock(dst)` *before* testing `if (w > 1 && h > 1)` and returns early **without calling `Unlock`** on 1-pixel clipped edge slivers.
2. **`FUN_004DF7A0` (terrain cache redraw)**: Calls `DAT_00a98460->Lock()` once, then calls `GetPixelAddress` (`0x00409090`, which internally calls `Lock()` without a matching `Unlock()`) hundreds of times, followed by a single `Unlock()`.
3. **`FUN_00405DF0` (16-bit BMP loader)**: Scans loaded pixels for colorkey `0x7E0` / `0x3E0` and jumps to `0x00406026` **skipping `Unlock()`** whenever a transparent pixel is found (setting `[this + 0x238] = 1` only after initial pitch setup).

Because `CSurface::Lock` only increments `[this + 0x254]` from `0 -> 1` (never above `1`), retail DH already relies on `DDSCAPS_SYSTEMMEMORY` surfaces staying safely locked in memory.

### 2.3 Leak-Proof Pin & Persistent-Lock Design

Patch A eliminates COM churn while remaining 100% immune to unbalanced retail locks and DirectDraw wrapper expectations:

1. **Shared Forced-Unlock Helper (`Cave_Surface_RealUnlock` @ `0x00DD2BB4`)**:
   * Checks `[ecx + 0x254] != 0`; if locked, calls `IDirectDrawSurface::Unlock(NULL)` (`vtbl + 0x80`) on `[ecx + 0x2C]` and zeroes both `[ecx + 0x20]` (`lpSurface`) and `[ecx + 0x254] = 0` while preserving `ebx, ecx, edx, esi, edi, ebp`.
2. **Hook 15 -- Backbuffer Frame Pinning (`RenderAll` @ `0x0040FF00` -> `Cave_RenderAll_PinBB` @ `0x00DD2BE9`)**:
   * On entry to `RenderAll`, if `DAT_00bd1bac != NULL` and `[DAT_00bd1bac + 0x238] == 1`, calls `CSurface::Lock` (`0x00408F70`) once and increments re-entrancy depth `g_dwBackbufferPinDepth` (`0x00DD2BB0`).
   * Executes the exact retail `RenderAll` drawable list loop (`0x0040FF08..0x0040FF1E`).
   * On exit, decrements `g_dwBackbufferPinDepth`; when depth reaches `0`, calls `Cave_Surface_RealUnlock(DAT_00bd1bac)` so the backbuffer is **always cleanly unlocked** prior to `Present` (`0x00583F10`), `Flip`, `PeekMessage`, or `Alt-Tab`.
   * Reduces backbuffer DirectDraw COM `Lock`/`Unlock` pairs from **2,000-15,000+ per frame down to 2 per frame** (1 in `RenderAll`, 1 in `Present`).
3. **Hook 16 -- Persistent Lock for Off-Screen `type == 1` Surfaces (`CSurface::Unlock` @ `0x00409040` -> `Cave_Surface_UnlockFast` @ `0x00DD2C53`)**:
   * If `[ecx + 0x238] == 1`:
     * If `ecx != [0x00BD1BAC]` (all sprite, counter, font, icon, and terrain cache surfaces): returns immediately (`ret`), keeping them persistently locked after first use (`0` COM calls per frame thereafter).
     * If `ecx == [0x00BD1BAC]` and `g_dwBackbufferPinDepth != 0`: returns immediately (`ret`), keeping the backbuffer pinned across the entire `RenderAll` pass.
   * Otherwise (primary surface `type == 2`, hardware cursor `type == 0`, or unpinned backbuffer outside `RenderAll`), jumps to `0x00409049` to execute the exact retail `Unlock` path.
4. **Hooks 17 & 18A-18D -- Exhaustive DirectDraw COM Safety Guards**:
   * Every remaining site in `Darkest Hour.exe` where a `CSurface` interacts directly with raw `IDirectDrawSurface` COM methods that reject locked surfaces (`DDERR_SURFACEBUSY` / `Release`) was audited and guarded:
     * **Hook 17 (`CSurface::~CSurface` @ `0x00405B85`)**: Calls `Cave_Surface_RealUnlock` before `pDDSurf->Release()` (`vtbl + 0x08`) if `[esi + 0x254] != 0`.
     * **Hooks 18A & 18B (`CSurface::Blt` `BltFast` @ `0x004066F0` & `0x0040671F`)**: Unlocks `dst` (`edi`) and `src` (`esi`) if `[+0x254] != 0` prior to `IDirectDrawSurface::BltFast` (`vtbl + 0x1C`); self-heals automatically on the next `CSurface::Lock` if `dst == DAT_00bd1bac`.
     * **Hook 18C (`CSurface::Blt` mode 6 @ `0x0040674D`)**: Unlocks `src` (`esi`) before direct `FUN_0057ADC0(pDDSurf)` raw lock.
     * **Hook 18D (`CSurface::LockRaw` @ `0x00406160`)**: Unlocks `this` (`ecx`) before `FUN_0057ADC0(pDDSurf)` (called by minimap/overlay routines at `0x0040E3A4` and `0x004E23F8`).

---

## 3. Patch B: Movement Arrow Frustum Culling & Triangle Pre-Clamp Rejection (`Hooks 19-20`)

### 3.1 Retail Engine Bottleneck

1. **Zero Culling in `CArrow::Draw` (`0x0040D770`)**:
   * `CArrow::Draw` checks only `[esi + 0x22] != 0` (spline count) and `[esi + 0x26] >= 2` (revealed animation count), then unconditionally invokes `CArrow::DrawSegmentPass` (`0x0040D820`) **twice** (shadow pass offset `(4 >> zoom, 6 >> zoom)` + foreground pass `(0, 0)`).
   * For every active movement arrow anywhere on Earth (even on the opposite side of the globe), `0x0040D820` projects 12 spline subdivisions per waypoint segment via `FUN_004D8A60` (~96+ projections across two passes) and submits **50+ triangles** to `CSurface::DrawTriangle` (`0x00404C50`).
2. **Clip-Before-Cull Bug & Edge Slivers in `CSurface::DrawTriangle` (`0x00404C50`)**:
   * At `0x00404CA7..0x00404D46`, `CSurface::DrawTriangle` clamps all three vertices `(x0, y0)`, `(x1, y1)`, `(x2, y2)` into `[0, screen_w - 1] x [0, screen_h - 1]` **before** performing any off-screen check, and `FUN_004D8A60` (`0x004D8AC1..0x004D8AE0`) separately clamps negative screen coordinates to `0`.
   * Consequently, off-screen arrows collapse onto `x = 0` (with shadow at `x = 4 >> zoom`) or `y = 0` (`y = 6 >> zoom`) or `x = screen_w - 1` / `y = screen_h - 1`, running full scanline setup and rasterizing degenerate 1-pixel edge slivers.

### 3.2 Hook 19: Waypoint Frustum Culling (`CArrow::Draw` @ `0x0040D787` -> `Cave_Arrow_DrawCull` @ `0x00DD2CF7`)

Hooked immediately after `[esi + 0x22] != 0` and `[esi + 0x26] >= 2`, `Cave_Arrow_DrawCull` walks the arrow's doubly-linked waypoint list `[esi + 0x10]` (`pWP = [pNode + 0]`, `pNext = [pNode + 8]`, typically 2-5 nodes):

1. **Viewport-Center-Relative Cylindrical Wrap Math (Zoom 0-3 Safe)**:
   * Retail camera globals updated by `CMap::Draw` (`0x004E0090` -> `0x004D8E20` -> `0x004D8CF0`) at render priority `100` (prior to arrows at priority `350`):
     * `cam_x = [0x00847858]` (world X of viewport **left** edge), `cam_y = [0x0084785C]` (world Y of viewport **top** edge)
     * `vx0 = [0x00A98430]`, `vy0 = [0x00A98434]`, `zoom = [0x00A98464]` (`0..3`)
     * E3 map width = `0x7500` (`29,952` px), half-width = `0x3A80` (`14,976` px).
   * **Why naive `dx > 0x3A80` wrapping would fail at Zoom 3**: On a `1920px`-wide screen at zoom 3 (`1:8`), the viewport spans `1920 * 8 = 15,360` world pixels (`> 14,976`), so visible points near the right edge legitimately have `dx = wx - cam_x > +0x3A80`.
   * Instead, `Cave_Arrow_DrawCull` measures wrap relative to the **viewport center** `center_dx = (screen_w << zoom) >> 1`:
     ```text
     wx_norm = wx wrapped into [0, 0x7500)
     dx      = wx_norm - cam_x
     rel     = dx - center_dx
     if (rel < -0x3A80) dx += 0x7500
     if (rel > +0x3A80) dx -= 0x7500
     sx      = (dx >> zoom) + vx0
     sy      = ((wy - cam_y) >> zoom) + vy0
     ```
     This places the wrap seam at the exact anti-meridian opposite the viewport center across all zoom levels `0..3`, negative `cam_x` values, and Pacific seam crossings.
2. **Point & Segment AABB Test with `192px` (`0xC0`) Margin**:
   * If any waypoint `(sx, sy)` falls inside `[-192, screen_w + 192] x [-192, screen_h + 192]`, arrow drawing proceeds immediately.
   * For each consecutive waypoint pair `(prev, cur)`: if `|sx - prev_sx| <= (0x3A80 >> zoom)` (confirming the segment crosses continuously rather than wrapping around the back of the globe), tests whether the segment AABB overlaps `[-192, screen_w + 192] x [-192, screen_h + 192]`. The `192px` padding accommodates spline curvature bowing, arrow head width, and shadow offsets without edge pop-in.
   * If no waypoint or segment intersects the padded viewport, returns `0` (`ret 4`) in ~35 integer ALU instructions (~15 ns per off-screen arrow, zero FPU/triangle calls).
   * Skipping `0x0040DCB0` while off-screen has zero visual side effects when scrolling back because `0x0040DCB0` computes arrow reveal progress directly from current game date vs. unit start/arrival timestamps (`[pUnit + 0x222]` / `[pUnit + 0x228]`).

### 3.3 Hook 20: Pre-Clamp Triangle & Sliver Culling (`CSurface::DrawTriangle` @ `0x00404CA7` -> `Cave_DrawTriangle_PreClampCull` @ `0x00DD2E63`)

Hooked at `0x00404CA7` right after computing unclamped screen vertices `(x0, y0)`, `(x1, y1)`, `(x2, y2)` and **before** `0x00404CB1` clamping:

1. **All-Left / All-Top Sign-Bit Reject**: `(x0 & x1 & x2) < 0` (`js`) or `(y0 & y1 & y2) < 0` (`js`) -> jump to epilogue.
2. **All-Right / All-Bottom Reject**: `(x0 >= w && x1 >= w && x2 >= w)` or `(y0 >= h && y1 >= h && y2 >= h)` -> jump to epilogue.
3. **Zero-Area Collinear Sliver Reject**: `(x0 == x1 && x1 == x2)` or `(y0 == y1 && y1 == y2)` -> jump to epilogue. This also eliminates `FUN_004D8A60`'s clamped `x = 0` / `y = 0` (and shadow `x = 4` / `y = 6`) off-screen artifacts for partially visible arrows crossing the top/left border.

---

## 4. Binary Hook & Cave Reference Matrix

All hooks are generated reproducibly by `build_and_apply_all.py` and deployed via `$PATCH18_CHUNKS` in `tools/patch_darkest_hour.bat` and `patch_darkest_hour.bat`:

| Hook | Target Function & VA | File Offset | Size | Original Bytes | Patched Bytes | Cave Target VA & Symbol |
|---|---|---|---|---|---|---|
| *(Data)* | N/A | `0x0048DBB0` | 4B | `00 00 00 00` | `00 00 00 00` | `0x00DD2BB0` (`g_dwBackbufferPinDepth`) |
| *(Helper)* | N/A | `0x0048DBB4` | 53B | N/A | N/A | `0x00DD2BB4` (`Cave_Surface_RealUnlock`) |
| **Hook 15** | `RenderAll` @ `0x0040FF00` | `0x0000FF00` | 6B | `56 8B 71 04 85 F6` | `E9 E4 2C 9C 00 90` | `0x00DD2BE9` (`Cave_RenderAll_PinBB`) |
| **Hook 16** | `CSurface::Unlock` @ `0x00409040` | `0x00009040` | 9B | `56 8B F1 8B 86 54 02 00 00` | `E9 0E 9C 9C 00 90 90 90 90` | `0x00DD2C53` (`Cave_Surface_UnlockFast`) |
| **Hook 17** | `CSurface::~CSurface` @ `0x00405B85` | `0x00005B85` | 5B | `8B 46 2C 85 C0` | `E8 F4 D0 9C 00` | `0x00DD2C7E` (`Cave_Surface_DtorUnlock`) |
| **Hook 18A** | `CSurface::Blt` (`BltFast` 1) @ `0x004066F0` | `0x000066F0` | 7B | `8B 7F 2C 8D 44 24 38` | `E8 A6 C5 9C 00 90 90` | `0x00DD2C9B` (`Cave_Surface_BltFastGuard`) |
| **Hook 18B** | `CSurface::Blt` (`BltFast` 2) @ `0x0040671F` | `0x0000671F` | 7B | `8B 7F 2C 8D 44 24 38` | `E8 77 C5 9C 00 90 90` | `0x00DD2C9B` (`Cave_Surface_BltFastGuard`) |
| **Hook 18C** | `CSurface::Blt` (mode 6) @ `0x0040674D` | `0x0000674D` | 7B | `C6 86 3C 02 00 00 01` | `E8 71 C5 9C 00 90 90` | `0x00DD2CC3` (`Cave_Surface_Mode6Guard`) |
| **Hook 18D** | `CSurface::LockRaw` @ `0x00406160` | `0x00006160` | 10B | `8B 41 2C C6 81 3C 02 00 00 01` | `E8 79 CB 9C 00 90 90 90 90 90` | `0x00DD2CDE` (`Cave_Surface_LockRawGuard`) |
| **Hook 19** | `CArrow::Draw` @ `0x0040D787` | `0x0000D787` | 6B | `8A 0D 08 EB 88 00` | `E9 6B 55 9C 00 90` | `0x00DD2CF7` (`Cave_Arrow_DrawCull`) |
| **Hook 20** | `CSurface::DrawTriangle` @ `0x00404CA7` | `0x00004CA7` | 10B | `85 DB 89 6C 24 20 89 7C 24 24` | `E9 B7 E1 9C 00 90 90 90 90 90` | `0x00DD2E63` (`Cave_DrawTriangle_PreClampCull`) |

---

## 5. Deferred Future Improvement Options (Patches C & D)

Current in-game validation shows Patches A + B already achieve smooth UI behavior through late game. The two remaining bottlenecks investigated during this audit are documented below so they can be enabled quickly if ever desired.

### 5.1 Option / Patch C: Map Hover & Mouse Hit-Test Fast-Reject (`FUN_00652570` & `0x004170C0`)

* **Retail Bottleneck**:
  * `FUN_00652570` (`0x00652570..0x00652BA0`, called from 11 map mouse-move/click/tooltip handlers) checks what object is under `(mouseX, mouseY)`.
  * Whenever the cursor is over empty terrain (not hitting an already-selected unit), `FUN_00652570` executes **four full-world linear scans**:
    1. `0x00652669..0x00652727`: All 344 country slots (`0x0089CAD8..0x0089D038`) -> every unit in `[pCountry + 0x4508]` -> `[unit + 0x15A]->vtbl[+0x20](mouseX, mouseY)`.
    2. `0x0065272D..0x0065283E`: All 8,021 E3 provinces (`1..[0x00877690]`) -> every province stack list `[prov + 0x46A]` -> `vtbl[+0x20]`.
    3. `0x006529BE..0x00652A55`: Second pass across all 344 country slots -> `vtbl[+0x20]`.
    4. `0x00652AB2..0x00652B74`: Third pass across all 344 country slots -> `vtbl[+0x20]`.
  * Each `CSprite::HitTest` (`0x004170C0`) call invokes **7 functions** (`FUN_004D8BA0` -> `FUN_004D8CF0` -> `FUN_004E1FC0`, `0x005841A0`, `0x005841B0`, `0x00415BD0`, `0x00415BE0`) *before* testing whether the unit is anywhere near `(mouseX, mouseY)` -- causing ~50,000-70,000+ function calls per mouse-move event in 3,000-unit late-game saves.
* **Candidate Implementation**:
  * Hook `0x004170C0` prologue (and verify any sibling `vtbl + 0x20` sprite hit-test implementations used in passes 3-4, e.g. near `0x00419170`):
    1. Compute inline `sy = (([esi + 0x8A] - [esi + 0x1E] - [0x0084785C]) >> zoom) + [0x00A98434]`; if `mouseY < sy - 16 || mouseY > sy + 128`, return `0` (`ret 8`) immediately (~6 instructions; rejects ~90-95% of all units worldwide with zero calls).
    2. Compute inline `sx` using `[0x00847858]` + `[0x00A98430]` + wrap; if `mouseX < sx - 16 || mouseX > sx + 128`, return `0` immediately (rejects >99.9%).
    3. Fall through to retail `0x004170C0` (preserving Patch 13's `effective_scale` pixel transparency check at `0x0041714B`) only for the 0-3 sprites actually overlapping the cursor neighborhood.

### 5.2 Option / Patch D: External DirectDraw GPU Presentation Wrapper (`cnc-ddraw` / `DDrawCompat`)

* **Retail Bottleneck**:
  * In windowed mode (`settings.cfg` windowed `1`, 16-bit RGB565), `Present` (`0x00583F10` -> `0x00406300` -> `0x00407A00`) calls `FUN_0057ADC0` (`IDirectDrawSurface::Lock`) directly on the **Primary Surface** (`DAT_00bd1bb0`), copies every scanline from `DAT_00bd1bac` via CPU `memcpy` (`0x004295C0`, ~3.86 MB/frame at `1910x1010`), and calls `FUN_0057AE50` (`IDirectDrawSurface::Unlock`).
  * Under Windows 10/11 Desktop Window Manager (DWM), locking a 16-bit primary surface invokes Microsoft's legacy DirectDraw compatibility shim (CPU 16-to-32bpp conversion + synchronous GDI/DWM composition stall on `Unlock`).
* **Candidate Deployment & Compatibility**:
  * Dropping **`cnc-ddraw`** (`ddraw.dll` + `ddraw.ini`, OpenGL/Direct3D9 backend, hardware 16->32bpp shader conversion, borderless fullscreen, configurable `maxfps`) or **`DDrawCompat`** (`ddraw.dll`, Direct3D9 backend; lighter alternative, preferable over heavier `dgVoodoo2`) into the game root directory (`Darkest Hour/`) offloads presentation to the GPU without modifying `Darkest Hour.exe` (reversible by deleting the DLL).
  * **Full Compatibility with Patches A + B**: Patch A explicitly unpins and unlocks `DAT_00bd1bac` at the end of `RenderAll` before `Present` (`0x00583F10`) and guards all `BltFast`, `LockRaw`, mode-6 `Blt`, and `~CSurface` paths, ensuring zero lock-state conflicts when stacked with `cnc-ddraw` or `DDrawCompat`.
