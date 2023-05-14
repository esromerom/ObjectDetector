# On Ubuntu 18.04, get the latest CMake from https://apt.kitware.com/.
cmake_minimum_required(VERSION 3.18)

project(ObjectDetector LANGUAGES C CXX)

# The options need to be the same as Open3D's default
# If Open3D is configured and built with custom options, you'll also need to
# specify the same custom options.
option(STATIC_WINDOWS_RUNTIME "Use static (MT/MTd) Windows runtime" ON)
if(STATIC_WINDOWS_RUNTIME)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

# Add Nlohmann JSON library
# Typically you don't care so much for a third party library's tests to be
# run from your own project's code.
# set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/json_handler/nlohmann_json)

# Find installed Open3D, which exports Open3D::Open3D
find_package(Open3D REQUIRED)

set(CONF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../data/config/)
set(PCD_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../data/captures/)
set(OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../data/output/)

add_executable(${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE "PCD_PATH=\"${PCD_PATH}\"")
target_compile_definitions(${PROJECT_NAME} PRIVATE "CONF_PATH=\"${CONF_PATH}\"")
target_compile_definitions(${PROJECT_NAME} PRIVATE "OUTPUT_PATH=\"${OUTPUT_PATH}\"")

set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/inputCapture.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/json_handler/json_handler.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/objectDetector.cpp)

set(HEADER
    ${HEADER}
    ${CMAKE_CURRENT_SOURCE_DIR}/json_handler/
    ${CMAKE_CURRENT_SOURCE_DIR}/json_handler/nlohmann_json/
    ${CMAKE_CURRENT_SOURCE_DIR}/ )

target_sources(${PROJECT_NAME}  PRIVATE ${SOURCE})
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADER})
target_link_libraries(${PROJECT_NAME} PRIVATE Open3D::Open3D)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

# On Windows if BUILD_SHARED_LIBS is enabled, copy .dll files to the executable directory
if(WIN32)
    get_target_property(open3d_type Open3D::Open3D TYPE)
    if(open3d_type STREQUAL "SHARED_LIBRARY")
        message(STATUS "Copying Open3D.dll to ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>")
        add_custom_command(TARGET Draw POST_BUILD
                           COMMAND ${CMAKE_COMMAND} -E copy
                                   ${CMAKE_INSTALL_PREFIX}/bin/Open3D.dll
                                   ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
    endif()
endif()
