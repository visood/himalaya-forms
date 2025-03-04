#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cmath>
#include <random>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "renderer/Renderer.h"
#include "terrain/ProceduralTerrain.h"
#include "Config.h"

// Global config object
Config config;

// Timing variables
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Terrain regneration flag
bool regenerate = false;

// Prototypes of callbacks used by GLFW
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

GLFWwindow* setupOpenGLContext(const Config& config) {
    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window using dimensions from config
    GLFWwindow* window = glfwCreateWindow(
        config.window.width, config.window.height,
        config.window.title.c_str(), NULL, NULL);

    if (window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Set up window context
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // Capture the mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Load OpenGL functions with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }

    // Configure OpenGL global state
    glEnable(GL_DEPTH_TEST);

    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    config.window.width = width;
    config.window.height = height;
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (config.mouse.firstMouse) {
        config.mouse.lastX = xpos;
        config.mouse.lastY = ypos;
        config.mouse.firstMouse = false;
    }

    float xoffset = xpos - config.mouse.lastX;
    float yoffset = config.mouse.lastY - ypos;
    config.mouse.lastX = xpos;
    config.mouse.lastY = ypos;

    xoffset *= config.camera.sensitivity;
    yoffset *= config.camera.sensitivity;

    config.camera.yaw += xoffset;
    config.camera.pitch += yoffset;

    // Make sure pitch doesn't go out of bounds
    if (config.camera.pitch > 89.0f)
        config.camera.pitch = 89.0f;
    if (config.camera.pitch < -89.0f)
        config.camera.pitch = -89.0f;

    glm::vec3 front;
    front.x
        = cos(glm::radians(config.camera.yaw))
        * cos(glm::radians(config.camera.pitch));
    front.y
        = sin(glm::radians(config.camera.pitch));
    front.z
        = sin(glm::radians(config.camera.yaw))
        * cos(glm::radians(config.camera.pitch));
    config.camera.front = glm::normalize(front);
}

void start_imgui_frame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void process_input(GLFWwindow* window, Config& config, float);
bool render_imgui(ProceduralTerrain& terrain, Config& config, bool& regenerate);

void runMainLoop(
    GLFWwindow* window, OpenGLRenderer& renderer, ProceduralTerrain& terrain,
    Config& config
) {
    // Timing variables
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    bool regenerate = false;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        process_input(window, config, deltaTime);

        start_imgui_frame();

        // ImGui controls
        bool terrainChanged = render_imgui(terrain, config, regenerate);

        // Render
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Create view and projection matrices
        glm::mat4 projection
            = glm::perspective(glm::radians(45.0f),
                               (float)config.window.width / (float)config.window.height,
                               0.1f, 1000.0f);

        glm::mat4 view
            = glm::lookAt(config.camera.position,
                          config.camera.position + config.camera.front,
                          config.camera.up);

        // Set wireframe mode if toggled
        glPolygonMode(GL_FRONT_AND_BACK, config.terrain.wireframe ? GL_LINE : GL_FILL);

        // Check if terrain needs regeneration
        if (regenerate || terrainChanged) {
            terrain = ProceduralTerrain(config.terrain.size, config.terrain.size);
            terrain.generateDiamondSquare(config.terrain.roughness, config.terrain.height);
            renderer.setTerrain(&terrain);
            regenerate = false;
        }

        // Render terrain
        renderer.render(view, projection);

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void process_input(GLFWwindow* window, Config& config, float deltaTime) {
    float camera_speed = config.camera.movementSpeed * deltaTime;
    glm::vec3 to_view(0.0f);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        to_view = config.camera.front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        to_view = -config.camera.front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        to_view =  -glm::normalize(glm::cross(config.camera.front, config.camera.up));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        to_view = glm::normalize(glm::cross(config.camera.front, config.camera.up));

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    config.camera.position += config.camera.movementSpeed * deltaTime * to_view;

    if (glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS)
        config.saveToFile("config.yaml");
}

bool render_imgui(
    ProceduralTerrain& terrain, Config& config, bool& regenerate
) {
    bool terrainChanged = false;

    ImGui::Begin("Mountain Parameters");
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);

    // Terrain parameters
    terrainChanged |= ImGui::SliderFloat("Roughness", &config.terrain.roughness, 0.1f, 1.0f);
    terrainChanged |= ImGui::SliderFloat("Height", &config.terrain.height, 10.0f, 200.0f);
    terrainChanged |= ImGui::SliderInt("Resolution", &config.terrain.size, 64, 512);
    ImGui::Checkbox("Wireframe Mode", &config.terrain.wireframe);

    // Camera parameters
    if (ImGui::CollapsingHeader("Camera Settings")) {
        ImGui::SliderFloat("Movement Speed", &config.camera.movementSpeed, 10.0f, 200.0f);
        ImGui::SliderFloat("Look Sensitivity", &config.camera.sensitivity, 0.05f, 0.5f);

        // Display current camera position
        ImGui::Text("Position: (%.1f, %.1f, %.1f)",
                    config.camera.position.x,
                    config.camera.position.y,
                    config.camera.position.z);
    }

    // Config save/load
    if (ImGui::CollapsingHeader("Configuration")) {
        static char configPath[256] = "config.yaml";
        ImGui::InputText("Config file", configPath, 256);

        if (ImGui::Button("Save Configuration")) {
            config.saveToFile(configPath);
        }

        ImGui::SameLine();

        if (ImGui::Button("Load Configuration")) {
            if (config.loadFromFile(configPath)) {
                regenerate = true; // Regenerate terrain with new settings
            }
        }
    }

    if (ImGui::Button("Regenerate Terrain")) {
        regenerate = true;
    }

    ImGui::End();

    return terrainChanged;
}

void setup_imgui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

int main() {
    GLFWwindow* window;

    try {
        // Set up OpenGL context
        window = setupOpenGLContext(config);
        setup_imgui(window);

        // Create terrain and renderer
        ProceduralTerrain terrain(config.terrain.size, config.terrain.size);
        terrain.generateDiamondSquare(config.terrain.roughness, config.terrain.height);

        OpenGLRenderer renderer;
        renderer.initialize();
        renderer.setTerrain(&terrain);

        // Run the main application loop
        runMainLoop(window, renderer, terrain, config);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
