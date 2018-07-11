cmake_minimum_required (VERSION 3.2)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED on)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")

set(LIB_COMMON_PROJECT_NAME common)

project(${LIB_COMMON_PROJECT_NAME})

aux_source_directory(source LIB_COMMON_SOURCES)

include_directories(include)

add_library(${LIB_COMMON_PROJECT_NAME} SHARED ${LIB_COMMON_SOURCES})

