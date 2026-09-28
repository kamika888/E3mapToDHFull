# Darkest Hour (v1.05.2, Checksum TENE) — Hourly Game Loop Disassembly Notes

## 1. Hourly Tick Dispatcher (`0x005AED00` – `0x005AEEC0`)

This function is part of the message/event dispatcher handling the timer tick message (`0x005AEC40` event handler):

```asm
005AEDB1: mov ecx, dword ptr ds:[0x00893530] ; Load global GameState pointer
005AEDB7: push 0x01                          ; Push 1 hour increment
005AEDB9: call 0x0042CF30                    ; AdvanceDate(1)
005AEDBE: push 0x0C                          ; Return site (break target)
005AEDC0: call 0x007A635C                    ; operator new(0x0C)
005AEDC5: mov esi, eax                       ; Allocated event object
005AEDC7: add esp, 0x04
005AEDCA: mov dword ptr ss:[esp+0x14], esi
...
005AEE8B: call 0x00565C30                    ; Enqueue/post tick event
...
005AEE90: mov ecx, dword ptr ds:[edi+0x04]
005AEE93: mov eax, dword ptr ss:[esp+0x14]
005AEE9A: inc eax                            ; Counter++
005AEE9B: mov edx, dword ptr ds:[ecx+0x0E]   ; Loop limit (normally 1)
005AEE9E: mov dword ptr ss:[esp+0x10], eax
005AEEA2: cmp eax, edx
005AEEA4: jl 0x005AEDB1                      ; Loop back if more hours to process
005AEEAA: pop ebp
005AEEAB: pop ebx
005AEEAC: jmp 0x005AEEC0                     ; Exit function
```

---

## 2. Date Progression Routine (`0x0042CF30` / `0x0042CF40`)

Top-level function that sets up SEH and invokes date arithmetic:

```asm
0042CF30: push 0xFFFFFFFF
0042CF32: push 0x7BA182                      ; SEH handler
0042CF37: mov eax, dword ptr fs:[0]
0042CF3E: mov dword ptr fs:[0], esp
0042CF45: sub esp, 0x1C
0042CF48: push ebx
0042CF49: mov edx, dword ptr ss:[esp+0x30]   ; Parameter: hours to add (1)
0042CF4E: mov ebp, ecx                       ; GameState pointer
...
0042CF5E: lea edi, ss:[ebp+0x14]             ; Pointer to packed Date struct
0042CF65: push edx                           ; Hours to add
0042CF66: mov ecx, edi                       ; this = Date struct
0042CF6C: call 0x0042DB80                    ; AddHoursToDate
```

---

## 3. Date Arithmetic & Remainder Conversion (`0x0042DB80`)

```asm
; Converts {year, month, day, hour} to absolute hours and adds delta:
0042DB80: movsx eax, word ptr ds:[ecx+0x04]  ; Year
0042DB84: movsx edx, byte ptr ds:[ecx+0x02]  ; Month
0042DB88: lea eax, ds:[eax+eax*2]            ; eax = year * 3
0042DB90: lea eax, ds:[edx+eax*4]            ; eax = month + year * 12
0042DB93: movsx edx, byte ptr ds:[ecx+0x01]  ; Day
0042DB97: lea eax, ds:[eax+eax*2]
0042DB9A: lea eax, ds:[eax+eax*4]            ; eax = (month + year*12) * 15
0042DB9D: lea eax, ds:[edx+eax*2]            ; eax = day + (total_months) * 30
0042DBA0: movsx edx, byte ptr ds:[ecx]       ; Hour
0042DBA3: lea eax, ds:[eax+eax*2]
0042DBA6: add esi, edx                       ; Add current hour
0042DBA8: lea esi, ds:[esi+eax*8]            ; Total absolute hours
...
; Divides total hours back into calendar components:
0042DBC4: mov esi, 0x21C0                    ; 8640 hours/year (360 * 24)
0042DBCA: idiv esi
0042DBC0: mov word ptr ds:[ecx+0x04], dx     ; Store new year

0042DBE6: mov esi, 0x2D0                     ; 720 hours/month (30 * 24)
0042DBEC: idiv esi
0042DBE3: mov byte ptr ds:[ecx+0x02], dl     ; Store new month

0042DC06: mov esi, 0x18                      ; 24 hours/day
0042DC0C: idiv esi
0042DC03: mov byte ptr ds:[ecx+0x01], dl     ; Store new day
0042DC0F: mov byte ptr ds:[ecx], dl          ; Store new hour (0x0042DC11 return)
```

---

## 4. UI Clock Formatting & Control Invalidation (`0x0064B170`)

```asm
0064B174: add ecx, 0x14                      ; Date struct pointer
0064B177: push ecx                           ; Arg 2: inDate struct
0064B178: push 0xD0B68C                      ; Arg 1: outBuffer ("0:00 July 4, 1936")
0064B17D: call 0x0079168D                    ; FormatDateString
0064B182: add esp, 0x08
0064B185: mov ecx, edi                       ; UI Clock control object
0064B187: push 0xD0B68C                      ; Formatted text
0064B18C: call 0x004129C4                    ; SetControlText
...
0064B1AF: call dword ptr ds:[edx+0x18]       ; Invalidate/Repaint Control
```

---

## 5. Main Game Loop Frame Presenter (`0x007902D0` – `0x00790340`)

```asm
007902D9: mov edx, dword ptr ds:[ecx]
007902E1: call dword ptr ds:[edx+0x34]       ; Process windows message pump
007902EC: call 0x006D09E0                    ; DirectDraw surface lock / render
00790312: call 0x0042E9A0                    ; Check pause state / timer
0079033C: mov ecx, dword ptr ds:[0x00BD1BA8] ; Map/Viewport renderer
00790342: call dword ptr ds:[eax+0x10]       ; Present frame
```
