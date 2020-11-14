cmake_minimum_required(VERSION 3.10)

project(TreesLib)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE Trees_sources_main_cpp trees/*.cpp)
file(GLOB_RECURSE Trees_sources_main_h trees/*.h)

list(APPEND Trees_sources ${Trees_sources_main_cpp})
list(APPEND Trees_sources ${Trees_sources_main_h})

include_directories(.)

add_definitions(-DAPI_EXPORTS)

if(MSVC)
  foreach(f ${Trees_sources})
    file(RELATIVE_PATH SRCGR ${CMAKE_HOME_DIRECTORY} ${f})
    set(SRCGR "${SRCGR}")

    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
  endforeach()
endif()

link_directories(${Trees_LINKER_LIBS})

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

add_library(TreesLib SHARED ${Trees_sources})
target_compile_options(TreesLib PRIVATE ${TREES_CXX_FLAGS} ${TREES_LINK_FLAGS})

if(NOT WIN32)
  target_link_libraries(TreesLib stdc++fs)
endif()

target_include_directories(TreesLib ${Trees_INCLUDE_DIRS} PUBLIC)

if(WIN32)
  install(
    TARGETS TreesLib
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
else()
  install(TARGETS TreesLib DESTINATION ${CMAKE_INSTALL_PREFIX})
endif()
