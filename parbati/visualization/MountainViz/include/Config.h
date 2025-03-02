#pragma once

#include <string>
#include "glm/glm.hpp"
#include "yaml-cpp/yaml.h"

class Config {
public:
    // Window settings
    struct {
        int width = 1200;
        int height = 800;
        std::string title = "Himalayan Mountain Landscapes";
    } window;

    // Camera settings
    struct {
        glm::vec3 position = glm::vec3(0.0f, 100.0f, 200.0f);
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        float yaw = -90.0f;
        float pitch = 0.0f;
        float movementSpeed = 50.0f;
        float sensitivity = 0.1f;
    } camera;

    // Terrain settings
    struct {
        float roughness = 0.6f;
        int size = 256;
        float height = 50.0f;
        bool wireframe = false;
    } terrain;

    // Mouse state (not saved to config file)
    struct {
        float lastX = 0;
        float lastY = 0;
        bool firstMouse = true;
    } mouse;

    // Constructor with default path
    Config(const std::string& configPath = "config.yaml");

    // Load config from file
    bool loadFromFile(const std::string& path);

    // Save config to file
    bool saveToFile(const std::string& path);

    // Initialize mouse position based on window size
    void initMousePosition();
};
