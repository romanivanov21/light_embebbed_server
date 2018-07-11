cmake_minimum_required (VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")

set(LIB_NETWORK_API_PROJECT_NAME network_api)

project(${LIB_NETWORK_API_PROJECT_NAME})

aux_source_directory(source LIB_NETWORK_API_SOURCES)
aux_source_directory(source/connection/ LIB_NETWORK_API_SOURCES)
aux_source_directory(source/connection/tcp_connection/ LIB_NETWORK_API_SOURCES)

include_directories(include)
include_directories(include/connection/)
include_directories(include/connection/tcp_connection)

#using library common
include_directories(../libcommon/include/)

add_library(${LIB_NETWORK_API_PROJECT_NAME} SHARED ${LIB_NETWORK_API_SOURCES})

target_link_libraries(${LIB_NETWORK_API_PROJECT_NAME} common)
