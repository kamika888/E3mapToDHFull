# Darkest Hour Core Data Structures & Global Tables

**Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour.exe`  
**Scope**: In-memory layout of simulation objects, global pointer arrays, country structures, AI modules, and linked lists.

---

## 1. Core Global Data Tables & Pointers

| Global Identifier | Virtual Address | Description | Access Pattern |
|---|---|---|---|
| `DAT_00dc0fd4` | `0x00DC0FD4` | **IsHuman Controller Array** | `*(int*)(0x00DC0FD4 + tag * 4)`<br>`1` = Human player, `0` = AI |
| `DAT_0089cad8` | `0x0089CAD8` | **Country Pointer Table** | `*(Country**)(0x0089CAD8 + tag * 4)`<br>Returns base pointer to country object |
| `pDateStruct` | `0x00893530` | **Engine Time & Date Pointer** | `[0x00893530] + 0x14`<br>Base of 6-byte runtime date struct |
| `szClockBuffer` | `0x00D0B68C` | **UI Formatted Clock String** | ASCII string: `"H:00 Month D, YYYY"` |
| `TokenTable` | `0x0084FA64` | **Scenario Parser Token Table** | Maps token strings to token IDs (e.g. `0x52E` = `dont_want_exp_forces`) |

---

## 2. Global Country Tags (Internal Engine Enum)

Country tags are **not** dynamically assigned per scenario; they are defined as a global, hardcoded internal enumeration compiled directly into the executable's tag registration function (`FUN_004ab800`). When the game initializes, `FUN_004ab800` builds the global hash/lookup table mapping 3-letter ASCII tags to 32-bit integers.

**These integer IDs are identical across ALL scenarios, save games, and mods:**

| ID | Tag | Country Name | ID | Tag | Country Name |
|---|---|---|---|---|---|
| `0` | `---` | None / Rebel / Uncontrolled | `11` | `JAP` | Japan |
| `1` | `ENG` | United Kingdom | `12` | `CHI` | Nationalist China |
| `2` | `FRA` | France | `13` | `POL` | Poland |
| `3` | `GER` | Germany | `14` | `NOR` | Norway |
| `4` | `HOL` | Netherlands | `15` | `BEL` | Belgium |
| `5` | `POR` | Portugal | `16` | `DEN` | Denmark |
| `6` | `ITA` | Italy | `17` | `SCH` | Switzerland |
| `7` | `SOV` | Soviet Union | `18` | `CUB` | Cuba |
| `8` | `SPA` | Nationalist Spain | `19` | `GRE` | Greece |
| `9` | `SWE` | Sweden | `20` | `BUL` | Bulgaria |
| `10` | `TUR` | Turkey | `21`.. | ... | Additional tags defined sequentially |

---

## 3. Runtime Data Structure Layouts

### 3.1 `Country` Structure
Base pointer retrieved from `DAT_0089cad8[tag]`:

```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x0000         void*               Virtual Method Table (vtable)
+0x0006         int32 (dword)       Country Tag (e.g. 1=ENG, 2=FRA, 3=GER)
+0x000A         void*               Country name / identity metadata
+0x0120         CAI*                AI Controller Subsystem pointer
                +0xB8               CAI::m_diplomacy / Foreign Minister module
                [[+0x120]+0xB8]+24  Virtual method: IsAtWar / CanCooperate(target_tag)
                +0x1C0              Trade Embargo container (HasTradeEmbargoAgainst @ 0x004A74E0)
                +0x204              Tech Embargo container (HasTechEmbargoAgainst @ 0x004A7500)
+0x12DA         CDiplomacy*         Diplomatic Relations & Master Relationship pointer
                +0x0C               Array of 344 relation records (44 bytes / 0x2C per tag)
                                    Record internal offsets:
                                      +0x00..+0x03: value (float, -200.0 to +200.0)
                                      +0x2C: atwar (byte, 1 = at war with target)
                                      +0x32: military control / guarantee (byte)
                                      +0x36: m_bNAP (Non-Aggression Pact byte, queried by 0x005861E0)
                                      +0x37: m_bAccess (Military Access byte, queried by 0x005861A0)
                +0x3B30             Master Country Tag (0 = sovereign)
+0x3350         CAlliance*          Alliance / Major Faction container pointer
                                    (All members of the same alliance share an identical m_pAlliance pointer.
                                     Note: Bilateral alliances are NOT stored as flags in relation records;
                                     alliances exist strictly via m_pAlliance and puppet/master relations)
                +0x22               Pointer to alliance member container
                [[+0x3350]+0x22]+4  Head node of ally country tags linked list
+0xE86E         FrontNode*          Head of active Fronts linked list (CFront*)
+0xF4EE         float[344]          m_TradeEfficiency array (0.0 to 1.0 per country tag)
+0x1183E        FlagMap             local_flags associative map (LookupFlag @ 0x006C5280)
+0x11862        uint8[] (byte[])    dont_want_exp_forces boolean array
                                    *(byte*)(Country + 0x11862 + target_tag)
                                    1 = refuses expeditionary forces from target_tag
                                    0 = accepts expeditionary forces
```

#### Linked List Traversal Pattern
Darkest Hour uses standard singly-linked list nodes across its simulation objects:
```c
struct ListNode {
    void*     pItem;    // +0x00: Pointer to object (or integer tag)
    void*     pUnk;     // +0x04: Context / back-pointer
    ListNode* pNext;    // +0x08: Pointer to next node (NULL at tail)
};
```

---

### 3.2 `CGarrisonAI` Structure
The garrison evaluator object passed as `this` (`ecx`) into `FUN_00695520` and `FUN_0068ba50`:

```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x00           void*               Vtable
+0x0A           Country*            Pointer to owning Country object (e.g. UK)
+0x10..+0x40    int32 / float       Garrison ratios, homeland defense requirements
```

- **Tag Query Helper (`FUN_006a9d50`)**:
  ```c
  int __fastcall CGarrisonAI::GetTag(CGarrisonAI* this) {
      return *(int*)(*(int*)(this + 0x0A) + 0x06);
  }
  ```

---

### 3.3 `CFront` (Front Object) Structure
Represents an active front or border segment:

```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x00           void*               Vtable
+0x52           int32               Front Requirement / Deficit Flag (>0 needs troops)
+0x56..+0x80    ProvinceList        Provinces along front and adjacent enemy provinces
```

- **Validation Routine (`FUN_004ca33c`)**: Verifies whether the front is active and valid for garrison operations.
- **Deficit Computation (`FUN_00695380`)**: Calculates net division deficit against enemy front concentration. Returns integer deficit (>0 indicates reinforcements required).

---

### 3.4 `CArmy` (Corps / Army Group) Structure
Represents a land unit counter on the map:

```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x00           void*               Vtable
+0x10           int32               Unit ID (e.g. 200010)
+0x14           char[]              Army Name (e.g. "BEF Corps")
+0x298          int32               Target Province ID (e.g. 41 = Le Havre; 0 = none)
+0x29C          List*               Movement Route / Waypoint List
```

- When an overseas mission is assigned by `FUN_00696ef0`, `[CArmy + 0x298]` is written with the port province ID, prompting the transport minister to schedule naval lift.

---

### 3.5 Engine Time & Date Structure
Located at `[0x00893530] + 0x14`:

```
Byte Offset     Type        Format / Meaning
--------------------------------------------------------------------------------------
+0x00           uint8       Hour of day (0x00 .. 0x17 = 0:00 to 23:00)
+0x01           uint8       Day of month (0-indexed: 0x00 = 1st, 0x03 = 4th, etc.)
+0x02           uint8       Month of year (0-indexed: 0x00 = Jan, 0x06 = July)
+0x03           uint8       Flags / Tick state
+0x04..0x05     uint16      Year (little-endian: 0x0790 = 1936)
```

