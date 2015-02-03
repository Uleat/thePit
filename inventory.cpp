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

#include "shareddb.h" // just need logging system for now
#include "inventory.h"


#include <algorithm>


std::list<Item::Instance*> dirty_list;


//
// class _Inventory::Container
//
_Inventory::Container::Container()
{
	m_Vector.reserve(EmuConstants::INVENTORY_CONTAINER_SIZE_LIMIT);
	m_Vector.resize(NIL);
}

_Inventory::Container::~Container()
{
	Consume();
}

bool _Inventory::Container::Initialize(size_t size)
{
	if (m_Vector.size() > NIL) { return false; }
	if (size > m_Vector.capacity()) { return false; }
	
	m_Vector.resize(size);
	return true;
}

size_t _Inventory::Container::Count()
{
	auto count = std::count_if(m_Vector.begin(), m_Vector.end(), [](Item::Instance *item_instance) {return item_instance != nullptr; });
	return static_cast<size_t>(count);
}

bool _Inventory::Container::Empty()
{
	return (Count() == NIL);
}

bool _Inventory::Container::Full()
{
	return (Count() == m_Vector.size());
}

const Item::Instance* _Inventory::Container::InstanceAt(size_t index)
{
	if (index >= m_Vector.size()) { return nullptr; }
	return const_cast<const Item::Instance*>(m_Vector[index]);
}

_Inventory::Container::Container(size_t size, size_t reserve)
{
	if (reserve > EmuConstants::INVENTORY_CONTAINER_SIZE_LIMIT) { reserve = EmuConstants::INVENTORY_CONTAINER_SIZE_LIMIT; }
	if (reserve == NIL) { reserve = 1; }
	m_Vector.reserve(reserve);

	if (size <= reserve)
		m_Vector.resize(size);
	else
		m_Vector.resize(NIL); // Can still be publicly initialized
}

bool _Inventory::Container::Reserve(size_t reserve)
{
	if (reserve == NIL) { return false; }
	if (reserve < Count()) { return false; }
	if (reserve <= _last()) { return false; }
	m_Vector.reserve(reserve);
}

bool _Inventory::Container::Resize(size_t size)
{
	if (size > m_Vector.capacity()) { return false; }
	if (size == m_Vector.size()) { return true; }
	if (size > m_Vector.size()) {
		m_Vector.resize(size);
		return true;
	}

	if (size < Count()) { return false; }
	if (size <= _last()) { return false; }
	m_Vector.resize(size);

	return false;
}

void _Inventory::Container::Concatenate()
{
	auto size = m_Vector.size();
	auto new_end = std::remove_if(m_Vector.begin(), m_Vector.end(), [](Item::Instance *item_instance) {return item_instance == nullptr; });
	m_Vector.erase(new_end, m_Vector.end());
	m_Vector.resize(size);
}

void _Inventory::Container::Clear()
{
	auto size = m_Vector.size();
	m_Vector.clear();
	m_Vector.resize(size);
}

void _Inventory::Container::Consume()
{
	// TODO: Determine if a m_Vector.clear() is needed (would need to m_Vector.resize(n) before being usable again)

	for (auto iterator = m_Vector.begin(); iterator != m_Vector.end(); ++iterator) {
		Instance::MarkDirty(static_cast<Item::Instance*>(*iterator));
		static_cast<Item::Instance*>(*iterator) = nullptr;
	}
}

Item::Instance* _Inventory::Container::GetInstance(size_t index)
{
	if (index >= m_Vector.size()) { return nullptr; }
	return m_Vector[index];
}

Item::Instance* _Inventory::Container::PutInstance(size_t index, Item::Instance* instance)
{
	if (index >= m_Vector.size()) { return instance; }
	if (m_Vector[index] != nullptr) { // If index is not empty, perform a 'swap' so that calling method can handle the return appropriately
		auto old_instance = m_Vector[index];
		m_Vector[index] = instance;
		return old_instance;
	}
	m_Vector[index] = instance;

	return nullptr;
}

void _Inventory::Container::PopInstance(size_t index)
{
	if (index >= m_Vector.size()) { return; }
	m_Vector[index] = nullptr;
}

Item::Instance* _Inventory::Container::RemoveInstance(size_t index)
{
	if (index >= m_Vector.size()) { return nullptr; }
	auto item_instance = m_Vector[index];
	m_Vector[index] = nullptr;

	return item_instance;
}

void _Inventory::Container::DeleteInstance(size_t index)
{
	if (index >= m_Vector.size()) { return; }
	Instance::MarkDirty(m_Vector[index]);
	m_Vector[index] = nullptr;
}

size_t _Inventory::Container::_last()
{
	// Not sure how to convert iterator into index offset
	//auto last = find_if(m_Vector.rbegin(), m_Vector.rend(), [](Item::Instance *item_instance) { return item_instance != nullptr; });

	size_t last = m_Vector.size();
	for (size_t index = INDEX_BEGIN; index < m_Vector.size(); ++index) {
		if (m_Vector[index] != nullptr)
			last = index;
	}
	return last;
}


//
// class _Inventory::Scope
//
_Inventory::Scope::Scope()
{
	memset(m_MapSizes, NIL, sizeof(m_MapSizes));

	m_PossessionsBitmask = NIL;
	m_EquipmentBitmask = NIL;
	m_GeneralBitmask = NIL;
	m_CursorBitmask = NIL;
	
	memset(m_ItemClassSizes, NIL, sizeof(m_ItemClassSizes));

	m_AllowsClickCastFromBag = false;
	m_AllowsEmptyBagInBag = false;
	m_RequiresLimboConcatenation = false;
}

_Inventory::Scope::Scope(ClientVersion clientVersion)
{
	Factory::ConfigureScope(*this, clientVersion);
}

size_t _Inventory::Scope::MapSize(size_t index)
{
	if (index >= INDEX_BEGIN && index < EmuConstants::INVENTORY_MAP_COUNT)
		return m_MapSizes[index];

	return NIL;
}

size_t _Inventory::Scope::ItemClassSize(size_t index)
{
	if (index >= INDEX_BEGIN && index < ITEM_CLASS_TYPE_COUNT)
		return m_ItemClassSizes[index];

	return NIL;
}

void _Inventory::Scope::DumpValues()
{
	for (size_t index = INDEX_BEGIN; index < EmuConstants::INVENTORY_MAP_COUNT; ++index) {
		Log.Out(Logs::General, Logs::Inventory, "Map%s(%u) size = %u", EmuConstants::InventoryMapName(index), index, m_MapSizes[index]);
	}
	
	Log.Out(Logs::General, Logs::Inventory, "PossessionsBitmask = 0x%08X", m_PossessionsBitmask);
	Log.Out(Logs::General, Logs::Inventory, "EquipmentBitmask = 0x%08X", m_EquipmentBitmask);
	Log.Out(Logs::General, Logs::Inventory, "GeneralBitmask = 0x%08X", m_GeneralBitmask);
	Log.Out(Logs::General, Logs::Inventory, "CursorBitmask = 0x%08X", m_CursorBitmask);

	Log.Out(Logs::General, Logs::Inventory, "ItemClassCommon(%u) size = %u", ItemClassCommon, m_ItemClassSizes[ItemClassCommon]);
	Log.Out(Logs::General, Logs::Inventory, "ItemClassContainer(%u) size = %u", ItemClassContainer, m_ItemClassSizes[ItemClassContainer]);
	Log.Out(Logs::General, Logs::Inventory, "ItemClassBook(%u) size = %u", ItemClassBook, m_ItemClassSizes[ItemClassBook]);

	Log.Out(Logs::General, Logs::Inventory, "AllowsClickCastFromBag = %s", (m_AllowsClickCastFromBag ? "true" : "false"));
	Log.Out(Logs::General, Logs::Inventory, "AllowsEmptyBagInBag = %s", (m_AllowsEmptyBagInBag ? "true" : "false"));
	Log.Out(Logs::General, Logs::Inventory, "RequiresLimboConcatenation = %s", (m_RequiresLimboConcatenation ? "true" : "false"));
}


//
// class _Inventory::Slot
//
void _Inventory::Slot::Invalidate(Slot_Struct &dst)
{
	dst.map = INDEX_INVALID;
	dst.unknown2 = NIL;
	dst.main = INDEX_INVALID;
	dst.sub = INDEX_INVALID;
	dst.aug = INDEX_INVALID;
	dst.unknown1 = NIL;
}

void _Inventory::Slot::Invalidate(SSlot_Struct &dst)
{
	dst.main = INDEX_INVALID;
	dst.sub = INDEX_INVALID;
	dst.aug = INDEX_INVALID;
	dst.unknown1 = NIL;
}

bool _Inventory::Slot::IsInvalid(const Slot_Struct &src)
{
	if (src.map != INDEX_INVALID) { return false; }
	if (src.unknown2 != NIL) { return false; }
	if (src.main != INDEX_INVALID) { return false; }
	if (src.sub != INDEX_INVALID) { return false; }
	if (src.aug != INDEX_INVALID) { return false; }
	if (src.unknown1 != NIL) { return false; }

	return true;
}

bool _Inventory::Slot::IsInvalid(const SSlot_Struct &src)
{
	if (src.main != INDEX_INVALID) { return false; }
	if (src.sub != INDEX_INVALID) { return false; }
	if (src.aug != INDEX_INVALID) { return false; }
	if (src.unknown1 != NIL) { return false; }

	return true;
}

bool _Inventory::Slot::IsDelete(const Slot_Struct &src)
{
	if (src.map != INDEX_INVALID) { return false; }
	if (src.main != INDEX_INVALID) { return false; }
	if (src.sub != INDEX_INVALID) { return false; }
	if (src.aug != INDEX_INVALID) { return false; }

	return true;
}

bool _Inventory::Slot::IsDelete(const SSlot_Struct &src)
{
	if (src.main != INDEX_INVALID) { return false; }
	if (src.sub != INDEX_INVALID) { return false; }
	if (src.aug != INDEX_INVALID) { return false; }

	return true;
}

bool _Inventory::Slot::IsMain(const Slot_Struct &src)
{
	if (src.map == INDEX_INVALID) { return false; }
	if (src.main == INDEX_INVALID) { return false; }
	if (src.sub != INDEX_INVALID) { return false; }
	if (src.aug != INDEX_INVALID) { return false; }

	return true;
}

bool _Inventory::Slot::IsMain(const SSlot_Struct &src)
{
	if (src.main == INDEX_INVALID) { return false; }
	if (src.sub != INDEX_INVALID) { return false; }
	if (src.aug != INDEX_INVALID) { return false; }

	return true;
}

bool _Inventory::Slot::IsSub(const Slot_Struct &src)
{
	if (src.map == INDEX_INVALID) { return false; }
	if (src.main == INDEX_INVALID) { return false; }
	if (src.sub == INDEX_INVALID) { return false; }
	if (src.aug != INDEX_INVALID) { return false; }

	return true;
}

bool _Inventory::Slot::IsSub(const SSlot_Struct &src)
{
	if (src.main == INDEX_INVALID) { return false; }
	if (src.sub == INDEX_INVALID) { return false; }
	if (src.aug != INDEX_INVALID) { return false; }

	return true;
}

bool _Inventory::Slot::IsMainAug(const Slot_Struct &src)
{
	if (src.map == INDEX_INVALID) { return false; }
	if (src.main == INDEX_INVALID) { return false; }
	if (src.sub != INDEX_INVALID) { return false; }
	if (src.aug == INDEX_INVALID) { return false; }

	return true;
}

bool _Inventory::Slot::IsMainAug(const SSlot_Struct &src)
{
	if (src.main == INDEX_INVALID) { return false; }
	if (src.sub != INDEX_INVALID) { return false; }
	if (src.aug == INDEX_INVALID) { return false; }

	return true;
}

bool _Inventory::Slot::IsSubAug(const Slot_Struct &src)
{
	if (src.map == INDEX_INVALID) { return false; }
	if (src.main == INDEX_INVALID) { return false; }
	if (src.sub == INDEX_INVALID) { return false; }
	if (src.aug == INDEX_INVALID) { return false; }

	return true;
}

bool _Inventory::Slot::IsSubAug(const SSlot_Struct &src)
{
	if (src.main == INDEX_INVALID) { return false; }
	if (src.sub == INDEX_INVALID) { return false; }
	if (src.aug == INDEX_INVALID) { return false; }

	return true;
}

bool _Inventory::Slot::IsEqual(const Slot_Struct &arg1, const Slot_Struct &arg2)
{
	if (arg1.map != arg2.map) { return false; }
	//if (arg1.unknown2 != arg2.unknown2) { return false; }
	if (arg1.main != arg2.main) { return false; }
	if (arg1.sub != arg2.sub) { return false; }
	if (arg1.aug != arg2.aug) { return false; }
	//if (arg1.unknown1 != arg2.unknown1) { return false; }

	return true;
}

bool _Inventory::Slot::IsEqual(const Slot_Struct &arg1, const SSlot_Struct &arg2)
{
	if (arg1.main != arg2.main) { return false; }
	if (arg1.sub != arg2.sub) { return false; }
	if (arg1.aug != arg2.aug) { return false; }
	//if (arg1.unknown1 != arg2.unknown1) { return false; }

	return true;
}

bool _Inventory::Slot::IsEqual(const SSlot_Struct &arg1, const Slot_Struct &arg2)
{
	return IsEqual(arg2, arg1);
}

bool _Inventory::Slot::IsEqual(const SSlot_Struct &arg1, const SSlot_Struct &arg2)
{
	if (arg1.main != arg2.main) { return false; }
	if (arg1.sub != arg2.sub) { return false; }
	if (arg1.aug != arg2.aug) { return false; }
	//if (arg1.unknown1 != arg2.unknown1) { return false; }

	return true;
}

void _Inventory::Slot::GetOwningSlot(Slot_Struct &dst, const Slot_Struct &src)
{
	if (IsSub(src)) {
		CopySlot(dst, src);
		dst.sub = INDEX_INVALID;
	}
	else if (IsMainAug(src) || IsSubAug(src)) {
		CopySlot(dst, src);
		dst.aug = INDEX_INVALID;
	}
	else {
		Invalidate(dst);
	}
}

void _Inventory::Slot::GetOwningSlot(SSlot_Struct &dst, const SSlot_Struct &src)
{
	if (IsSub(src)) {
		CopySlot(dst, src);
		dst.sub = INDEX_INVALID;
	}
	else if (IsMainAug(src) || IsSubAug(src)) {
		CopySlot(dst, src);
		dst.aug = INDEX_INVALID;
	}
	else {
		Invalidate(dst);
	}
}

void _Inventory::Slot::GetTopSlot(Slot_Struct &dst, const Slot_Struct &src)
{
	if (IsMainAug(src) || IsSub(src) || IsSubAug(src)) {
		CopySlot(dst, src);
		dst.sub = INDEX_INVALID;
		dst.aug = INDEX_INVALID;
	}
	else {
		Invalidate(dst);
	}
}

void _Inventory::Slot::GetTopSlot(SSlot_Struct &dst, const SSlot_Struct &src)
{
	if (IsMainAug(src) || IsSub(src) || IsSubAug(src)) {
		CopySlot(dst, src);
		dst.sub = INDEX_INVALID;
		dst.aug = INDEX_INVALID;
	}
	else {
		Invalidate(dst);
	}
}

void _Inventory::Slot::CopySlot(Slot_Struct &dst, const Slot_Struct &src)
{
	dst.map = src.map;
	dst.unknown2 = src.unknown2;
	dst.main = src.main;
	dst.sub = src.sub;
	dst.aug = src.aug;
	dst.unknown1 = src.unknown1;
}

void _Inventory::Slot::CopySlot(SSlot_Struct &dst, const SSlot_Struct &src)
{
	dst.main = src.main;
	dst.sub = src.sub;
	dst.aug = src.aug;
	dst.unknown1 = src.unknown1;
}


//
// class _Inventory::Inventory
//


//
// class _Inventory::Factory
//
_Inventory::Instance* _Inventory::Factory::GenerateInstance(ClientVersion clientVersion)
{
	Instance *new_instance = new Instance();
	ReconfigureInstance(*new_instance, clientVersion);

	return new_instance;
}

void _Inventory::Factory::ReconfigureInstance(Instance &instance, ClientVersion clientVersion)
{
	ConfigureScope(instance, clientVersion);
}

void _Inventory::Factory::ConfigureScope(Scope &scope, ClientVersion clientVersion)
{
	for (size_t index = INDEX_BEGIN; index < EmuConstants::INVENTORY_MAP_COUNT; ++index) {
		scope.m_MapSizes[index] = EQLimits::InventoryMapSize(index, clientVersion);
	}
	
	scope.m_PossessionsBitmask = EQLimits::PossessionsBitmask(clientVersion);
	scope.m_EquipmentBitmask = EQLimits::EquipmentBitmask(clientVersion);
	scope.m_GeneralBitmask = EQLimits::GeneralBitmask(clientVersion);
	scope.m_CursorBitmask = EQLimits::CursorBitmask(clientVersion);

	for (size_t index = INDEX_BEGIN; index < ITEM_CLASS_TYPE_COUNT; ++index) {
		scope.m_ItemClassSizes[index] = EQLimits::ItemClassSize(index, clientVersion);
	}

	scope.m_AllowsClickCastFromBag = EQLimits::AllowsClickCastFromBag(clientVersion);
	scope.m_AllowsEmptyBagInBag = EQLimits::AllowsEmptyBagInBag(clientVersion);
	scope.m_RequiresLimboConcatenation = EQLimits::RequiresLimboConcatenation(clientVersion);
}


//
// class _Inventory::Query
//
_Inventory::Query::Query()
{
	ResetCriteria();
}

_Inventory::Query::~Query()
{
	m_Instance = nullptr;
	m_Container = nullptr;
	m_ExternalList = nullptr;

	m_Pointer = nullptr;

	m_ResultList.clear();
	m_ContainerResultList.clear();
	container_working_list.clear();
}

void _Inventory::Query::ResetCriteria()
{
	m_Instance = nullptr;
	m_Container = nullptr;
	m_ContainerSize = NIL;

	memset(m_Locations, 0, sizeof(m_Locations));

	m_Equipment = false;
	m_General = false;
	m_Cursor = false;
	m_IgnoreMain = false;
	m_IgnoreSub = false;
	m_IgnoreMainAug = false;
	m_IgnoreSubAug = false;

	m_Type = QueryType::None;
	m_Quantity = NIL;
	m_QuantityFound = NIL;

	m_Pointer = nullptr;
	m_SerialNumber = NIL;
	m_ItemID = NIL;
	m_LoreGroup = NIL;
	m_AugmentType = NIL;

	m_ItemClass = NIL;
	m_ItemUse = NIL;
	m_BagType = NIL;

	m_ResultList.clear();
	m_ExternalList = nullptr;
	m_Found = false;

	m_ContainerResultList.clear();
	m_ContainerFound = false;

	location_set = false;
	Slot::Invalidate(slot_found);
	container_working_list.clear();
}

void _Inventory::Query::FlagMap(InventoryMaps index)
{
	if (index < INDEX_BEGIN || index >= EmuConstants::INVENTORY_MAP_COUNT)
		return;
	
	m_Locations[index] = true;
	if (index == MapPossessions) {
		m_Equipment = true;
		m_General = true;
		m_Cursor = true;
	}
	location_set = true;
}

void _Inventory::Query::FlagEquipment()
{
	m_Equipment = true;
	m_Locations[MapPossessions] = true;
	location_set = true;
}

void _Inventory::Query::FlagGeneral()
{
	m_General = true;
	m_Locations[MapPossessions] = true;
	location_set = true;
}

void _Inventory::Query::FlagCursor()
{
	m_Cursor = true;
	m_Locations[MapPossessions] = true;
	location_set = true;
}

void _Inventory::Query::FlagDefault()
{
	FlagMap(MapPossessions);
	m_Locations[MapBank] = true;
	m_Locations[MapSharedBank] = true;
	m_Locations[MapTrade] = true;
	m_Locations[MapWorld] = true;
}

void _Inventory::Query::Execute()
{
	m_QuantityFound = NIL;
	m_Found = false;
	m_ResultList.clear();

	if (m_Instance == nullptr) { return; }
	if (!location_set) { return; }
	if (m_IgnoreMain && m_IgnoreSub && m_IgnoreMainAug && m_IgnoreSubAug) { return; }
	if (!_validate_criteria()) { return; }

	_execute();
	_restore_criteria();

	if (m_Quantity != NIL && m_Quantity > m_QuantityFound)
		m_ResultList.clear();

	if (m_ExternalList != nullptr)
		*m_ExternalList = m_ResultList;

	m_Found = !m_ResultList.empty();
}

void _Inventory::Query::ExecuteContainer()
{
	m_QuantityFound = NIL;
	m_ContainerFound = false;
	container_working_list.clear();

	if (m_Container == nullptr) { return; }
	if (m_ContainerSize == NIL) { return; }
	if (!_validate_criteria()) { return; }

	_execute_container();
	_restore_criteria();

	if (m_QuantityFound > NIL && m_QuantityFound >= m_Quantity) {
		m_ContainerResultList.merge(container_working_list);
		m_ContainerResultList.sort();
		m_ContainerFound = true;
	}
}

void _Inventory::Query::_execute()
{
	size_t sub_size = m_Instance->ItemClassSize(ItemClassContainer);
	size_t aug_size = m_Instance->ItemClassSize(ItemClassCommon);

	uint64 possessions_bitmask = NIL;
	if (m_Equipment) { possessions_bitmask |= m_Instance->EquipmentBitmask(); }
	if (m_General) { possessions_bitmask |= m_Instance->GeneralBitmask(); }
	if (m_Cursor) { possessions_bitmask |= m_Instance->CursorBitmask(); }
	if (possessions_bitmask == NIL) { m_Locations[MapPossessions] = false; }

	for (size_t map_index = INDEX_BEGIN; map_index < EmuConstants::INVENTORY_MAP_COUNT; ++map_index) { // Iterate Map
		if (m_Quantity != NIL && m_QuantityFound >= m_Quantity) { break; }
		if (!m_Locations[map_index]) { continue; }

		size_t map_size = m_Instance->MapSize(map_index);
		if (map_size == NIL)
			continue;

		auto map_container = m_Instance->GetMapContainer(map_index);
		if (map_container == nullptr)
			continue;

		for (size_t main_index = INDEX_BEGIN; main_index < map_size; ++main_index) { // Iterate Main
			if (m_Quantity != NIL && m_QuantityFound >= m_Quantity) { break; }
			if (map_index == MapPossessions && !(possessions_bitmask & (static_cast<uint64>(1) << main_index))) { continue; }

			auto main_instance = map_container->GetInstance(main_index);
			
			if (!m_IgnoreMain && _check_criteria(main_instance)) {
				Slot::Invalidate(slot_found);
				slot_found.map = static_cast<int16>(map_index);
				slot_found.main = static_cast<int16>(main_index);
				m_ResultList.push_back(slot_found);
			}

			auto main_container = main_instance->GetContainer();
			if (main_container == nullptr)
				continue;

			if (!m_IgnoreMainAug && main_instance->IsClassType(ItemClassCommon)) {
				for (size_t aug_index = INDEX_BEGIN; aug_index < aug_size; ++aug_index) { // Iterate MainAug
					if (m_Quantity != NIL && m_QuantityFound >= m_Quantity)
						break;

					auto aug_instance = main_container->GetInstance(aug_index);
					if (_check_criteria(aug_instance)) {
						Slot::Invalidate(slot_found);
						slot_found.map = static_cast<int16>(map_index);
						slot_found.main = static_cast<int16>(main_index);
						slot_found.aug = static_cast<int16>(aug_index);
						m_ResultList.push_back(slot_found);
					}
				}
			}

			if (m_IgnoreSub && m_IgnoreSubAug) { continue; }
			if (!main_instance->IsClassType(ItemClassContainer)) { continue; }

			size_t bag_slots = main_instance->GetData()->BagSlots;
			for (size_t sub_index = INDEX_BEGIN; sub_index < sub_size && sub_index < bag_slots; ++sub_index) { // Iterate Sub
				if (m_Quantity != NIL && m_QuantityFound >= m_Quantity)
					break;

				auto sub_instance = main_container->GetInstance(sub_index);
				if (!m_IgnoreSub && _check_criteria(sub_instance)) {
					Slot::Invalidate(slot_found);
					slot_found.map = static_cast<int16>(map_index);
					slot_found.main = static_cast<int16>(main_index);
					slot_found.sub = static_cast<int16>(sub_index);
					m_ResultList.push_back(slot_found);
				}

				if (!m_IgnoreSubAug && sub_instance->IsClassType(ItemClassCommon)) { // Iterate SubAug
					auto sub_container = sub_instance->GetContainer();
					if (sub_container == nullptr)
						continue;

					for (size_t aug_index = INDEX_BEGIN; aug_index < aug_size; ++aug_index) {
						if (m_Quantity != NIL && m_QuantityFound >= m_Quantity)
							break;

						auto aug_instance = sub_container->GetInstance(aug_index);
						if (_check_criteria(aug_instance)) {
							Slot::Invalidate(slot_found);
							slot_found.map = static_cast<int16>(map_index);
							slot_found.main = static_cast<int16>(main_index);
							slot_found.sub = static_cast<int16>(sub_index);
							slot_found.aug = static_cast<int16>(aug_index);
							m_ResultList.push_back(slot_found);
						}
					}
				}
			}
		}
	}
}

void _Inventory::Query::_execute_container()
{
	for (size_t index = INDEX_BEGIN; index < m_ContainerSize && index < m_Container->Size(); ++index) {
		if (m_Quantity != NIL && m_QuantityFound >= m_Quantity)
			break;

		auto target = m_Container->GetInstance(index);
		if (_check_criteria(target))
			container_working_list.push_back(index);
	}
}

bool _Inventory::Query::_validate_criteria()
{
	switch (m_Type) {
	case QueryType::None:
		break;
// Non-criteria specific
	case QueryType::Empty:
		return true;
	case QueryType::Extant:
		return true;
// Query criteria-specific, non-offset adjusted
	case QueryType::Pointer:
		if (m_Pointer != nullptr) {
			m_Quantity = 1;
			return true;
		}
		break;
	case QueryType::SerialNumber:
		if (m_SerialNumber != NIL) {
			m_Quantity = 1;
			return true;
		}
		break;
	case QueryType::ItemID:
		if (m_ItemID != NIL) { return true; }
		break;
	
	case QueryType::LoreGroup:
		if (m_LoreGroup != NIL) { return true; }
		break;
	case QueryType::AugmentType:
		if (m_AugmentType != NIL) { return true; }
		break;
// Query criteria-specific, offset-adjusted
	case QueryType::ItemClass:
		if (m_ItemClass != NIL) {
			m_ItemClass -= 1;
			return true;
		}
		break;
	case QueryType::ItemUse:
		if (m_ItemUse != NIL) {
			m_ItemUse -= 1;
			return true;
		}
		break;
	case QueryType::BagType:
		if (m_BagType != NIL) {
			m_BagType -= 1;
			return true;
		}
		break;
// Item data criteria-specific
	case QueryType::Lore:
	case QueryType::Temporary:
	case QueryType::NotTemporary:
	case QueryType::Tradeable:
	case QueryType::NotTradeable:
	case QueryType::Petable:
	case QueryType::NotPetable:
	case QueryType::Transferable:
	case QueryType::NotTransferable:
	case QueryType::Storable:
	case QueryType::NotStorable:
		return true;
	default:
		break;
	}

	return false;
}

void _Inventory::Query::_restore_criteria()
{
	// Only needed where an offset was changed in _validate_criteria()
	// (Criteria failures do not change criteria)
	switch (m_Type) {
	case QueryType::ItemClass:
		m_ItemClass += 1;
		break;
	case QueryType::ItemUse:
		m_ItemUse += 1;
		break;
	case QueryType::BagType:
		m_BagType += 1;
		break;
	default:
		break;
	}
}

bool _Inventory::Query::_check_criteria(Item::Instance* targetItemInstance)
{
	if (m_Type == QueryType::None)
		return false;

	bool criteria_met = false;
	if (targetItemInstance == nullptr) {
		if (m_Type == QueryType::Empty) {
			criteria_met = true;
			m_QuantityFound += 1;
		}
		return criteria_met;
	}
	
	switch (m_Type) {
// Non-criteria specific
	case QueryType::Extant:
		criteria_met = true;
		break;
// Query criteria-specific, non-offset adjusted
	case QueryType::Pointer:
		if (targetItemInstance == m_Pointer) { criteria_met = true; }
		break;
	case QueryType::SerialNumber:
		if (targetItemInstance->GetSerialNumber() == m_SerialNumber) { criteria_met = true; }
		break;
	case QueryType::ItemID:
		if (targetItemInstance->GetID() == m_ItemID) { criteria_met = true; }
		break;
	case QueryType::LoreGroup:
		if (targetItemInstance->GetData()->LoreGroup == m_LoreGroup) { criteria_met = true; }
		break;
	case QueryType::AugmentType:
		if (targetItemInstance->IsAugmentType(m_AugmentType)) { criteria_met = true; }
		break;
// Query criteria-specific, offset-adjusted
	case QueryType::ItemClass:
		if (targetItemInstance->IsClassType(m_ItemClass)) { criteria_met = true; }
		break;
	case QueryType::ItemUse:
		if (targetItemInstance->IsUseType(m_ItemUse)) { criteria_met = true; }
		break;
	case QueryType::BagType:
		if (targetItemInstance->IsBagType(m_BagType)) { criteria_met = true; }
		break;
// Item data criteria-specific
	case QueryType::Lore:
		if (targetItemInstance->GetData()->LoreFlag == true) { criteria_met = true; }
		break;
	case QueryType::Temporary:
		if (targetItemInstance->IsTemporary()) { criteria_met = true; }
		break;
	case QueryType::NotTemporary:
		if (!targetItemInstance->IsTemporary()) { criteria_met = true; }
		break;
	case QueryType::Tradeable:
		if (targetItemInstance->IsTradeable()) { criteria_met = true; }
		break;
	case QueryType::NotTradeable:
		if (!targetItemInstance->IsTradeable()) { criteria_met = true; }
		break;
	case QueryType::Petable:
		if (targetItemInstance->IsPetable()) { criteria_met = true; }
		break;
	case QueryType::NotPetable:
		if (!targetItemInstance->IsPetable()) { criteria_met = true; }
		break;
	case QueryType::Transferable:
		if (targetItemInstance->IsTransferable()) { criteria_met = true; }
		break;
	case QueryType::NotTransferable:
		if (!targetItemInstance->IsTransferable()) { criteria_met = true; }
		break;
	case QueryType::Storable:
		if (targetItemInstance->IsStorable()) { criteria_met = true; }
		break;
	case QueryType::NotStorable:
		if (!targetItemInstance->IsStorable()) { criteria_met = true; }
		break;
	default:
		break;
	}

	if (criteria_met)
		m_QuantityFound += (targetItemInstance->IsStackable() ? targetItemInstance->GetCharges() : 1);

	return criteria_met;
}
