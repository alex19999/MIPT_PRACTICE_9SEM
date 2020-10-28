cmake_minimum_required(VERSION 3.10)

project(TreesTests)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
file(RELATIVE_PATH REL_TREES_ROOT ${CMAKE_INSTALL_PREFIX} ${CMAKE_CURRENT_SOURCE_DIR}/../../../)

if(REL_TREES_ROOT STREQUAL "")
    set(REL_TREES_ROOT ".")
endif()

file(GLOB_RECURSE TreesTests_sources_tests ./*.cpp)
file(GLOB_RECURSE TreesTests_sources_tests_h ./*.h)

# Google Test Initialization
file(GLOB TreesTests_gtest ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty/gtest/src/gtest-all.cc)
file(GLOB TreesTests_gtest_h
     ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty/gtest/include/gtest/*.h)

list(APPEND TreesTests_sources ${TreesTests_sources_tests})
list(APPEND TreesTests_sources ${TreesTests_sources_tests_h})
list(APPEND TreesTests_sources ${TreesTests_gtest})
list(APPEND TreesTests_sources ${TreesTests_gtest_h})

add_definitions(-DGTEST_HAS_PTHREAD=0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty/gtest)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty/gtest/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libs/treeslib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../applications/tests)

include(GoogleTest)
enable_testing()

if(MSVC)
  foreach(f ${TreesTests_sources})
    file(RELATIVE_PATH SRCGR ${CMAKE_HOME_DIRECTORY} ${f})
    set(SRCGR "${SRCGR}")

    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
  endforeach()
endif()

link_directories(${Trees_LINKER_LIBS})

add_executable(TreesTests ${TreesTests_sources})
target_compile_options(TreesTests PRIVATE ${TREES_CXX_FLAGS} ${TREES_LINK_FLAGS})
target_link_libraries(TreesTests TreesLib)

if(NOT WIN32)
  target_link_libraries(TreesTests stdc++fs)
endif()

install(TARGETS TreesTests DESTINATION ${CMAKE_INSTALL_PREFIX})