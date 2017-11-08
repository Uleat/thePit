#EQEmu CMake
#Variables used:
#EQEMU_DISABLE_CRT_SECURE_WARNINGS
#EQEMU_FAST_FLOATINGPOINT
#EQEMU_ENABLE_CRASH_LOGGING
#EQEMU_DISABLE_SAFESEH
#EQEMU_BUILD_MSVC_MP
#EQEMU_DEBUG_LEVEL
#EQEMU_LOG_LEVEL_STATUS
#EQEMU_LOG_LEVEL_NORMAL
#EQEMU_LOG_LEVEL_ERROR
#EQEMU_LOG_LEVEL_DEBUG
#EQEMU_LOG_LEVEL_QUEST
#EQEMU_LOG_LEVEL_COMMANDS
#EQEMU_LOG_LEVEL_CRASH
#EQEMU_STREAM_SEND_RATE
#EQEMU_STREAM_DECAY_RATE
#EQEMU_STREAM_RETRANSMIT_TIMEOUT_MUL
#EQEMU_STREAM_RETRANSMIT_TIMEOUT_MAX
#EQEMU_STREAM_AVERAGE_DELTA_MAX
#EQEMU_STREAM_RETRANSMIT_ACKED_PACKETS
#EQEMU_DEPOP_INVALIDATES_CACHE
#EQEMU_ENABLE_BOTS
#EQEMU_DISABLE_LOGSYS
#EQEMU_COMMANDS_LOGGING
#EQEMU_BUILD_SERVER
#EQEMU_BUILD_LOGIN
#EQEMU_BUILD_TESTS
#EQEMU_BUILD_PERL
#EQEMU_BUILD_LUA
#EQEMU_SANITIZE_LUA_LIBS
#EQEMU_BUILD_CLIENT_FILES
#EQEMU_USE_MAP_MMFS
#EQEMU_MAP_DIR

#We set a fairly new version (as of 2013) because I found finding perl was a bit... buggy on older ones
#Can change this if you really want but you should upgrade!
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#FindMySQL is located here so lets make it so CMake can find it
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/" ${CMAKE_MODULE_PATH})

#Our project name is LimitlessGS
PROJECT(LimitlessGS)

#Default build type is set to RelWithDebInfo for generators that honor that like makefiles
IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

#Add our various windows definitions
ADD_DEFINITIONS(-D_WINDOWS)
ADD_DEFINITIONS(-DWIN32)

SET(ZLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/zlib_x86")
SET(MYSQL_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/mysql_x86")
SET(LUA_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/luaj_x86")
SET(SODIUM_INCLUDE_HINTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libsodium/include")
SET(OPENSSL_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/openssl_x86")
IF(MSVC_VERSION GREATER 1800)
	SET(SODIUM_LIBRARY_HINTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libsodium/Win32/Release/v140/dynamic")
ELSEIF(MSVC_VERSION EQUAL 1800)
	SET(SODIUM_LIBRARY_HINTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libsodium/Win32/Release/v120/dynamic")
ELSE()
	SET(SODIUM_LIBRARY_HINTS "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libsodium/Win32/Release/v110/dynamic")
ENDIF()

#disable CRT warnings on windows cause they're annoying as shit and we use C functions everywhere
OPTION(LGS_DISABLE_CRT_SECURE_WARNINGS "Disable Secure CRT Warnings" ON)
IF(LGS_DISABLE_CRT_SECURE_WARNINGS)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(LGS_DISABLE_CRT_SECURE_WARNINGS)

#fast FP if you'd like it
OPTION(LGS_FAST_FLOATINGPOINT "Use MSVC /fp:fast option" ON)
IF(LGS_FAST_FLOATINGPOINT)
	ADD_DEFINITIONS(/fp:fast)
ENDIF(LGS_FAST_FLOATINGPOINT)

OPTION(LGS_BUILD_MSVC_MP "Enable build with multiple processes." ON)
IF(LGS_BUILD_MSVC_MP)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
ENDIF(LGS_BUILD_MSVC_MP)

#We want to compile /MT not /MD so we change that
FOREACH(flag_var CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_RELWITHDEBINFO)
	IF(${flag_var} MATCHES "/MD")
		STRING(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
	ENDIF(${flag_var} MATCHES "/MD")
ENDFOREACH(flag_var)

ADD_DEFINITIONS(-DNOMINMAX)

#debug level, 5 is default. Most people wont ever change this but it's there if you want to
SET(LGS_DEBUG_LEVEL 5 CACHE STRING "LGS debug level:
	0 - Quiet mode Errors to file Status and Normal ignored
	1 - Status and Normal to console, Errors to logfile
	2 - Status, Normal, and Error to console and logfile
	3 - Light debug release errors and status
	4 - Moderate debug release errors and status
	5 - Maximum debug release errors and status
	10 - More errors than you ever wanted to see"
)

SET(LGS_LOG_LEVEL_STATUS 2 CACHE STRING "LGS logging level for [Status]:
	0 - Disabled
	1 - Ouput to File Enabled
	2 - Output to stdout Enabled
	3 - Output to File and stdout Enabled
	8 - Output to stderr Enabled
	9 - Output to File and stderr Enabled
	11 - Output to File, stdout and stderr Enabled"
)

SET(LGS_LOG_LEVEL_NORMAL 3 CACHE STRING "LGS logging level for [Normal]:
	0 - Disabled
	1 - Ouput to File Enabled
	2 - Output to stdout Enabled
	3 - Output to File and stdout Enabled
	8 - Output to stderr Enabled
	9 - Output to File and stderr Enabled
	11 - Output to File, stdout and stderr Enabled"
)

SET(LGS_LOG_LEVEL_ERROR 2 CACHE STRING "LGS logging level for [Error]:
	0 - Disabled
	1 - Ouput to File Enabled
	2 - Output to stdout Enabled
	3 - Output to File and stdout Enabled
	8 - Output to stderr Enabled
	9 - Output to File and stderr Enabled
	11 - Output to File, stdout and stderr Enabled"
)

SET(LGS_LOG_LEVEL_DEBUG 3 CACHE STRING "LGS logging level for [Debug]:
	0 - Disabled
	1 - Ouput to File Enabled
	2 - Output to stdout Enabled
	3 - Output to File and stdout Enabled
	8 - Output to stderr Enabled
	9 - Output to File and stderr Enabled
	11 - Output to File, stdout and stderr Enabled"
)

SET(LGS_LOG_LEVEL_QUEST 2 CACHE STRING "LGS logging level for [Quest]:
	0 - Disabled
	1 - Ouput to File Enabled
	2 - Output to stdout Enabled
	3 - Output to File and stdout Enabled
	8 - Output to stderr Enabled
	9 - Output to File and stderr Enabled
	11 - Output to File, stdout and stderr Enabled"
)

SET(LGS_LOG_LEVEL_COMMANDS 1 CACHE STRING "LGS logging level for [Commands]:
	0 - Disabled
	1 - Ouput to File Enabled
	2 - Output to stdout Enabled
	3 - Output to File and stdout Enabled
	8 - Output to stderr Enabled
	9 - Output to File and stderr Enabled
	11 - Output to File, stdout and stderr Enabled"
)

SET(LGS_LOG_LEVEL_CRASH 3 CACHE STRING "LGS logging level for [Crash]:
	0 - Disabled
	1 - Ouput to File Enabled
	2 - Output to stdout Enabled
	3 - Output to File and stdout Enabled
	8 - Output to stderr Enabled
	9 - Output to File and stderr Enabled
	11 - Output to File, stdout and stderr Enabled"
)

MARK_AS_ADVANCED(LGS_LOG_LEVEL_STATUS LGS_LOG_LEVEL_NORMAL LGS_LOG_LEVEL_ERROR LGS_LOG_LEVEL_DEBUG LGS_LOG_LEVEL_QUEST LGS_LOG_LEVEL_COMMANDS LGS_LOG_LEVEL_CRASH)

SET(LGS_STREAM_SEND_RATE 1048576 CACHE STRING "Advanced: Base amount of data stream can send before throttle.")
SET(LGS_STREAM_DECAY_RATE 78642 CACHE STRING "Advanced: Base amount of data stream recovers per tic.")
SET(LGS_STREAM_RETRANSMIT_TIMEOUT_MUL 3.0 CACHE STRING "Advanced: Multiplier on retransmit timeout.")
SET(LGS_STREAM_RETRANSMIT_TIMEOUT_MAX 5000 CACHE STRING "Advanced: Max in ms for retransmit timeout timer.")
SET(LGS_STREAM_AVERAGE_DELTA_MAX 2500 CACHE STRING "Advanced: The maximum average delta in ms allowed.")
SET(LGS_STREAM_RETRANSMIT_ACKED_PACKETS TRUE CACHE BOOL "Advanced: Whether or not acked packets can be retransmitted")
MARK_AS_ADVANCED(LGS_STREAM_SEND_RATE LGS_STREAM_DECAY_RATE LGS_STREAM_RETRANSMIT_TIMEOUT_MUL LGS_STREAM_RETRANSMIT_TIMEOUT_MAX LGS_STREAM_AVERAGE_DELTA_MAX LGS_STREAM_RETRANSMIT_ACKED_PACKETS)

ADD_DEFINITIONS(-DLUA_LGS)
ADD_DEFINITIONS(-DLGSDEBUG=${LGS_DEBUG_LEVEL})
ADD_DEFINITIONS(-DINVERSEXY)
ADD_DEFINITIONS(-DFIELD_ITEMS)
ADD_DEFINITIONS(-DMAP_DIR="${LGS_MAP_DIR}")
ADD_DEFINITIONS(-DRATEBASE=${LGS_STREAM_SEND_RATE})
ADD_DEFINITIONS(-DDECAYBASE=${LGS_STREAM_DECAY_RATE})
ADD_DEFINITIONS(-DRETRANSMIT_TIMEOUT_MULT=${LGS_STREAM_RETRANSMIT_TIMEOUT_MUL})
ADD_DEFINITIONS(-DRETRANSMIT_TIMEOUT_MAX=${LGS_STREAM_RETRANSMIT_TIMEOUT_MAX})
ADD_DEFINITIONS(-DAVERAGE_DELTA_MAX=${LGS_STREAM_AVERAGE_DELTA_MAX})
ADD_DEFINITIONS(-DLOG_LEVEL_STATUS=${LGS_LOG_LEVEL_STATUS})
ADD_DEFINITIONS(-DLOG_LEVEL_NORMAL=${LGS_LOG_LEVEL_NORMAL})
ADD_DEFINITIONS(-DLOG_LEVEL_ERROR=${LGS_LOG_LEVEL_ERROR})
ADD_DEFINITIONS(-DLOG_LEVEL_DEBUG=${LGS_LOG_LEVEL_DEBUG})
ADD_DEFINITIONS(-DLOG_LEVEL_QUEST=${LGS_LOG_LEVEL_QUEST})
ADD_DEFINITIONS(-DLOG_LEVEL_COMMANDS=${LGS_LOG_LEVEL_COMMANDS})
ADD_DEFINITIONS(-DLOG_LEVEL_CRASH=${LGS_LOG_LEVEL_CRASH})
ADD_DEFINITIONS(-DGLM_FORCE_RADIANS)

IF(LGS_STREAM_RETRANSMIT_ACKED_PACKETS)
	ADD_DEFINITIONS(-DRETRANSMIT_ACKED_PACKETS=true)
ELSE(LGS_STREAM_RETRANSMIT_ACKED_PACKETS)
	ADD_DEFINITIONS(-DRETRANSMIT_ACKED_PACKETS=false)
ENDIF(LGS_STREAM_RETRANSMIT_ACKED_PACKETS)

FIND_PACKAGE(ZLIB REQUIRED)
FIND_PACKAGE(MySQL REQUIRED)

#SET(SERVER_LIBS common debug ${MySQL_LIBRARY_DEBUG} optimized ${MySQL_LIBRARY_RELEASE} ${ZLIB_LIBRARY} libuv fmt)
SET(SERVER_LIBS common debug ${MySQL_LIBRARY_DEBUG} optimized ${MySQL_LIBRARY_RELEASE} ${ZLIB_LIBRARY})

FIND_PACKAGE(Sodium REQUIRED)
IF(SODIUM_FOUND)
	OPTION(LGS_ENABLE_SECURITY "Use Encryption For TCP Connections" ON)
	IF(LGS_ENABLE_SECURITY)
		INCLUDE_DIRECTORIES(SYSTEM "${SODIUM_INCLUDE_DIRS}")
		ADD_DEFINITIONS(-DENABLE_SECURITY)
		SET(SERVER_LIBS ${SERVER_LIBS} ${SODIUM_LIBRARIES})
	ENDIF()
ENDIF()

IF(WIN32)
	SET(SERVER_LIBS ${SERVER_LIBS} "ws2_32" "psapi" "iphlpapi" "userenv")
ENDIF()

FIND_PACKAGE(LGSLua51 REQUIRED)
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)
SET(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/boost")

FIND_PACKAGE(Boost REQUIRED)
INCLUDE_DIRECTORIES(SYSTEM "${LUA_INCLUDE_DIR}" "${Boost_INCLUDE_DIRS}")
INCLUDE_DIRECTORIES(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/luabind")

OPTION(LGS_SANITIZE_LUA_LIBS "Sanitize Lua Libraries (Remove OS and IO standard libraries from being able to run)." ON)
IF(LGS_SANITIZE_LUA_LIBS)
	ADD_DEFINITIONS(-DSANITIZE_LUA_LIBS)
ENDIF(LGS_SANITIZE_LUA_LIBS)

INCLUDE_DIRECTORIES(SYSTEM "${ZLIB_INCLUDE_DIRS}")
INCLUDE_DIRECTORIES(SYSTEM "${MySQL_INCLUDE_DIR}")
INCLUDE_DIRECTORIES(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/common/glm")
#INCLUDE_DIRECTORIES(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/libraries/cereal")
#INCLUDE_DIRECTORIES(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/libraries/libuv/include" )
#INCLUDE_DIRECTORIES(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/libraries/libuv/src")
#INCLUDE_DIRECTORIES(SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/libraries/format")

#ADD_SUBDIRECTORY(administration_panel)
#ADD_SUBDIRECTORY(client)
#ADD_SUBDIRECTORY(client_updater)
ADD_SUBDIRECTORY(common)
#ADD_SUBDIRECTORY(libraries)
#ADD_SUBDIRECTORY(login_controller)
#ADD_SUBDIRECTORY(server_updater)
#ADD_SUBDIRECTORY(universal_chat_service)
#ADD_SUBDIRECTORY(world_controller)
#ADD_SUBDIRECTORY(world_manager)
ADD_SUBDIRECTORY(world_shard)
#ADD_SUBDIRECTORY(zone_manager)
#ADD_SUBDIRECTORY(zone_shard)
