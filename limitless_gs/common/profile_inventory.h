#pragma once


#include "object_item.h"


namespace inventory {

	enum MapSlots : slot_t {
		map_slots_inactive = SLOT_T_MAX,
		MapEquipment = SLOT_T_MIN,
		MapAppearance,
		MapGeneral,
		MapCombatReady,
		MapCursor,
		MapLost,
		MapDeleted,
		MapTrading,
		MapWorldObject,
		MapTradeskill,
		MapLoot,
		MapInspect,
		MapBank,
		MapGuildBank,
		MapParcel,
		MapMerchantStock,
		MapMerchantResell,
		MapConsignment,
		MapGuildConsignment,
		MapTheExchange,
		MapMiscellaneous,
		map_slots_begin_ = MapEquipment,
		map_slots_end_ = MapMiscellaneous,
		map_slots_count_
	};

	inline bool IsMapSlotInactive(const MapSlots r) { return (r == map_slots_inactive); }
	
	void MapSlotsToString(const MapSlots r, std::string& l);

	enum EquipmentSlots : slot_t {
		equipment_slots_inactive = SLOT_T_MAX,
		// basic
		EquipmentHead = SLOT_T_MIN,
		EquipmentFace,
		EquipmentBody,
		EquipmentShoulders,
		EquipmentBack,
		EquipmentChest,
		EquipmentArms,
		EquipmentWrist1,
		EquipmentWrist2,
		EquipmentHands,
		EquipmentWaist,
		EquipmentTail,
		EquipmentLegs,
		EquipmentFeet,
		// adornments
		EquipmentNeck,
		EquipmentWings,
		EquipmentEar1,
		EquipmentEar2,
		EquipmentFinger1,
		EquipmentFinger2,
		// implants
		EquipmentCranialImplant,
		EquipmentOpticalImplant1,
		EquipmentOpticalImplant2,
		EquipmentAuditoryImplant1,
		EquipmentAuditoryImplant2,
		EquipmentCNSImplant,
		// held
		EquipmentPrimary,
		EquipmentSecondary,
		equipment_slots_begin_ = EquipmentHead,
		equipment_slots_end_ = EquipmentSecondary,
		equipment_slots_count_
	};

	inline bool IsEquipmentSlotInactive(const EquipmentSlots r) { return (r == equipment_slots_inactive); }
	
	void EquipmentSlotsToString(const EquipmentSlots r, std::string& l);

	enum EquipmentBits : bitmask64_t {
		equipment_bits_none_ = BITMASK64_T_NONE,

		equipment_bits_held_,
		equipment_bits_worn_,
		equipment_bits_accoutrement_,
		equipment_bits_all_ = BITMASK64_T_ALL
	};

	enum AppearanceSlots : slot_t {
		appearance_slots_inactive = SLOT_T_MAX,
		// basic
		AppearanceHead = SLOT_T_MIN,
		AppearanceFace,
		AppearanceBody,
		AppearanceShoulders,
		AppearanceBack,
		AppearanceChest,
		AppearanceArms,
		AppearanceWrist1,
		AppearanceWrist2,
		AppearanceHands,
		AppearanceWaist,
		AppearanceTail,
		AppearanceLegs,
		AppearanceFeet,
		// adornments
		AppearanceNeck,
		AppearanceWings,
		AppearanceEar1,
		AppearanceEar2,
		AppearanceFinger1,
		AppearanceFinger2,
		// implants
		AppearanceCranialImplant,
		AppearanceOpticalImplant,
		AppearanceAuditoryImplant,
		AppearanceCNSImplant,
		// held
		AppearancePrimary,
		AppearanceSecondary,
		appearance_slots_begin_ = AppearanceHead,
		appearance_slots_end_ = AppearanceSecondary,
		appearance_slots_count_
	};

	inline bool IsAppearanceSlotInactive(const EquipmentSlots r) { return (r == appearance_slots_inactive); }

	void AppearanceSlotsToString(const AppearanceSlots r, std::string& l);

	enum AppearanceBits : bitmask64_t {
		appearance_bits_none_ = BITMASK64_T_NONE,
		appearance_bits_held_,
		appearance_bits_worn_,
		appearance_bits_accoutrement_, // only accoutrement bits that have appearance/visual effects
		appearance_bits_all_ = BITMASK64_T_ALL
	};

	enum GeneralSlots : slot_t {
		general_slots_inactive = SLOT_T_MAX,
		general_slots_begin_ = SLOT_T_MIN,
		general_slots_end_ = 11,
		general_slots_count_
	};

	inline bool IsGeneralSlotInactive(const GeneralSlots r) { return (r == general_slots_inactive); }

	inline void GeneralSlotsToString(const GeneralSlots r, std::string& l);

	enum CombatReadySlots : slot_t {
		combat_ready_slots_inactive = SLOT_T_MAX,
		CombatReadyBack = SLOT_T_MIN,
		CombatReadyLumbar,
		CombatReadyBelt,
		CombatReadyQuiver,
		CombatReadyBandolier,
		CombatReadyForearm1,
		CombatReadyForearm2,
		CombatReadyArm1,
		CombatReadyArm2,
		CombatReadyThigh1,
		CombatReadyThigh2,
		combat_ready_slots_begin_ = CombatReadyBack,
		combat_ready_slots_end_ = CombatReadyThigh2,
		combat_ready_slots_count_,
	};

	inline bool IsCombatReadySlotInactive(const CombatReadySlots r) { return (r == combat_ready_slots_inactive); }

	void CombatReadySlotsToString(const CombatReadySlots r, std::string& l);

	enum CombatReadyBits : bitmask64_t {
		combat_ready_bits_none_ = BITMASK64_T_NONE,
		combat_ready_bits_all_ = BITMASK64_T_ALL
	};

	enum MainSlots : slot_t {
		main_slots_inactive = SLOT_T_MAX,
		main_slots_begin_ = SLOT_T_MIN,
		main_slots_end_ = MAIN_SLOT_MAX,
		main_slots_count_
	};

	inline bool IsMainSlotInactive(const MainSlots r) { return (r == main_slots_inactive); }
	
	void MainSlotsToString(const MapSlots r1, const MainSlots r2, std::string& l);
	
	inline bool IsMapSlotBounded(const MapSlots r) { return (r >= map_slots_begin_ && r <= map_slots_end_); }

	const size_t MainSlotsSize[map_slots_count_] = {
		equipment_slots_count_,
		appearance_slots_count_,
		general_slots_count_,
		combat_ready_slots_count_,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
	};

	inline bool IsMainSlotBounded(const MapSlots r1, const MainSlots r2);

	inline bool IsEquipmentSlotBounded(const EquipmentSlots r) { return (r >= equipment_slots_begin_ && r < MainSlotsSize[MapEquipment]); }
	inline bool IsAppearanceSlotBounded(const AppearanceSlots r) { return (r >= appearance_slots_begin_ && r < MainSlotsSize[MapAppearance]); }
	inline bool IsGeneralSlotBounded(const GeneralSlots r) { return (r >= general_slots_begin_ && r < MainSlotsSize[MapGeneral]); }
	inline bool IsCombatReadySlotBounded(const CombatReadySlots r) { return (r >= combat_ready_slots_begin_ && r < MainSlotsSize[MapCombatReady]); }

} // namespace inventory

#pragma pack(1)

namespace formats {

	struct inventory_map_ {
		inventory::MapSlots Map;
	};

	struct InventorySlot {
		inventory::MainSlots Main;
		item::ContainerSlots Container;
		item::UpgradeSlots Upgrade;
	};

	struct InventoryLocation :
		inventory_map_,
		InventorySlot {
		
		const InventorySlot& slot() const { return dynamic_cast<const InventorySlot&>(*this); }
		InventorySlot& slot() { return dynamic_cast<InventorySlot&>(*this); }
	};

	struct InventoryData {
		~InventoryData();

		inventory_vector_t InventoryVector;
	};

} // namespace formats

#pragma pack()

//namespace inventory {
//
//} // namespace inventory

namespace profiles {

	struct InventoryAttributes {
		virtual bool InitializeInventoryData();
		bool IsInventoryDataInitialized() const { return initialized_; }

		inline bool IsInventoryLocationBounded(const formats::InventoryLocation& r) const { return IsInventoryLocationBounded(r.Map, r.Main, r.Container, r.Upgrade); }
		inline bool IsInventoryLocationBounded(const inventory::MapSlots r1, const formats::InventorySlot& r2) const { return IsInventoryLocationBounded(r1, r2.Main, r2.Container, r2.Upgrade); }
		bool IsInventoryLocationBounded(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3, const item::UpgradeSlots r4) const;

		inline bool IsMapSlotBounded(const formats::InventoryLocation& r) const { return IsMapSlotBounded(r.Map); }
		bool IsMapSlotBounded(const inventory::MapSlots r) const;

		inline bool IsMainSlotBounded(const formats::InventoryLocation& r) const { return IsMainSlotBounded(r.Map, r.Main); }
		bool IsMainSlotBounded(const inventory::MapSlots r1, const inventory::MainSlots r2) const;

		inline bool IsContainerSlotBounded(const formats::InventoryLocation& r) const { return IsContainerSlotBounded(r.Map, r.Main, r.Container); }
		inline bool IsContainerSlotBounded(const inventory::MapSlots r1, const formats::InventorySlot& r2) const { return IsContainerSlotBounded(r1, r2.Main, r2.Container); }
		bool IsContainerSlotBounded(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3) const;

		inline bool IsUpgradeSlotBounded(const formats::InventoryLocation& r) const { return IsUpgradeSlotBounded(r.Map, r.Main, r.Container, r.Upgrade); }
		inline bool IsUpgradeSlotBounded(const inventory::MapSlots r1, const formats::InventorySlot& r2) const { return IsUpgradeSlotBounded(r1, r2.Main, r2.Container, r2.Upgrade); }
		bool IsUpgradeSlotBounded(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3, const item::UpgradeSlots r4) const;

		inline const inventory_vector_t& GetInventoryVector() const { return inventory_data_.InventoryVector; }

		inline const item_vector_t* GetMainItemVector(const formats::InventoryLocation& r) const { return const_cast<InventoryAttributes*>(this)->GetMainItemVector(r.Map); }
		inline const item_vector_t* GetMainItemVector(const inventory::MapSlots r) const { return const_cast<InventoryAttributes*>(this)->GetMainItemVector(r); }

		inline const item_vector_t* GetContainerItemVector(const formats::InventoryLocation& r) const { return const_cast<InventoryAttributes*>(this)->GetContainerItemVector(r.Map, r.Main); }
		inline const item_vector_t* GetContainerItemVector(const inventory::MapSlots r1, const formats::InventorySlot& r2) const { return const_cast<InventoryAttributes*>(this)->GetContainerItemVector(r1, r2.Main); }
		inline const item_vector_t* GetContainerItemVector(const inventory::MapSlots r1, const inventory::MainSlots r2) const { return const_cast<InventoryAttributes*>(this)->GetContainerItemVector(r1, r2); }

		inline const item_vector_t* GetUpgradeItemVector(const formats::InventoryLocation& r) const { return const_cast<InventoryAttributes*>(this)->GetUpgradeItemVector(r.Map, r.Main, r.Container); }
		inline const item_vector_t* GetUpgradeItemVector(const inventory::MapSlots r1, const formats::InventorySlot& r2) const { return const_cast<InventoryAttributes*>(this)->GetUpgradeItemVector(r1, r2.Main, r2.Container); }
		inline const item_vector_t* GetUpgradeItemVector(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3) const { return const_cast<InventoryAttributes*>(this)->GetUpgradeItemVector(r1, r2, r3); }
		
		inline const objects::Item* GetItemAt(const formats::InventoryLocation& r) const { return const_cast<InventoryAttributes*>(this)->GetItemAt(r.Map, r.Main, r.Container, r.Upgrade); }
		inline const objects::Item* GetItemAt(const inventory::MapSlots r1, const formats::InventorySlot& r2) const { return const_cast<InventoryAttributes*>(this)->GetItemAt(r1, r2.Main, r2.Container, r2.Upgrade); }
		inline const objects::Item* GetItemAt(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3, const item::UpgradeSlots r4) const { return const_cast<InventoryAttributes*>(this)->GetItemAt(r1, r2, r3, r4); }

		inline const objects::Item* GetMainItemAt(const formats::InventoryLocation& r) const { return const_cast<InventoryAttributes*>(this)->GetMainItemAt(r.Map, r.Main); }
		inline const objects::Item* GetMainItemAt(const inventory::MapSlots r1, const formats::InventorySlot& r2) const { return const_cast<InventoryAttributes*>(this)->GetMainItemAt(r1, r2.Main); }
		inline const objects::Item* GetMainItemAt(const inventory::MapSlots r1, const inventory::MainSlots r2) const { return const_cast<InventoryAttributes*>(this)->GetMainItemAt(r1, r2); }

		inline const objects::Item* GetContainerItemAt(const formats::InventoryLocation& r) const { return const_cast<InventoryAttributes*>(this)->GetContainerItemAt(r.Map, r.Main, r.Container); }
		inline const objects::Item* GetContainerItemAt(const inventory::MapSlots r1, const formats::InventorySlot& r2) const { return const_cast<InventoryAttributes*>(this)->GetContainerItemAt(r1, r2.Main, r2.Container); }
		inline const objects::Item* GetContainerItemAt(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3) const { return const_cast<InventoryAttributes*>(this)->GetContainerItemAt(r1, r2, r3); }

		inline const objects::Item* GetUpgradeItemAt(const formats::InventoryLocation& r) const { return const_cast<InventoryAttributes*>(this)->GetUpgradeItemAt(r.Map, r.Main, r.Container, r.Upgrade); }
		inline const objects::Item* GetUpgradeItemAt(const inventory::MapSlots r1, const formats::InventorySlot& r2) const { return const_cast<InventoryAttributes*>(this)->GetUpgradeItemAt(r1, r2.Main, r2.Container, r2.Upgrade); }
		inline const objects::Item* GetUpgradeItemAt(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3, const item::UpgradeSlots r4) const { return const_cast<InventoryAttributes*>(this)->GetUpgradeItemAt(r1, r2, r3, r4); }

	protected:

		inline inventory_vector_t& GetInventoryVector() { return inventory_data_.InventoryVector; }

		inline item_vector_t* GetMainItemVector(const formats::InventoryLocation& r) { return GetMainItemVector(r.Map); }
		item_vector_t* GetMainItemVector(const inventory::MapSlots r);

		inline item_vector_t* GetContainerItemVector(const formats::InventoryLocation& r) { return GetContainerItemVector(r.Map, r.Main); }
		inline item_vector_t* GetContainerItemVector(const inventory::MapSlots r1, const formats::InventorySlot& r2) { return GetContainerItemVector(r1, r2.Main); }
		item_vector_t* GetContainerItemVector(const inventory::MapSlots r1, const inventory::MainSlots r2);

		inline item_vector_t* GetUpgradeItemVector(const formats::InventoryLocation& r) { return GetUpgradeItemVector(r.Map, r.Main, r.Container); }
		inline item_vector_t* GetUpgradeItemVector(const inventory::MapSlots r1, const formats::InventorySlot& r2) { return GetUpgradeItemVector(r1, r2.Main, r2.Container); }
		item_vector_t* GetUpgradeItemVector(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3);

		inline objects::Item* GetItemAt(const formats::InventoryLocation& r) { return GetItemAt(r.Map, r.Main, r.Container, r.Upgrade); }
		inline objects::Item* GetItemAt(const inventory::MapSlots r1, const formats::InventorySlot& r2) { return GetItemAt(r1, r2.Main, r2.Container, r2.Upgrade); }
		objects::Item* GetItemAt(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3, const item::UpgradeSlots r4);

		inline objects::Item* GetMainItemAt(const formats::InventoryLocation& r) { return GetMainItemAt(r.Map, r.Main); }
		inline objects::Item* GetMainItemAt(const inventory::MapSlots r1, const formats::InventorySlot& r2) { return GetMainItemAt(r1, r2.Main); }
		objects::Item* GetMainItemAt(const inventory::MapSlots r1, const inventory::MainSlots r2);

		inline objects::Item* GetContainerItemAt(const formats::InventoryLocation& r) { return GetContainerItemAt(r.Map, r.Main, r.Container); }
		inline objects::Item* GetContainerItemAt(const inventory::MapSlots r1, const formats::InventorySlot& r2) { return GetContainerItemAt(r1, r2.Main, r2.Container); }
		objects::Item* GetContainerItemAt(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3);

		inline objects::Item* GetUpgradeItemAt(const formats::InventoryLocation& r) { return GetUpgradeItemAt(r.Map, r.Main, r.Container, r.Upgrade); }
		inline objects::Item* GetUpgradeItemAt(const inventory::MapSlots r1, const formats::InventorySlot& r2) { return GetUpgradeItemAt(r1, r2.Main, r2.Container, r2.Upgrade); }
		objects::Item* GetUpgradeItemAt(const inventory::MapSlots r1, const inventory::MainSlots r2, const item::ContainerSlots r3, const item::UpgradeSlots r4);



	private:

		inline bool is_container_slot_limited_(const item::ContainerSlots r1, const item_vector_t* r2);
		inline bool is_upgrade_slot_limited_(const item::UpgradeSlots r1, const item_vector_t* r2);

		bool initialized_;

		formats::InventoryData inventory_data_;
	};

} // namespace profiles
