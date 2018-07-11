cmake_minimum_required (VERSION 3.2)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED on)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++")

set(TESTING_PROJECT_NAME testing)

aux_source_directory(source/ TESTING_SOURCES)
include_directories(include)
include_directories(../libthread_api/include)
include_directories(../libnetwork_api/include)
include_directories(../libnetwork_api/include/connection)
#using library common
include_directories(../libcommon/include/)

link_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

include(CTest)

if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif()

include(DownloadProject.cmake)
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/google/googletest.git
                 GIT_TAG             master
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

include_directories(../googletest-src/googletest/include/)

# When using CMake 2.8.11 or later, header path dependencies
# are automatically added to the gtest and gmock targets.
# For earlier CMake versions, we have to explicitly add the
# required directories to the header search path ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include")
endif()

# Trivial example using gtest and gmock
add_executable(${TESTING_PROJECT_NAME} ${TESTING_SOURCES})
target_link_libraries(${TESTING_PROJECT_NAME} gtest gmock_main http_api thread_api network_api common)
add_test(NAME example_test COMMAND example)

