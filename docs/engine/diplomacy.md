# Darkest Hour Diplomacy Subsystem & Command Architecture

**Engine**: Darkest Hour / Europa Engine (v1.05.2, 32-bit x86 PE)  
**Binary Executable**: `Darkest Hour.exe`  
**Scope**: Native vanilla diplomacy execution model, the 28 hardcoded diplomatic actions, embargo data structures, puppet trade constraints, and trade efficiency calculation pipeline.

---

## 1. Deterministic Command Queue & Execution Model

Darkest Hour executes diplomatic interactions through a deterministic, queue-based command architecture:

1. **User Action / AI Trigger**:
   - The user clicks a diplomacy button or an AI personality triggers a diplomatic evaluation.
   - Validation is performed via `CCountry::CanPerformDiplomacyAction` (`0x004A1110`).
2. **Packet Serialization**:
   - The action is packaged into a diplomatic command buffer containing `(ActorTag, TargetTag, ActionID, Parameter1, Parameter2, DataBuffer)`.
3. **Queue Dispatch**:
   - The packet is appended to the engine's global command queue and dispatched during the simulation tick via `CCountry::ExecuteDiplomacyAction` (`0x0049ED10`).
4. **Deterministic Resolution**:
   - In multiplayer, commands are synchronized across clients before execution, ensuring identical game states.

---

## 2. Catalog of the 28 Hardcoded Diplomatic Actions

The engine compiles an internal enumeration of exactly 28 diplomatic actions within `CCountry::CanPerformDiplomacyAction` (`0x004A1110`) and `CCountry::ExecuteDiplomacyAction` (`0x0049ED10`):

| ID (Hex) | Internal Identifier | Action Name | Token ID | UI Status | Engine Behavior & Rules |
|---|---|---|---|---|---|
| **0** (`0x00`) | `DIP_DECLARE_WAR` | Declare War | 315 | Active | Initiates hostilities, cancels non-aggression pacts, breaks trade agreements. |
| **1** (`0x01`) | `DIP_OFFER_PEACE` | Offer Peace | 316 | Contextual | Proposes bilateral white peace or negotiated terms during wartime. |
| **2** (`0x02`) | `DIP_OFFER_ALLIANCE` | Bring to Alliance | 317 | Active | Invites target into actor faction / bilateral alliance. |
| **3** (`0x03`) | `DIP_LEAVE_ALLIANCE` | Leave Alliance | 318 | Contextual | Visible only when in an alliance; severs alliance ties. |
| **4** (`0x04`) | `DIP_CANCEL_ALLIANCE` | Break Alliance | 319 | Contextual | Faction leader action to expel an ally. |
| **5** (`0x05`) | `DIP_CREATE_ALLIANCE` | Create Alliance | 320 | **Omitted from Diplo UI** | **Legacy HoI1 action.** Retained in internal enum but not populated in Diplo dialog. |
| **6** (`0x06`) | `DIP_INFLUENCE_NATION` | Influence Nation | 321 | Active | Costs money; pulls target domestic policy sliders towards actor. |
| **7** (`0x07`) | `DIP_COUP_NATION` | Coup Nation | 322 | **Omitted from Diplo UI** | **Legacy HoI2 action.** Migrated to Espionage screen (`SPY_COUP`). |
| **8** (`0x08`) | `DIP_ASK_FOR_MILITARY_ACCESS` | Ask for Military Access | 323 | Active | Requests troop transit through target territory. |
| **9** (`0x09`) | `DIP_CANCEL_MILITARY_ACCESS` | Cancel Military Access | 324 | Active | Cancels military access previously granted to target. |
| **10** (`0x0A`)| `DIP_REVOKE_MILITARY_ACCESS` | Revoke Military Access | 325 | Active | Revokes access actor possesses through target territory. |
| **11** (`0x0B`)| `DIP_ASSUME_MILITARY_CONTROL` | Assume Military Control | 326 | Active | Transfers operational command of ally divisions to actor. |
| **12** (`0x0C`)| `DIP_CANCEL_MILITARY_CONTROL` | Relinquish Military Control | -- | Active | Returns operational military control to ally. |
| **13** (`0x0D`)| `DIP_SEND_EXPEDITIONARY_FORCE` | Send Expeditionary Force | 327 | Active | Transfers selected divisions to ally command. |
| **14** (`0x0E`)| `DIP_GUARANTEE_INDEPENDENCE` | Guarantee Independence | 328 | Active | Grants casus belli and mitigates dissent if target is attacked. |
| **15** (`0x0F`)| `DIP_ANNEX_NATION` | Annex Nation | 329 | Contextual | Available when target is fully occupied (100% of VPs controlled). |
| **16** (`0x10`)| `DIP_PUPPET_REGIME` | Puppet Regime | -- | **Omitted from Diplo UI** | **Legacy HoI1 action.** Peacetime puppet ultimatum. Superseded by peace deals/events. |
| **17** (`0x11`)| `DIP_DEMAND_TERRITORY` | Demand Territory | 330 | Active | Demands national core claims from target country. |
| **18** (`0x12`)| `DIP_TRADE` | Open Negotiations | 331 | Active | Bilateral one-time deal interface (provinces, tech blueprints, units). |
| **19** (`0x13`)| `DIP_OFFER_NON_AGGRESSION` | Offer Non-Aggression Pact | 332 | Active | Proposes bilateral Non-Aggression Pact. |
| **20** (`0x14`)| `DIP_CANCEL_NA` | Cancel Non-Aggression Pact | 333 | Contextual | Visible only when an active Non-Aggression Pact exists. |
| **21** (`0x15`)| `DIP_OFFER_TA` | Offer Trade Agreement | 334 | Active | Establishes daily recurring resource trade agreement. |
| **22** (`0x16`)| `DIP_CANCEL_TA` | Break Trade Agreement | 335 | Contextual | Visible only when an active trade agreement exists with target. |
| **23** (`0x17`)| `DIP_CANCEL_PT` | Cancel Peace Treaty | 336 | **Omitted from Diplo UI** | **Engine-only command.** Backend command to break truce early. |
| **24** (`0x18`)| `DIP_SUE_FOR_PEACE` | Sue For Peace | 337 | Contextual | Available when at war with target; opens peace negotiation conditions. |
| **25** (`0x19`)| `DIP_RELEASE_PUPPET` | Release Puppet | 338 | Contextual | Visible only when viewing own puppet; grants independence. |
| **26** (`0x1A`)| `LIBERATE_NATION` | Liberate Nation | 339 | Contextual | Releases a sovereign or puppet nation from occupied non-core territory. |
| **27** (`0x1B`)| `DONTSENDFORCES` | Don't Send Expeditionary Forces | 340 | Contextual | Darkest Hour innovation. One-sided toggle to prevent ally AI spamming units. |

### 2.1 Unused Legacy CSV Strings
- `DIP_REQUEST_SPECIFIC_ATTACK` (*"Request Specific Attack"*, `text.csv` line 694) and `DIP_OFFER_LEND_LEASE` (*"Offer Lend Lease"*, `text.csv` line 697) are pre-release HoI2 text entries. They have **zero references** in `Darkest Hour.exe` and were never compiled into executable logic.

---

## 3. Embargo Architecture & Runtime Representation

Darkest Hour contains a native internal trade and technology embargo subsystem:

### 3.1 Country Structure Data Offsets
- `[Country + 0x120 + 0x1C0]` (`[Country + 288 + 448]`): Container of active trade embargoes.
- `[Country + 0x120 + 0x204]` (`[Country + 288 + 516]`): Container of active technology embargoes / AI preference restrictions.

### 3.2 Validation Functions
- `CCountry::HasTradeEmbargoAgainst(target_tag)`: `sub_4A74E0` (`0x004A74E0`), checks trade embargo set (`+0x1C0`).
- `CCountry::HasTechEmbargoAgainst(target_tag)`: `sub_4A7500` (`0x004A7500`), checks tech embargo set (`+0x204`).

### 3.3 UI Tooltip & Deal Checks
Trade dialogs (`0x005FE241`) and the tooltip generator (`0x0061DA1F`) call `sub_4A74E0`. If an embargo is active between either party, the trade option is blocked with tooltip string `DIPROL_TRADE_EMBARGO` (*"We or they are currently under a trade embargo"*).

### 3.4 Scripted Event Command Pipeline
The scripted event command `type = embargo which = TAG where = TAG value = X` is deserialized as `CExecuteEventEffectCommand` (Command ID 278, Sub-effect 330) and executed in `CCountry::ExecuteEmbargoCommand` (`0x00494B90` / `0x00494C41`):
- `value = 1`: Updates Trade Embargo list (`+0x1C0`).
- `value = 2`: Updates Tech Embargo list (`+0x204`).

---

## 4. Puppet Trade Mechanics & Master Relationships (Vanilla)

### 4.1 Master Tag Resolution
- Actor master tag: `*(*(Country_Actor + 0x12DA) + 0x3B30)` (returns `0` if independent).
- Target master tag: `*(*(Country_Target + 0x12DA) + 0x3B30)` (returns `0` if independent).

### 4.2 Vanilla Engine Trade Blocks
In the unmodified retail engine:
- `CCountry::CanPerformDiplomacyAction`:
  - Case `0x12` (`DIP_OFFER_TA` at `0x004A16CC`): Unconditionally rejects action if either party is a puppet and the other party is not their master.
  - Case `0x15` (`DIP_TRADE` at `0x004A1782`): Performs identical master-only verification.
- **Tooltip Handler** (`0x0061D84B` / `0x0061D941`): Jumps to `0x0061DA73` to display `DIPROL_SAT` (*"Puppet states of other nations are not free to do that"*).
- **AI Evaluations** (`0x0067B384` and `0x0067C78A`): AI evaluates puppet status and rejects proposing trades to non-masters.

*(Note: For configurable puppet trade rules and master veto mechanics, see [Patch 4 Documentation](../plans/plan_puppet_trade.md)).*

---

## 5. Trade Efficiency Pipeline & Puppet Restrictions (Vanilla)

### 5.1 Trade Efficiency Table (`m_TradeEfficiency`)
- Located at offset `+0xF4EE` within `CCountry` (`float m_TradeEfficiency[344]`).
- Represents direct trade efficiency ($0.0$ to $1.0$) between the country and each target country tag.
- Calculated for all active countries at scenario start (`0x00485E5B`) and during daily country updates (`0x004832C3`) inside `CCountry::CalculateTradeEfficiencies` (`0x0044E800`).

### 5.2 Hardcoded Puppet Zero-Efficiency Block (Vanilla)
In `CCountry::CalculateTradeEfficiencies` (`0x0044EB23` to `0x0044EB66`):
- Initializes target efficiency to $0.0f$ (`0x0044EB27`).
- At `0x0044EB39`: Checks if actor is a puppet (`test al, al`). If target is not actor's master (`cmp [esp+0x3c], edi`), jumps to `0x0044F49B` (skipping route calculation and leaving efficiency locked at $0.0f$).
- At `0x0044EB4F`: Checks if target is a puppet. If actor is not target's master, jumps to `0x0044F49B` (leaving efficiency at $0.0f$).
- **Consequence**: In vanilla, any trade agreement involving a puppet and a non-master was mathematically locked to 0% efficiency, even if established by event or save-file edit.

### 5.3 Consumers of Trade Efficiency
- **Trade Dialog UI** (`0x0060646F` / `0x00647BC0`): Averages actor and target efficiency `(eff1 + eff2) * 0.5 * 100.0%` and displays string `TA_EFF_EST` (*"Estimated Effectiveness: %.2f%%"*).
- **Trade Deal Creation** (`0x00781F4F`): Initializes deal efficiency `[CTradeDeal + 0x46]` from `(eff1 + eff2) * 0.5`.
- **Daily Trade Deal Updates** (`0x0058A870`): Iterates all active deals and updates `[CTradeDeal + 0x46]` from current country efficiencies.
- **Daily Deliveries**: Resource amounts transferred each hour/day are multiplied by deal efficiency `[CTradeDeal + 0x46]`.

