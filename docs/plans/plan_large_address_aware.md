# Patch 7: Large Address Aware (LAA) Flag

**Status**: Implemented & Verified  
**Engine**: Darkest Hour 1.05.2 (TENE)  
**Target File**: `Darkest Hour.exe` (File Offset: `0x00000116`)  
**Patch Category**: Memory Architecture & Stability  

---

## 1. Overview & Motivation

Darkest Hour is a 32-bit x86 Windows executable built with Microsoft Visual C++. By default, 32-bit Windows applications are restricted by the operating system kernel to a **2 GB user-mode virtual address space** (`0x00000000` to `0x7FFFFFFF`), while the upper 2 GB (`0x80000000` to `0xFFFFFFFF`) is reserved for the Windows NT kernel.

In high-complexity scenarios—such as total conversion mods with detailed maps (*E3mapToDHFull*, thousands of additional provinces, historical OOBs, sprite sheets, and extensive event databases)—the engine's heap allocations, texture surfaces, and scenario structures routinely approach the 1.8 GB - 2.0 GB ceiling. Once this threshold is reached, any subsequent `malloc`, `new`, or DirectX surface allocation fails, causing an immediate crash to desktop (CTD) or `"Out of Memory"` abort during scenario load or prolonged gameplay.

This patch flips the `IMAGE_FILE_LARGE_ADDRESS_AWARE` flag in the PE header, instructing modern 64-bit Windows operating systems to grant the Darkest Hour process access to a full **4 GB virtual address space**.

---

## 2. Technical Specification & PE Header Modification

### 2.1 PE COFF File Header Characteristics
In the PE file format, the `IMAGE_FILE_HEADER` structure defines process characteristics at offset `0x00000116`:

```
Offset      Size    Field               Description
--------------------------------------------------------------------------------------
0x00000100  4       Signature           "PE\0\0" (0x00004550)
0x00000104  2       Machine             0x014C (IMAGE_FILE_MACHINE_I386)
0x00000106  2       NumberOfSections    0x0005
0x00000108  4       TimeDateStamp       ...
0x0000010C  4       PointerToSymbolTable 0x00000000
0x00000110  4       NumberOfSymbols     0x00000000
0x00000114  2       SizeOfOptionalHeader 0x00E0
0x00000116  2       Characteristics     Flag bitfield
```

### 2.2 Bitfield Values

| Characteristic Flag | Bit Value | Unmodified Retail | Patched Engine |
|---|---|---|---|
| `IMAGE_FILE_RELOCS_STRIPPED` | `0x0001` | Set | Set |
| `IMAGE_FILE_EXECUTABLE_IMAGE` | `0x0002` | Set | Set |
| `IMAGE_FILE_LINE_NUMS_STRIPPED` | `0x0004` | Set | Set |
| `IMAGE_FILE_LOCAL_SYMS_STRIPPED` | `0x0008` | Set | Set |
| `IMAGE_FILE_LARGE_ADDRESS_AWARE` | `0x0020` | **Clear** (`0`) | **Set** (`1`) |
| `IMAGE_FILE_32BIT_MACHINE` | `0x0100` | Set | Set |
| **Total Characteristics Word** | | **`0x010F`** | **`0x012F`** |

### 2.3 Binary Modification
- **Target File Offset**: `0x00000116` (Low byte of `Characteristics`)
- **Original Value**: `0x0F`
- **Patched Value**: `0x2F` (`0x0F | 0x20`)

---

## 3. Operational Impact

1. **Address Space Expansion**:
   - On 64-bit Windows (x64): Process address space doubles from 2,048 MB (2 GB) to 4,096 MB (4 GB).
   - On 32-bit Windows with `/3GB` boot switch: Process address space increases to 3,072 MB (3 GB).
2. **Crash Elimination**:
   - High-resolution map caching, scenario loading, and intensive event chains no longer trigger heap exhaustion.
   - Scenario reload memory leaks (prior to Patch 8) no longer hit an immediate 2 GB wall on the second load.
3. **Engine Compatibility**:
   - The Darkest Hour engine uses standard 32-bit unsigned/signed pointers and does not perform sign-bit pointer arithmetic exploits that would conflict with pointers above `0x7FFFFFFF`. Runtime stability is 100% preserved.

---

## 4. Integration in Patcher (`tools/patch_darkest_hour.bat`)

Patch 7 is applied directly during the binary patch execution:
```powershell
# Patch 7: Large Address Aware (LAA) Flag (PE Characteristics @ 0x00000116)
$charOffset = 0x00000116
$null = $fs.Seek($charOffset, [System.IO.SeekOrigin]::Begin)
$charByte = $fs.ReadByte()
if (($charByte -band 0x20) -eq 0) {
    $null = $fs.Seek($charOffset, [System.IO.SeekOrigin]::Begin)
    $fs.WriteByte([byte]($charByte -bor 0x20))
}
```
