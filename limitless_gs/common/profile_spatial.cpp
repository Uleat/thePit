#include "common_macros.h"
#include "profile_spatial.h"


formats::SpatialDynamicData::SpatialDynamicData() {
	LastWaypointList = nullptr;
	NextWaypointList = nullptr;
}

formats::SpatialDynamicData::SpatialDynamicData(const SpatialDynamicData& r) {
	*this = r;

	if (r.LastWaypointList)
		LastWaypointList = new spatial::waypoint_list_t(*r.LastWaypointList);
	if (r.NextWaypointList)
		NextWaypointList = new spatial::waypoint_list_t(*r.NextWaypointList);
}

formats::SpatialDynamicData::~SpatialDynamicData() {
	SAFE_DELETE(LastWaypointList);
	SAFE_DELETE(NextWaypointList);
}

spatial::waypoint_list_t& profiles::SpatialDynamicAttributes::GetLastWaypointList() {
	if (spatial_dynamic_data_.LastWaypointList == nullptr)
		spatial_dynamic_data_.LastWaypointList = new spatial::waypoint_list_t;

	return *spatial_dynamic_data_.LastWaypointList;
}

spatial::waypoint_list_t& profiles::SpatialDynamicAttributes::GetNextWaypointList() {
	if (spatial_dynamic_data_.NextWaypointList == nullptr)
		spatial_dynamic_data_.NextWaypointList = new spatial::waypoint_list_t;

	return *spatial_dynamic_data_.NextWaypointList;
}

void profiles::SpatialDynamicAttributes::SetLastWaypointList(const spatial::waypoint_list_t& r) {
	if (spatial_dynamic_data_.LastWaypointList == nullptr)
		spatial_dynamic_data_.LastWaypointList = new spatial::waypoint_list_t;

	*spatial_dynamic_data_.LastWaypointList = r;
}

void profiles::SpatialDynamicAttributes::SetNextWaypointList(const spatial::waypoint_list_t& r) {
	if (spatial_dynamic_data_.NextWaypointList == nullptr)
		spatial_dynamic_data_.NextWaypointList = new spatial::waypoint_list_t;

	*spatial_dynamic_data_.NextWaypointList = r;
}

void profiles::SpatialDynamicAttributes::ForceLastWaypointList(const spatial::waypoint_list_t& r) {
	if (spatial_dynamic_data_.LastWaypointList == nullptr)
		spatial_dynamic_data_.LastWaypointList = new spatial::waypoint_list_t;

	*spatial_dynamic_data_.LastWaypointList = r;
}

void profiles::SpatialDynamicAttributes::ForceNextWaypointList(const spatial::waypoint_list_t& r) {
	if (spatial_dynamic_data_.NextWaypointList == nullptr)
		spatial_dynamic_data_.NextWaypointList = new spatial::waypoint_list_t;

	*spatial_dynamic_data_.NextWaypointList = r;
}
