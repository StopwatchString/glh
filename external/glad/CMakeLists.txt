cmake_minimum_required(VERSION 3.30)

if (WIN32)
    set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/windows/wgl.h
    )

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/windows/wgl.c
    )

    add_library(glad ${SOURCES} ${HEADERS})
    target_include_directories(
        glad
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/windows
    )
elseif(UNIX)
    set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/gl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/linux/glx.h
    )

    set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/linux/glx.c
    )
    
    add_library(glad ${SOURCES} ${HEADERS})
    target_include_directories(
        glad
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/linux
    )
endif()
