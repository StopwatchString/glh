cmake_minimum_required(VERSION 3.30)

if (WIN32)
    set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/gl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/wgl.h
    )

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glad/gl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glad/wgl.c
    )
elseif(UNIX)
    set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/gl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glx.h
    )

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glad/gl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glad/glx.c
    )
endif()

add_library(glad ${SOURCES} ${HEADERS})
target_include_directories(
    glad
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

if (MSVC)
    # Enable Multiprocessor compile on target
    target_compile_options(glad PRIVATE /MP)

    # Provides folder tree in visual studio filters
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "Headers" FILES ${HEADERS})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Sources" FILES ${SOURCES})
endif()