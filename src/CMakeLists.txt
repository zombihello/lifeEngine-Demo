cmake_minimum_required( VERSION 2.6 )
project( episodic )

#
#   --- Настройки сборки ---
#

option( LIFEENGINE_DEBUG "Enable debug mode" OFF )
set( LIFEENGINE_SDK_PATH lifeEngine-SDK CACHE PATH "Path to lifeEngine SDK" )

set( BUILD_DIR ${PROJECT_SOURCE_DIR}/../game )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LIFEENGINE_SDK_PATH}/cmake" )

if( LIFEENGINE_DEBUG )
	message( STATUS "Debug mode enabled" )
	add_definitions( -DLIFEENGINE_DEBUG )
endif()

#
#   --- Задаем переменные ---
#

file( GLOB SOURCE_FILES "*.h" "*.cpp" )
set( MODULE_NAME episodic )

#
#   --- Настройки проекта ---
#

add_library( ${MODULE_NAME} SHARED ${SOURCE_FILES} )
include_directories( ${CMAKE_BINARY_DIR}/${MODULE_NAME} )

install( TARGETS ${MODULE_NAME} DESTINATION ${BUILD_DIR} )

add_custom_target( Launch DEPENDS ${MODULE_NAME} ) 
add_custom_command( TARGET Launch 
					COMMAND ${LIFEENGINE_SDK_LAUNCHER} -game ${BUILD_DIR} 
					WORKING_DIRECTORY ${LIFEENGINE_SDK_LAUNCHER_DIR}
					COMMENT "Game start..." )
#
#   --- Ищим и подключаем зависимости ---
#

#---------------
#   lifeEngine SDK

find_package( LifeEngineSDK REQUIRED )
if ( NOT LIFEENGINE_SDK_FOUND )
    return()
else()
    include_directories( ${LIFEENGINE_SDK_INCLUDE} )
endif()