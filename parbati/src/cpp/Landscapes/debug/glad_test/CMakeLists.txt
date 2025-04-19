cmake_minimum_required(VERSION 3.12)
project(GladTest VERSION 0.1.0)

# Define important directories
set(EXTERN_DIR ${CMAKE_SOURCE_DIR}/extern)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directories
include_directories(
    ${EXTERN_DIR}
)

# GLAD source
set(GLAD_SOURCES ${EXTERN_DIR}/glad/glad.c)

# Create a simple test executable
add_executable(glad_test test_glad.cpp ${GLAD_SOURCES})

# Link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(glad_test PRIVATE OpenGL::GL)

# On macOS, add required frameworks
if(APPLE)
    target_link_libraries(glad_test PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()

# Output binary location
set_target_properties(glad_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

message(STATUS "EXTERN_DIR: ${EXTERN_DIR}")
message(STATUS "GLAD_SOURCES: ${GLAD_SOURCES}")
