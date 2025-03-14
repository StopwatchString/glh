cmake_minimum_required(VERSION 3.30)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imconfig.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_internal.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imstb_rectpack.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imstb_textedit.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imstb_truetype.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.h
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3_loader.h
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui ${SOURCES} ${HEADERS})
target_include_directories(
    imgui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
)