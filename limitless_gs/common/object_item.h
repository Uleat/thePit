#pragma once


#include "profile_item_data.h"


namespace item {

} // namespace item

#pragma pack(1)

namespace formats {

	struct ItemTrackingData {

	};

	struct ItemDynamicData {

	};

} // namespace formats

#pragma pack()

//namespace item {
//
//} // namespace item

namespace managers {

	class Bonus;

} // namespace managers

namespace profiles {

	struct InventoryAttributes;

} // namespace profiles

namespace objects {

	class Item :
		public formats::ItemTrackingData,
		public formats::ItemDynamicData,
		public profiles::ItemContainerAttributes,
		public profiles::ItemUpgradeAttributes {

		friend class managers::Bonus;

		friend struct profiles::InventoryAttributes;

	public:

		Item() : static_data_(item::NullItemStaticData), modifiable_data_(nullptr), initialized_(false) {  } // this should never be used to instantiate an ItemInstance
		Item(const formats::ItemStaticData& r) : static_data_(r), modifiable_data_(nullptr), initialized_(false) {  }
		~Item();

		inline bool IsReflection(const Item* r) const { return (r == this); }

		bool Initialize();
		inline bool IsInitialized() const { return initialized_; }

		inline const formats::ItemTrackingData& GetTrackingData() const { return dynamic_cast<const formats::ItemTrackingData&>(*this); }
		inline formats::ItemTrackingData& GetTrackingData() { return dynamic_cast<formats::ItemTrackingData&>(*this); }

		inline const formats::ItemDynamicData& GetDynamicData() const { return dynamic_cast<const formats::ItemDynamicData&>(*this); }
		inline formats::ItemDynamicData& GetDynamicData() { return dynamic_cast<formats::ItemDynamicData&>(*this); }

		inline const formats::ItemStaticData& GetStaticData() const { return static_data_; }
		inline const formats::ItemIdentificationData& GetIdentificationData() const { return dynamic_cast<const formats::ItemIdentificationData&>(static_data_); }
		inline const formats::ItemDescriptionData& GetDescriptionData() const { return dynamic_cast<const formats::ItemDescriptionData&>(static_data_); }
		inline const formats::ItemScalableData& GetScalableData() const { return dynamic_cast<const formats::ItemScalableData&>(static_data_); }

		inline bool HasModifiableData() const { return (modifiable_data_ != nullptr); }
		inline const formats::ItemScalableData* GetModifiableData() const { return modifiable_data_; }
		inline formats::ItemScalableData* GetModifiableData() { return modifiable_data_; }

		bool IsAllowedByRace(const races::RaceTypes r) const;
		bool IsAllowedByClass(const classes::ClassTypes r) const;
		bool IsAllowedInEquipmentSlot(const inventory::EquipmentSlots r) const;
		bool IsAllowedInHeldSlot(const inventory::EquipmentSlots r) const;
		bool IsAllowedInWornSlot(const inventory::EquipmentSlots r) const;
		bool IsAllowedInAccoutrementSlot(const inventory::EquipmentSlots r) const;
		bool IsAllowedInAppearanceSlot(const inventory::AppearanceSlots r) const;
		bool IsAllowedInCombatReadySlot(const inventory::CombatReadySlots r) const;

		bool IsEquipmentUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const inventory::EquipmentSlots r3) const;
		bool IsHeldUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const inventory::EquipmentSlots r3) const;
		bool IsWornUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const inventory::EquipmentSlots r3) const;
		bool IsAccoutrementUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const inventory::EquipmentSlots r3) const;
		bool IsAppearanceUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const inventory::AppearanceSlots r3) const;
		bool IsCombatReadyUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const inventory::CombatReadySlots r3) const;

		bool IsItemAllowedInContainer(const Item* r) const;
		bool IsItemAllowedInContainer(const formats::ItemStaticData& r1, const bool r2 = false) const;

		bool IsItemAllowedInUpgrade(const Item* r) const;
		bool IsItemAllowedInUpgrade(const formats::ItemStaticData& r) const;

		inline bool IsUpgradeSlotFree(const item::UpgradeTypes r) const; using ItemUpgradeAttributes::IsUpgradeSlotFree;

		bool IsUpgradeUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const Item* r3) const;
		bool IsUpgradeUsable(const races::RaceTypes r1, const classes::ClassTypes r2, const formats::ItemStaticData& r3) const;

	protected:

		// this class should not be inherited

	private:

		formats::ItemScalableData* initialize_modifiable_data();
		void delete_modifiable_data_();

		bool initialized_;

		const formats::ItemStaticData& static_data_;
		formats::ItemScalableData* modifiable_data_;
	};

} // namespace objects
