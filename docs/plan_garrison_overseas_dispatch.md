# Technical Analysis & Fix: AI Homeland Garrison Dispatch to Human Allies

## 1. Executive Summary

In Darkest Hour (v1.05.2, checksum `TENE`), when starting from peacetime scenarios (such as `TestSave2.eug`, July 4, 1936), the British AI (`ENG`) was observed to behave differently depending on who controlled France (`FRA`):

- **When loaded as Germany (France AI)**: Exactly at `0:00 July 5, 1936` (24 hour ticks), British AI Garrison logic dispatches the homeland army **"BEF Corps"** (`id = 200010`, division "BEF HQ" `id = 200011`) from London (`location = 19`) towards France with `target = 41` (Le Havre), and at `01:00 July 5` it begins moving to Dover (`location = 20`) to board transport vessels.
- **When loaded as France (France Human)**: The British AI never assigned `target = 41` to BEF Corps, leaving it permanently stationed in London.

Reverse engineering of the game executable revealed a hardcoded human-player check in the Garrison AI's allied reinforcement evaluator (`FUN_00695520`) that explicitly skipped evaluating fronts belonging to human allies.

Furthermore, an investigation into the in-game diplomacy toggle *"We do not want expeditionary forces from [country name]"* (`dont_want_exp_forces = yes`) revealed an edge-case bug: while core unit control transfer honored the toggle upon arrival, the Garrison AI overseas dispatch logic did not check it. This created an infinite transport loop (troops shipped to France -> refused -> shipped back home -> dispatched again).

By replacing the old human check with a direct evaluation of `dont_want_exp_forces` utilizing the function's trailing code cave, the AI now:
1. Dispatches overseas garrison reinforcements to human-controlled allies when welcomed (e.g. `TestSave2.eug`).
2. Honors the diplomatic refusal flag and suppresses overseas troop shipments completely (e.g. `TestSave3.eug`), eliminating the embark/recall loop.

---

## 2. Reverse Engineering & Architecture

### 2.1 The Peacetime Expedition Subsystems

Allied expeditionary support in Darkest Hour consists of three interconnected layers:

1. **Stationed Unit Control Transfer (`FUN_004ccb2c`, `Front::GetLeadingCountry`)**:
   - Governs whether troops *already present* on an ally's territory are handed over to the host nation.
   - Addressed by **Fix #1** (`0x000CCCC0: 0x75 -> 0xEB`).
2. **Homeland Garrison Expedition Dispatch (`FUN_0068ba50` & `FUN_00695520`)**:
   - Governs whether AI nations evaluate overseas allied fronts for troop deficits and dispatch *reserve armies stationed at home* across sea zones.
   - Addressed by **Fix #2 & #3** (`0x00295593` and `0x002955E5`).
3. **Diplomatic Relations Structure (`Country + 0x11862 + target_tag`)**:
   - A 1-byte boolean array inside each `Country` struct.
   - Initialized from scenario / save token `dont_want_exp_forces` (token ID `0x52E`, parsed at `0x00588CFD`).
   - If country $A$ does not want expeditionary forces from country $B$:
     `*(byte*)(Country_A + 0x11862 + Tag_B) == 1`.
   - Checked at `0x00693C61` during unit transfer and at `0x00696546` in AI transport operations, but previously omitted in Garrison overseas front selection (`FUN_00695520`).

---

### 2.2 The Garrison AI Dispatch Pipeline (`FUN_0068ba50`)

At the start of `FUN_0068ba50` (hourly garrison evaluation), the routine queries:
```c
local_e4 = FUN_00695520(param_1); // FindAlliedFrontNeedingTroops
```
Later in the function (at `LAB_0068db1c`, `0x0068DB2F`):
```asm
0x0068DB2F: cmp dword ptr [ebp-0xE0], ebx   ; check if local_e4 == 0
0x0068DB35: je 0x0068E291                   ; IF NULL, SKIP ENTIRE EXPEDITION DISPATCH!
```
If `local_e4 != 0`:
1. It computes overseas reserve capacity based on homeland garrison ratios.
2. It selects a port province belonging to the allied front (`target = 41`, Le Havre).
3. At `0x0068E18E`, it calls `FUN_00696ef0` with `param_2 = BEF Corps` and `param_3 = 41`.
4. Instruction `0x00696F43` writes `[BEF Corps + 0x298] = 41`.
5. `CAITransportMinister::UpdateArmy` books naval transports, orders the army to march to Dover (`20`), and logs:
   `"Garrison AI: %s ships size %d army from %s to %s."`

---

### 2.3 The Ally Evaluation Loop in `FUN_00695520`

Inside `FUN_00695520`, the AI loops through all members of its diplomatic alliance:

```asm
; --- Alliance Member Iteration ---
0x00695561: mov eax, ebx
0x00695563: mov ebx, dword ptr [ebx+0x08]            ; next ally node
0x00695566: mov ecx, dword ptr [eax]                 ; ally tag (e.g. FRA = 2)
0x00695568: mov eax, dword ptr [ebp+0x0A]            ; donor country pointer (UK)
0x0069556B: mov esi, dword ptr [ecx*4+0x0089CAD8]    ; ally country pointer
0x00695572: cmp esi, eax                             ; skip self (UK)
0x00695574: je 0x006955D3
0x00695576: mov eax, dword ptr [eax+0x120]           ; AI configuration
0x0069557C: mov edx, dword ptr [esi+0x06]
0x0069557F: push edx
0x00695580: lea ecx, [eax+0xB8]
0x00695586: mov eax, dword ptr [eax+0xB8]
0x0069558C: call dword ptr [eax+0x24]                ; check no_expeditionary_forces list
0x0069558F: test al, al
0x00695591: jne 0x006955D3

; --- ORIGINAL HUMAN CHECK (REPLACED) ---
0x00695593: mov ecx, dword ptr [esi+0x06]            ; ally tag
0x00695596: mov eax, dword ptr [ecx*4+0x00DC0FD4]    ; IsHuman[tag]
0x0069559D: test eax, eax
0x0069559F: jne 0x006955D3                           ; skipped all human allies
```

---

## 3. Patch Implementation

Rather than merely disabling the `IsHuman` check, the 14-byte slot at `0x00695593` and the 11-byte NOP padding cave at `0x006955E5` (at the function epilogue) are repurposed to query `dont_want_exp_forces`.

### 3.1 Hook at `0x00695593` (14 bytes)

```asm
0x00695593: 8B 45 0A         mov eax, dword ptr [ebp + 0x0A]   ; donor Country* (UK)
0x00695596: 8B 40 06         mov eax, dword ptr [eax + 0x06]   ; donor tag (UK tag = 3)
0x00695599: 03 C6            add eax, esi                      ; eax = ally Country* + donor tag
0x0069559B: EB 48            jmp short 0x006955E5              ; jump to cave
0x0069559D: 90 90 90 90      nop; nop; nop; nop                ; alignment padding
```

### 3.2 Code Cave at `0x006955E5` (11 bytes)

```asm
0x006955E5: 80 B8 62 18 01 00 00   cmp byte ptr [eax + 0x11862], 0  ; test dont_want_exp_forces[donor]
0x006955EC: 75 E5                  jne 0x006955D3                   ; if set, skip ally!
0x006955EE: EB B1                  jmp 0x006955A1                   ; else proceed to evaluate fronts
```

Both blocks fit their respective boundaries with exact byte precision:
- `0x00695593` to `0x006955A0`: exactly 14 bytes.
- `0x006955E5` to `0x006955EF`: exactly 11 bytes (formerly compiler NOP alignment).
- Next function at `0x006955F0`: 100% untouched.

---

## 4. Empirical Verification

Verification was performed under `x32dbg` attached to `Darkest Hour.exe` across both scenarios:

### Case A: Human France with `dont_want_exp_forces = yes` (`TestSave3.eug`)
- **Setup**: France is human-controlled and has toggled *"We do not want expeditionary forces from United Kingdom"*.
- **Runtime Observation**:
  - Breakpoint at `0x006955E5` triggers.
  - `[eax + 0x11862]` evaluates to `0x01` (`ZF = false`).
  - Instruction `0x006955EC` (`jne 0x006955D3`) takes the branch, cleanly skipping France.
  - Over **13 consecutive in-game days** (from July 4 to July 17, 1936), the British **BEF Corps remained peacefully stationed in London** without attempting to embark on transports or sail to France. The infinite loop is completely resolved.

### Case B: Human France without `dont_want_exp_forces` (`TestSave2.eug`)
- **Setup**: France is human-controlled with standard alliance relations.
- **Runtime Observation**:
  - `[eax + 0x11862]` evaluates to `0x00` (`ZF = true`).
  - Instruction `0x006955EE` jumps to `0x006955A1`, entering France's front list.
  - At `0:00 July 5`, UK Garrison AI identifies troop deficit in France and assigns `target = 41` (Le Havre).
  - At `1:00 July 5`, BEF Corps departs London, marches to Dover (`20`), and embarks on transports to aid human France.

---

## 5. Binary Signatures & Hashes

| File | Status | SHA-256 |
|---|---|---|
| `Darkest Hour_original.exe` | Pristine v1.05.2 (TENE) | `7A1AE8BB802377B6C9EC808F420ACE58475D1816464390422CF97AD450A51EB4` |
| `Darkest Hour_modified.exe` | Patched (v2.0 All Fixes) | `1DB5DC08A644080CDACF56B103F91B3C696DBF5FCB83723E671B9A51814CD98E` |
| `Darkest Hour.exe` | Active Executable | `1DB5DC08A644080CDACF56B103F91B3C696DBF5FCB83723E671B9A51814CD98E` |

The standalone batch tool `patch_darkest_hour.bat` in the game root directory supports applying, reverting, and verifying all three fixes without external dependencies.
