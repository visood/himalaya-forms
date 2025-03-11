// height_map.hpp
#pragma once

#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

class HeightMap {
public:
    /**
     * @brief Constructor for the heightmap
     * @param resolution The resolution of the heightmap grid
     */
    HeightMap(int resolution);

    /**
     * @brief Destructor
     */
    ~HeightMap();

    /**
     * @brief Loads heightmap data from an image file
     * @param filepath Path to the heightmap image file
     * @return True if loading was successful
     */
    bool load_from_image(const std::string& filepath);

    /**
     * @brief Generates procedural heightmap data
     * @param seed Random seed for terrain generation
     * @param roughness Roughness parameter (0-1) for terrain generation
     * @param num_octaves Number of noise octaves to use
     * @return True if generation was successful
     */

    // height_map.hpp (continued)
    bool generate_procedural(unsigned int seed, float roughness = 0.5f, int num_octaves = 6);

    /*
     * @brief Gets the height value at a specific grid coordinate
     * @param x X coordinate in grid space (0 to resolution-1)
     * @param y Y coordinate in grid space (0 to resolution-1)
     * @return Height value at the specified position
     */
    float get_height(int x, int y) const;

    /*
     * @brief Sets the height value at a specific grid coordinate
     * @param x X coordinate in grid space (0 to resolution-1)
     * @param y Y coordinate in grid space (0 to resolution-1)
     * @param height New height value
     */
    void set_height(int x, int y, float height);

    /*
     * @brief Smoothly modifies the height in a circular area
     * @param center_x Center X coordinate in grid space
     * @param center_y Center Y coordinate in grid space
     * @param height_delta Amount to add to the current height
     * @param radius Radius of influence in grid cells
     * @param falloff Falloff factor for the brush (0-1)
     */
    void modify_height_area(int center_x, int center_y, float height_delta,
                           float radius, float falloff = 0.5f);

    /*
     * @brief Saves the heightmap to an image file
     * @param filepath Path to save the image file
     * @return True if saving was successful
     */
    bool save_to_image(const std::string& filepath) const;

    /*
     * @brief Gets the resolution of the heightmap
     * @return Resolution (width and height are the same)
     */
    int get_resolution() const { return _resolution; }

    /*
     * @brief Gets the raw height data pointer
     * @return Pointer to the height data array
     */
    const float* get_data() const { return _height_data.data(); }

    /*
     * @brief Gets the normal at a specific grid coordinate
     * @param x X coordinate in grid space
     * @param y Y coordinate in grid space
     * @return Normal vector at the specified position
     */
    glm::vec3 get_normal(int x, int y) const;

    /*
     * @brief Calculates normals for the entire heightmap
     */
    void calculate_normals();

    /*
     * @brief Apply erosion simulation to the heightmap
     * @param iterations Number of erosion iterations
     * @param rain_rate Rate of rain/erosion
     * @param solubility Solubility factor for erosion
     * @param evaporation Evaporation rate
     */
    void apply_erosion(int iterations = 50000, float rain_rate = 0.01f,
                      float solubility = 0.01f, float evaporation = 0.5f);

private:
    int _resolution;
    std::vector<float> _height_data;
    std::vector<glm::vec3> _normals;

    // Helper methods
    int _index(int x, int y) const { return y * _resolution + x; }
    float _sample_bilinear(float x, float y) const;
    void _apply_thermal_erosion(float talus_angle);
    void _apply_hydraulic_erosion(float rain_rate, float solubility, float evaporation);
};
