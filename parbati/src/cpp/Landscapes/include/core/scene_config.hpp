#pragma once

#include <memory>                       // std::shared_ptr/std::unique_ptr
#include <functional>                   // std::function
#include <iostream>                     // std::cout, etc.
#include <string>                       // std::string
#include <vector>                       // std::vector
#include <fstream>                      // file operations
#include <random>                       // random number generation
#include <getopt.h>                     // command-line parsing
#include <unordered_map>                // parameter management
#include <cstdint>                      // fixed-width integer types
#include <optional>                     // optional values
#include <variant>                      // variant parameter types

#include "glm/glm.hpp"                  // GLM core
#include "glm/gtc/matrix_transform.hpp" // transformations
#include "glm/gtc/type_ptr.hpp"         // value_ptr

#include "utilities/logger.hpp"

// Forward declarations
class Camera;
class Terrain;
class Light;


/**
 * @class SceneConfig
 * @brief Configuration container for visual models of landscapes
 *  Holds all parameters required to configure different aspects of a
 *  landscape scene, organized into logical sections.
*/
struct SceneConfig {
    struct RunSettings {
        std::string scene_name = "View Himalaya";
        std::string scene_description = "Behold a Himalayan landscape.";
        float global_scale = 1.0f;
        float time_of_day = 12.0f;
        bool enable_simulation = false; //drop this
        float simulation_speed = 1.0f;  //or move to a simulation section
        unsigned int random_seed = 12345; //to seed the random number generator
    };

    struct WindowSettings {
        std::string title = "View Himalaya";
        int width = 1200; int height = 720;
        bool fullscreen = false; bool vsync = true;
        float bg_clear_color[4] = {0.2f, 0.3f, 0.4f, 1.0f}; //background
        int msaa_samples = 4; //multisample-antialiasing
    };

    RunSettings run;
    WindowSettings window;

    SceneConfig() = default;

    bool load_from_file(const std::string& filename);
    bool save_to_file(const std::string& filename) const;

    void reset_to_defaults();

    bool validate();

    void randomize_aesthetics(unsigned int seed);

    SceneConfig clone() const;

    std::string to_string() const;

    // Parse command line arguments
    void parse_command_line(int argc, char* argv[]);

};
