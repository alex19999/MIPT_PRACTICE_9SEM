cmake_minimum_required(VERSION 2.8)

project(TrianglesDemo)

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB TrianglesDemo_sources_tests ./*.cpp)
file(GLOB TrianglesDemo_sources_tests_h ./*.h)

list(APPEND TrianglesDemo_sources ${TrianglesDemo_sources_tests})
list(APPEND TrianglesDemo_sources ${TrianglesDemo_sources_tests_h})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../libs/triangleslib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty)

if(MSVC)
    foreach(f ${TrianglesDemo_sources})
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

link_directories(${Triangles_LINKER_LIBS})

add_executable(TrianglesDemo ${TrianglesDemo_sources})
target_compile_options(TrianglesDemo PRIVATE ${TRIANGLES_CXX_FLAGS})

target_link_libraries(TrianglesDemo TrianglesLib)

install(TARGETS TrianglesDemo DESTINATION ${CMAKE_INSTALL_PREFIX})
