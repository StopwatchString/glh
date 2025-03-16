cmake_minimum_required(VERSION 3.30)

# Globals
set(PROJECT_NAME "GLH Project")
set(TARGET_NAME "glh")

project(${PROJECT_NAME})

# Environment settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# List all project source in these variables
set(SOURCES
${CMAKE_SOURCE_DIR}/src/glh/font.cpp
)
set(PRIVATE_HEADERS
${CMAKE_SOURCE_DIR}/src/glh/font.h
)
set(PUBLIC_HEADERS
${CMAKE_SOURCE_DIR}/include/glh/glh.h
)
# List all GTest files here
# Generally every hpp/cpp combo should have a matching [filename].test.cpp.
# Header-only should also receive test files.
set(TEST_SOURCES
${CMAKE_SOURCE_DIR}/tests/glh/test.cpp
)

# -------------- PROJECT LIBRARY --------------
# Create linkable library from project files
# We break this into a library so that the main exe and test project
# share the same artefacts
add_library(${TARGET_NAME}_lib ${SOURCES} ${PRIVATE_HEADERS} ${PUBLIC_HEADERS})
target_include_directories(
    ${TARGET_NAME}_lib
    PUBLIC  ${CMAKE_SOURCE_DIR}/include # All headers in /include should be public
    PRIVATE ${CMAKE_SOURCE_DIR}/src     # All headers in /src should be private
)

## External project linkage would go here
add_subdirectory("external/glfw")
set_property(TARGET glfw            PROPERTY FOLDER "external/glfw")
set_property(TARGET update_mappings PROPERTY FOLDER "external/glfw")

add_subdirectory("external/imgui")
set_property(TARGET imgui PROPERTY FOLDER "external/imgui")

add_subdirectory("external/glad")
set_property(TARGET glad PROPERTY FOLDER "external/glad")


# ------------- PROJECT EXECUTABLE -------------
add_executable(${TARGET_NAME}_example examples/example_1.cpp)
target_link_libraries(${TARGET_NAME}_example PRIVATE ${TARGET_NAME}_lib)
target_link_libraries(
    ${TARGET_NAME}_example
    PRIVATE glfw
    PRIVATE imgui
    PRIVATE glad
)

# ------------------ TESTING ------------------
# Add Google Test
add_subdirectory(external/googletest)
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
    PRIVATE ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)

include(GoogleTest)
gtest_discover_tests(${TARGET_NAME}_tests)

# --------------- MSVC Settings ---------------
if (MSVC)
    # Set Visual Studio startup project as our main target (normally VS will default to BUILD_ALL)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME}_example)

    # Enable Multiprocessor compile on targets
    target_compile_options(${TARGET_NAME}_lib PRIVATE /MP)
    target_compile_options(${TARGET_NAME}_example PRIVATE /MP)
    target_compile_options(${TARGET_NAME}_tests PRIVATE /MP)

    # Provides folder tree in visual studio filters
    source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX "Source Files" FILES ${SOURCES})
    source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX "Private Header Files" FILES ${PRIVATE_HEADERS})
    source_group(TREE ${CMAKE_SOURCE_DIR}/include PREFIX "Public Header Files" FILES ${PUBLIC_HEADERS})
endif()