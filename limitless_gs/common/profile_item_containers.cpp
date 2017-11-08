#include "common_macros.h"
#include "object_item.h"
#include "profile_item_containers.h"


void item::ContainerSlotsToString(const ContainerSlots r, std::string& l) {
	l = "Container";

	if (IsContainerSlotInactive(r))
		l.append("Slot inactive");
	else if (IsContainerSlotBounded(r))
		l.append(std::to_string(r));
	else
		l.append("Slot unknown");
}

formats::ItemContainerData::~ItemContainerData() {
	for (auto iter : ContainerVector)
		SAFE_DELETE(iter);
}

profiles::ItemContainerAttributes::~ItemContainerAttributes() {
	SAFE_DELETE(container_data_);
}

bool profiles::ItemContainerAttributes::InitializeContainerData(const slot_t r) {
	if (container_data_ != nullptr)
		return false;

	if (r < 1 || r > item::container_slots_count_)
		return false;

	container_data_ = new formats::ItemContainerData;
	container_data_->ContainerVector.resize(r);

	initialized_ = true;

	return true;
}

slot_t profiles::ItemContainerAttributes::GetContainerDataSize() const {
	if (container_data_ == nullptr)
		return 0;

	auto test_val = container_data_->ContainerVector.size();
	if (test_val > SLOT_T_MAX)
		return 0;

	return (slot_t)test_val;
}

slot_t profiles::ItemContainerAttributes::GetContainerDataCount() const {
	slot_t ret_val = 0;

	if (container_data_ == nullptr)
		return ret_val;

	for (auto iter : container_data_->ContainerVector) {
		if (iter != nullptr)
			++ret_val;
	}

	return ret_val;
}

bool profiles::ItemContainerAttributes::IsContainerDataEmpty() const {
	if (container_data_ == nullptr)
		return true;

	for (auto iter : container_data_->ContainerVector) {
		if (iter != nullptr)
			return false;
	}

	return true;
}

bool profiles::ItemContainerAttributes::IsContainerSlotBounded(const item::ContainerSlots r) const {
	if (container_data_ == nullptr)
		return false;

	return (r >= item::container_slots_begin_ && r < container_data_->ContainerVector.size());
}

bool profiles::ItemContainerAttributes::IsContainerSlotFree(const item::ContainerSlots r) const {
	if (!IsContainerSlotBounded(r))
		return false;

	return (container_data_->ContainerVector[r] == nullptr);
}

item_vector_t* profiles::ItemContainerAttributes::GetContainerVector() {
	if (container_data_ == nullptr)
		return nullptr;

	return &container_data_->ContainerVector;
}

item::ContainerSlots profiles::ItemContainerAttributes::FindEmptyContainerSlot() {
	if (container_data_ == nullptr)
		return item::container_slots_inactive_;

	for (slot_t test_val = item::container_slots_begin_; test_val < container_data_->ContainerVector.size(); ++test_val) {
		if (container_data_->ContainerVector[test_val] == nullptr)
			return static_cast<item::ContainerSlots>(test_val);
	}

	return item::container_slots_inactive_;
}

objects::Item* profiles::ItemContainerAttributes::GetContainerItemAt(const item::ContainerSlots r) {
	if (!IsContainerSlotBounded(r))
		return nullptr;

	return container_data_->ContainerVector[r];
}

objects::Item* profiles::ItemContainerAttributes::SetContainerItemAt(const item::ContainerSlots r1, objects::Item* r2) {
	if (!IsContainerSlotBounded(r1))
		return r2;

	if (container_data_->ContainerVector[r1] != nullptr)
		return r2;

	container_data_->ContainerVector[r1] = r2;

	return nullptr;
}

objects::Item* profiles::ItemContainerAttributes::RemoveContainerItemAt(const item::ContainerSlots r) {
	if (!IsContainerSlotBounded(r))
		return nullptr;

	auto ret_val = container_data_->ContainerVector[r];
	container_data_->ContainerVector[r] = nullptr;

	return ret_val;
}

objects::Item* profiles::ItemContainerAttributes::SwapContainerItemAt(const item::ContainerSlots r1, objects::Item* r2) {
	if (!IsContainerSlotBounded(r1))
		return r2;

	auto ret_val = container_data_->ContainerVector[r1];
	container_data_->ContainerVector[r1] = r2;
	
	return ret_val;
}

bool profiles::ItemContainerAttributes::SwapContainerSlots(const item::ContainerSlots r1, const item::ContainerSlots r2) {
	if (!IsContainerSlotBounded(r1))
		return false;

	if (r2 < item::container_slots_begin_ || r2 >= container_data_->ContainerVector.size())
		return false;

	auto swap_val = container_data_->ContainerVector[r1];
	container_data_->ContainerVector[r1] = container_data_->ContainerVector[r2];
	container_data_->ContainerVector[r2] = swap_val;

	return true;
}
