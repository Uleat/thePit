#pragma once


#include "profile_item_containers.h"
#include "profile_item_upgrades.h"


namespace item {

	enum ClassTypes : ubyte_t {
		class_types_none_ = UBYTE_T_MAX,
		ClassEquipment = UBYTE_T_MIN,
		ClassContainer,
		ClassUpgrade,
		ClassUtility,
		ClassQuest,
		ClassTradeskill,
		ClassOther,
		class_types_begin_ = ClassEquipment,
		class_types_end_ = ClassOther,
		class_types_count_
	};

	typedef ubyte_t sub_class_type_t; // definition specfic to item namespace

	enum EquipmentTypes : sub_class_type_t {
		equipment_types_none_ = UBYTE_T_MAX,

		// melee
		HeldHandToHand = UBYTE_T_MIN,
		Held1HMartial,
		Held2HMartial,
		Held1HBlunt,
		Held2HBlunt,
		Held1HPierce,
		Held2HPierce,
		Held1HSlash,
		Held2HSlash,

		// ranged
		HeldMartialThrown,
		HeldSmallThrown,
		HeldLargeThrown,
		HeldLongBow,
		HeldShortBow,
		HeldCompoundBow,
		HeldPistolCrossbow,
		HeldCrossbow,
		HeldPistol,
		HeldCarbine,
		HeldRifle,
		HeldHeavyGun,

		HeldShield,

		// musical instruments?

		WornClothing,
		WornMartialArmor,
		WornLightArmor,
		WornMediumArmor,
		WornHeavyArmor,

		AccoutrementJewelry,

		// consumables
		AccoutrementFood,
		AccoutrementDrink,
		AccoutrementDietarySupplement,

		equipment_types_begin_ = HeldHandToHand,
		equipment_types_end_ = AccoutrementDietarySupplement,
		equipment_types_count_
	};

	enum ContainerTypes : sub_class_type_t {
		container_types_none_ = UBYTE_T_MAX,
		ContainerSmallBag = UBYTE_T_MIN,
		ContainerMediumBag,
		ContainerLargeBag,
		ContainerSmallChest,
		ContainerMediumChest,
		ContainerLargeChest,
		container_types_begin_ = ContainerSmallBag,
		container_types_end_ = ContainerLargeChest,
		container_types_count_
	};

	enum UpgradeTypes : sub_class_type_t {
		upgrade_types_none_ = UBYTE_T_MAX,
		Upgrade1 = UBYTE_T_MIN,
		upgrade_types_begin_ = Upgrade1,
		upgrade_types_end_ = Upgrade1,
		upgrade_types_count_
	};

	enum UtilityTypes : sub_class_type_t {
		utility_types_none_ = UBYTE_T_MAX,
		UtilityLightSource = UBYTE_T_MIN,
		UtilityAlcohol,
		UtilityBandage,
		UtilityMedicine,
		UtilityBook,
		UtilityNote,
		UtilityKey,
		UtilityLockPick,
		UtilityPassCard,
		UtilityScanner,
		UtilityInterface,
		UtilityComputer,
		utility_types_begin_ = UtilityLightSource,
		utility_types_end_ = UtilityComputer,
		utility_types_count_
	};

	enum QuestTypes : ubyte_t {
		quest_types_none_ = UBYTE_T_MAX,
		Quest1 = UBYTE_T_MIN,
		quest_types_begin_ = Quest1,
		quest_types_end_ = Quest1,
		quest_types_count_
	};

	enum TradeskillTypes : ubyte_t {
		tradeskill_types_none_ = UBYTE_T_MAX,
		Tradeskill1 = UBYTE_T_MIN,
		tradeskill_types_begin_ = Tradeskill1,
		tradeskill_types_end_ = Tradeskill1,
		tradeskill_types_count_
	};

	const UpgradeSlots UpgradeTypesToSlots[upgrade_types_count_] = {
		item::upgrade_slots_inactive_
	};

	UpgradeSlots ConvertUpgradeTypeToSlot(const UpgradeTypes r);

	enum ItemSizes : ubyte_t {
		item_sizes_none_ = UBYTE_T_MIN
	};

	inline EquipmentTypes to_equipment_types(const sub_class_type_t r) { return static_cast<EquipmentTypes>(r); }
	inline ContainerTypes to_container_types(const sub_class_type_t r) { return static_cast<ContainerTypes>(r); }
	inline UpgradeTypes to_upgrade_types(const sub_class_type_t r) { return static_cast<UpgradeTypes>(r); }
	inline UtilityTypes to_utility_types(const sub_class_type_t r) { return static_cast<UtilityTypes>(r); }
	inline QuestTypes to_quest_types(const sub_class_type_t r) { return static_cast<QuestTypes>(r); }
	inline TradeskillTypes to_tradeskill_types(const sub_class_type_t r) { return static_cast<TradeskillTypes>(r); }

	inline sub_class_type_t to_sub_class_type(const EquipmentTypes r) { return static_cast<sub_class_type_t>(r); }
	inline sub_class_type_t to_sub_class_type(const ContainerTypes r) { return static_cast<sub_class_type_t>(r); }
	inline sub_class_type_t to_sub_class_type(const UpgradeTypes r) { return static_cast<sub_class_type_t>(r); }
	inline sub_class_type_t to_sub_class_type(const UtilityTypes r) { return static_cast<sub_class_type_t>(r); }
	inline sub_class_type_t to_sub_class_type(const QuestTypes r) { return static_cast<sub_class_type_t>(r); }
	inline sub_class_type_t to_sub_class_type(const TradeskillTypes r) { return static_cast<sub_class_type_t>(r); }

} // namespace item

namespace inventory {

	enum EquipmentSlots : slot_t;
	enum EquipmentBits : bitmask64_t;
	enum AppearanceSlots : slot_t;
	enum AppearanceBits : bitmask64_t;
	enum CombatReadySlots : slot_t;
	enum CombatReadyBits : bitmask64_t;

} // namespace inventory

namespace races {

	enum RaceTypes : race_t;
	enum RaceBits : bitmask64_t;

} // namespace races

namespace classes {

	enum ClassTypes : class_t;
	enum ClassBits : bitmask64_t;

} // namespace classes

#pragma pack(1)

namespace formats {

	struct ItemIdentificationData {
		id_t ID;
		item::ClassTypes ClassType;
		item::sub_class_type_t SubClassType;
		name_t Name;
	};

	struct ItemDescriptionData {
		// allowable bitmasks
		inventory::EquipmentBits EquipmentBitmask;
		inventory::AppearanceBits AppearanceBitmask;
		inventory::CombatReadyBits CombatReadyBitmask;
		item::UpgradeBits UpgradeBitmask;
		races::RaceBits RaceBitmask;
		classes::ClassBits ClassBitmask;

		// equipment specs
		// additional specs
		// container specs
		slot_t ContainerSlotCount;
		item::ItemSizes ContainerStorageSize;
		ubyte_t ContainerWeightReduction;
		// additional specs
		// upgrade specs
		// additional specs

		// specialty flags
		bool DroppableFlag;
		bool TradeableFlag;
		bool ArtifactFlag;
		bool CraftingFlag;

		// basic specs

		description_t Description;
		udword_t LoreGroup;
		item::ItemSizes Size;
		price_t Price;
		stack_t StackCountMax;
		charge_t ChargeCountMax;
		skill_t RequiredSkillLevel;
	};

	struct ItemScalableData {

	};

	struct ItemStaticData :
		ItemIdentificationData,
		ItemDescriptionData,
		ItemScalableData {
		
	};

} // namespace formats

#pragma pack()

namespace item {

	const formats::ItemStaticData NullItemStaticData;

} // namespace item

namespace profiles {

} // namespace profiles
