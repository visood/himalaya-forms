#pragma once

#include "scene_config.hpp"        // Our scene configuration
#include "window.hpp"
#include "input_handler.hpp"
#include "scene.hpp"
#include "terrain_renderer.hpp"
#include "ui_manager.hpp"

#include <string>                  // For std::string
#include <functional>              // For std::function
#include <memory>                  // For smart pointers
#include <chrono>                  // For time measurement
#include <vector>                  // For collections
#include <algorithm>               // For standard algorithms
#include <iostream>                // For error reporting
#include <stdexcept>               // For exception handling
#include <atomic>                  // For thread-safe state variables
#include <thread>                  // For threading support
#include <mutex>                   // For synchronization
#include <utility>                 // For std::pair, std::move
#include <filesystem>              // For file path handling

class Application {
private:
    std::shared_ptr<SceneConfig> _config;
    std::unique_ptr<Window> _window;
    std::unique_ptr<InputHandler> _input_handler;
    std::unique_ptr<Scene> _scene;
    std::unique_ptr<TerrainRenderer> _renderer;
    std::unique_ptr<UIManager> _ui_manager;

    std::chrono::time_point<std::chrono::high_resolution_clock> _last_frame_time;

public:
    Application(std::shared_ptr<SceneConfig> config);
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void initialize();

    int run();

    void update(float delta_time);

    void render();
};
