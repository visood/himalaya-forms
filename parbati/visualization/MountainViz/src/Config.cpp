#include "Config.h"
#include <iostream>
#include <fstream>

Config::Config(const std::string& configPath) {
    // Try to load the config file
    if (!loadFromFile(configPath)) {
        std::cout << "Using default configuration" << std::endl;
    }

    // Initialize mouse position based on window size
    initMousePosition();
}

void Config::initMousePosition() {
    mouse.lastX = window.width / 2.0f;
    mouse.lastY = window.height / 2.0f;
    mouse.firstMouse = true;
}

bool Config::loadFromFile(const std::string& path) {
    try {
        // Check if file exists
        std::ifstream file(path);
        if (!file.good()) {
            std::cerr << "Config file not found: " << path << std::endl;
            return false;
        }

        YAML::Node config = YAML::LoadFile(path);

        // Load window settings
        if (config["window"]) {
            window.width = config["window"]["width"].as<int>(window.width);
            window.height = config["window"]["height"].as<int>(window.height);
            window.title = config["window"]["title"].as<std::string>(window.title);
        }

        // Load camera settings
        if (config["camera"]) {
            if (config["camera"]["position"]) {
                auto pos = config["camera"]["position"];
                camera.position.x = pos[0].as<float>();
                camera.position.y = pos[1].as<float>();
                camera.position.z = pos[2].as<float>();
            }

            if (config["camera"]["front"]) {
                auto front = config["camera"]["front"];
                camera.front.x = front[0].as<float>();
                camera.front.y = front[1].as<float>();
                camera.front.z = front[2].as<float>();
            }

            if (config["camera"]["up"]) {
                auto up = config["camera"]["up"];
                camera.up.x = up[0].as<float>();
                camera.up.y = up[1].as<float>();
                camera.up.z = up[2].as<float>();
            }

            camera.yaw
                = config["camera"]["yaw"].as<float>(camera.yaw);
            camera.pitch
                = config["camera"]["pitch"].as<float>(camera.pitch);
            camera.movementSpeed
                = config["camera"]["movement_speed"].as<float>(camera.movementSpeed);
            camera.sensitivity
                = config["camera"]["sensitivity"].as<float>(camera.sensitivity);
        }

        // Load terrain settings
        if (config["terrain"]) {
            terrain.roughness
                = config["terrain"]["roughness"].as<float>(terrain.roughness);
            terrain.size
                = config["terrain"]["size"].as<int>(terrain.size);
            terrain.height
                = config["terrain"]["height"].as<float>(terrain.height);
            terrain.wireframe
                = config["terrain"]["wireframe"].as<bool>(terrain.wireframe);
        }

        std::cout << "Configuration loaded from: " << path << std::endl;
        return true;
    } catch (const YAML::Exception& e) {
        std::cerr << "Error loading configuration: " << e.what() << std::endl;
        return false;
    }
}

bool Config::saveToFile(const std::string& path) {
    try {
        YAML::Node config;

        // Save window settings
        config["window"]["width"] = window.width;
        config["window"]["height"] = window.height;
        config["window"]["title"] = window.title;

        // Save camera settings
        config["camera"]["position"].push_back(camera.position.x);
        config["camera"]["position"].push_back(camera.position.y);
        config["camera"]["position"].push_back(camera.position.z);

        config["camera"]["front"].push_back(camera.front.x);
        config["camera"]["front"].push_back(camera.front.y);
        config["camera"]["front"].push_back(camera.front.z);

        config["camera"]["up"].push_back(camera.up.x);
        config["camera"]["up"].push_back(camera.up.y);
        config["camera"]["up"].push_back(camera.up.z);

        config["camera"]["yaw"] = camera.yaw;
        config["camera"]["pitch"] = camera.pitch;
        config["camera"]["movement_speed"] = camera.movementSpeed;
        config["camera"]["sensitivity"] = camera.sensitivity;

        // Save terrain settings
        config["terrain"]["roughness"] = terrain.roughness;
        config["terrain"]["size"] = terrain.size;
        config["terrain"]["height"] = terrain.height;
        config["terrain"]["wireframe"] = terrain.wireframe;

        // Write to file
        std::ofstream fout(path);
        fout << config;

        std::cout << "Configuration saved to: " << path << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error saving configuration: " << e.what() << std::endl;
        return false;
    }
}
