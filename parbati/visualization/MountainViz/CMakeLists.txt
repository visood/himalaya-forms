cmake_minimum_required(VERSION 3.12)

# Add your existing compile definitions
add_compile_definitions(
    GLM_FORCE_PURE=1
    GLM_FORCE_CTOR_INIT=1
    GLM_FORCE_CXX17=1
    GLM_ENABLE_EXPERIMENTAL=1
    GLM_FORCE_INLINE=1
    GLM_FORCE_EXPLICIT_CTOR=1
    GLM_FORCE_SILENT_WARNINGS=1
)

project(MountainViz)

set(CMAKE_CXX_STANDARD 17)

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

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

    # Add include directories
    include_directories(${YAML_CPP_INCLUDE_DIR})

    message(STATUS "Using Homebrew yaml-cpp at: ${HOMEBREW_PREFIX}")
    message(STATUS "yaml-cpp include: ${YAML_CPP_INCLUDE_DIR}")
    message(STATUS "yaml-cpp library: ${YAML_CPP_LIBRARY}")
else()
    # Non-macOS systems
    find_package(yaml-cpp REQUIRED)
    include_directories(${YAML_CPP_INCLUDE_DIR})
endif()

# Include GLM
include_directories(${PROJECT_SOURCE_DIR}/third-party)

# Include GLAD
include_directories(include)
set(GLAD_SOURCES include/glad/glad.c)

# ImGui sources
set(IMGUI_DIR include/imgui)
include_directories(${IMGUI_DIR})
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Define source files
set(SOURCES
    src/main.cpp
    src/renderer/OpenGLRenderer.cpp
    src/terrain/ProceduralTerrain.cpp
    src/Config.cpp
    ${GLAD_SOURCES}
    ${IMGUI_SOURCES}
)

# Create executable
add_executable(MountainViz ${SOURCES})

# Link libraries - use the explicit path for yaml-cpp on macOS
if(APPLE)
    target_link_libraries(MountainViz
        OpenGL::GL
        glfw
        ${YAML_CPP_LIBRARY}
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
else()
    target_link_libraries(MountainViz
        OpenGL::GL
        glfw
        yaml-cpp
    )
endif()
