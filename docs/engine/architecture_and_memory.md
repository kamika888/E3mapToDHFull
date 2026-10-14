# Darkest Hour Engine Binary & Memory Model

**Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour.exe` (Size: `4,730,956` bytes, Image Base: `0x00400000`)  
**Scope**: Core binary architecture, PE section layout, memory mapping, checksum calculation model, and function alignment rules.

---

## 1. Executable Universality & Checksum Architecture

### 1.1 Single Executable for All Configurations
The physical binary `Darkest Hour.exe` is identical regardless of which mod or scenario is launched (e.g., *Darkest Hour Full*, *Darkest Hour Light*, *E3mapToDHFull*). Mod folders provide data, scripts, and interface overrides, while the core simulation engine remains constant across all game installations.

### 1.2 Lightweight Debugging Target
*Darkest Hour Light* (vanilla baseline checksum `TENE`) is optimal for reverse engineering and debugging:
- Database footprint loads in ~3–5 seconds under x32dbg, compared to 30–60 seconds for large total-conversion mods.
- Core memory offsets, global variables, and calling conventions are 100% identical between Light, Full, and custom mods.

### 1.3 The Checksum Mechanism
- The four-letter checksum displayed in the main menu (e.g., `TENE`) is calculated exclusively over script databases (`db/`, `map/`, events, scenario definitions).
- **The checksum does NOT hash `Darkest Hour.exe`**.
- Native binary patches, hooks, or code modifications to `Darkest Hour.exe` preserve the original checksum completely, avoiding multiplayer desync flags or launcher mismatch warnings caused by executable changes.

---

## 2. Binary Layout & Memory Mapping

### 2.1 Compiler & Architecture
- **Compiler**: Microsoft Visual C++ (MSVC 6.0 / .NET 2003 era), 32-bit x86 Little-Endian.
- **Image Base**: `0x00400000`

### 2.2 PE Section Map
The vanilla retail executable (`Darkest Hour_original.exe`) contains exactly **four standard PE sections**. In the modified/patched executable (`Darkest Hour.exe`), a **fifth custom section (`.mod`)** was injected into the PE section table to provide dedicated space for extensive binary hooks and data structures:

| Section | Origin | Virtual Address Range | Virtual Size | Raw File Offset | Raw Size | Permissions | Content |
|---|---|---|---|---|---|---|---|
| `.text` | Vanilla Retail | `0x00401000` - `0x007E2D2A` | `4,070,698` | `0x00001000` | `4,071,424` | `R-X` (Code) | Executable machine code instructions |
| `.rdata` | Vanilla Retail | `0x007E3000` - `0x0082BF76` | `298,870` | `0x003E3000` | `299,008` | `R--` (Read-Only) | Constant literals, vtables, import address table |
| `.data` | Vanilla Retail | `0x0082C000` - `0x00DC6C94` | `5,876,884` | `0x0042C000` | `348,160` | `RW-` (Data) | Global variables, static tables, runtime heap |
| `.rsrc` | Vanilla Retail | `0x00DC7000` - `0x00DC8618` | `5,656` | `0x00481000` | `8,192` | `R--` (Resource) | Windows icons, dialog templates, version info |
| `.mod` | **Custom Injected** | `0x00DC9000` - `0x00DCD000` | `16,384` | `0x00484000` | `8,192` | `RWX` (Code/Data) | Custom extension cave (straits, trade hooks, memory fixes) |

### 2.3 Address Translation Formula
Throughout the primary `.text` section:
$$\text{Virtual Address} = \text{File Offset} + \text{0x00400000}$$
$$\text{File Offset} = \text{Virtual Address} - \text{0x00400000}$$

*(Note: Data sections mapped beyond raw file sizes use RVA offsets defined in the PE Optional Header).*

---

## 3. Function Alignment & Code Caves

### 3.1 16-Byte Function Boundary Alignment
MSVC compiles x86 functions aligned to 16-byte address boundaries (`address % 16 == 0`). Functions that terminate before filling their 16-byte block are padded with **1 to 15 bytes of `0x90` (NOP) or `0xCC` (INT3) padding**.

### 3.2 Utilizing Local Code Caves (Vanilla Padding)
These alignment padding bytes reside within the original mapped PE image:
- Can be safely used for short jump trampolines, local register setup, or small conditional tests without displacing surrounding code.
- Example: The 48 padding bytes preceding `0x007E2DB0` (`0x007E2D80` - `0x007E2DAF`) host the sequential INI configuration loader for custom diplomacy toggles.

### 3.3 Custom Injected Cave: The `.mod` Section
In the pristine retail release (`Darkest Hour_original.exe`), **the `.mod` section does not exist**. In vanilla, binary instrumentation is strictly constrained to either:
1. Squeezing small snippets into local 16-byte NOP alignment gaps, or
2. Displacing existing instructions and routing them through external DLL injections.

To facilitate larger modding additions without requiring external DLL loaders or displacing existing engine code, a new PE section named `.mod` was explicitly added to the binary:
- **Virtual Address**: `0x00DC9000` - `0x00DCD000` (16 KB allocated in process memory).
- **File Offset**: `0x00484000` (8 KB appended to the executable file on disk).
- **Permissions**: Read, Write, and Execute (`RWX` / `0xE0000020`), allowing both dynamic execution and writable data tables.
- **Subsystems Hosted**:
  - **Patch 6 (Custom Straits System)**: Global 64-entry strait array `g_Straits` (`0x007E50C0`), CSV parser subroutines, transit check hooks (`0x007E4670`), and natural language UI tooltip grammar engine.
  - **Patch 6 Extension (Black Sea Naval Trade)**: Exclusive OR bilateral trade filter cave (`0x00DCA100`).
  - **Patch 8 (Scenario Memory Leak Patch)**: Event/decision deallocation cave (`0x00DCA000`).

---

## 4. Execution Model & Simulation Loop

1. **Hourly Tick**:
   - The engine simulation advances in 1-hour discrete increments.
   - Handled via `[pDateStruct + 0x14]` where hour advances from `0x00` to `0x17` (23:00).
   - Province combats, naval movements, air sorties, and hourly supply consumption update every hour.
2. **Daily Midnight Update**:
   - At hour 0:00, daily routines fire: IC calculations, resource stockpile updates, trade agreement deliveries, diplomacy checks, and AI garrison evaluations (`CGarrisonAI::UpdateGarrisons` @ `0x0068BA50`).
3. **Deterministic Command Queue**:
   - All diplomatic actions, unit orders, and event choices are serialized into deterministic command packets processed in FIFO order.
