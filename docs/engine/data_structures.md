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
Represents an active front or border segment. Linked list head at `pCountry + 0xE86E`. Vtable: `0x007E7D34`.

```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x00           void*               Vtable (0x007E7D34)
+0x04           void*               Internal state container (vtable: 0x007E4B04)
+0x18           void*               Front node vtable (0x007E7C08)
+0x28           void*               Front segment descriptor (vtable: 0x007E6EAC)
+0x3C           void*               Province list container (vtable: 0x007E8AB0)
+0x44           uint16              Count of provinces comprising this front segment
+0x52           int32               Front Requirement / Deficit Flag (>0 needs troops)
+0x8C           uint32              Owning Country Tag (e.g. 7 = SOV)
+0x94           uint32              Opposing Enemy Country Tag (e.g. 3 = GER)
+0x98           uint32              Secondary opposing tag / allied border tag
+0xD8           Country*            Pointer to owning Country object
```

- **Validation Routine (`FUN_004ca33c` @ `0x004CA33C`)**: Verifies whether the front is active and valid for operations.
- **Deficit Computation (`FUN_00695380` @ `0x00695380`)**: Calculates net division deficit against enemy front concentration. Returns integer deficit (>0 indicates reinforcements required).
- **Front Army Evaluation (`0x006A6A20`)**: Evaluates assigned armies (`[this + 0x94]`) and dispatches shift, attack, or support move orders.

---

### 3.4 `CLandArmy` (Land Army / Division Group) Structure
Represents a land unit counter on the map. Vtable: `0x007E85C0`. Size: `0x320` bytes.

```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x00           void*               Vtable (0x007E85C0)
+0x04           char*               Pointer to null-terminated unit name
+0x0C           uint16              Current Province ID (where army is stationed)
+0x10           void*               Head of child divisions linked list
+0x18           uint16              Unit ID Type field (e.g. 10848 / 0x2A60)
+0x1A           uint16              Unit ID Sequence Number (e.g. 9 / 0x0009)
+0x28           void*               IsLandArmy virtual call (+0x28 -> 0x00509C90, returns 1)
+0x11C          struct              Combat State container (vtable: 0x007E8B04, +0x0C: in-combat flag)
+0x15A          void*               Map Sprite / Counter graphics object
+0x17B          uint8               Movement State Byte: 1 = actively marching, 0 = stationary
+0x17E          uint8               Movement arrow update flag (1 = dirty)
+0x1F0          void*               Movement path container
+0x22E          void*               Waypoint container vtable (0x007EAAD0)
+0x230          void*               Waypoint queue pointer
+0x238          uint16              Waypoint count in queue
+0x240          uint16              Starting province ID of current move leg
+0x248          Country*            Owning Country pointer ([pArmy + 0x248])
+0x260          struct              CMissionController (0x60 bytes, vtable: 0x007E8754)
+0x264          uint32              Mission Type in controller (1 = MOVE, 0 = NONE)
+0x268          uint32              Target Province ID in controller
+0x26C          float               Movement speed multiplier (1.0f = 0x3F800000)
+0x270          uint32              Mission Start Date (packed format)
+0x27E          uint16              Active Mission Code (1 = MOVE)
+0x282          uint16              Destination Province ID
```

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

---

### 3.6 `CProvince` Structure
All provinces are stored in a contiguous array in the engine heap.

- **Base Pointer**: `*(uint32_t*)0x00AB27B4`
- **Structure Stride**: `0x4B2` (1,202 bytes)
- **Direct Address Formula**: `prov_base + prov_id * 0x4B2`

```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x00           void*               Vtable
+0x0C           uint16              Owner Country Tag / ID
+0x0E           uint16              Controller Country Tag / ID
+0x12           uint16              Province Numerical ID
+0x180          uint8               Impassable / Blocked border flag (1 = blocked)
+0x254          uint32              Terrain Type (8 = Sea, 9 = Ocean)
+0x290          uint32              Count of adjacent neighbor provinces
+0x298          void*               Pointer to neighbor array (12 bytes per record)
                                      +0x00: Neighbor Province ID (uint32)
                                      +0x04: Connection / Border Type
                                      +0x08: Distance / Flags
+0x471          uint8               Direct sea zone access flag
```

---

### 3.7 `CMissionController` Structure (Embedded at `pArmy + 0x260`)
Vtable: `0x007E8754`. Manages operational missions (Move, Attack, Rebase, Patrol).

```
Offset from Base  Type          Description
--------------------------------------------------------------------------------------
+0x00             void*         Vtable (0x007E8754)
+0x04             uint32        Mission Type: 0 = None, 1 = Move, 2 = Attack, 3 = Rebase...
+0x08             uint32        Target Province ID
+0x0C             float         Speed Multiplier (1.0f = 0x3F800000)
+0x10             uint32        Mission Start Date / Packed Timestamp
+0x1C             uint16        Mission Active Flag (1 = active)
+0x1E             uint16        Active Mission Code (1 = MOVE)
+0x22             uint16        Destination Province ID
```

