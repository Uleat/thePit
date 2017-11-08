CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(world_shard_sources
	actor_combatant.cpp
	actor_mobile.cpp
	actor_static.cpp
	actor_world.cpp
	manager_actor.cpp
	manager_bonus.cpp
	world_shard.cpp
)

SET(world_shard_headers
	actor_combatant.h
	actor_mobile.h
	actor_static.h
	actor_world.h
	manager_actor.h
	manager_bonus.h
	world_shard.h
)

SOURCE_GROUP(Actors FILES
	actor_combatant.cpp
	actor_combatant.h
	actor_mobile.cpp
	actor_mobile.h
	actor_static.cpp
	actor_static.h
	actor_world.cpp
	actor_world.h
)

SOURCE_GROUP(Managers FILES
	manager_actor.cpp
	manager_actor.h
	manager_bonus.cpp
	manager_bonus.h
)

ADD_EXECUTABLE(WorldShard ${world_shard_sources} ${world_shard_headers})

INSTALL(TARGETS WorldShard RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

TARGET_LINK_LIBRARIES(WorldShard ${SERVER_LIBS})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
