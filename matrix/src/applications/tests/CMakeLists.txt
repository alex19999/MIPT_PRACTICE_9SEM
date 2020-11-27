cmake_minimum_required(VERSION 3.10)

project(MatrixTests)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
file(RELATIVE_PATH REL_MATRIX_ROOT ${CMAKE_INSTALL_PREFIX} ${CMAKE_CURRENT_SOURCE_DIR}/../../../)

if(REL_MATRIX_ROOT STREQUAL "")
    set(REL_MATRIX_ROOT ".")
endif()

file(GLOB_RECURSE MatrixTests_sources_tests ./*.cpp)
file(GLOB_RECURSE MatrixTests_sources_tests_h ./*.h)

# Google Test Initialization
file(GLOB MatrixTests_gtest ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty/gtest/src/gtest-all.cc)
file(GLOB MatrixTests_gtest_h ${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty/gtest/include/gtest/*.h)

list(APPEND MatrixTests_sources ${MatrixTests_sources_tests})
list(APPEND MatrixTests_sources ${MatrixTests_sources_tests_h})
list(APPEND MatrixTests_sources ${MatrixTests_gtest})
list(APPEND MatrixTests_sources ${MatrixTests_gtest_h})

add_definitions(-DGTEST_HAS_PTHREAD=0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty/gtest)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty/gtest/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../applications/tests)

include(GoogleTest)
enable_testing()

if(MSVC)
  foreach(f ${MatrixTests_sources})
    file(RELATIVE_PATH SRCGR ${CMAKE_HOME_DIRECTORY} ${f})
    set(SRCGR "${SRCGR}")

    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
  endforeach()
endif()

link_directories(${Matrix_LINKER_LIBS})

add_executable(MatrixTests ${MatrixTests_sources})
target_compile_options(MatrixTests PRIVATE ${MATRIX_CXX_FLAGS} ${MATRIX_LINK_FLAGS})

if(NOT WIN32)
  target_link_libraries(MatrixTests stdc++fs)
endif()

install(TARGETS MatrixTests DESTINATION ${CMAKE_INSTALL_PREFIX})