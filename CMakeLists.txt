cmake_minimum_required(VERSION 3.30)

# Globals
set(PROJECT_NAME "GLH Project")
set(TARGET_NAME "glh")

project(${PROJECT_NAME})

# Options
option(${TARGET_NAME}_BUILD_TESTS "Enable building tests for ${TARGET_NAME}" OFF)
option(${TARGET_NAME}_BUILD_EXAMPLES "Enable building examples for ${TARGET_NAME}" OFF)

# Folder Structure for VS
if (PROJECT_IS_TOP_LEVEL)
    set(FOLDER_TARGET "")
else()
    set(FOLDER_TARGET "${TARGET_NAME}/")
endif()

# ------ DEFAULT OPTIONS FOR SUBPROJECTS ------
# GLFW
option(GLFW_BUILD_DOCS              OFF)
option(GLFW_BUILD_EXAMPLES          OFF)
option(GLFW_BUILD_TESTS             OFF)
option(GLFW_BUILD_WIN32              ON)
option(GLFW_INSTALL                 OFF)
option(GLFW_USE_HYBRID_HPG          OFF)
option(USE_MSVC_RUNTIME_LIBRARY_DLL  ON)

# Environment settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# List all project source in these variables
set(SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/src/glh/font.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/glh/classes/Framebuffer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/glh/classes/OpenGLApplication.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/glh/classes/Program.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/glh/classes/Shader.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/glh/classes/Texture2D.cpp

${CMAKE_CURRENT_SOURCE_DIR}/src/glh/directXInterop/D3DInteropTexture2D.cpp
${CMAKE_CURRENT_SOURCE_DIR}/src/glh/directXInterop/direct3d_utils.cpp
)
set(PRIVATE_HEADERS
${CMAKE_CURRENT_SOURCE_DIR}/src/cpputils/windows/dwm.h
${CMAKE_CURRENT_SOURCE_DIR}/src/cpputils/SharedLibraryLoader.h
)
set(PUBLIC_HEADERS
${CMAKE_CURRENT_SOURCE_DIR}/include/glh/glh.h
${CMAKE_CURRENT_SOURCE_DIR}/include/glh/font.h
${CMAKE_CURRENT_SOURCE_DIR}/include/glh/functionWrappers.h
${CMAKE_CURRENT_SOURCE_DIR}/include/glh/macros.h
${CMAKE_CURRENT_SOURCE_DIR}/include/glh/openglapi.h
${CMAKE_CURRENT_SOURCE_DIR}/include/glh/utils.h

${CMAKE_CURRENT_SOURCE_DIR}/include/glh/classes/Framebuffer.h
${CMAKE_CURRENT_SOURCE_DIR}/include/glh/classes/OpenGLApplication.h
${CMAKE_CURRENT_SOURCE_DIR}/include/glh/classes/Program.h
${CMAKE_CURRENT_SOURCE_DIR}/include/glh/classes/Shader.h
${CMAKE_CURRENT_SOURCE_DIR}/include/glh/classes/Texture2D.h
${CMAKE_CURRENT_SOURCE_DIR}/include/glh/classes/SharedLibraryLoader.h

${CMAKE_CURRENT_SOURCE_DIR}/include/glh/directXInterop/D3DInteropTexture2D.h
${CMAKE_CURRENT_SOURCE_DIR}/include/glh/directXInterop/direct3d_utils.h

${CMAKE_CURRENT_SOURCE_DIR}/include/glh/RFont/DejaVuSans.h
${CMAKE_CURRENT_SOURCE_DIR}/include/glh/RFont/DroidSansJapanese.h
${CMAKE_CURRENT_SOURCE_DIR}/include/glh/RFont/RFont.h
)
# List all GTest files here
# Generally every hpp/cpp combo should have a matching [filename].test.cpp.
# Header-only should also receive test files.
set(TEST_SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/tests/glh/test.cpp
)

# -------------- PROJECT LIBRARY --------------
# Create linkable library from project files
# We break this into a library so that the main exe and test project
# share the same artefacts
add_library(${TARGET_NAME}_lib ${SOURCES} ${PRIVATE_HEADERS} ${PUBLIC_HEADERS})
target_include_directories(
    ${TARGET_NAME}_lib
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include # All headers in /include should be public
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src     # All headers in /src should be private
)
set_property(TARGET ${TARGET_NAME}_lib PROPERTY FOLDER "${FOLDER_TARGET}")

## External project linkage
add_subdirectory("external/glfw")
set_property(TARGET glfw            PROPERTY FOLDER "${FOLDER_TARGET}external/glfw")
set_property(TARGET update_mappings PROPERTY FOLDER "${FOLDER_TARGET}external/glfw")

add_subdirectory("external/imgui")
set_property(TARGET imgui           PROPERTY FOLDER "${FOLDER_TARGET}external/imgui")
target_link_libraries(
    imgui
    PRIVATE glfw
)

add_subdirectory("external/glad")
set_property(TARGET glad            PROPERTY FOLDER "${FOLDER_TARGET}external/glad")

target_link_libraries(
    ${TARGET_NAME}_lib
    PUBLIC glfw
    PUBLIC imgui
    PUBLIC  glad
)

# ------------------ EXAMPLES -----------------
if (${TARGET_NAME}_BUILD_EXAMPLES)
    add_executable(${TARGET_NAME}_example examples/example_1.cpp)
    target_link_libraries(${TARGET_NAME}_example PRIVATE ${TARGET_NAME}_lib)
    set_property(TARGET ${TARGET_NAME}_example PROPERTY FOLDER "${FOLDER_TARGET}")
endif()

# ------------------ TESTING ------------------
If (${TARGET_NAME}_BUILD_TESTS)
    # Add Google Test
    include(FetchContent)

    # Fetch Google Test
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1 # Use the latest stable release or a specific tag
    )
    FetchContent_MakeAvailable(googletest)

    set_property(TARGET gmock      PROPERTY FOLDER "external/googletest")
    set_property(TARGET gmock_main PROPERTY FOLDER "external/googletest")
    set_property(TARGET gtest      PROPERTY FOLDER "external/googletest")
    set_property(TARGET gtest_main PROPERTY FOLDER "external/googletest")

    enable_testing()

    add_executable(${TARGET_NAME}_tests ${TEST_SOURCES})
    target_link_libraries(
        ${TARGET_NAME}_tests
        PRIVATE GTest::gtest_main
        PRIVATE ${TARGET_NAME}_lib
    )
    target_include_directories(
        ${TARGET_NAME}_tests
        # Explicitly access all headers, regardless of visibility from _lib
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    )
    set_property(TARGET ${TARGET_NAME}_tests PROPERTY FOLDER "${FOLDER_TARGET}")

    include(GoogleTest)
    gtest_discover_tests(${TARGET_NAME}_tests)
endif()

# --------------- MSVC Settings ---------------
if (MSVC)
    # Enable Multiprocessor compile 
    target_compile_options(${TARGET_NAME}_lib PRIVATE /MP)

    if (${TARGET_NAME}_BUILD_EXAMPLES)
        # Set Visual Studio startup project as our main target (normally VS will default to BUILD_ALL)
        target_compile_options(${TARGET_NAME}_example PRIVATE /MP)
    endif()

    if (${TARGET_NAME}_BUILD_TESTS)
        target_compile_options(${TARGET_NAME}_tests PRIVATE /MP)
    endif()

    # Provides folder tree in visual studio filters
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Source Files" FILES ${SOURCES})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "Private Header Files" FILES ${PRIVATE_HEADERS})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include PREFIX "Public Header Files" FILES ${PUBLIC_HEADERS})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/tests PREFIX "Tests" FILES ${TEST_SOURCES})
endif()