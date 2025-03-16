cmake_minimum_required(VERSION 3.30)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/imconfig.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui_internal.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/imstb_rectpack.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/imstb_textedit.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/imstb_truetype.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui_impl_glfw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui_impl_opengl3.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui_impl_opengl3_loader.h
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src//imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src//imgui_impl_opengl3.cpp
)

add_library(imgui ${SOURCES} ${HEADERS})
target_include_directories(
    imgui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (MSVC)
    # Enable Multiprocessor compile on target
    target_compile_options(imgui PRIVATE /MP)

    # Provides folder tree in visual studio filters
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "Headers" FILES ${HEADERS})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Sources" FILES ${SOURCES})
endif()