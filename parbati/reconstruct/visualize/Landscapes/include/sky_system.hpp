// sky_system.hpp
#pragma once

#include <memory>
#include <vector>
#include <string>
#include <glad/glad.h>
#include "glm/glm.hpp"
#include <GLFW/glfw3.h>
#include "scene_config.hpp"

/*
 * @class SkySystem
 * @brief Manages and renders the sky, including the sky dome, sun, and atmospheric effects
 */
class SkySystem {
public:
    /*
     * @brief Constructor
     * @param config Reference to the scene configuration
     */
    SkySystem(const SceneConfig& config);

    /*
     * @brief Destructor
     */
    ~SkySystem();

    /*
     * @brief Initializes the sky system resources
     * @return True if initialization was successful
     */
    bool initialize();

    /*
     * @brief Renders the sky
     * @param view_matrix The view matrix
     * @param projection_matrix The projection matrix
     */
    void render(const glm::mat4& view_matrix, const glm::mat4& projection_matrix);

    /*
     * @brief Updates the sky based on time of day
     * @param delta_time Time elapsed since last update in seconds
     * @param time_of_day Current time of day (0-24 hours)
     */
    void update(float delta_time, float time_of_day);

    /*
     * @brief Sets the sun position based on time of day
     * @param time_of_day Time in hours (0-24)
     */
    void set_time_of_day(float time_of_day);

    /*
     * @brief Gets the current sun direction
     * @return Normalized vector pointing toward the sun
     */
    glm::vec3 get_sun_direction() const { return _sun_direction; }

    /*
     * @brief Gets the current sun color
     * @return RGB color of the sun
     */
    glm::vec3 get_sun_color() const { return _sun_color; }

    /*
     * @brief Gets the ambient light color
     * @return RGB color of ambient light
     */
    glm::vec3 get_ambient_color() const { return _ambient_color; }

    /*
     * @brief Sets the fog density
     * @param density Fog density value
     */
    void set_fog_density(float density) { _fog_density = density; }

    /*
     * @brief Sets the fog color
     * @param color RGB color of the fog
     */
    void set_fog_color(const glm::vec3& color) { _fog_color = color; }

    /*
     * @brief Gets the fog density
     * @return Current fog density
     */
    float get_fog_density() const { return _fog_density; }

    /*
     * @brief Gets the fog color
     * @return RGB color of the fog
     */
    glm::vec3 get_fog_color() const { return _fog_color; }

private:
    const SceneConfig& _config;

    // Sky dome
    GLuint _sky_vao;
    GLuint _sky_vbo;
    GLuint _sky_ibo;
    GLuint _sky_shader;

    // Sky parameters
    glm::vec3 _zenith_color;
    glm::vec3 _horizon_color;

    // Sun parameters
    glm::vec3 _sun_direction;
    glm::vec3 _sun_color;
    float _sun_size;

    // Atmospheric parameters
    glm::vec3 _ambient_color;
    float _fog_density;
    glm::vec3 _fog_color;

    // Star field for night sky
    bool _stars_visible;
    GLuint _star_texture;

    // Helper methods
    bool _compile_shaders();
    void _create_sky_dome();
    void _calculate_sun_position(float time_of_day);

    void _update_colors(float time_of_day);
};
