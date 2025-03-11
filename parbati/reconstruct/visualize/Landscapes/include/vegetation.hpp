// vegetation.hpp
#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "scene_config.hpp"
#include "terrain.hpp"

/*
 * @class VegetationSystem
 * @brief Manages and renders vegetation elements like trees, grass, and plants
 */
class VegetationSystem {
public:
    /*
     * @brief Vegetation type enumeration
     */
    enum class VegetationType {
        TREE,
        GRASS,
        BUSH,
        FLOWER,
        CUSTOM
    };

    /*
     * @brief Structure to hold vegetation instance data
     */
    struct VegetationInstance {
        glm::vec3 position;
        glm::vec3 scale;
        float rotation;
        int type;
        int variation;
    };

    /*
     * @brief Constructor
     * @param config Reference to the scene configuration
     * @param terrain Reference to the terrain system
     */
    VegetationSystem(const SceneConfig& config, const Terrain& terrain);

    /*
     * @brief Destructor
     */
    ~VegetationSystem();

    /*
     * @brief Initializes the vegetation system resources
     * @return True if initialization was successful
     */
    bool initialize();

    /*
     * @brief Renders all vegetation
     * @param view_matrix The view matrix
     * @param projection_matrix The projection matrix
     * @param camera_position Position of the camera
     */
    void render(const glm::mat4& view_matrix, const glm::mat4& projection_matrix,
               const glm::vec3& camera_position);

    /*
     * @brief Updates the vegetation system
     * @param delta_time Time elapsed since last update in seconds
     * @param wind_direction Direction of the wind
     * @param wind_strength Strength of the wind
     */
    void update(float delta_time, const glm::vec2& wind_direction, float wind_strength);

    /*
     * @brief Adds a vegetation model to the system
     * @param type Vegetation type
     * @param model_path Path to the 3D model file
     * @param texture_path Path to the texture file
     * @return ID of the added vegetation model
     */
    int add_vegetation_model(VegetationType type, const std::string& model_path,
                           const std::string& texture_path);

    /*
     * @brief Populates the terrain with vegetation based on density maps
     * @param density_map_path Path to the density map image
     */
    void populate_from_density_map(const std::string& density_map_path);

    /*
     * @brief Procedurally populates the terrain with vegetation
     * @param seed Random seed for vegetation distribution
     * @param tree_density Density of trees (0-1)
     * @param grass_density Density of grass (0-1)
     * @param variation_amount Amount of variation in scale and rotation (0-1)
     */
    void populate_procedural(unsigned int seed, float tree_density, float grass_density,
                           float variation_amount);

    /*
     * @brief Adds a single vegetation instance
     * @param type Vegetation type
     * @param position World position
     * @param scale Scale factor
     * @param rotation Rotation in radians
     * @param variation Variation index
     * @return ID of the added instance
     */
    int add_instance(VegetationType type, const glm::vec3& position,
                    const glm::vec3& scale, float rotation, int variation = 0);

    /*
     * @brief Removes a vegetation instance
     * @param instance_id ID of the instance to remove
     * @return True if successfully removed
     */
    bool remove_instance(int instance_id);

    /*
     * @brief Removes all vegetation of a specific type
     * @param type Type of vegetation to remove
     */
    void clear_vegetation_type(VegetationType type);

    /*
     * @brief Removes all vegetation
     */
    void clear_all();

    /*
     * @brief Sets the level of detail parameters
     * @param near_distance Distance for highest detail
     * @param far_distance Distance for lowest detail
     * @param lod_levels Number of detail levels
     */
    void set_lod_parameters(float near_distance, float far_distance, int lod_levels);

    /*
     * @brief Enables or disables wind animation
     * @param enabled Whether wind animation is enabled
     */
    void set_wind_animation(bool enabled) { _wind_animation_enabled = enabled; }

    /*
     * @brief Gets the count of vegetation instances
     * @return Total number of vegetation instances
     */
    size_t get_instance_count() const { return _instances.size(); }

    /*
     * @brief Gets the count of vegetation instances by type
     * @param type Vegetation type
     * @return Number of instances of the specified type
     */
    size_t get_instance_count_by_type(VegetationType type) const;

private:
    struct ModelInfo {
        GLuint vao;
        GLuint vbo;
        GLuint ibo;
        GLuint texture;
        int index_count;
        VegetationType type;
        int variation;
    };

    const SceneConfig& _config;
    const Terrain& _terrain;

    // OpenGL resources
    GLuint _vegetation_shader;
    GLuint _billboards_vao;
    GLuint _billboards_vbo;
    GLuint _instance_buffer;

    // Wind animation
    bool _wind_animation_enabled;
    float _wind_time;

    // Level of detail
    float _near_distance;
    float _far_distance;
    int _lod_levels;

    // Vegetation data
    std::vector<ModelInfo> _models;
    std::vector<VegetationInstance> _instances;
    std::unordered_map<int, size_t> _instance_id_map;
    int _next_instance_id;

    // Helper methods
    bool _compile_shaders();
    void _load_models();
    void _setup_billboards();
    void _update_instance_buffer();
    void _render_trees(const glm::mat4& view_projection, const glm::vec3& camera_position);
    void _render_grass(const glm::mat4& view_projection, const glm::vec3& camera_position);
    int _determine_lod_level(float distance) const;
    bool _is_in_view(const glm::vec3& position, float radius, const glm::mat4& view_projection) const;
    bool _load_texture(const std::string& path, GLuint& texture_id);
};
