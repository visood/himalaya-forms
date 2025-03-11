// scene.hpp
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include "scene_config.hpp"
#include "terrain.hpp"
#include "sky_system.hpp"
#include "clouds.hpp"
#include "vegetation.hpp"
#include "water.hpp"

/**
 * @class Scene
 * @brief Central manager for all landscape elements
 *
 * The Scene class coordinates all landscape subsystems and manages their interactions.
 * It serves as the main entry point for creating and modifying the virtual landscape.
 */
class Scene {
public:
    /**
     * @brief Constructor
     * @param config Reference to the scene configuration
     */
    Scene(const SceneConfig& config);

    /**
     * @brief Destructor
     */
    ~Scene();

    /**
     * @brief Initializes the scene and all subsystems
     * @return True if initialization was successful
     */
    bool initialize();

    /**
     * @brief Updates the scene and all subsystems
     * @param delta_time Time elapsed since last update in seconds
     */
    void update(float delta_time);

    /**
     * @brief Loads a scene from a configuration file
     * @param config_path Path to the configuration file
     * @return True if loading was successful
     */
    bool load_from_config(const std::string& config_path);

    /**
     * @brief Saves the current scene to a configuration file
     * @param config_path Path to save the configuration file
     * @return True if saving was successful
     */
    bool save_to_config(const std::string& config_path) const;

    /**
     * @brief Sets up an empty terrain with default parameters
     * @return True if setup was successful
     */
    bool setup_empty_base_terrain();

    /**
     * @brief Loads terrain from a heightmap file
     * @param heightmap_path Path to the heightmap image
     * @param height_scale Vertical scale factor for the terrain
     * @return True if loading was successful
     */
    bool load_terrain_from_heightmap(
        const std::string& heightmap_path, float height_scale = 500.0f);

    /**
     * @brief Generates procedural terrain
     * @param seed Random seed for generation
     * @param roughness Roughness parameter (0-1)
     * @param resolution Resolution of the heightmap
     * @return True if generation was successful
     */
    bool generate_procedural_terrain(
        unsigned int seed, float roughness = 0.5f, int resolution = 1024);

    /**
     * @brief Adds a water plane to the scene
     * @param height Height of the water plane
     * @param size Size of the water plane
     * @return ID of the created water body
     */
    int add_water_plane(
        float height, float size);

    /**
     * @brief Adds a river to the scene
     * @param path_points Points defining the river path
     * @param width Width of the river
     * @return ID of the created river
     */
    int add_river(
        const std::vector<glm::vec3>& path_points, float width);

    /**
     * @brief Populates the scene with vegetation
     * @param tree_density Density of trees (0-1)
     * @param grass_density Density of grass (0-1)
     * @return True if population was successful
     */
    bool populate_vegetation(
        float tree_density = 0.1f, float grass_density = 0.3f);

    /**
     * @brief Sets the time of day
     * @param time_of_day Time in hours (0-24)
     */
    void set_time_of_day(float time_of_day);

    /**
     * @brief Gets a reference to the terrain
     * @return Reference to the terrain system
     */
    const Terrain& get_terrain() const {
        return *_terrain;
    }

    /**
     * @brief Gets a reference to the sky system
     * @return Reference to the sky system
     */
    const SkySystem& get_sky_system() const {
        return *_sky_system;
    }

    /**
     * @brief Gets a reference to the cloud system
     * @return Reference to the cloud system
     */
    const CloudSystem& get_cloud_system() const {
        return *_cloud_system;
    }

    /**
     * @brief Gets a reference to the vegetation system
     * @return Reference to the vegetation system
     */
    const VegetationSystem& get_vegetation_system() const {
        return *_vegetation_system;
    }

    /**
     * @brief Gets a reference to the water system
     * @return Reference to the water system
     */
    const WaterSystem& get_water_system() const {
        return *_water_system;
    }

    /**
     * @brief Gets the sun direction
     * @return Normalized vector pointing toward the sun
     */
    glm::vec3 get_sun_direction() const;

    /**
     * @brief Gets the current time of day
     * @return Time in hours (0-24)
     */

    float get_time_of_day() const {
        return _time_of_day;
    }

    /*
     * @brief Gets the current wind direction and speed
     * @return Pair of wind direction vector and speed
     */
    std::pair<glm::vec2, float> get_wind() const {
        return {_wind_direction, _wind_speed};
    }

    /*
     * @brief Sets the wind parameters
     * @param direction Direction vector
     * @param speed Wind speed
     */
    void set_wind(const glm::vec2& direction, float speed);

    /*
     * @brief Gets whether the scene simulation is enabled
     * @return True if simulation is running
     */
    bool is_simulation_enabled() const {
        return _simulation_enabled;
    }

    /*
     * @brief Sets whether the scene simulation is enabled
     * @param enabled Whether to enable simulation
     */
    void set_simulation_enabled(bool enabled) {
        _simulation_enabled = enabled;
    }

    /*
     * @brief Sets the simulation speed multiplier
     * @param speed_multiplier Speed multiplier (1.0 = normal speed)
     */
    void set_simulation_speed(float speed_multiplier) {
        _simulation_speed = speed_multiplier;
    }

    /*
     * @brief Gets the simulation speed multiplier
     * @return Current simulation speed multiplier
     */
    float get_simulation_speed() const {
        return _simulation_speed;
    }

private:
    const SceneConfig& _config;

    // Scene subsystems
    std::unique_ptr<Terrain> _terrain;
    std::unique_ptr<SkySystem> _sky_system;
    std::unique_ptr<CloudSystem> _cloud_system;
    std::unique_ptr<VegetationSystem> _vegetation_system;
    std::unique_ptr<WaterSystem> _water_system;

    // Scene state
    float _time_of_day;
    bool _simulation_enabled;
    float _simulation_speed;
    glm::vec2 _wind_direction;
    float _wind_speed;
    float _accumulated_time;

    // Helper methods
    void _update_time_of_day(float delta_time);
    void _update_sky_parameters();
    void _update_wind(float delta_time);
};
