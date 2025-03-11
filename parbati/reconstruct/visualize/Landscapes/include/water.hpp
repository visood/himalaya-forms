// water.hpp
#pragma once

#include <memory>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "scene_config.hpp"
#include "terrain.hpp"

/**
 * @class WaterSystem
 * @brief Manages and renders water bodies including rivers, lakes, and oceans
 */
class WaterSystem {
public:
    /**
     * @brief Constructor
     * @param config Reference to the scene configuration
     * @param terrain Reference to the terrain system
     */
    WaterSystem(const SceneConfig& config, const Terrain& terrain);

    /**
     * @brief Destructor
     */
    ~WaterSystem();

    /**
     * @brief Initializes the water system resources
     * @return True if initialization was successful
     */
    bool initialize();

    /**
     * @brief Renders all water bodies
     * @param view_matrix The view matrix
     * @param projection_matrix The projection matrix
     * @param camera_position Position of the camera
     */
    void render(const glm::mat4& view_matrix, const glm::mat4& projection_matrix,
               const glm::vec3& camera_position);

    /**
     * @brief Updates the water simulation
     * @param delta_time Time elapsed since last update in seconds
     */
    void update(float delta_time);

    /**
     * @brief Creates a water plane at the specified height
     * @param height Water height in world units
     * @param size Size of the water plane
     * @return ID of the created water body
     */
    int create_water_plane(float height, float size);

    /**
     * @brief Creates a river following a path
     * @param path_points Points defining the river path
     * @param width Width of the river
     * @return ID of the created river
     */
    int create_river(const std::vector<glm::vec3>& path_points, float width);

    /**
     * @brief Creates a lake with a custom shape
     * @param center_position Center of the lake
     * @param shape_points Points defining the lake boundary relative to center
     * @param depth Depth of the lake
     * @return ID of the created lake
     */
    int create_lake(const glm::vec3& center_position,
                   const std::vector<glm::vec2>& shape_points, float depth);

    /**
     * @brief Removes a water body
     * @param water_id ID of the water body to remove
     * @return True if successfully removed
     */
    bool remove_water_body(int water_id);

    /**
     * @brief Clears all water bodies
     */
    void clear_all();

    /**
     * @brief Sets the water color
     * @param color RGB color of the water
     */
    void set_water_color(const glm::vec3& color) { _water_color = color; }

    /**
     * @brief Sets the water transparency
     * @param transparency Transparency value (0-1)
     */
    void set_transparency(float transparency) { _transparency = transparency; }

    /**
     * @brief Sets the wave parameters
     * @param height Height of waves
     * @param speed Speed of wave animation
     * @param choppiness Choppiness factor of waves
     */
    void set_wave_parameters(float height, float speed, float choppiness);

    /**
     * @brief Sets the reflection and refraction parameters
     * @param reflection_strength Strength of reflections (0-1)
     * @param refraction_strength Strength of refractions (0-1)
     * @param fresnel_factor Fresnel effect factor
     */
    void set_reflection_parameters(float reflection_strength,
                                  float refraction_strength,
                                  float fresnel_factor);

    /**
     * @brief Enables or disables caustics
     * @param enabled Whether caustics are enabled
     * @param strength Strength of the caustic effect
     */
    void set_caustics(bool enabled, float strength = 1.0f);

    /**
     * @brief Enables or disables foam
     * @param enabled Whether foam is enabled
     * @param amount Amount of foam (0-1)
     */
    void set_foam(bool enabled, float amount = 0.5f);

private:
    struct WaterBody {
        int id;
        enum class Type { PLANE, RIVER, LAKE } type;
        std::vector<glm::vec3> vertices;
        std::vector<GLuint> indices;
        GLuint vao;
        GLuint vbo;
        GLuint ibo;
        glm::vec3 position;
        float size;
    };

    const SceneConfig& _config;
    const Terrain& _terrain;

    // OpenGL resources
    GLuint _water_shader;
    GLuint _reflection_fbo;
    GLuint _refraction_fbo;
    GLuint _reflection_texture;
    GLuint _refraction_texture;
    GLuint _depth_texture;
    GLuint _normal_map;
    GLuint _dudv_map;

    // Water bodies
    std::vector<WaterBody> _water_bodies;
    int _next_water_id;

    // Water properties
    glm::vec3 _water_color;
    float _transparency;
    float _wave_height;
    float _wave_speed;
    float _wave_choppiness;
    float _reflection_strength;
    float _refraction_strength;
    float _fresnel_factor;
    float _dudv_offset;
    bool _caustics_enabled;
    float _caustics_strength;
    bool _foam_enabled;
    float _foam_amount;

    // Helper methods
    bool _compile_shaders();
    void _create_fbos();
    void _render_reflection_pass(const glm::mat4& view_matrix,
                               const glm::mat4& projection_matrix,
                               const glm::vec3& camera_position);
    void _render_refraction_pass(const glm::mat4& view_matrix,
                               const glm::mat4& projection_matrix,
                               const glm::vec3& camera_position);
    void _create_water_plane_mesh(WaterBody& water, float size);
    void _create_river_mesh(WaterBody& water, const std::vector<glm::vec3>& path_points, float width);
    void _create_lake_mesh(WaterBody& water, const glm::vec3& center,
                          const std::vector<glm::vec2>& shape_points);
    void _update_waves(float delta_time);
    bool _load_textures();
};
