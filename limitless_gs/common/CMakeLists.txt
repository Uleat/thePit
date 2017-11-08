CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(common_sources
	common_types.cpp
	object_item.cpp
	profile_identity.cpp
	profile_inventory.cpp
	profile_item_containers.cpp
	profile_item_data.cpp
	profile_item_upgrades.cpp
	profile_spatial.cpp
	profile_stats.cpp
)

SET(common_headers
	common_definitions.h
	common_macros.h
	common_types.h
	object_item.h
	profile_appearance.h
	profile_classes.h
	profile_identity.h
	profile_inventory.h
	profile_item_containers.h
	profile_item_data.h
	profile_item_upgrades.h
	profile_races.h
	profile_skills.h
	profile_spatial.h
	profile_stats.h
)

SOURCE_GROUP(Objects FILES
	object_item.cpp
	object_item.h
)

SOURCE_GROUP(Profiles FILES
	profile_appearance.h
	profile_classes.h
	profile_identity.cpp
	profile_identity.h
	profile_inventory.cpp
	profile_inventory.h
	profile_item_containers.cpp
	profile_item_containers.h
	profile_item_data.cpp
	profile_item_data.h
	profile_item_upgrades.cpp
	profile_item_upgrades.h
	profile_races.h
	profile_skills.h
	profile_spatial.cpp
	profile_spatial.h
	profile_stats.cpp
	profile_stats.h
)

ADD_LIBRARY(common ${common_sources} ${common_headers})

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
