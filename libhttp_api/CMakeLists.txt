cmake_minimum_required (VERSION 3.2)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED on)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")

set(LIB_HTTP_API_PROJECT_NAME http_api)

project(${LIB_HTTP_API_PROJECT_NAME})

aux_source_directory(source LIB_HTTP_API_SOURCES)

include_directories(include)

add_library(${LIB_HTTP_API_PROJECT_NAME} SHARED ${LIB_HTTP_API_SOURCES})
