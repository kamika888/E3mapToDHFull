# Darkest Hour Core Data Structures & Global Tables

**Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour.exe`  
**Scope**: In-memory layout of simulation objects, global pointer arrays, country structures, AI modules, and linked lists.

---

## 1. Core Global Data Tables & Pointers

| Global Identifier | Virtual Address | Description | Access Pattern |
|---|---|---|---|
| `DAT_00dc0fd4` | `0x00DC0FD4` | **IsHuman Controller Array** | `*(int*)(0x00DC0FD4 + tag * 4)`<br>`1` = Human player, `0` = AI |
| `DAT_00d0ca90` | `0x00D0CA90` | **Local Player Country Pointer** | `*(Country**)0x00D0CA90`<br>Pointer to local human player's `Country` object |
| `DAT_0089cad8` | `0x0089CAD8` | **Country Pointer Table** | `*(Country**)(0x0089CAD8 + tag * 4)`<br>Returns base pointer to country object |
| `DAT_00ab27b4` | `0x00AB27B4` | **Province Array Base Pointer** | `*(CProvince**)0x00AB27B4 + prov_id * 0x4B2` |
| `pDateStruct` | `0x00893530` | **Engine Time & Date Pointer** | `[0x00893530] + 0x14`<br>Base of 6-byte runtime date struct |
| `szClockBuffer` | `0x00D0B68C` | **UI Formatted Clock String** | ASCII string: `"H:00 Month D, YYYY"` |
| `g_bNoFog` | `0x00D610DC` | **Global NoFog Toggle** | `uint8`: `1` = fog of war disabled (also requires `[pPlayerCountry + 0x21E90] = 1`) |
| `g_bShowId` | `0x00D610E8` | **Global ShowId Toggle** | `uint8`: `1` = display province IDs on map tooltip |
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
+0x34AC         uint8[344]          Per-country front passivity / truce array (checked by 0x006A8720)
+0x4508         ListNode*           Head of country's land armies linked list (CLandArmy*)
+0x451C         ListNode*           Head of strategic redeployment pool linked list
+0xE86E         FrontNode*          Head of active Fronts linked list (CFrontAI*)
+0xF4EE         float[344]          m_TradeEfficiency array (0.0 to 1.0 per country tag)
+0x117DE        uint32              Capital Province ID
+0x1183E        FlagMap             local_flags associative map (LookupFlag @ 0x006C5280)
+0x11862        uint8[] (byte[])    dont_want_exp_forces boolean array
                                    *(byte*)(Country + 0x11862 + target_tag)
                                    1 = refuses expeditionary forces from target_tag
                                    0 = accepts expeditionary forces
+0x13C84        CAI*                Country operational AI controller pointer (ecx for CAI::DispatchMoveOrder @ 0x006AAFF0; NULL for non-AI / pure player)
+0x21E90        uint8               Per-country fog-of-war bypass flag (1 = nofog active when paired with [0x00D610DC] = 1)
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

### 3.3 `CFrontAI` (Front AI / Theater Object) Structure
Represents an active land front segment and its operational AI controller. Linked list head at `pCountry + 0xE86E`. Vtable: `0x007F3868` (base `CFront` vtable: `0x007E7D34`).

```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x00           void*               Vtable (0x007F3868)
+0x04           ListNode*           Head of front border province descriptors list
+0x12           struct              Front Country/Tag query context
+0x1C           Country*            Pointer to owning Country object
+0x9E           uint8               Active wartime evaluation flag
+0xA0           void*               Assigned armies list container vtable
+0xA4           ListNode*           Head of assigned CLandArmy* linked list
+0xC8           CIdList             m_SalientEvacuatingUnits (list of 6-byte TypeId structs [type:u16, id:u32] exempt from normal front quota/StopMovement overrides; Insert @ 0x0049A190)
+0x124          uint32              Front distribution mode (0 = default, 1 = reactive, 2 = defensive, 3 = op_defensive)
+0x125          uint8               Defensive hold flag
+0x126          uint32              Hourly evaluation tick counter
+0x12A          CIntList            m_SalientProvinces (interior provinces adjacent to salient border provinces)
+0x12E          ListNode*           Head of single-connection salient tip province IDs
```

- **Master Front AI Tick (`CFrontAI::Execute` @ `0x006811B0`)**: Invokes `CFrontAI::MoveUnitsToFront` (`0x006829B0`, unless `0x006A8720` indicates a passive/truce border) followed by `CFrontAI::ExecuteTactical` (`0x006853C0`).
- **Retail Salient Handler (`CFrontAI::ManageSalientUnits` @ `0x00681CD0`)**: Called from `0x00682A58` inside `0x006829B0`. Clears `+0x12A`, scans single-connection border tips (`+0x12E`), pulls at most 2 units back by 1 hop to an adjacent border province, and records their `TypeId`s in `+0xC8`.

---

### 3.4 `CLandArmy` (Land Army / Division Group) Structure
Represents a land unit counter on the map. Vtable: `0x007E85C0`. Size: `0x320` bytes.

```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x00           void*               Vtable (0x007E85C0)
+0x04           char*               Pointer to null-terminated unit name
+0x0C           uint16              Current Province ID (where army is stationed)
+0x18           uint16              Unit ID Type field (e.g. 10848 / 0x2A60)
+0x1A           uint32              Unit ID Sequence Number
+0x22           void*               CDivisionList container vtable (GetCount @ [vtable + 4])
+0x26           ListNode*           Head of child divisions (CDivision*) linked list
+0x28           void*               IsLandArmy virtual call (+0x28 -> 0x00509C90, returns 1)
+0x11C          void*               Combat list container vtable (0x007E8B04)
+0x120          ListNode*           Head of active combat list (`[[pArmy + 0x120]]` = `CCombat*`)
+0x128          uint32              Count of active combats (`> 0` = unit is in combat)
+0x13A          uint16              Attack target province ID (when attacking an adjacent province; 0 otherwise)
+0x15A          void*               Map Sprite / Counter graphics object
+0x17B          uint8               Retreat State Byte (m_bRetreating): 1 = retreating from combat, 0 = not retreating
+0x17E          uint8               Movement arrow update flag (1 = dirty)
+0x1F0          void*               Movement arrow graphics node container
+0x22E          void*               CPathList vtable (0x007EAAD0)
+0x232          ListNode*           Head of active waypoint path queue (`[[pArmy + 0x232]]` = immediate next step province ID)
+0x236          ListNode*           Tail of active waypoint path queue (`[[pArmy + 0x236]]` = final path destination province ID)
+0x23A          uint32              Waypoint count in path queue
+0x240          uint16              Starting province ID of current move leg
+0x248          Country*            Owning Country pointer ([pArmy + 0x248])
+0x260          struct              CMissionController (0x60 bytes, vtable: 0x007E8754)
+0x264          uint32              Mission Type in controller (1 = explicit Move/Attack mission, 0 = AI move / None)
+0x268          uint32              Target Province ID in controller
+0x26C          float               Movement speed multiplier (1.0f = 0x3F800000)
+0x270          uint32              Mission Start Date (packed format)
+0x27E          uint32              Active Movement Flag (m_bMoving: 1 = actively marching along path, 0 = stationary)
+0x282          uint32              Immediate Next Waypoint Province ID (matches [[pArmy + 0x232]])
```

---

### 3.5 `CDivision` (Individual Division) Structure
Accessed via the `CLandArmy` division list at `[pArmy + 0x26]`:

```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x00           void*               Vtable
+0x48           uint32              Division unit type / class flags
+0xF0           float               m_fStrength (current strength, e.g. 100.0f)
+0xF4           float               m_fOrganization (current organization; checked >= 1.0 by CArmy::CanMove @ 0x0051A4C0)
+0xF8           float               m_fMaxOrganization (maximum organization, e.g. 30.0f)
+0xFC           float               m_fMorale (morale, e.g. 30.0f)
+0x157          uint8               m_bLocked (1 = locked in place / cannot move, 0 = unlocked)
```

---

### 3.6 `CCombat` & `CLandCombatSide` Structures
When `[pArmy + 0x128] > 0`, `pCombat = **(CCombat***)(pArmy + 0x120)`.

#### `CCombat` (Vtable: `0x007E7000`)
```
Offset          Type                Description
--------------------------------------------------------------------------------------
+0x00           void*               Vtable (0x007E7000)
+0x74           uint32              Combat Type (1 = Land Combat)
+0x78           CProvince*          Pointer to battle province (`[[pCombat + 0x78] + 0x12]` = battle province ID)
+0x80           CLandCombatSide*    m_pAttackerSide (vtable: 0x007E7020, `[+0x4E] == 1`)
+0x84           CLandCombatSide*    m_pDefenderSide (vtable: 0x007E7020, `[+0x4E] == 0`)
```

- **`CCombat::GetAttackerWinFraction` (`0x004BEBE0`, `__thiscall`, `ecx = pCombat`)**: Returns `float` in `ST(0)` in $[0.0, 1.0]$ representing the attacker's winning progress/odds fraction (used by the UI combat progress bar).
- **`CLandCombatSide::OrderRetreat` (`0x004BE920`, `__thiscall`, `ecx = pCombatSide`, args: `(CLandArmy* pArmy, uint32_t targetProvId)`)**: Validates `targetProvId` via `0x005091C0`, sets `pArmy->m_bRetreating = 1` (`+0x17B`), calls `CLandArmy::OrderRetreat` (`0x00522930`), and invokes `[vtable + 0x5C]` (`0x004BE280` = `CLandCombatSide::RetreatUnit`) to detach `pArmy` from combat and start its retreat march. Note: `ecx` **must** be `CLandCombatSide*` (`[pCombat + 0x84]` for defenders or `[pCombat + 0x80]` for attackers), not `CCombat*`.

---

### 3.7 Engine Time & Date Structure
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

### 3.8 `CProvince` Structure
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
+0x12           uint32              Province Numerical ID
+0x180          uint8               Impassable / Blocked border flag (1 = blocked)
+0x254          uint32              Terrain Type (8 = Sea, 9 = Ocean)
+0x290          uint32              Count of adjacent neighbor provinces
+0x298          void*               Pointer to neighbor array (12 bytes per record)
                                      +0x00: Neighbor Province ID (uint32)
                                      +0x04: Connection / Border Type (4 = impassable)
                                      +0x08: Distance / Flags
+0x3D8          Country*            Pointer to controlling Country object
+0x471          uint8               Direct sea zone access flag
```

---

### 3.9 `CMissionController` Structure (Embedded at `pArmy + 0x260`)
Vtable: `0x007E8754`. Manages operational missions (Move, Attack, Rebase, Patrol).

```
Offset from Base  Type          Description
--------------------------------------------------------------------------------------
+0x00             void*         Vtable (0x007E8754)
+0x04             uint32        Mission Type: 0 = None, 1 = Move/Attack...
+0x08             uint32        Target Province ID
+0x0C             float         Speed Multiplier (1.0f = 0x3F800000)
+0x10             uint32        Mission Start Date / Packed Timestamp
+0x1C             uint16        Mission Active Flag (1 = active)
+0x1E             uint32        Active Movement Flag (m_bMoving: 1 = moving)
+0x22             uint32        Immediate Next Waypoint Province ID
```

