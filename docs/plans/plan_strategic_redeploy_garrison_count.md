# Implementation Plan: Fix Perpetual Garrison Shuffling via Strategic Redeployment & Immediate Arrival Accounting

## Executive Summary

The retail Darkest Hour engine contains a fundamental blind spot in `CGarrisonAI::UpdateGarrisons` (`FUN_0068ba50` / `0x0068BA50`).

When calculating the incoming troop count (`CurrentIncoming`) for a candidate province, the engine checks only active map armies (`CArmy*`) moving overland on foot (`FUN_0068E340`). Divisions in the **strategic redeployment pool** have been temporarily detached from the map and placed into `CCountry::m_listStrategicRedeployment`. Because the garrison AI never inspects this list, it treats provinces awaiting strategic redeployment arrivals as having **0 incoming troops**.

This causes the AI to perceive a full deficit, immediately dispatching duplicate divisions from elsewhere. When the redeploying troops arrive, the province suffers a massive surplus, prompting the AI to evacuate them anew--producing the **perpetual garrison shuffling** loop that worsens drastically when `max_redeploying` is increased or `strat_redeploy_threshold` is decreased.

Furthermore, upon arrival, newly spawned divisions have not yet been assigned to the area's garrison AI (`m_pAIController == NULL` or parent `pRootGarrisonAI`), causing a momentary 1-hour garrison deficit glitch where nearby divisions are ordered away before immediately reversing.

---

## Technical Root Cause Analysis

### 1. Disassembly of Retail Incoming Count Calculation
In `Darkest Hour.exe` at `0x0068CCC4`-`0x0068CD0A` (`CGarrisonAI::UpdateGarrisons`):

```asm
0068CCB5: push   eax                         ; Target Province ID ([pProv + 0x12])
0068CCB6: lea    edx, [ebp-0x154]
0068CCBC: push   ecx
0068CCBD: push   edx
0068CCBE: mov    ecx, ebx                    ; ecx = CGarrisonAI* (this)
0068CCC0: mov    byte ptr [ebp-0x04], 0x0E
0068CCC4: call   0x0068E340                  ; Populates marching armies list at [ebp-0xD8]
0068CCC9: mov    eax, dword ptr [ebp-0xD8]   ; Head of marching armies list
0068CCCF: xor    edi, edi                    ; edi = Incoming division counter (starts at 0)
0068CCD1: test   eax, eax
0068CCD3: jz     0x0068CCEC                  ; If marching list empty, skip march loop!
0068CCD5: mov    esi, dword ptr [esi+0x12]   ; esi = Target Province ID
0068CCD8: mov    ecx, eax
0068CCDA: mov    eax, dword ptr [eax+0x08]   ; node->next
0068CCDD: mov    ecx, dword ptr [ecx]        ; ecx = CArmy*
0068CCDF: cmp    dword ptr [ecx+0x14C], esi  ; Check CArmy march destination
0068CCE5: jnz    0x0068CCE8
0068CCE7: inc    edi                         ; edi++ (Overland marching division count)
0068CCE8: test   eax, eax
0068CCEA: jnz    0x0068CCD8
0068CCEC: lea    ecx, [ebp-0x154]            ; <-- HOOK SITE: Both paths converge here!
0068CCF2: call   0x00527B40                  ; eax = Divisions physically present in province
0068CCF7: mov    ecx, dword ptr [ebp-0xD0]
0068CCFD: mov    edx, dword ptr [ebp-0x8C]
0068CD03: add    edx, ecx
0068CD05: add    eax, edi                    ; Total = Present (eax) + Marching (edi)
0068CD0A: mov    dword ptr [ebp-0x12C], eax  ; Store CurrentIncoming
```

### 2. The Critical Flaws
1. `FUN_0068E340` only traverses `CArmy` entities currently physically present on the map that have an active overland march destination (`[pArmy + 0x14C]`).
2. When a division is strategically redeployed:
   - It is removed from the province `CArmy` list and from the world map.
   - It is added to `CCountry`'s linked list `m_listStrategicRedeployment`.
3. **`FUN_0068cb23` completely ignores `CCountry::m_listStrategicRedeployment`!**
4. For any province awaiting strategic redeployment arrivals:
   - `OverlandMarchingCount (edi)` = 0.
   - `PhysicallyPresentCount (eax)` = 0.
   - `CurrentIncoming` = `0 + 0 = 0`!
5. **Fresh Arrival Assignment Disconnect**:
   - When strategic redeployments arrive, `ProcessStrategicRedeployments` creates a new `CArmy` with `m_pAIController == NULL` (or parent `pRootGarrisonAI`).
   - In `CAreaGarrisonAI`'s province unit counting loop (`0x0068C201`), the engine strictly compares `cmp [pArmy + 0x1F4], ecx` (`m_pAIController == this`).
   - Because `m_pAIController` is not yet set to this `CAreaGarrisonAI`, the freshly arrived units count as 0 for up to an hour until the next hierarchy scan, triggering spurious dispatches.

---

## Technical Solution Architecture

### 1. Struct Offsets in Engine Memory
- `ebx` in `UpdateGarrisons` holds `CAreaGarrisonAI*`.
- `[ebx + 0x0A]` holds `CCountry*`.
- `[ebx + 0x3C]` holds `m_pRootGarrisonAI` (parent `CRootGarrisonAI*`).
- `[ebp - 0x28]` holds `CProvince*` for the target province.
- `[pProv + 0x12]` holds the `Target Province ID` (uint32).
- Inside `CCountry`:
  - `[pCountry + 0x4518]` is `CPtrList m_listStrategicRedeployment`.
  - `[pCountry + 0x4518 + 0x04]` = `m_pHead` (pointer to first `CNode`).
- Inside `CNode`:
  - `[pNode + 0x00]` = `pDiv` (`CDivision*`).
  - `[pNode + 0x08]` = `next` (`CNode*`).
- Inside `CDivision`:
  - `[pDiv + 0x14C]` = `Destination Province ID` (uint32).
- Inside `CRootGarrisonAI`:
  - `[pRoot + 0x208]` is `CPtrList m_listArmies`.
  - `[pRoot + 0x208 + 0x04]` = `m_pHead` (`CNode*`).

---

### 2. Patch 15: Strategic Redeployment Accounting (`0x0068CCEC` / `0x00DCB400`)

- **Hook Site**: `0x0068CCEC` (6 bytes: `E9 0F E7 73 00 90` -> `jmp 0x00DCB400; nop`).
- **Cave**: `0x00DCB400` (109 bytes):
  1. Checks runtime toggle `g_EnableStratRedeployGarrison` at `0x00DCB01C`. If 0, skips straight to `.done`.
  2. Traverses `CCountry::m_listStrategicRedeployment` (`[ebx+0x0A] -> +0x451C`). For each division heading to `Target Province ID` (`[pDiv + 0x14C] == TargetProv`), increments `edi` (`CurrentIncoming`).
  3. Traverses `m_pRootGarrisonAI::m_listArmies` (`[ebx+0x3C] -> +0x20C`). For each army present in `Target Province ID` (`[pArmy + 0x0C] == TargetProv`), increments `edi`.
  4. Restores registers, executes replaced instruction `lea ecx, [ebp - 0x154]`, and jumps back to `0x0068CCF2`.

```asm
Cave_CountStrategicRedeployments:
    push    edx
    push    ecx
    push    eax
    push    esi

    cmp     dword ptr [0x00DCB01C], 0
    je      .done

    mov     eax, dword ptr [ebp - 0x28] ; CProvince*
    test    eax, eax
    je      .done
    mov     esi, dword ptr [eax + 0x12] ; Target Province ID

    mov     eax, dword ptr [ebx + 0x0A] ; CCountry*
    test    eax, eax
    je      .check_root
    mov     edx, dword ptr [eax + 0x451C]

.loop_strat:
    test    edx, edx
    je      .check_root
    mov     eax, dword ptr [edx]
    test    eax, eax
    je      .next_strat
    cmp     esi, dword ptr [eax + 0x14C]
    jne     .next_strat
    inc     edi
.next_strat:
    mov     edx, dword ptr [edx + 8]
    jmp     .loop_strat

.check_root:
    mov     eax, dword ptr [ebx + 0x3C] ; m_pRootGarrisonAI
    test    eax, eax
    je      .done
    mov     edx, dword ptr [eax + 0x20C]

.loop_root:
    test    edx, edx
    je      .done
    mov     eax, dword ptr [edx]
    test    eax, eax
    je      .next_root
    cmp     esi, dword ptr [eax + 0x0C]
    jne     .next_root
    inc     edi
.next_root:
    mov     edx, dword ptr [edx + 8]
    jmp     .loop_root

.done:
    pop     esi
    pop     eax
    pop     ecx
    pop     edx
    lea     ecx, dword ptr [ebp - 0x154]
    jmp     0x0068CCF2
```

---

### 3. Patch 16: Immediate Garrison Accounting for Freshly Arrived Armies (`0x0068C201` / `0x00DCB480`)

- **Hook Site**: `0x0068C201` (10 bytes: `E9 7A F2 73 00 90 90 90 90 90` -> `jmp 0x00DCB480; 5x nop`).
- **Cave**: `0x00DCB480` (49 bytes):
  1. Inspects `pArmy->m_pAIController` (`[esi + 0x1F4]`). If already equal to this `CAreaGarrisonAI` (`ecx`), immediately jumps to `count_army` (`0x0068C20B`).
  2. If `EnableStratRedeployGarrison == 0`, jumps to `skip_army` (`0x0068C218`) to maintain 100% retail vanilla behavior.
  3. Verifies army country ownership: `[esi + 0x248] == [ecx + 0x0A]`. If not owned by the same country, jumps to `skip_army`.
  4. If `m_pAIController == NULL` (freshly arrived unassigned) or `m_pAIController == m_pRootGarrisonAI` (`[ecx + 0x3C]`), jumps to `count_army` (`0x0068C20B`).
  5. Otherwise, jumps to `skip_army` (`0x0068C218`).

```asm
Cave_FreshArmyGarrisonFilter:
    mov     eax, dword ptr [esi + 0x1F4]
    cmp     eax, ecx
    je      .count_army

    cmp     dword ptr [0x00DCB01C], 0
    je      .skip_army

    mov     edx, dword ptr [ecx + 0x0A]
    cmp     edx, dword ptr [esi + 0x248]
    jne     .skip_army

    test    eax, eax
    je      .count_army
    cmp     eax, dword ptr [ecx + 0x3C]
    je      .count_army

.skip_army:
    jmp     0x0068C218

.count_army:
    jmp     0x0068C20B
```

---

### 4. Runtime INI Configuration (`db\mod_settings.ini`)

Both Patch 15 and Patch 16 are gated behind a single runtime configuration switch in `db\mod_settings.ini`:

```ini
[GarrisonAI]
; Account for Strategic Redeployment and freshly arrived units in Garrison calculations:
; 0 = Vanilla retail behavior (strat redeploying and unassigned units ignored, causes shuffling)
; 1 = Enhanced behavior (counts strat redeploying and newly arrived units at target provinces, default)
EnableStratRedeployGarrison = 1
```

- **Global Variable**: `g_EnableStratRedeployGarrison` at `0x00DCB01C` (default `1`).
- **INI Loader Cave**: `0x00DCB2D0` (67 bytes). Hooked at `0x00DCB138` during startup Garrison AI configuration. Invokes `GetPrivateProfileIntA("GarrisonAI", "EnableStratRedeployGarrison", 1, ".\\db\\mod_settings.ini")`.
- When set to `0`:
  - Patch 15 immediately exits via `.done`.
  - Patch 16 skips unassigned/root armies, enforcing strict `pArmy->m_pAIController == this`.
  - Behavior reverts to 100.00% unmodified retail vanilla.

---

## Post-Mortem of Intermittent Exception (`0x0068CEB2`)

During intermediate implementation, an Access Violation was encountered at `CIP = 0x0068CEB2`:
1. **Displaced Relative Jumps**: Moving caves from `0x00DCB240`/`0x00DCB290` to `0x00DCB400`/`0x00DCB480` without re-assembling them shifted relative jumps (`E9 <rel32>`) by `+0x1C0` / `+0x1F0`, landing inside a 10-byte instruction at `0x0068CEB2` (`add [eax], al` where `eax = 0`).
2. **Inverted Branch in Obsolete Hook Restore**: File offset `0x0028E3A3` had been written as `39 AF F4 01 00 00 74 08` (`je +8`) instead of pristine `39 AF F4 01 00 00 75 08` (`jne +8`).
3. **Resolution**: Cleanly reassembled both caves with their exact base origins (`0x00DCB400` and `0x00DCB480`), restored `0x0028E3A3` to pristine `jne`, and verified 100% integrity across all entry/exit paths.

---

## Verification & Test Results

- **`TestSave8.eug` (UK Peacetime Allied Garrisoning of France)**:
  - 6 divisions in strategic redeployment pool (2 Amiens, 2 Dieppe, 2 Le Havre) are accurately counted as incoming throughout their multi-day transit.
  - 5 divisions stationed in Caen correctly dispatch 3 to Paris and keep 2 in Caen.
  - Upon redeployment arrival, newly spawned divisions are immediately counted by `CAreaGarrisonAI`, completely eliminating the 1-hour glitch where units launched towards Amiens/Dieppe before reversing.
  - Settle state: Exactly 11 divisions across 5 French provinces (2 Caen, 2 Le Havre, 2 Dieppe, 2 Amiens, 3 Paris) with zero perpetual redeployment shuffling.
