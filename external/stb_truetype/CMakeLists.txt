cmake_minimum_required(VERSION 3.30)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/stb_truetype.h
)

set(SOURCES
)

add_library(stb_truetype INTERFACE ${SOURCES} ${HEADERS})
target_include_directories(
    stb_truetype
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (MSVC)
    # Enable Multiprocessor compile on target
    # target_compile_options(vectorclass PRIVATE /MP)

    # Provides folder tree in visual studio filters
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "Headers" FILES ${HEADERS})
    #source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Sources" FILES ${SOURCES})
endif()