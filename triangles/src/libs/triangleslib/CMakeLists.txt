cmake_minimum_required(VERSION 3.10)

project(TrianglesLib)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE Triangles_sources_main_cpp triangles/*.cpp)
file(GLOB_RECURSE Triangles_sources_main_h triangles/*.h)

list(APPEND Triangles_sources ${Triangles_sources_main_cpp})
list(APPEND Triangles_sources ${Triangles_sources_main_h})

include_directories(.)

add_definitions(-DAPI_EXPORTS)

if(MSVC)
  foreach(f ${Triangles_sources})
    file(RELATIVE_PATH SRCGR ${CMAKE_HOME_DIRECTORY} ${f})
    set(SRCGR "${SRCGR}")

    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
  endforeach()
endif()

link_directories(${Triangles_LINKER_LIBS})

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

add_library(TrianglesLib SHARED ${Triangles_sources})
target_compile_options(TrianglesLib PRIVATE ${TRIANGLES_CXX_FLAGS} ${TRIANGLES_LINK_FLAGS})

if(NOT WIN32)
  target_link_libraries(TrianglesLib stdc++fs)
endif()

target_include_directories(TrianglesLib ${Triangles_INCLUDE_DIRS} PUBLIC)

if(WIN32)
  install(
    TARGETS TrianglesLib
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
else()
  install(TARGETS TrianglesLib DESTINATION ${CMAKE_INSTALL_PREFIX})
endif()