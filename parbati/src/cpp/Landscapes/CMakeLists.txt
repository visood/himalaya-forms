cmake_minimum_required(VERSION 3.12)
project(HimalayanLandscapes VERSION 0.1.0)

# Define important directories
set(ASSETS_DIR  ${CMAKE_SOURCE_DIR}/assets)
set(SHADERS_DIR ${CMAKE_SOURCE_DIR}/shaders)
set(EXTERN_DIR  ${CMAKE_SOURCE_DIR}/extern)

# Use C++20 for modern features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add your existing compile definitions
add_compile_definitions(
    GLM_FORCE_PURE=1
    GLM_FORCE_CXX20=1
    GLM_FORCE_CTOR_INIT=1
    GLM_FORCE_EXPLICIT_CTOR=1
    GLM_ENABLE_EXPERIMENTAL=1
    GLM_FORCE_INLINE=1
    GLM_FORCE_SILENT_WARNINGS=1
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(spdlog REQUIRED)

# Homebrew handling for yaml-cpp
if(APPLE)
    # Determine Homebrew prefix (different on Intel vs Apple Silicon)
    if(EXISTS "/opt/homebrew/opt/yaml-cpp")
        # Apple Silicon Mac
        set(HOMEBREW_PREFIX "/opt/homebrew")
    else()
        # Intel Mac
        set(HOMEBREW_PREFIX "/usr/local")
    endif()

    # Explicitly set yaml-cpp paths
    set(YAML_CPP_INCLUDE_DIR "${HOMEBREW_PREFIX}/include")
    set(YAML_CPP_LIBRARY "${HOMEBREW_PREFIX}/lib/libyaml-cpp.dylib")

    message(STATUS "Using Homebrew yaml-cpp at: ${HOMEBREW_PREFIX}")
    message(STATUS "yaml-cpp include: ${YAML_CPP_INCLUDE_DIR}")
    message(STATUS "yaml-cpp library: ${YAML_CPP_LIBRARY}")
else()
    # Non-macOS systems
    find_package(yaml-cpp REQUIRED)
endif()

set(GLM_CPP_INCLUDE_DIR ${EXTERN_DIR})

# GLAD loader
set(GLAD_SOURCES ${EXTERN_DIR}/glad/glad.c)

# ImGui includes and sources
set(IMGUI_DIR ${EXTERN_DIR}/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${EXTERN_DIR}
    ${YAML_CPP_INCLUDE_DIR}
    ${EXTERN_DIR}/imgui
)

# Generate a header with path definitions
configure_file(
    ${CMAKE_SOURCE_DIR}/include/path_config.hpp.in
    ${CMAKE_BINARY_DIR}/include/path_config.hpp
)
include_directories(${CMAKE_BINARY_DIR}/include)

# Define source files for the core framework
set(CORE_SOURCES
    source/core/application.cpp
    source/core/window.cpp
    source/core/scene_config.cpp
)

# Define source files for landscape components
set(LANDSCAPE_SOURCES
    source/landscape/terrain.cpp
)

# Define source files for landscape components
set(RENDERER_SOURCES
    source/renderers/terrain_renderer.cpp
)

# Define source files for common utilities
set(UTILITY_SOURCES
    source/utilities/logger.cpp
)

# Define source files for common utilities
set(APP_SOURCES
    source/apps/main.cpp
)

# Define source files for common utilities
# Combine all sources
set(ALL_SOURCES
    ${CORE_SOURCES}
    ${UTILITY_SOURCES}
    ${APP_SOURCES}
    ${GLAD_SOURCES}
    ${IMGUI_SOURCES}
)

# Create executable
add_executable(HimalayanLandscapes ${ALL_SOURCES})

# Link libraries - use the explicit path for yaml-cpp on macOS
if(APPLE)
    target_link_libraries(HimalayanLandscapes
        PRIVATE
        OpenGL::GL
        glfw
        ${YAML_CPP_LIBRARY}
        spdlog::spdlog
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(HimalayanLandscapes
        PRIVATE
        OpenGL::GL
        glfw
        yaml-cpp
    )
endif()

# Copy assets and shaders to build directory
add_custom_command(
    TARGET HimalayanLandscapes POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
)

add_custom_command(
    TARGET HimalayanLandscapes POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    ${CMAKE_BINARY_DIR}/shaders
)

add_custom_command(
    TARGET HimalayanLandscapes POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/terrain_data
    ${CMAKE_BINARY_DIR}/terrain_data
)
# Copy default configuration
add_custom_command(
    TARGET HimalayanLandscapes POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/config/default_scene.yaml
    ${CMAKE_BINARY_DIR}/config/default_scene.yaml
)


# Install targets
install(
    TARGETS HimalayanLandscapes
    RUNTIME DESTINATION bin
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/assets
    DESTINATION share/HimalayanLandscapes
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/shaders
    DESTINATION share/HimalayanLandscapes
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/config
    DESTINATION share/HimalayanLandscapes
)

option(BUILD_DOCS "Build documentation" OFF)
if(BUILD_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        # Configure Doxygen file
        configure_file(
            ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in
            ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
        # Add custom target for documentation
        add_custom_target(
            docs
            ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
        )
    endif()
endif()


# Add option for building tests
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    # Enable testing
    enable_testing()
    # Add tests subdirectory
    add_subdirectory(tests)
endif()
