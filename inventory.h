/*	EQEMu: Everquest Server Emulator
	Copyright (C) 2001-2015 EQEMu Development Team (http://eqemulator.net)

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

#ifndef __INVENTORY_H
#define __INVENTORY_H


#include "eq_dictionary.h"
#include "item2.h"

#include <vector>
#include <list>


// Forward declarations
namespace Item
{
	//struct Effect_Struct;
	//struct Data;
	class Instance;
	//class Evolution;
	//class Factory;
}

class Object;


// Rename to 'Inventory' after removing 'class Inventory'
namespace _Inventory
{
	struct Slot_Struct;
	struct SSlot_Struct;
	class Container;
	class Scope;
	class Slot;
	class Instance;
	class Factory;
	class Query;
	

	// Ready for ALPHA
	struct Slot_Struct {
		size_t map;
		size_t unknown2;
		size_t main;
		size_t sub;
		size_t aug;
		size_t unknown1;
	};

	// Ready for ALPHA
	struct SSlot_Struct { // S(hort)Slot_Struct
		size_t main;
		size_t sub;
		size_t aug;
		size_t unknown1;
	};


	// Ready for ALPHA
	class Container {
		// Not a friend of Item::Instance because we want all transctions to occur in a limit-checked Inventory instance
		// Item::Instance is a presentation/data retrieval class
		friend Object; // Ground spawns, dropped items, world tradeskill containers
		friend Instance;
		friend Query;

	public:
		Container();
		~Container();

		bool Initialize(size_t size);	// Public accessor only initializes if m_Vector.size() == 0

		size_t Size() { return m_Vector.size(); }	// Returns allocated size of m_Vector
		size_t Count();								// Returns number of non-null pointers
		bool Empty();								// Returns true if all Item::Instance pointer values are null, false otherwise
		bool Full();								// Returns true if all Item::Instance pointer values are not null, false otherwise

		const Item::Instance* InstanceAt(size_t index);	// Returns const Item::Instance pointer at index

		std::vector<Item::Instance*>::const_iterator CBegin() { return m_Vector.cbegin(); }	// Probably not needed...
		std::vector<Item::Instance*>::const_iterator CEnd() { return m_Vector.cend(); }		// Probably not needed...

	protected:
		Container(size_t size, size_t reserve);	// 

		size_t Capacity() { return m_Vector.capacity(); }
		bool Reserve(size_t reserve);

		bool Resize(size_t size);	// 
		void Concatenate();			// Performs a std::remove_if() lambda with resize() to treat m_Vector as a FIFO buffer (UF- client compatibility)
		void Clear();				// Clear vector with no Item::Instance pointer handling
		void Consume();				// Clear vector with all Item::Instances consumed

		Item::Instance* GetInstance(size_t index);								// 
		Item::Instance* PutInstance(size_t index, Item::Instance* instance);	// 
		void PopInstance(size_t index);											// Clear index with no Item::Instance pointer handling
		Item::Instance* RemoveInstance(size_t index);							// Clear index with Item::Instance pointer return
		void DeleteInstance(size_t index);										// Clear index with Item::Instance consumption

		std::vector<Item::Instance*>::iterator Begin() { return m_Vector.begin(); }	// Probably not needed...
		std::vector<Item::Instance*>::iterator End() { return m_Vector.end(); }		// Probably not needed...

	private:
		size_t _last();

		std::vector<Item::Instance*> m_Vector;
	};
	
	
	// In development
	class Scope {
		friend Factory;

	public:
		Scope();
		Scope(ClientVersion clientVersion);

		size_t MapSize(size_t index);

		uint64 PossessionsBitmask() { return m_PossessionsBitmask; }
		uint64 EquipmentBitmask() { return m_EquipmentBitmask; }
		uint64 GeneralBitmask() { return m_GeneralBitmask; }
		uint64 CursorBitmask() { return m_CursorBitmask; }

		size_t ItemClassSize(size_t index);
		
		bool AllowsClickCastFromBag() { return m_AllowsClickCastFromBag; }
		bool AllowsEmptyBagInBag() { return m_AllowsEmptyBagInBag; }
		bool RequiresLimboConcatenation() { return m_RequiresLimboConcatenation; }

	protected:
		void DumpValues();
		
	private:
		size_t m_MapSizes[EmuConstants::INVENTORY_MAP_COUNT];

		// Must be uint64 across all platforms
		uint64 m_PossessionsBitmask;
		uint64 m_EquipmentBitmask;
		uint64 m_GeneralBitmask;
		uint64 m_CursorBitmask;

		size_t m_ItemClassSizes[ITEM_CLASS_TYPE_COUNT];

		bool m_AllowsClickCastFromBag;
		bool m_AllowsEmptyBagInBag;
		bool m_RequiresLimboConcatenation;
	};


	// Ready for ALPHA
	class Slot {
	public:
		static void Invalidate(Slot_Struct &dst);
		static void Invalidate(SSlot_Struct &dst);

		static bool IsInvalid(const Slot_Struct &src);
		static bool IsInvalid(const SSlot_Struct &src);

		static bool IsDelete(const Slot_Struct &src);
		static bool IsDelete(const SSlot_Struct &src);
		static bool IsMain(const Slot_Struct &src);
		static bool IsMain(const SSlot_Struct &src);
		static bool IsSub(const Slot_Struct &src);
		static bool IsSub(const SSlot_Struct &src);
		static bool IsMainAug(const Slot_Struct &src);
		static bool IsMainAug(const SSlot_Struct &src);
		static bool IsSubAug(const Slot_Struct &src);
		static bool IsSubAug(const SSlot_Struct &src);

		static bool IsEqual(const Slot_Struct &arg1, const Slot_Struct &arg2);
		static bool IsEqual(const Slot_Struct &arg1, const SSlot_Struct &arg2);
		static bool IsEqual(const SSlot_Struct &arg1, const Slot_Struct &arg2);
		static bool IsEqual(const SSlot_Struct &arg1, const SSlot_Struct &arg2);

		static void GetOwningSlot(Slot_Struct &dst, const Slot_Struct &src);
		static void GetOwningSlot(SSlot_Struct &dst, const SSlot_Struct &src);
		static void GetTopSlot(Slot_Struct &dst, const Slot_Struct &src);
		static void GetTopSlot(SSlot_Struct &dst, const SSlot_Struct &src);

		static void CopySlot(Slot_Struct &dst, const Slot_Struct &src);
		static void CopySlot(SSlot_Struct &dst, const SSlot_Struct &src);
	};


	// In development
	class Instance : public Scope {
	public:
		static void MarkDirty(Item::Instance* dirty);
		static void CleanMarked();

		Container* GetMapContainer(size_t index);

	};


	// Ready for Alpha
	class Factory {
	public:
		static Instance* GenerateInstance(ClientVersion clientVersion = ClientVersion::Unknown);
		static void ReconfigureInstance(Instance &instance, ClientVersion clientVersion);
		static void ConfigureScope(Scope &scope, ClientVersion clientVersion);
	};


	// Ready for ALPHA
	class Query {
	public:
		enum class QueryType {
			None = INDEX_BEGIN,
			// Non-criteria specific
			Empty,
			Extant,
			// Query criteria-specific, non-offset adjusted
			Pointer,
			SerialNumber,
			ItemID,
			LoreGroup,
			AugmentType,
			// Query criteria-specific, offset-adjusted
			ItemClass,
			ItemUse,
			BagType,
			// Item data criteria-specific
			Lore,
			Temporary,
			NotTemporary,
			Tradeable,
			NotTradeable,
			Petable,
			NotPetable,
			Transferable,
			NotTransferable,
			Storable,
			NotStorable
		};

		Query();
		~Query();

		// Query-scope methods
		void ResetCriteria();

		void SetType(QueryType queryType) { m_Type = queryType; }

		void SetQuantity(size_t queryQuantity) { m_Quantity = queryQuantity; }
		size_t QuantityFound() { return m_QuantityFound; }

		void SetExternalList(std::list<Slot_Struct>* queryExternalList) { m_ExternalList = queryExternalList; }

		// Fields that do not require adjustment of zero-based values
		void SetPointer(Item::Instance* queryPointer) { m_Pointer = queryPointer; }
		void SetSerialNumber(uint32 querySerialNumber) { m_SerialNumber = querySerialNumber; }
		void SetItemID(uint32 queryItemID) { m_ItemID = queryItemID; }
		void SetLoreGroup(uint32 queryLoreGroup) { m_LoreGroup = queryLoreGroup; }
		void SetAugmentType(uint32 queryAugmentType) { m_AugmentType = queryAugmentType; }

		// Fields that require adjustment of zero-based values to regisiter
		void SetItemClass(uint8 queryItemClass) { m_ItemClass = (queryItemClass + 1); }
		void SetItemUse(uint8 queryItemUse) { m_ItemUse = (queryItemUse + 1); }
		void SetBagType(uint8 queryBagType) { m_BagType = (queryBagType + 1); }

		// Inventory-scope methods
		void SetInstance(Instance* queryInstance) { m_Instance = queryInstance; }

		void FlagMap(InventoryMaps index);
		void FlagEquipment();
		void FlagGeneral();
		void FlagCursor();
		void FlagDefault();
		
		void IgnoreMain() { m_IgnoreMain = true; }
		void IgnoreSub() { m_IgnoreSub = true; }
		void IgnoreMainAug() { m_IgnoreMainAug = true; }
		void IgnoreSubAug() { m_IgnoreSubAug = true; }

		void Execute();

		std::list<Slot_Struct>* ResultList() { return &m_ResultList; }
		std::list<Slot_Struct>::iterator Begin() { return m_ResultList.begin(); }
		std::list<Slot_Struct>::iterator End() { return m_ResultList.end(); }

		bool Found() { return m_Found; }
		size_t Count() { return m_ResultList.size(); }
		void Clear() { m_ResultList.clear(); }

		// Container-scope methods
		void SetContainer(Container* queryContainer) { m_Container = queryContainer; }
		void SetContainerSize(size_t queryContainerSize) { m_ContainerSize = queryContainerSize; }

		void ExecuteContainer();

		std::list<size_t>* ContainerResultList() { return &m_ContainerResultList; }
		std::list<size_t>::iterator ContainerBegin() { return m_ContainerResultList.begin(); }
		std::list<size_t>::iterator ContainerEnd() { return m_ContainerResultList.end(); }

		bool ContainerFound() { return m_ContainerFound; }
		size_t ContainerCount() { return m_ContainerResultList.size(); }
		void ContainerClear() { return m_ContainerResultList.clear(); }

	private:
		void _execute();
		void _execute_container();
		bool _validate_criteria();
		void _restore_criteria();
		bool _check_criteria(Item::Instance* targetItemInstance);

		Instance* m_Instance;
		Container* m_Container;
		size_t m_ContainerSize;

		bool m_Locations[EmuConstants::INVENTORY_MAP_COUNT];
		bool m_Equipment;
		bool m_General;
		bool m_Cursor;
		bool m_IgnoreMain;
		bool m_IgnoreSub;
		bool m_IgnoreMainAug;
		bool m_IgnoreSubAug;

		QueryType m_Type;
		size_t m_Quantity;
		size_t m_QuantityFound;

		Item::Instance* m_Pointer;
		uint32 m_SerialNumber;
		uint32 m_ItemID;
		uint32 m_LoreGroup;
		uint32 m_AugmentType;

		uint8 m_ItemClass;
		uint8 m_ItemUse;
		uint8 m_BagType;

		std::list<Slot_Struct> m_ResultList;
		std::list<Slot_Struct>* m_ExternalList;
		bool m_Found;

		std::list<size_t> m_ContainerResultList;
		bool m_ContainerFound;

		bool location_set;
		Slot_Struct slot_found;
		std::list<size_t> container_working_list;
	};
}

#endif // #define __INVENTORY_H
