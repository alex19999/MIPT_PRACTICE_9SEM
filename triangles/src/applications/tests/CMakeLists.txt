cmake_minimum_required(VERSION 3.10)

project(TrianglesTests)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
file(RELATIVE_PATH REL_TRIANGLES_ROOT ${CMAKE_INSTALL_PREFIX} ${CMAKE_CURRENT_SOURCE_DIR}/../../../)

if(REL_TRIANGLES_ROOT STREQUAL "")
    set(REL_TRIANGLES_ROOT ".")
endif()

file(GLOB_RECURSE TrianglesTests_sources_tests ./*.cpp)
file(GLOB_RECURSE TrianglesTests_sources_tests_h ./*.h)

# Google Test Initialization
file(GLOB TrianglesTests_gtest ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty/gtest/src/gtest-all.cc)
file(GLOB TrianglesTests_gtest_h
     ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty/gtest/include/gtest/*.h)

list(APPEND TrianglesTests_sources ${TrianglesTests_sources_tests})
list(APPEND TrianglesTests_sources ${TrianglesTests_sources_tests_h})
list(APPEND TrianglesTests_sources ${TrianglesTests_gtest})
list(APPEND TrianglesTests_sources ${TrianglesTests_gtest_h})

add_definitions(-DGTEST_HAS_PTHREAD=0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty/gtest)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty/gtest/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libs/triangleslib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../applications/tests)

include(GoogleTest)
enable_testing()

if(MSVC)
  foreach(f ${TrianglesTests_sources})
    file(RELATIVE_PATH SRCGR ${CMAKE_HOME_DIRECTORY} ${f})
    set(SRCGR "${SRCGR}")

    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
  endforeach()
endif()

link_directories(${Triangles_LINKER_LIBS})

add_executable(TrianglesTests ${TrianglesTests_sources})
target_compile_options(TrianglesTests PRIVATE ${TRIANGLES_CXX_FLAGS} ${TRIANGLES_LINK_FLAGS})
target_link_libraries(TrianglesTests TrianglesLib)

if(NOT WIN32)
  target_link_libraries(TrianglesTests stdc++fs)
endif()

install(TARGETS TrianglesTests DESTINATION ${CMAKE_INSTALL_PREFIX})