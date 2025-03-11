// terrain.hpp
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "height_map.hpp"

class Terrain {
public:
    /**
     * @brief Constructor for the terrain system
     * @param resolution The resolution of the terrain grid
     * @param size The physical size of the terrain in world units
     * @param height_scale Scale factor applied to height values
     */
    Terrain(
        int resolution = 1024, float size = 1000.0f, float height_scale = 500.0f);

    /**
     * @brief Destructor
     */
    ~Terrain();

    /**
     * @brief Initializes the terrain system
     * @return True if initialization was successful
     */
    bool initialize();

    /**
     * @brief Loads terrain data from a heightmap file
     * @param filepath Path to the heightmap image file
     * @return True if loading was successful
     */
    bool load_from_heightmap(const std::string& filepath);

    /**
     * @brief Generates procedural terrain
     * @param seed Random seed for terrain generation
     * @param roughness Roughness parameter (0-1) for terrain generation
     * @param num_octaves Number of noise octaves to use
     * @return True if generation was successful
     */
    bool generate_procedural(
        unsigned int seed, float roughness = 0.5f, int num_octaves = 6);

    /**
     * @brief Get the height at a specific world position
     * @param x X coordinate in world space
     * @param z Z coordinate in world space
     * @return Height value at the specified position
     */
    float get_height_at(float x, float z) const;

    /**
     * @brief Get the normal vector at a specific world position
     * @param x X coordinate in world space
     * @param z Z coordinate in world space
     * @return Normal vector at the specified position
     */
    glm::vec3 get_normal_at(float x, float z) const;

    /**
     * @brief Updates the terrain system
     * @param delta_time Time elapsed since last update
     */
    void update(float delta_time);

    // Getters and setters
    int get_resolution() const { return _resolution; }
    float get_size() const { return _size; }
    float get_height_scale() const { return _height_scale; }
    void set_height_scale(float scale) { _height_scale = scale; }

    /**
     * @brief Gets a pointer to the underlying heightmap
     * @return Raw pointer to the heightmap
     */
    HeightMap* get_heightmap() { return _heightmap.get(); }

    /**
     * @brief Modifies the height at a specific point (for terrain editing)
     * @param x X coordinate in world space
     * @param z Z coordinate in world space
     * @param height_delta Amount to add to the current height
     * @param radius Radius of influence
     * @param falloff Falloff factor for the brush (0-1)
     */
    void modify_height(
        float x, float z, float height_delta, float radius, float falloff = 0.5f);

private:
    int _resolution;               // Resolution of the terrain grid
    float _size;                   // Physical size in world units
    float _height_scale;           // Scale factor for height values
    std::unique_ptr<HeightMap> _heightmap; // The heightmap data

    // Private helper methods
    void _recalculate_normals();
    float _world_to_grid_scale() const { return _resolution / _size; }
    void _update_mesh_data();

    // Internal data structures
    std::vector<float> _cached_normals;
    bool _needs_mesh_update;
};
