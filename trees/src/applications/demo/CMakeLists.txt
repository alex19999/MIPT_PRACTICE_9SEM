cmake_minimum_required(VERSION 2.8)

project(TreesDemo)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB TreesDemo_sources_tests ./*.cpp)
file(GLOB TreesDemo_sources_tests_h ./*.h)

list(APPEND TreesDemo_sources ${TreesDemo_sources_tests})
list(APPEND TreesDemo_sources ${TreesDemo_sources_tests_h})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libs/treeslib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty)

if(MSVC)
    foreach(f ${TreesDemo_sources})
        # Get the path of the file relative to ${CMAKE_HOME_DIRECTORY},
        # then alter it (not compulsory)
        file(RELATIVE_PATH SRCGR ${CMAKE_HOME_DIRECTORY} ${f})
        set(SRCGR "${SRCGR}")

        # Extract the folder, ie remove the filename part
        string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

        # Source_group expects \\ (double antislash), not / (slash)
        string(REPLACE / \\ SRCGR ${SRCGR})
        source_group("${SRCGR}" FILES ${f})
    endforeach()
endif()

link_directories(${Trees_LINKER_LIBS})

add_executable(TreesDemo ${TreesDemo_sources})
target_compile_options(TreesDemo PRIVATE ${TREES_CXX_FLAGS})

target_link_libraries(TreesDemo TreesLib)

install(TARGETS TreesDemo DESTINATION ${CMAKE_INSTALL_PREFIX})
