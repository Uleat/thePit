#include "common_macros.h"
#include "object_item.h"
#include "profile_item_upgrades.h"


void item::UpgradeSlotsToString(const UpgradeSlots r, std::string& l) {
	switch (r) {
	case upgrade_slots_inactive_:
		l = "UpgradeSlot inactive";
		break;
	case UpgradeAttack:
		l = "UpgradeAttack";
		break;
	case UpgradeSpeed:
		l = "UpgradeSpeed";
		break;
	case UpgradeAccuracy:
		l = "UpgradeAccuracy";
		break;
	case UpgradeTargetBias:
		l = "UpgradeTargetBias";
		break;
	case UpgradeMultiplier:
		l = "UpgradeMultiplier";
		break;
	case UpgradePowerCell:
		l = "UpgradePowerCell";
		break;
	case UpgradeDefense:
		l = "UpgradeDefense";
		break;
	case UpgradeSpecialization:
		l = "UpgradeSpecialization";
		break;
	case UpgradeAppearance:
		l = "UpgradeAppearance";
		break;
	case UpgradeMiscellaneous:
		l = "UpgradeMiscellaneous";
		break;
	default:
		l = "UpgradeSlot unknown";
		break;
	}
}

formats::ItemUpgradeData::~ItemUpgradeData() {
	for (auto iter : UpgradeVector)
		SAFE_DELETE(iter);
}

profiles::ItemUpgradeAttributes::~ItemUpgradeAttributes() {
	SAFE_DELETE(upgrade_data_);
}

bool profiles::ItemUpgradeAttributes::InitializeUpgradeData(const item::UpgradeBits r) {
	if (upgrade_data_ != nullptr)
		return false;

	upgrade_data_ = new formats::ItemUpgradeData;
	upgrade_data_->UpgradeVector.resize(item::upgrade_slots_count_);

	upgrade_bitmask_ = r;

	initialized_ = true;

	return true;
}

slot_t profiles::ItemUpgradeAttributes::GetUpgradeDataSize() const {
	if (upgrade_data_ == nullptr)
		return 0;

	auto test_val = upgrade_data_->UpgradeVector.size();
	if (test_val > SLOT_T_MAX)
		return 0;

	return (slot_t)test_val;
}

bool profiles::ItemUpgradeAttributes::IsUpgradeDataEmpty() const {
	if (upgrade_data_ == nullptr)
		return true;

	for (auto iter : upgrade_data_->UpgradeVector) {
		if (iter != nullptr)
			return false;
	}

	return true;
}

bool profiles::ItemUpgradeAttributes::IsUpgradeSlotBounded(const item::UpgradeSlots r) const {
	if (upgrade_data_ == nullptr)
		return false;

	if (r < item::upgrade_slots_begin_ || r >= upgrade_data_->UpgradeVector.size())
		return false;

	return (((1ui32 << r) & upgrade_bitmask_) != item::upgrade_bits_none_);
}

bool profiles::ItemUpgradeAttributes::IsUpgradeSlotFree(const item::UpgradeSlots r) const {
	if (!IsUpgradeSlotBounded(r))
		return false;

	return (upgrade_data_->UpgradeVector[r] == nullptr);
}

item_vector_t* profiles::ItemUpgradeAttributes::GetUpgradeVector() {
	if (upgrade_data_ == nullptr)
		return nullptr;

	return &upgrade_data_->UpgradeVector;
}

objects::Item* profiles::ItemUpgradeAttributes::GetUpgradeItemAt(const item::UpgradeSlots r) {
	if (!IsUpgradeSlotBounded(r))
		return nullptr;

	return upgrade_data_->UpgradeVector[r];
}

objects::Item* profiles::ItemUpgradeAttributes::SetUpgradeItemAt(const item::UpgradeSlots r1, objects::Item* r2) {
	if (!IsUpgradeSlotBounded(r1))
		return r2;

	if (upgrade_data_->UpgradeVector[r1] != nullptr)
		return r2;

	upgrade_data_->UpgradeVector[r1] = r2;

	return nullptr;
}

objects::Item* profiles::ItemUpgradeAttributes::RemoveUpgradeItemAt(const item::UpgradeSlots r) {
	if (!IsUpgradeSlotBounded(r))
		return nullptr;

	auto ret_val = upgrade_data_->UpgradeVector[r];
	upgrade_data_->UpgradeVector[r] = nullptr;

	return ret_val;
}

objects::Item* profiles::ItemUpgradeAttributes::SwapUpgradeItemAt(const item::UpgradeSlots r1, objects::Item* r2) {
	if (!IsUpgradeSlotBounded(r1))
		return r2;

	auto ret_val = upgrade_data_->UpgradeVector[r1];
	upgrade_data_->UpgradeVector[r1] = r2;

	return ret_val;
}
