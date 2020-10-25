cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(Triangles)

option(TRIANGLES_BUILD_TESTS "Configure Tests target" ON)
option(TRIANGLES_BUILD_DEMO "Configure Demo target" ON)

# TRIANGLES project directory
set(TRIANGLES_ROOT ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(src/libs/triangleslib)

if(TRIANGLES_BUILD_TESTS)
  add_subdirectory(src/applications/tests)
endif()

if(TRIANGLES_BUILD_DEMO)
  add_subdirectory(src/applications/demo)
endif()