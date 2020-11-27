cmake_minimum_required(VERSION 3.10)

project(MatrixDemo)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
file(RELATIVE_PATH REL_MATRIX_ROOT ${CMAKE_INSTALL_PREFIX} ${CMAKE_CURRENT_SOURCE_DIR}/../../../)

if(REL_MATRIX_ROOT STREQUAL "")
    set(REL_MATRIX_ROOT ".")
endif()

file(GLOB_RECURSE MatrixDemo_sources_Demo ./*.cpp)
file(GLOB_RECURSE MatrixDemo_sources_Demo_h ./*.h)

list(APPEND MatrixDemo_sources ${MatrixDemo_sources_Demo})
list(APPEND MatrixDemo_sources ${MatrixDemo_sources_Demo_h})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../applications/Demo)

if(MSVC)
  foreach(f ${MatrixDemo_sources})
    file(RELATIVE_PATH SRCGR ${CMAKE_HOME_DIRECTORY} ${f})
    set(SRCGR "${SRCGR}")

    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
  endforeach()
endif()

link_directories(${Matrix_LINKER_LIBS})

add_executable(MatrixDemo ${MatrixDemo_sources})
target_compile_options(MatrixDemo PRIVATE ${MATRIX_CXX_FLAGS} ${MATRIX_LINK_FLAGS})

if(NOT WIN32)
  target_link_libraries(MatrixDemo stdc++fs)
endif()

install(TARGETS MatrixDemo DESTINATION ${CMAKE_INSTALL_PREFIX})