#pragma once

#include <memory>                       // For std::shared_ptr, std::unique_ptr
#include <functional>                   // For std::function
#include <iostream>                     // For std::cout, etc.
#include <string>                       // For std::string
#include <vector>                       // For std::vector
#include <fstream>                      // For file operations
#include <random>                       // For random number generation
#include <unordered_map>                // For parameter management
#include <cstdint>                      // For fixed-width integer types
#include <optional>                     // For optional values
#include <variant>                      // For variant parameter types

#include "glm/glm.hpp"                  // GLM core
#include "glm/gtc/matrix_transform.hpp" // For transformations
#include "glm/gtc/type_ptr.hpp"         // For value_ptr

// Forward declarations
class Camera;
class Terrain;
class Light;

/**
* @class SceneConfig
* @brief Configuration container for landscape visualization scenes
*
* Holds all parameters required to configure different aspects of a scene,
* organized into logical sections for easier management.
*/

struct SceneConfig {
    struct GeneralSettings {
        std::string scene_name = "Default Landscape";
        std::string scene_description = "";
        float global_scale = 1.0f;
        unsigned int random_seed = 12345;
        float time_of_day = 12.0f;
        bool enable_simulation = false;
        float simulation_speed = 1.0f;
    };

    struct WindowSettings {
        int width = 1200;
        int height = 720;
        bool fullscreen = false;
        std::string title = "Himalayan Landscape";
        bool vsync = true;
        int msaa_samples = 4;
        float bg_clear_color[4] = {0.2f, 0.3f, 0.4f, 1.0f};
    };

    struct UISettings {
        bool show_ui = true;
        bool show_fps = true;
        bool show_coords = true;
        bool show_control_help = true;
        float ui_scale = 1.0f;
        bool dark_theme = true;
        bool show_debug_info = false;
    };

    struct TerrainSettings {
        bool enabled = true;
        float base_height = 0.0f;
        float height_scale = 500.0f;
        int resolution = 1024;
        std::string height_map_path = "";
        bool use_procedural_terrain = true;
        float base_color[3] = {0.2f, 0.5f, 0.2f};
        float roughness = 0.7f;
        int lod_levels = 5;
        float lod_distance = 500.0f;
        bool wireframe = false;
    };

    struct CameraSettings {
        glm::vec3 initial_position = glm::vec3(0.0f, 100.0f, 500.0f);
        glm::vec3 initial_target = glm::vec3(0.0f, 0.0f, 0.0f);
        float view_field = 60.0f;
        float near_plane = 0.1f;
        float far_plane = 10000.0f;
        float move_speed = 100.0f;
        float rotate_speed = 0.1f;
        float zoom_speed = 10.0f;
        bool invert_y = false;
        bool terrain_follow = false;
        float terrain_offset = 10.0f;
    };

    struct LightingSettings {
        bool  enable_shadows = true;
        int   shadow_map_resolution = 0.2f;
        float ambient_color[3] = {1.0f, 0.9f, 0.8f};
        float ambient_intensity = 0.2f;
        float sun_direction[3] = {0.5f, -0.8f, 0.2f};
        float sun_color[3] = {1.0f, 0.9f, 0.8f};
        float sun_intensity = 1.0f;
        bool  dynamic_time_of_day = false;
        float fog_density = 0.002f;
        float fog_color[3] = {0.8f, 0.9f, 1.0f};
    };

    GeneralSettings general;
    WindowSettings window;
    UISettings ui;
    TerrainSettings terrain;
    CameraSettings camera;
    LightingSettings lighting;

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
