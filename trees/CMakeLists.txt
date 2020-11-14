cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(Trees)

option(TREES_BUILD_TESTS "Configure Tests target" ON)
option(TREES_BUILD_DEMO "Configure Demo target" ON)

# TREES project directory
set(TREES_ROOT ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(src/libs/treeslib)

if(TREES_BUILD_TESTS)
  add_subdirectory(src/applications/tests)
endif()

if(TREES_BUILD_DEMO)
  add_subdirectory(src/applications/demo)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-O2")