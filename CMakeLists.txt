cmake_minimum_required (VERSION 3.2)

set(PROJECT server)

set (CMAKE_CXX_STANDARD_REQUIRED on)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")

SET(FLAG_DEBUG "Debug")

if("${CMAKE_BUILD_TYPE}" STREQUAL "${FLAG_DEBUG}")
    SET( CMAKE_DEBUG_POSTFIX "_d" CACHE STRING "postfix applied to debug build of libraries" )
    SET( CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
    add_definitions(-D_DEBUG)
else()
    SET(CMAKE_RELEASE_POSTFIX "" CACHE STRING "postfix applied to release build of libraries" )
    SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -g" )
endif()

#output executable files directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
#output shared library directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
#output static library directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

project(${PROJECT})

find_package(Threads)

#current project
aux_source_directory(source SOURCES)
include_directories(include)

#subproject libtherad_api
add_subdirectory(libthread_api)
include_directories(libthread_api/include)

#subproject libhttp_api
add_subdirectory(libhttp_api)
include_directories(libhttp_api/include)

#subproject libnetwork_api
add_subdirectory(libnetwork_api)
include_directories(libnetwork_api/include)
include_directories(libnetwork_api/include/connection)
include_directories(libnetwork_api/include/connection/tcp_connection)
include_directories(libnetwork_api/include/system)

#subdirectory libcommon
add_subdirectory(libcommon)
include_directories(libcommon/include)

#subproject testing
add_subdirectory(testing)

add_executable(${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} pthread thread_api common network_api http_api)
