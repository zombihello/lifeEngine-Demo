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

if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
    if ( MINGW )
        set( CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -static )
        set( CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -static )
    endif()
endif()

#
#   --- Задаем переменные ---
#

file( GLOB_RECURSE SOURCE_FILES "*.h" "*.cpp" )
set( MODULE_NAME episodic )

#
#   --- Настройки проекта ---
#

add_library( ${MODULE_NAME} SHARED ${SOURCE_FILES} )
set_target_properties( ${MODULE_NAME} PROPERTIES PREFIX "" )
include_directories( ${CMAKE_BINARY_DIR}/${MODULE_NAME} )
include_directories( ./)

file( GLOB SCRIPTAPI_GAME "scripts_api/entites/*.h" )

install( TARGETS ${MODULE_NAME} DESTINATION ${BUILD_DIR} )
install( FILES ${SCRIPTAPI_GAME} DESTINATION ${BUILD_DIR}/scripts/entites )
install( DIRECTORY "shaders/shaders" DESTINATION ${BUILD_DIR} )

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
    include_directories( ${LIFEENGINE_SDK_SCRIPTAPI_INCLUDE} )
endif()
