#pragma once

#include "utilities/logger.hpp"
#include "core/scene_config.hpp"        // Our scene configuration
#include "core/window.hpp"

#include <string>                  // For std::string
#include <functional>              // For std::function
#include <memory>                  // For smart pointers
#include <chrono>                  // For time measurement
#include <vector>                  // For collections
#include <random>                  // For random numbers
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
   
   std::chrono::time_point<std::chrono::high_resolution_clock> _last_frame_time;

   std::shared_ptr<std::mt19937> _random_generator;

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
