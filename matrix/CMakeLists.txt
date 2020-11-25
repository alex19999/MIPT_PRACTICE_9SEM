cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(Matrix)

option(MATRIX_BUILD_TESTS "Configure Tests target" ON)
option(MATRIX_BUILD_DEMO "Configure Demo target" ON)

# MATRIX project directory
set(MATRIX_ROOT ${CMAKE_CURRENT_LIST_DIR})

if(MATRIX_BUILD_TESTS)
  add_subdirectory(src/applications/tests)
endif()

if(MATRIX_BUILD_DEMO)
  add_subdirectory(src/applications/demo)
endif()