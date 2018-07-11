cmake_minimum_required (VERSION 3.2)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED on)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")

set(LIB_THREAD_API_PROJECT_NAME thread_api)

project(${LIB_THREAD_API_PROJECT_NAME})

aux_source_directory(source LIB_THREAD_API_SOURCES)

include_directories(include)

add_library(${LIB_THREAD_API_PROJECT_NAME} SHARED ${LIB_THREAD_API_SOURCES})
