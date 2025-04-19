#include <iostream>

// Include GLAD before GLFW as GLAD contains the OpenGL headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "utilities/logger.hpp"

// Error callback for GLFW
void errorCallback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

// Window resize callback
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    // Update the viewport to match the new window dimensions
    glViewport(0, 0, width, height);
}

// Process keyboard input
void processInput(GLFWwindow* window) {
    // Close the window when Escape is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
};

int main() {
    // ---- 1. Initialize GLFW ----
    LOG_DEBUG(CORE_LOG, "Initializing GLFW...");
    
    if (!glfwInit()) {
        LOG_DEBUG(CORE_LOG, "Failed to inbitialize GLFW");
        return -1;
    };

    // Set error callback
    glfwSetErrorCallback(errorCallback);

    // Configure GLFW
    // OpenGL 3.3 core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);;

    // Make window visible (explicitly)
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

    // For macOS compatibility
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // ---- 2. Create GLFW Window ----
    LOG_DEBUG(CORE_LOG, "Creating window...");
    
    int windowWidth = 800; int windowHeight = 600;
    
    GLFWWindow* window =
        glfwCreateWindow(
            windowWidth, windowHeight, "OpenGL Single Color Example",
            nullptr, nullptr);
    
    if (!window) {
        LOG_ERROR(CORE_LOG, "Failed to create GLFW window");
        glfwTerminate();
        return -1;};

    // Make the window's context current
    glfwMakeContextCurrent(window);;

    // Center the window on screen
    const GLFWvidmode* mode =
        glfwGetVideoMode(glfwGetPrimaryMonitor());
    if (mode) {
        int xpos = (mode->width - windowWidth) / 2;
        int ypos = (mode->height - windowHeight) / 2;
        glfwSetWindowPos(window, xpos, ypos);}

    // ---- 3. Initialize GLAD ----
    LOG_DEBUG(CORE_LOG, "Initializing GLAD...")
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR(CORE_LOG, "Failed to initialize GLAD");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    };

    // Set up framebuffer resize callback
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // ---- 4. Configure OpenGL state ----
    std::cout << "Configuring OpenGL state..." << std::endl;

    // Set the initial viewport dimensions
    glViewport(0, 0, windowWidth, windowHeight);;

    // Set a clear color (teal blue color)
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);;

    // ---- 5. Render Loop ----
    LOG_INFO("Entering render loop...");
    while (!glfwWindowShouldClose(window)) {
        // Process input
        processInput(window);
    
        //Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
    
        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    };

    // Clean up
    glfwDestroyWindow(window);
    glfwTerminate();
    
    LOG_INFO("Program terminated normally");;

    return 0;
}
