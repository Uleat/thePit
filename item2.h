/*	EQEMu: Everquest Server Emulator
	Copyright (C) 2001-2003 EQEMu Development Team (http://eqemulator.net)

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; version 2 of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY except by those people which sell it, which
	are required to give you total support for your newly bought product;
	without even the implied warranty of MERCHANTABILITY or FITNESS FOR
	A PARTICULAR PURPOSE. See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef __ITEM2_H
#define __ITEM2_H


#include "../common/timer.h"

#include "inventory.h"

#include <map>


// Forward declarations
namespace _Inventory
{
	//struct Slot_Struct;
	//struct SSlot_Struct;
	class Container;
	//class Scope;
	//class Slot;
	class Instance;
	//class Factory;
	class Query;
}


namespace Item
{
	struct Effect_Struct;
	struct Data;
	class Instance;
	class Evolution;
	class Factory;
	

	// Ready for ALPHA
	struct Effect_Struct {
		int16 Effect;
		uint8 Type;
		uint8 Level;
		uint8 Level2;
		//MaxCharges
		//CastTime
		//RecastDelay
		//RecastType
		//ProcRate
	};
	

	// In development
	struct Data {
		bool IsName(char *name[64]);
		bool IsLore(char *lore[80]);
		bool IsIDFile(char *idFile[30]);
		bool IsCharmFile(char *charmFile[32]);
		bool IsFilename(char *filename[33]);
		bool IsClickName(char *clickName[65]);
		bool IsProcName(char *procName[65]);
		bool IsWornName(char *wornName[65]);
		bool IsFocusName(char *focusName[65]);
		bool IsScrollName(char *scrollName[65]);

		// TODO: Need to add 'flag' checks..especially for reverse-context fields (NoDrop != 0 >> wha?..)

		bool IsAmmo();
		bool IsAugmentable();
		bool IsEquipable(uint16 Race, uint16 Class);
		bool IsEquipable(_Inventory::Slot_Struct slot);
		bool IsExpendable();
		bool IsWeapon();

		bool _IsEquipable(size_t index); // Not meant for unmoderated use (assumes: map = 0, sub = -1, aug = -1)

		// Non packet based fields
		uint8 MinStatus;
		bool ScaledReference;

		// Packet based fields
		uint8 ItemClass;		// Item Type: 0=common, 1=container, 2=book
		char Name[64];			// Name
		char Lore[80];			// Lore Name: *=lore, &=summoned, #=artifact, ~=pending lore
		char IDFile[30];		// Visible model
		uint32 ID;				// Unique ID (also PK for DB)
		uint8 Weight;			// Item weight * 10
		uint8 NoRent;			// No Rent: 0=norent, 255=not norent
		uint8 NoDrop;			// No Drop: 0=nodrop, 255=not nodrop
		uint8 Size;				// Size: 0=tiny, 1=small, 2=medium, 3=large, 4=giant
		uint32 Slots;			// Bitfield for which slots this item can be used in
		uint32 Price;			// Item cost (?)
		uint32 Icon;			// Icon Number
		uint32 LoreGroup;		// Later items use LoreGroup instead of LoreFlag. we might want to see about changing this to int32 since it is commonly -1 and is constantly being cast from signed (-1) to unsigned (4294967295)
		bool LoreFlag;			// This will be true if LoreGroup is non-zero
		bool PendingLoreFlag;
		bool ArtifactFlag;
		bool SummonedFlag;
		uint8 FVNoDrop;			// Firiona Vie nodrop flag
		uint32 Favor;			// Individual favor
		uint32 GuildFavor;		// Guild favor
		uint32 PointType;

		//uint32 Unk117;
		//uint32 Unk118;
		//uint32 Unk121;
		//uint32 Unk124;

		uint8 BagType;			// 0:Small Bag, 1:Large Bag, 2:Quiver, 3:Belt Pouch ... there are 50 types
		uint8 BagSlots;			// Number of slots: can only be 2, 4, 6, 8, or 10
		uint8 BagSize;			// 0:TINY, 1:SMALL, 2:MEDIUM, 3:LARGE, 4:GIANT
		uint8 BagWR;			// 0->100

		bool BenefitFlag;
		bool Tradeskills;		// Is this a tradeskill item?
		int8 CR;				// Save vs Cold
		int8 DR;				// Save vs Disease
		int8 PR;				// Save vs Poison
		int8 MR;				// Save vs Magic
		int8 FR;				// Save vs Fire
		int8 AStr;				// Strength
		int8 ASta;				// Stamina
		int8 AAgi;				// Agility
		int8 ADex;				// Dexterity
		int8 ACha;				// Charisma
		int8 AInt;				// Intelligence
		int8 AWis;				// Wisdom
		int32 HP;				// HP
		int32 Mana;				// Mana
		int32 AC;				// AC
		uint32 Deity;			// Bitmask of Deities that can equip this item
		//uint32 Unk033
		int32 SkillModValue;	// % Mod to skill specified in SkillModType
		uint32 SkillModType;	// Type of skill for SkillModValue to apply to
		uint32 BaneDmgRace;		// Bane Damage Race
		int8 BaneDmgAmt;		// Bane Damage Body Amount
		uint32 BaneDmgBody;		// Bane Damage Body
		bool Magic;				// True=Magic Item, False=not
		int32 CastTime_;
		uint8 ReqLevel;			// Required Level to use item
		uint32 BardType;		// Bard Skill Type
		int32 BardValue;		// Bard Skill Amount
		int8 Light;				// Light
		uint8 Delay;			// Delay * 10
		uint8 RecLevel;			// Recommended level to use item
		uint8 RecSkill;			// Recommended skill to use item (refers to primary skill of item)
		uint8 ElemDmgType;		// Elemental Damage Type (1=magic, 2=fire)
		uint8 ElemDmgAmt;		// Elemental Damage
		uint8 Range;			// Range of item
		uint32 Damage;			// Delay between item usage (in 0.1 sec increments)
		uint32 Color;			// RR GG BB 00 <-- as it appears in pc
		uint32 Classes;			// Bitfield of classes that can equip item (1 << class#)
		uint32 Races;			// Bitfield of races that can equip item (1 << race#)
		//uint32 Unk054;
		int16 MaxCharges;		// Maximum charges items can hold: -1 if not a chargeable item
		uint8 ItemType;			// Item Type/Skill (itemClass* from above)
		uint8 Material;			// Item material type
		uint32 HerosForgeModel;	// Hero's Forge Armor Model Type (2-13?)
		float SellRate;			// Sell rate
		//uint32 Unk059;
		union {
			uint32 Fulfilment;	// Food fulfilment (How long it lasts)
			int16 CastTime;		// Cast Time for clicky effects, in milliseconds
		};
		uint32 EliteMaterial;
		int32 ProcRate;
		int8 CombatEffects;		// PoP: Combat Effects +
		int8 Shielding;			// PoP: Shielding %
		int8 StunResist;		// PoP: Stun Resist %
		int8 StrikeThrough;		// PoP: Strike Through %
		uint32 ExtraDmgSkill;
		uint32 ExtraDmgAmt;
		int8 SpellShield;		// PoP: Spell Shield %
		int8 Avoidance;			// PoP: Avoidance +
		int8 Accuracy;			// PoP: Accuracy +
		uint32 CharmFileID;
		int32 FactionMod1;		// Faction Mod 1
		int32 FactionMod2;		// Faction Mod 2
		int32 FactionMod3;		// Faction Mod 3
		int32 FactionMod4;		// Faction Mod 4
		int32 FactionAmt1;		// Faction Amt 1
		int32 FactionAmt2;		// Faction Amt 2
		int32 FactionAmt3;		// Faction Amt 3
		int32 FactionAmt4;		// Faction Amt 4
		char CharmFile[32];		// ?
		uint32 AugType;
		uint8 AugSlotType[EmuConstants::ITEM_COMMON_SIZE];		// RoF: Augment Slot 1-6 Type
		uint8 AugSlotVisible[EmuConstants::ITEM_COMMON_SIZE];	// RoF: Augment Slot 1-6 Visible
		uint8 AugSlotUnk2[EmuConstants::ITEM_COMMON_SIZE];		// RoF: Augment Slot 1-6 Unknown
		uint32 LDoNTheme;
		uint32 LDoNPrice;
		uint32 LDoNSold;
		uint32 BaneDmgRaceAmt;
		uint32 AugRestrict;
		uint32 Endur;
		uint32 DotShielding;
		uint32 Attack;
		uint32 Regen;
		uint32 ManaRegen;
		uint32 EnduranceRegen;
		uint32 Haste;
		uint32 DamageShield;
		uint32 RecastDelay;
		uint32 RecastType;
		uint32 AugDistiller;
		bool Attuneable;
		bool NoPet;
		bool PotionBelt;
		bool Stackable;
		bool NoTransfer;
		bool QuestItemFlag;
		int16 StackSize;
		uint8 PotionBeltSlots;

		Effect_Struct Click;
		Effect_Struct Proc;
		Effect_Struct Worn;
		Effect_Struct Focus;
		Effect_Struct Scroll;
		Effect_Struct Bard;

		uint8 Book;				// 0=Not book, 1=Book
		uint32 BookType;
		char Filename[33];		// Filename for book data

		// Begin SoF Fields
		int32 SVCorruption;
		uint32 Purity;
		uint8 EvolvingLevel;
		uint32 BackstabDmg;
		uint32 DSMitigation;
		int32 HeroicStr;
		int32 HeroicInt;
		int32 HeroicWis;
		int32 HeroicAgi;
		int32 HeroicDex;
		int32 HeroicSta;
		int32 HeroicCha;
		int32 HeroicMR;
		int32 HeroicFR;
		int32 HeroicCR;
		int32 HeroicDR;
		int32 HeroicPR;
		int32 HeroicSVCorrup;
		int32 HealAmt;
		int32 SpellDmg;
		uint32 LDoNSellBackRate;
		uint32 ScriptFileID;
		uint16 ExpendableArrow;
		uint32 Clairvoyance;
		char ClickName[65];
		char ProcName[65];
		char WornName[65];
		char FocusName[65];
		char ScrollName[65];
	};
	

	// Ready for ALPHA
	// Empty data struct to proxy a bad id reference (and avoid server crashes)
	static const Data error_data = {
		255, // MinStatus
		false, // ScaledReference
		255, // ItemClass
		"ERROR\0", // Name
		"ERROR\0", // Lore
		"ERROR\0", // IDFile
		0, // ID
		0, // Weight
		0, // NoRent
		0, // NoDrop
		0, // Size
		0, // Slots
		0, // Price
		0, // Icon
		0, // LoreGroup
		false, // LoreFlag
		false, // PendingLoreFlag
		false, // ArtifactFlag
		false, // SummonedFlag
		0, // FVNoDrop
		0, // Favor
		0, // GuildFavor
		0, // PointType
		255, // BagType
		0, // BagSlots
		0, // BagSize
		0, // BagWR
		false, // BenefitFlag
		false, // Tradeskills
		0, // CR
		0, // DR
		0, // PR
		0, // MR
		0, // FR
		0, // AStr
		0, // ASta
		0, // AAgi
		0, // ADex
		0, // ACha
		0, // AInt
		0, // AWis
		0, // HP
		0, // Mana
		0, // AC
		0, // Deity
		0, // SkillModValue
		0, // SkillModType
		0, // BaneDmgRace
		0, // BaneDmgAmt
		0, // BaneDmgBody
		false, // Magic
		0, // CastTime_
		255, // ReqLevel
		0, // BardType
		0, // BardValue
		0, // Light
		0, // Delay
		255, // RecLevel
		255, // RecSkill
		0, // ElemDmgType
		0, // ElemDmgAmt
		0, // Range
		0, // Damage
		0, // Color
		0, // Classes
		0, // Races
		0, // MaxCharges
		255, // ItemType
		0, // Material
		0, // HerosForgeModel
		0.0, // SellRate
		0, // Fulfilment / CastTime
		0, // EliteMaterial
		0, // ProcRate
		0, // CombatEffects
		0, // Shielding
		0, // StunResist
		0, // StrikeThrough
		0, // ExtraDmgSkill
		0, // ExtraDmgAmt
		0, // SpellShield
		0, // Avoidance
		0, // Accuracy
		0, // CharmFileID
		0, // FactionMod1
		0, // FactionMod2
		0, // FactionMod3
		0, // FactionMod4
		0, // FactionAmt1
		0, // FactionAmt2
		0, // FactionAmt3
		0, // FactionAmt4
		"ERROR\0", // CharmFile
		0, // AugType;
		{ 0, 0, 0, 0, 0, 0 }, // AugSlotType
		{ 0, 0, 0, 0, 0, 0 }, // AugSlotVisible
		{ 0, 0, 0, 0, 0, 0 }, // AugSlotUnk2
		0, // LDoNTheme
		0, // LDoNPrice
		0, // LDoNSold
		0, // BaneDmgRaceAmt
		0, // AugRestrict
		0, // Endur
		0, // DotShielding
		0, // Attack
		0, // Regen
		0, // ManaRegen
		0, // EnduranceRegen
		0, // Haste
		0, // DamageShield
		0, // RecastDelay
		0, // RecastType
		0, // AugDistiller
		false, // Attuneable
		false, // NoPet
		false, // PotionBelt
		false, // Stackable
		false, // NoTransfer
		false, // QuestItemFlag
		0, // StackSize
		0, // PotionBeltSlots
		Effect_Struct() = { 0, 0, 0, 0 }, // Click
		Effect_Struct() = { 0, 0, 0, 0 }, // Proc
		Effect_Struct() = { 0, 0, 0, 0 }, // Worn
		Effect_Struct() = { 0, 0, 0, 0 }, // Focus
		Effect_Struct() = { 0, 0, 0, 0 }, // Scroll
		Effect_Struct() = { 0, 0, 0, 0 }, // Bard
		0, // Book
		0, // BookType
		"ERROR\0", // Filename
		0, // SVCorruption
		0, // Purity
		0, // EvolvingLevel
		0, // BackstabDmg
		0, // DSMitigation
		0, // HeroicStr
		0, // HeroicInt
		0, // HeroicWis
		0, // HeroicAgi
		0, // HeroicDex
		0, // HeroicSta
		0, // HeroicCha
		0, // HeroicMR
		0, // HeroicFR
		0, // HeroicCR
		0, // HeroicDR
		0, // HeroicPR
		0, // HeroicSVCorrup
		0, // HealAmt
		0, // SpellDmg
		0, // LDoNSellBackRate
		0, // ScriptFileID
		0, // ExpendableArrow
		0, // Clairvoyance
		"ERROR\0", // ClickName
		"ERROR\0", // ProcName
		"ERROR\0", // WornName
		"ERROR\0", // FocusName
		"ERROR\0", // ScrollName
	};


	// In development
	class Instance {
		friend _Inventory::Instance;
		friend _Inventory::Query;
		friend Factory;

	public:
		~Instance();

		// Item::Data instance 'get' accessors
		const Item::Data* GetData();
		const Item::Data* GetBaseData();
		const Item::Data* GetScaledData();
		const Item::Data* GetOrnamentData();

		// Item::Instance property 'get' accessors
		uint32 GetSerialNumber();
		uint32 GetRecastTimestamp();
		uint32 GetColor();
		int16 GetCharges();
		bool GetAttuned();

		uint32 GetMerchantSlot();
		uint32 GetMerchantPrice();
		int32 GetMerchantCount();

		const Evolution* GetEvolution();

		uint32 GetExperience();
		int8 GetEvolvedLevel();
		bool GetActivated();
		bool GetScaling();

		std::string GetCustomDataString();
		std::string GetCustomData(std::string identifier);

		// Item::Data property 'get' accessors
		uint32 GetID();

		bool IsClassType(uint8 itemClassType);
		bool IsUseType(uint8 itemUseType);
		bool IsBagType(uint8 bagUseType);
		bool IsAugmentType(uint32 augmentUseType);

		bool IsTemporary();
		bool IsTradeable();
		bool IsPetable();
		bool IsTransferable();
		bool IsStorable();

		bool IsStackable();

	protected:
		Instance(const Item::Data *data, _Inventory::Container *container, int16 charges = NIL);

		_Inventory::Container* GetContainer() { return m_Container; }

	private:
		const Data *m_BaseData;
		Data *m_ScaledData;

		const Data *m_OrnamentData;

		uint32 m_SerialNumber;		// Assigned on a per-Inventory::Instance basis
		uint32 m_RecastTimestamp;
		uint32 m_Color;
		int16 m_Charges;
		bool m_Attuned;				// Soul-bound

		uint32 m_MerchantSlot;
		uint32 m_MerchantPrice;
		int32 m_MerchantCount;		// Number avaliable on the merchant, -1 = unlimited
		
		Evolution *m_Evolution;

		uint32 m_Experience;
		int8 m_EvolvedLevel;
		bool m_Activated;
		bool m_Scaling;

		_Inventory::Container *m_Container;

		std::map<std::string, std::string>	m_CustomData;
		std::map<std::string, Timer> m_Timers;
	};


	// In development
	class Evolution {
		friend Instance;

	public:
		Evolution();
		Evolution(uint32 first, uint8 max, bool allkills, uint32 L2, uint32 L3, uint32 L4, uint32 L5, uint32 L6, uint32 L7, uint32 L8, uint32 L9, uint32 L10);
		~Evolution();

		uint16 LvlKills[9];
		uint32 FirstItem;
		uint8 MaxLvl;
		bool AllKills;
	};


	// In development
	class Factory {
		// Nullptr returns from database should be proxied with the const Item::Data error_data definition above
	public:

	};


	// Ready for ALPHA
	namespace Field {
		enum {
			source = INDEX_BEGIN,
#define F(x) x,
#include "item_fieldlist.h"
#undef F
			updated
		};
	}
}

#endif // #define __ITEM2_H
