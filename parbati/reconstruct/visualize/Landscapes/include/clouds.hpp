// clouds.hpp
#pragma once

#include <memory>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "scene_config.hpp"

/*
 * @class CloudSystem
 * @brief Manages and renders cloud formations in the sky
 */
class CloudSystem {
public:
    enum class CloudType {
        VOLUMETRIC,
        BILLBOARD,
        PROCEDURAL
    };

    /*
     * @brief Constructor
     * @param config Reference to the scene configuration
     */
    CloudSystem(const SceneConfig& config);

    /*
     * @brief Destructor
     */
    ~CloudSystem();

    /*
     * @brief Initializes the cloud system resources
     * @return True if initialization was successful
     */
    bool initialize();

    /*
     * @brief Renders the clouds
     * @param view_matrix The view matrix
     * @param projection_matrix The projection matrix
     * @param sun_direction Direction vector to the sun
     * @param sun_color Color of the sun
     */
    void render(const glm::mat4& view_matrix, const glm::mat4& projection_matrix,
               const glm::vec3& sun_direction, const glm::vec3& sun_color);

    /*
     * @brief Updates the cloud system
     * @param delta_time Time elapsed since last update in seconds
     * @param camera_position Position of the camera
     */
    void update(float delta_time, const glm::vec3& camera_position);

    /*
     * @brief Sets the cloud coverage amount (0-1)
     * @param coverage Cloud coverage value
     */
    void set_cloud_coverage(float coverage) { _cloud_coverage = coverage; }

    /*
     * @brief Sets the cloud density
     * @param density Cloud density value
     */
    void set_cloud_density(float density) { _cloud_density = density; }

    /*
     * @brief Sets the wind direction and speed
     * @param direction Wind direction vector
     * @param speed Wind speed in units per second
     */
    void set_wind(const glm::vec2& direction, float speed);

    /*
     * @brief Gets the current cloud coverage
     * @return Cloud coverage value (0-1)
     */
    float get_cloud_coverage() const { return _cloud_coverage; }

    /*
     * @brief Gets the current cloud density
     * @return Cloud density value
     */
    float get_cloud_density() const { return _cloud_density; }

    /*
     * @brief Sets the cloud type to use
     * @param type Cloud rendering technique to use
     */
    void set_cloud_type(CloudType type) { _cloud_type = type; }

private:
    const SceneConfig& _config;

    // Cloud rendering options
    CloudType _cloud_type;

    // Cloud parameters
    float _cloud_coverage;  // 0-1
    float _cloud_density;
    float _cloud_base_height;
    float _cloud_height;

    // Wind parameters
    glm::vec2 _wind_direction;
    float _wind_speed;
    float _accumulated_time;

    // OpenGL resources
    GLuint _cloud_shader;
    GLuint _noise_texture;
    GLuint _volume_texture;

    // Volumetric cloud resources
    std::vector<glm::vec3> _cloud_positions;
    std::vector<float> _cloud_sizes;

    // Helper methods
    bool _compile_shaders();
    void _generate_noise_texture();
    void _create_volumetric_clouds();
    void _create_billboard_clouds();
    void _update_cloud_positions(float delta_time);
};
