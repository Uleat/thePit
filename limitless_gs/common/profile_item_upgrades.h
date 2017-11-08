#pragma once


#include "common_types.h"


namespace item {

	enum UpgradeSlots : slot_t {
		upgrade_slots_inactive_ = SLOT_T_MAX,
		UpgradeAttack = SLOT_T_MIN,
		UpgradeSpeed,
		UpgradeAccuracy,
		UpgradeTargetBias,
		UpgradeMultiplier,
		UpgradePowerCell,
		UpgradeDefense,
		UpgradeSpecialization,
		UpgradeAppearance,
		UpgradeMiscellaneous,
		upgrade_slots_begin_ = UpgradeAttack,
		upgrade_slots_end_ = UpgradeMiscellaneous,
		upgrade_slots_count_ // should re-work these up to 20 slots (4 groups of 5)
		// attack group
		// defense group
		// specialization group
		// miscellaneous group
	};

	inline bool IsUpgradeSlotInactive(const UpgradeSlots r) { return (r == upgrade_slots_inactive_); }
	inline bool IsUpgradeSlotBounded(const UpgradeSlots r) { return (r >= upgrade_slots_begin_ && r <= upgrade_slots_end_); }

	void UpgradeSlotsToString(const UpgradeSlots r, std::string& l);

	enum UpgradeBits : bitmask32_t {
		upgrade_bits_none_ = BITMASK32_T_NONE,
		UpgradeBitAttack = (1 << UpgradeAttack),
		UpgradeBitSpeed = (1 << UpgradeSpeed),
		UpgradeBitAccuracy = (1 << UpgradeAccuracy),
		UpgradeBitTargetBias = (1 << UpgradeTargetBias),
		UpgradeBitMultiplier = (1 << UpgradeMultiplier),
		UpgradeBitPowerCell = (1 << UpgradePowerCell),
		UpgradeBitDefense = (1 << UpgradeDefense),
		UpgradeBitSpecialization = (1 << UpgradeSpecialization),
		UpgradeBitAppearance = (1 << UpgradeAppearance),
		UpgradeBitMiscellaneous = (1 << UpgradeMiscellaneous),
		upgrade_bits_all_ = BITMASK32_T_ALL
	};

	inline UpgradeSlots to_upgrade_slots(const slot_t r) { return static_cast<UpgradeSlots>(r); }
	inline slot_t to_slot_t(const UpgradeSlots r) { return (slot_t)(r); }

} // namespace item

#pragma pack(1)

namespace formats {

	struct ItemUpgradeData {
		~ItemUpgradeData();

		item_vector_t UpgradeVector;
	};

} // namespace formats

#pragma pack()

//namespace item {
//
//} // namespace item

namespace profiles {

	struct ItemUpgradeAttributes {
		ItemUpgradeAttributes() : upgrade_data_(nullptr), upgrade_bitmask_(item::upgrade_bits_none_), initialized_(false) { }
		ItemUpgradeAttributes(const ItemUpgradeAttributes& r) : upgrade_data_(nullptr), upgrade_bitmask_(item::upgrade_bits_none_), initialized_(false) { }
		~ItemUpgradeAttributes();

		bool InitializeUpgradeData(const item::UpgradeBits r);
		inline bool IsUpgradeDataInitialized() const { return initialized_; }

		slot_t GetUpgradeDataSize() const;

		bool IsUpgradeDataEmpty() const;

		bool IsUpgradeSlotBounded(const item::UpgradeSlots r) const;

		bool IsUpgradeSlotFree(const item::UpgradeSlots r) const;

		inline const item_vector_t* GetUpgradeVector() const { return const_cast<ItemUpgradeAttributes*>(this)->GetUpgradeVector(); }

		inline const objects::Item* GetUpgradeItemAt(const item::UpgradeSlots r) const { return const_cast<ItemUpgradeAttributes*>(this)->GetUpgradeItemAt(r); }

	protected:

		item_vector_t* GetUpgradeVector();

		objects::Item* GetUpgradeItemAt(const item::UpgradeSlots r);
		objects::Item* SetUpgradeItemAt(const item::UpgradeSlots r1, objects::Item* r2);
		objects::Item* RemoveUpgradeItemAt(const item::UpgradeSlots r);
		objects::Item* SwapUpgradeItemAt(const item::UpgradeSlots r1, objects::Item* r2);

		// upgrades cannot be in-place swapped due to their type association with slot index

	private:

		bool initialized_;

		item::UpgradeBits upgrade_bitmask_;

		formats::ItemUpgradeData* upgrade_data_;
	};

} // namespace profiles
