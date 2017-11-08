#pragma once


#include "common_types.h"


namespace item {

	enum ContainerSlots : slot_t {
		container_slots_inactive_ = SLOT_T_MAX,
		container_slots_begin_ = SLOT_T_MIN,
		container_slots_end_ = CONTAINER_SLOT_MAX,
		container_slots_count_
	};

	inline bool IsContainerSlotInactive(const ContainerSlots r) { return (r == container_slots_inactive_); }
	inline bool IsContainerSlotBounded(const ContainerSlots r) { return (r >= container_slots_begin_ && r <= container_slots_end_); }

	void ContainerSlotsToString(const ContainerSlots r, std::string& l);

	inline ContainerSlots to_container_slots(const slot_t r) { return static_cast<ContainerSlots>(r); }
	inline slot_t to_slot_t(const ContainerSlots r) { return (slot_t)(r); }

} // namespace item

#pragma pack(1)

namespace formats {

	struct ItemContainerData {
		~ItemContainerData();

		item_vector_t ContainerVector;
	};

} // namespace formats

#pragma pack()

  //namespace item {
  //
  //} // namespace item

namespace profiles {

	struct ItemContainerAttributes {
		ItemContainerAttributes() : container_data_(nullptr), initialized_(false) { }
		ItemContainerAttributes(const ItemContainerAttributes& r) : container_data_(nullptr), initialized_(false) { }
		~ItemContainerAttributes();

		bool InitializeContainerData(const slot_t r);
		inline bool IsContainerDataInitialized() const { return initialized_; }

		slot_t GetContainerDataSize() const;
		slot_t GetContainerDataCount() const;

		bool IsContainerDataEmpty() const;

		bool IsContainerSlotBounded(const item::ContainerSlots r) const;

		bool IsContainerSlotFree(const item::ContainerSlots r) const;

		inline const item_vector_t* GetContainerVector() const { return const_cast<ItemContainerAttributes*>(this)->GetContainerVector(); }

		inline const objects::Item* GetContainerItemAt(const item::ContainerSlots r) const { return const_cast<ItemContainerAttributes*>(this)->GetContainerItemAt(r); }

	protected:

		item_vector_t* GetContainerVector();

		item::ContainerSlots FindEmptyContainerSlot();

		objects::Item* GetContainerItemAt(const item::ContainerSlots r);
		objects::Item* SetContainerItemAt(const item::ContainerSlots r1, objects::Item* r2);
		objects::Item* RemoveContainerItemAt(const item::ContainerSlots r);
		objects::Item* SwapContainerItemAt(const item::ContainerSlots r1, objects::Item* r2);

		bool SwapContainerSlots(const item::ContainerSlots r1, const item::ContainerSlots r2);

	private:

		bool initialized_;

		formats::ItemContainerData* container_data_;
	};

} // namespace profiles
