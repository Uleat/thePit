#include "common_macros.h"
#include "profile_inventory.h"


void inventory::MapSlotsToString(const MapSlots r, std::string& l) {
	switch (r) {
	case map_slots_inactive:
		l = "MapSlot inactive";
		break;
	case MapEquipment:
		l = "MapEquipment";
		break;
	case MapAppearance:
		l = "MapAppearance";
		break;
	case MapGeneral:
		l = "MapGeneral";
		break;
	case MapCombatReady:
		l = "MapCombatReady";
		break;
	case MapCursor:
		l = "MapCursor";
		break;
	case MapLost:
		l = "MapLost";
		break;
	case MapDeleted:
		l = "MapDeleted";
		break;
	case MapTrading:
		l = "MapTrading";
		break;
	case MapWorldObject:
		l = "MapWorldObject";
		break;
	case MapTradeskill:
		l = "MapTradeskill";
		break;
	case MapLoot:
		l = "MapLoot";
		break;
	case MapInspect:
		l = "MapInspect";
		break;
	case MapBank:
		l = "MapBank";
		break;
	case MapGuildBank:
		l = "MapGuildBank";
		break;
	case MapParcel:
		l = "MapParcel";
		break;
	case MapMerchantStock:
		l = "MapMerchantStock";
		break;
	case MapMerchantResell:
		l = "MapMerchantResell";
		break;
	case MapConsignment:
		l = "MapConsignment";
		break;
	case MapGuildConsignment:
		l = "MapGuildConsignment";
		break;
	case MapTheExchange:
		l = "MapTheExchange";
		break;
	case MapMiscellaneous:
		l = "MapMiscellaneous";
		break;
	default:
		l.clear();
		l.append("MapSlot unknown (" + std::to_string(r) + ")");
		break;
	}
}

void inventory::EquipmentSlotsToString(const EquipmentSlots r, std::string& l) {
	switch (r) {
	case equipment_slots_inactive:
		l = "EquipmentSlot inactive";
		break;
	case EquipmentHead:
		l = "EquipmentHead";
		break;
	case EquipmentFace:
		l = "EquipmentFace";
		break;
	case EquipmentBody:
		l = "EquipmentBody";
		break;
	case EquipmentShoulders:
		l = "EquipmentShoulders";
		break;
	case EquipmentBack:
		l = "EquipmentBack";
		break;
	case EquipmentChest:
		l = "EquipmentChest";
		break;
	case EquipmentArms:
		l = "EquipmentArms";
		break;
	case EquipmentWrist1:
		l = "EquipmentWrist1";
		break;
	case EquipmentWrist2:
		l = "EquipmentWrist2";
		break;
	case EquipmentHands:
		l = "EquipmentHands";
		break;
	case EquipmentWaist:
		l = "EquipmentWaist";
		break;
	case EquipmentTail:
		l = "EquipmentTail";
		break;
	case EquipmentLegs:
		l = "EquipmentLegs";
		break;
	case EquipmentFeet:
		l = "EquipmentFeet";
		break;
	case EquipmentNeck:
		l = "EquipmentNeck";
		break;
	case EquipmentWings:
		l = "EquipmentWings";
		break;
	case EquipmentEar1:
		l = "EquipmentEar1";
		break;
	case EquipmentEar2:
		l = "EquipmentEar2";
		break;
	case EquipmentFinger1:
		l = "EquipmentFinger1";
		break;
	case EquipmentFinger2:
		l = "EquipmentFinger2";
		break;
	case EquipmentCranialImplant:
		l = "EquipmentCranialImplant";
		break;
	case EquipmentOpticalImplant1:
		l = "EquipmentOpticalImplant1";
		break;
	case EquipmentOpticalImplant2:
		l = "EquipmentOpticalImplant2";
		break;
	case EquipmentAuditoryImplant1:
		l = "EquipmentAuditoryImplant1";
		break;
	case EquipmentAuditoryImplant2:
		l = "EquipmentAuditoryImplant2";
		break;
	case EquipmentCNSImplant:
		l = "EquipmentCNSImplant";
		break;
	case EquipmentPrimary:
		l = "EquipmentPrimary";
		break;
	case EquipmentSecondary:
		l = "EquipmentSecondary";
		break;
	default:
		l.clear();
		l.append("EquipmentSlot unknown (" + std::to_string(r) + ")");
		break;
	}
}

void inventory::AppearanceSlotsToString(const AppearanceSlots r, std::string& l) {
	switch (r) {
	case equipment_slots_inactive:
		l = "AppearanceSlot inactive";
		break;
	case AppearanceHead:
		l = "AppearanceHead";
		break;
	case AppearanceFace:
		l = "AppearanceFace";
		break;
	case AppearanceBody:
		l = "AppearanceBody";
		break;
	case AppearanceShoulders:
		l = "AppearanceShoulders";
		break;
	case AppearanceBack:
		l = "AppearanceBack";
		break;
	case AppearanceChest:
		l = "AppearanceChest";
		break;
	case AppearanceArms:
		l = "AppearanceArms";
		break;
	case AppearanceWrist1:
		l = "AppearanceWrist1";
		break;
	case AppearanceWrist2:
		l = "AppearanceWrist2";
		break;
	case AppearanceHands:
		l = "AppearanceHands";
		break;
	case AppearanceWaist:
		l = "AppearanceWaist";
		break;
	case AppearanceTail:
		l = "AppearanceTail";
		break;
	case AppearanceLegs:
		l = "AppearanceLegs";
		break;
	case AppearanceFeet:
		l = "AppearanceFeet";
		break;
	case AppearanceNeck:
		l = "AppearanceNeck";
		break;
	case AppearanceWings:
		l = "AppearanceWings";
		break;
	case AppearanceEar1:
		l = "AppearanceEar1";
		break;
	case AppearanceEar2:
		l = "AppearanceEar2";
		break;
	case AppearanceFinger1:
		l = "AppearanceFinger1";
		break;
	case AppearanceFinger2:
		l = "AppearanceFinger2";
		break;
	case AppearanceCranialImplant:
		l = "AppearanceCranialImplant";
		break;
	case AppearanceOpticalImplant:
		l = "AppearanceOpticalImplant";
		break;
	case AppearanceAuditoryImplant:
		l = "AppearanceAuditoryImplant";
		break;
	case AppearanceCNSImplant:
		l = "AppearanceCNSImplant";
		break;
	case AppearancePrimary:
		l = "AppearancePrimary";
		break;
	case AppearanceSecondary:
		l = "AppearanceSecondary";
		break;
	default:
		l.clear();
		l.append("AppearanceSlot unknown (" + std::to_string(r) + ")");
		break;
	}
}

void inventory::GeneralSlotsToString(const GeneralSlots r, std::string& l) {
	return MainSlotsToString(MapGeneral, static_cast<MainSlots>(r), l);
}

void inventory::CombatReadySlotsToString(const CombatReadySlots r, std::string& l) {
	switch (r) {
	case combat_ready_slots_inactive:
		l = "CombatReadySlot inactive";
		break;
	case CombatReadyBack:
		l = "CombatReadyBack";
		break;
	case CombatReadyLumbar:
		l = "CombatReadyLumbar";
		break;
	case CombatReadyBelt:
		l = "CombatReadyBelt";
		break;
	case CombatReadyQuiver:
		l = "CombatReadyQuiver";
		break;
	case CombatReadyBandolier:
		l = "CombatReadyBandolier";
		break;
	case CombatReadyForearm1:
		l = "CombatReadyForearm1";
		break;
	case CombatReadyForearm2:
		l = "CombatReadyForearm2";
		break;
	case CombatReadyArm1:
		l = "CombatReadyArm1";
		break;
	case CombatReadyArm2:
		l = "CombatReadyArm2";
		break;
	case CombatReadyThigh1:
		l = "CombatReadyThigh1";
		break;
	case CombatReadyThigh2:
		l = "CombatReadyThigh2";
		break;
	default:
		l.clear();
		l.append("CombatReadySlot unknown (" + std::to_string(r) + ")");
		break;
	}
}

void inventory::MainSlotsToString(const MapSlots r1, const MainSlots r2, std::string& l) {
	switch (r1) {
	case map_slots_inactive:
		l = "MapSlot inactive ";
		break;
	case MapEquipment:
		l = "Equipment";
		break;
	case MapAppearance:
		l = "Appearance";
		break;
	case MapGeneral:
		l = "General";
		break;
	case MapCombatReady:
		l = "CombatReady";
		break;
	case MapCursor:
		l = "Cursor";
		break;
	case MapLost:
		l = "Lost";
		break;
	case MapDeleted:
		l = "Deleted";
		break;
	case MapTrading:
		l = "Trading";
		break;
	case MapWorldObject:
		l = "WorldObject";
		break;
	case MapTradeskill:
		l = "Tradeskill";
		break;
	case MapLoot:
		l = "Loot";
		break;
	case MapInspect:
		l = "Inspect";
		break;
	case MapBank:
		l = "Bank";
		break;
	case MapGuildBank:
		l = "GuildBank";
		break;
	case MapParcel:
		l = "Parcel";
		break;
	case MapMerchantStock:
		l = "MerchantStock";
		break;
	case MapMerchantResell:
		l = "MerchantResell";
		break;
	case MapConsignment:
		l = "Consignment";
		break;
	case MapGuildConsignment:
		l = "GuildConsignment";
		break;
	case MapTheExchange:
		l = "TheExchange";
		break;
	case MapMiscellaneous:
		l = "Miscellaneous";
		break;
	default:
		l = "Unknown";
		break;
	}

	if (IsMainSlotInactive(r2))
		l.append("Slot inactive");
	else if (IsMainSlotBounded(r1, r2))
		l.append(std::to_string(r2));
	else
		l.append("Slot unknown (" + std::to_string(r2) + ")");
}

bool inventory::IsMainSlotBounded(const MapSlots r1, const MainSlots r2) {
	if (!IsMapSlotBounded(r1))
		return false;

	if (r2 < main_slots_begin_ || r2 >= MainSlotsSize[r1])
		return false;

	return true;
}

formats::InventoryData::~InventoryData() {
	for (auto iter1 : InventoryVector) {
		if (iter1) {
			for (auto iter2 : *iter1)
				SAFE_DELETE(iter2);
		}

		SAFE_DELETE(iter1);
	}
}

bool profiles::InventoryAttributes::InitializeInventoryData() {
	for (auto iter : inventory_data_.InventoryVector)
		iter = new item_vector_t;

	initialized_ = true;

	return true;
}

bool profiles::InventoryAttributes::IsInventoryLocationBounded(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3, const item::UpgradeSlots r4) const {
	if (!IsMainSlotBounded(r1, r2))
		return false;

	if (item::IsContainerSlotInactive(r3) && item::IsUpgradeSlotInactive(r4))
		return true;

	const auto* test_val1 = (*inventory_data_.InventoryVector[r1])[r2];
	if (test_val1 == nullptr)
		return false;

	if (item::IsContainerSlotInactive(r3))
		return test_val1->IsUpgradeSlotBounded(r4);

	if (!test_val1->IsContainerSlotBounded(r3))
		return false;

	const auto* test_val2 = test_val1->GetContainerItemAt(r3);
	if (test_val2 == nullptr)
		return false;

	return test_val2->IsUpgradeSlotBounded(r4);
}

bool profiles::InventoryAttributes::IsMapSlotBounded(const inventory::MapSlots r) const {
	if (!inventory::IsMapSlotBounded(r))
		return false;
	
	return (inventory_data_.InventoryVector[r] != nullptr);
}

bool profiles::InventoryAttributes::IsMainSlotBounded(const inventory::MapSlots r1, const inventory::MainSlots r2) const {
	if (!inventory::IsMainSlotBounded(r1, r2))
		return false;

	return (inventory_data_.InventoryVector[r1] != nullptr);
}

bool profiles::InventoryAttributes::IsContainerSlotBounded(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3) const {
	if (item::IsContainerSlotInactive(r3))
		return false;
	
	if (!IsMainSlotBounded(r1, r2))
		return false;

	auto test_val = (*inventory_data_.InventoryVector[r1])[r2];
	if (test_val == nullptr)
		return false;

	return test_val->IsContainerSlotBounded(r3);
}

bool profiles::InventoryAttributes::IsUpgradeSlotBounded(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3, const item::UpgradeSlots r4) const {
	if (item::IsUpgradeSlotInactive(r4))
		return false;
	
	if (!IsMainSlotBounded(r1, r2))
		return false;

	const auto* test_val1 = (*inventory_data_.InventoryVector[r1])[r2];
	if (test_val1 == nullptr)
		return false;

	if (item::IsContainerSlotInactive(r3))
		return test_val1->IsUpgradeSlotBounded(r4);

	if (!test_val1->IsContainerSlotBounded(r3))
		return false;

	const auto* test_val2 = test_val1->GetContainerItemAt(r3);
	if (test_val2 == nullptr)
		return false;

	return test_val2->IsUpgradeSlotBounded(r4);
}

item_vector_t* profiles::InventoryAttributes::GetMainItemVector(const inventory::MapSlots r) {
	if (!inventory::IsMapSlotBounded(r))
		return nullptr;

	return inventory_data_.InventoryVector[r];
}

item_vector_t* profiles::InventoryAttributes::GetContainerItemVector(const inventory::MapSlots r1, const inventory::MainSlots r2) {
	if (!IsMainSlotBounded(r1, r2))
		return nullptr;

	auto test_val = (*inventory_data_.InventoryVector[r1])[r2];
	if (test_val == nullptr)
		return nullptr;

	return test_val->GetContainerVector();
}

item_vector_t* profiles::InventoryAttributes::GetUpgradeItemVector(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3) {
	if (!IsMainSlotBounded(r1, r2))
		return nullptr;

	auto test_val1 = (*inventory_data_.InventoryVector[r1])[r2];
	if (test_val1 == nullptr)
		return nullptr;

	if (item::IsContainerSlotInactive(r3))
		return test_val1->GetUpgradeVector();

	if (!test_val1->IsContainerSlotBounded(r3))
		return nullptr;

	auto test_val2 = test_val1->GetContainerItemAt(r3);
	if (test_val2 == nullptr)
		return false;

	return test_val2->GetUpgradeVector();
}

objects::Item* profiles::InventoryAttributes::GetItemAt(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3, const item::UpgradeSlots r4) {
	if (!IsMainSlotBounded(r1, r2))
		return nullptr;

	auto ret_val1 = (*inventory_data_.InventoryVector[r1])[r2];
	if (item::IsContainerSlotInactive(r3) && item::IsUpgradeSlotInactive(r4))
		return ret_val1;

	if (item::IsContainerSlotInactive(r3))
		return ret_val1->GetUpgradeItemAt(r4);

	if (item::IsUpgradeSlotInactive(r4))
		return ret_val1->GetContainerItemAt(r3);

	auto ret_val2 = ret_val1->GetContainerItemAt(r3);
	if (ret_val2 == nullptr)
		return nullptr;

	return ret_val2->GetUpgradeItemAt(r4);
}

objects::Item* profiles::InventoryAttributes::GetMainItemAt(const inventory::MapSlots r1, const inventory::MainSlots r2) {
	if (!IsMainSlotBounded(r1, r2))
		return nullptr;

	return (*inventory_data_.InventoryVector[r1])[r2];
}

objects::Item* profiles::InventoryAttributes::GetContainerItemAt(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3) {
	if (!IsMainSlotBounded(r1, r2))
		return nullptr;

	auto ret_val = (*inventory_data_.InventoryVector[r1])[r2];
	if (ret_val == nullptr)
		return nullptr;

	return ret_val->GetContainerItemAt(r3);
}

objects::Item* profiles::InventoryAttributes::GetUpgradeItemAt(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3, const item::UpgradeSlots r4) {
	if (!IsMainSlotBounded(r1, r2))
		return nullptr;

	auto ret_val1 = (*inventory_data_.InventoryVector[r1])[r2];
	if (ret_val1 == nullptr)
		return nullptr;

	if (item::IsContainerSlotInactive(r3))
		return ret_val1->GetUpgradeItemAt(r4);

	auto ret_val2 = ret_val1->GetContainerItemAt(r3);
	if (ret_val2 == nullptr)
		return nullptr;

	return ret_val2->GetUpgradeItemAt(r4);
}



bool profiles::InventoryAttributes::is_container_slot_limited_(const item::ContainerSlots r1, const item_vector_t* r2) {
	if (r2 == nullptr)
		return false;

	if (r1 < item::container_slots_begin_ || r1 >= r2->size())
		return false;

	return true;
}

bool profiles::InventoryAttributes::is_upgrade_slot_limited_(const item::UpgradeSlots r1, const item_vector_t* r2) {
	if (r2 == nullptr)
		return false;

	if (r1 < item::upgrade_slots_begin_ || r1 >= r2->size())
		return false;

	return true;
}