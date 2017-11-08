#include "common_macros.h"
#include "object_item.h"
#include "profile_classes.h"
#include "profile_inventory.h"
#include "profile_races.h"


#define MODIFIABLE_DATA_RETURN(f) \
	if (modifiable_data_ != nullptr) \
		return modifiable_data_->f; \
	else \
		return item_static_data_.f;

objects::Item::~Item() {
	SAFE_DELETE(modifiable_data_);
}

bool objects::Item::Initialize() {
	if (initialized_ == true)
		return false;

	if (&static_data_ == &item::NullItemStaticData)
		return false;

	if (static_data_.ContainerSlotCount != 0 && !InitializeContainerData(static_data_.ContainerSlotCount))
		return false;

	if (static_data_.UpgradeBitmask != item::upgrade_bits_none_ && !InitializeUpgradeData(static_data_.UpgradeBitmask))
		return false;

	if (IsContainerDataInitialized() && IsUpgradeDataInitialized())
		return false;

	// need to add scalable initialization

	initialized_ = true;

	return true;
}

bool objects::Item::IsAllowedByRace(const races::RaceTypes r) const {
	if (!races::IsPlayerRace(r))
		return false;

	return (((1ui64 << r) & static_data_.RaceBitmask) != races::race_bits_none_);
}

bool objects::Item::IsAllowedByClass(const classes::ClassTypes r) const {
	if (!classes::IsPlayerClass(r))
		return false;

	return (((1ui64 << r) & static_data_.ClassBitmask) != classes::class_bits_none_);
}

bool objects::Item::IsAllowedInEquipmentSlot(const inventory::EquipmentSlots r) const {
	// need to include ItemClass checks here too..can't rely 100% on world building accuracy...
	// (i.e., ClassType == item::ClassEquipment || (ClassType == item::ClassUtility && UtilityType == {...})

	if (!inventory::IsEquipmentSlotBounded(r))
		return false;

	return (((1ui64 << r) & static_data_.EquipmentBitmask) != inventory::equipment_bits_none_);
}

bool objects::Item::IsAllowedInHeldSlot(const inventory::EquipmentSlots r) const {
	// need to include ItemClass checks here too..can't rely 100% on world building accuracy...
	// (i.e., ClassType == item::ClassEquipment || (ClassType == item::ClassUtility && UtilityType == {...})

	if (!inventory::IsEquipmentSlotBounded(r))
		return false;

	return (((1ui64 << r) & static_data_.EquipmentBitmask) != inventory::equipment_bits_none_);
}

bool objects::Item::IsAllowedInWornSlot(const inventory::EquipmentSlots r) const {
	// need to include ItemClass checks here too..can't rely 100% on world building accuracy...
	// (i.e., ClassType == item::ClassEquipment || (ClassType == item::ClassUtility && UtilityType == {...})

	if (!inventory::IsEquipmentSlotBounded(r))
		return false;

	return (((1ui64 << r) & static_data_.EquipmentBitmask) != inventory::equipment_bits_none_);
}

bool objects::Item::IsAllowedInAccoutrementSlot(const inventory::EquipmentSlots r) const {
	// need to include ItemClass checks here too..can't rely 100% on world building accuracy...
	// (i.e., ClassType == item::ClassEquipment || (ClassType == item::ClassUtility && UtilityType == {...})

	if (!inventory::IsEquipmentSlotBounded(r))
		return false;

	return (((1ui64 << r) & static_data_.EquipmentBitmask) != inventory::equipment_bits_none_);
}

bool objects::Item::IsAllowedInAppearanceSlot(const inventory::AppearanceSlots r) const {
	if (!inventory::IsAppearanceSlotBounded(r))
		return false;

	return (((1ui64 << r) & static_data_.AppearanceBitmask) != inventory::appearance_bits_none_);
}

bool objects::Item::IsAllowedInCombatReadySlot(const inventory::CombatReadySlots r) const {
	if (!inventory::IsCombatReadySlotBounded(r))
		return false;

	return (((1ui64 << r) & static_data_.CombatReadyBitmask) != inventory::combat_ready_bits_none_);
}

bool objects::Item::IsEquipmentUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const inventory::EquipmentSlots r3) const {
	if (!races::IsPlayerRace(r1))
		return false;

	if (((1ui64 << r1) & static_data_.RaceBitmask) == races::race_bits_none_)
		return false;

	if (!classes::IsPlayerClass(r2))
		return false;

	if (((1ui64 << r2) & static_data_.ClassBitmask) == classes::class_bits_none_)
		return false;

	if (!inventory::IsEquipmentSlotBounded(r3))
		return false;

	return (((1ui64 << r3) & static_data_.EquipmentBitmask) != inventory::equipment_bits_none_);
}

bool objects::Item::IsHeldUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const inventory::EquipmentSlots r3) const {
	if (!races::IsPlayerRace(r1))
		return false;

	if (((1ui64 << r1) & static_data_.RaceBitmask) == races::race_bits_none_)
		return false;

	if (!classes::IsPlayerClass(r2))
		return false;

	if (((1ui64 << r2) & static_data_.ClassBitmask) == classes::class_bits_none_)
		return false;

	if (!inventory::IsEquipmentSlotBounded(r3))
		return false;

	return (((1ui64 << r3) & static_data_.EquipmentBitmask) != inventory::equipment_bits_none_);
}

bool objects::Item::IsWornUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const inventory::EquipmentSlots r3) const {
	if (!races::IsPlayerRace(r1))
		return false;

	if (((1ui64 << r1) & static_data_.RaceBitmask) == races::race_bits_none_)
		return false;

	if (!classes::IsPlayerClass(r2))
		return false;

	if (((1ui64 << r2) & static_data_.ClassBitmask) == classes::class_bits_none_)
		return false;

	if (!inventory::IsEquipmentSlotBounded(r3))
		return false;

	return (((1ui64 << r3) & static_data_.EquipmentBitmask) != inventory::equipment_bits_none_);
}

bool objects::Item::IsAccoutrementUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const inventory::EquipmentSlots r3) const {
	if (!races::IsPlayerRace(r1))
		return false;

	if (((1ui64 << r1) & static_data_.RaceBitmask) == races::race_bits_none_)
		return false;

	if (!classes::IsPlayerClass(r2))
		return false;

	if (((1ui64 << r2) & static_data_.ClassBitmask) == classes::class_bits_none_)
		return false;

	if (!inventory::IsEquipmentSlotBounded(r3))
		return false;

	return (((1ui64 << r3) & static_data_.EquipmentBitmask) != inventory::equipment_bits_none_);
}

bool objects::Item::IsAppearanceUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const inventory::AppearanceSlots r3) const {
	if (!races::IsPlayerRace(r1))
		return false;

	if (((1ui64 << r1) & static_data_.RaceBitmask) == races::race_bits_none_)
		return false;

	if (!classes::IsPlayerClass(r2))
		return false;

	if (((1ui64 << r2) & static_data_.ClassBitmask) == classes::class_bits_none_)
		return false;

	if (!inventory::IsAppearanceSlotBounded(r3))
		return false;

	return (((1ui64 << r3) & static_data_.AppearanceBitmask) != inventory::appearance_bits_none_);
}

bool objects::Item::IsCombatReadyUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const inventory::CombatReadySlots r3) const {
	if (!races::IsPlayerRace(r1))
		return false;

	if (((1ui64 << r1) & static_data_.RaceBitmask) == races::race_bits_none_)
		return false;

	if (!classes::IsPlayerClass(r2))
		return false;

	if (((1ui64 << r2) & static_data_.ClassBitmask) == classes::class_bits_none_)
		return false;

	if (!inventory::IsCombatReadySlotBounded(r3))
		return false;

	return (((1ui64 << r3) & static_data_.CombatReadyBitmask) != inventory::combat_ready_bits_none_);
}

bool objects::Item::IsItemAllowedInContainer(const Item* r) const {
	if (r == nullptr)
		return true;

	return IsItemAllowedInContainer(r->static_data_, r->GetContainerDataCount());
}

bool objects::Item::IsItemAllowedInContainer(const formats::ItemStaticData& r1, const bool r2) const {
	if (static_data_.ClassType != item::ClassContainer)
		return false;

	if (static_data_.ContainerStorageSize == item::item_sizes_none_)
		return false;

	if (r1.ClassType == item::ClassContainer && r2 == false) // empty container check (r2 = profiles::ItemHoldingAttributes::IsHoldingDataEmpty())
		return false;

	return (static_data_.ContainerStorageSize >= r1.Size);
}

bool objects::Item::IsItemAllowedInUpgrade(const Item* r) const {
	if (r == nullptr)
		return true;

	return IsItemAllowedInUpgrade(r->static_data_);
}

bool objects::Item::IsItemAllowedInUpgrade(const formats::ItemStaticData& r) const {
	if (r.ClassType != item::ClassUpgrade)
		return false;

	auto test_val = item::ConvertUpgradeTypeToSlot(item::to_upgrade_types(r.SubClassType));
	if (test_val == item::upgrade_slots_inactive_)
		return false;

	return (((1ui64 << test_val) & static_data_.UpgradeBitmask) != item::upgrade_bits_none_);
}

bool objects::Item::IsUpgradeSlotFree(const item::UpgradeTypes r) const {
	return IsUpgradeSlotFree(item::ConvertUpgradeTypeToSlot(r));
}

bool objects::Item::IsUpgradeUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const Item* r3) const {
	if (r3 == nullptr)
		return true;

	return IsUpgradeUsable(r1, r2, r3->static_data_);
}

bool objects::Item::IsUpgradeUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const formats::ItemStaticData& r3) const {
	if (!races::IsPlayerRace(r1))
		return false;

	if (((1ui64 << r1) & static_data_.RaceBitmask) == races::race_bits_none_)
		return false;

	if (!classes::IsPlayerClass(r2))
		return false;

	if (((1ui64 << r2) & static_data_.ClassBitmask) == classes::class_bits_none_)
		return false;

	if (r3.ClassType != item::ClassUpgrade)
		return false;

	auto test_val = item::ConvertUpgradeTypeToSlot(item::to_upgrade_types(r3.SubClassType));
	if (test_val == item::upgrade_slots_inactive_)
		return false;

	return (((1ui64 << test_val) & static_data_.UpgradeBitmask) != item::upgrade_bits_none_);
}

formats::ItemScalableData* objects::Item::initialize_modifiable_data() {
	if (modifiable_data_ == nullptr)
		modifiable_data_ = new formats::ItemScalableData;

	return modifiable_data_;
}

void objects::Item::delete_modifiable_data_() {
	SAFE_DELETE(modifiable_data_);
}

#undef MODIFIABLE_DATA_RETURN