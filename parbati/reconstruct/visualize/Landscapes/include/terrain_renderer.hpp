// terrain_renderer.hpp
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "terrain.hpp"
#include "scene_config.hpp"
#include "window.hpp"
#include "scene.hpp"

class TerrainRenderer {
public:
    /**
     * @brief Constructor for the terrain renderer
     * @param window Reference to the window
     * @param terrain Reference to the terrain system
     * @param config Reference to the scene configuration
     */
    TerrainRenderer(
        const Window& window, const Terrain& terrain, const SceneConfig& config);

    /**
     * @brief Constructor for the terrain renderer
     * @param window Reference to the window
     * @param scene Reference to the scene to render
     * @param config Reference to the scene configuration
     */
    TerrainRenderer(
        const Window& window, const Scene& scene, const SceneConfig& config);

    /**
     * @brief Destructor
     */
    ~TerrainRenderer();

    /**
     * @brief Initializes the terrain renderer
     * @return True if initialization was successful
     */
    bool initialize();

    /**
     * @brief Begins a new frame for rendering
     */
    void begin_frame();

    /**
     * @brief Renders the terrain
     */
    void render_terrain();

    /**
     * @brief Renders the sky system
     */
    void render_sky();

    /**
     * @brief Ends the current frame
     */
    void end_frame();

    /**
     * @brief Updates the terrain renderer
     * @param delta_time Time elapsed since last update
     */
    void update(float delta_time);

    /**
     * @brief Sets the wireframe rendering mode
     * @param enabled True to enable wireframe rendering
     */
    void set_wireframe_mode(bool enabled);

    /**
     * @brief Sets the level of detail parameters
     * @param num_levels Number of LOD levels
     * @param distance_factor Distance factor for LOD transitions
     */
    void set_lod_parameters(int num_levels, float distance_factor);

private:
    const Window& _window;
    const Terrain& _terrain;
    const SceneConfig& _config;

    // OpenGL handles
    GLuint _vao;
    GLuint _vbo;
    GLuint _ibo;
    GLuint _shader_program;

    // Rendering state
    bool _wireframe_enabled;
    int _lod_levels;
    float _lod_distance_factor;

    // Internal methods
    bool _compile_shaders();
    void _setup_mesh_buffers();
    void _update_view_projection();

    // Cached matrices
    glm::mat4 _view_matrix;
    glm::mat4 _projection_matrix;
};
