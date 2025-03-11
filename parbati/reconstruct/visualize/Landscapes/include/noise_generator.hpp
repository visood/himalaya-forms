// noise_generator.hpp
#pragma once

#include <vector>
#include <random>
#include <glm/glm.hpp>

/*
 * @class NoiseGenerator
 * @brief Generates various types of procedural noise for terrain and textures
 */
class NoiseGenerator {
public:
    /*
     * @brief Constructor with seed
     * @param seed Random seed
     */
    NoiseGenerator(unsigned int seed = 12345);

    /*
     * @brief Sets the random seed
     * @param seed New random seed
     */
   void set_seed(unsigned int seed);

    /**
     * @brief Generates 2D Perlin noise
     * @param x X coordinate
     * @param y Y coordinate
     * @param frequency Noise frequency
     * @return Noise value in range [-1, 1]
     */
    float perlin(float x, float y, float frequency = 1.0f) const;

    /**
     * @brief Generates 3D Perlin noise
     * @param x X coordinate
     * @param y Y coordinate
     * @param z Z coordinate
     * @param frequency Noise frequency
     * @return Noise value in range [-1, 1]
     */
    float perlin(float x, float y, float z, float frequency = 1.0f) const;

    /**
     * @brief Generates 2D Simplex noise
     * @param x X coordinate
     * @param y Y coordinate
     * @param frequency Noise frequency
     * @return Noise value in range [-1, 1]
     */
    float simplex(float x, float y, float frequency = 1.0f) const;

    /**
     * @brief Generates 3D Simplex noise
     * @param x X coordinate
     * @param y Y coordinate
     * @param z Z coordinate
     * @param frequency Noise frequency
     * @return Noise value in range [-1, 1]
     */
    float simplex(float x, float y, float z, float frequency = 1.0f) const;

    /**
     * @brief Generates 2D fractal Brownian motion (fBm) noise
     * @param x X coordinate
     * @param y Y coordinate
     * @param octaves Number of octaves
     * @param persistence Persistence factor (amplitude multiplier)
     * @param lacunarity Lacunarity factor (frequency multiplier)
     * @param frequency Base frequency
     * @return Noise value in range [-1, 1]
     */
    float fbm(float x, float y, int octaves = 6,
             float persistence = 0.5f, float lacunarity = 2.0f,
             float frequency = 1.0f) const;

    /**
     * @brief Generates 3D fractal Brownian motion (fBm) noise
     * @param x X coordinate
     * @param y Y coordinate
     * @param z Z coordinate
     * @param octaves Number of octaves
     * @param persistence Persistence factor (amplitude multiplier)
     * @param lacunarity Lacunarity factor (frequency multiplier)
     * @param frequency Base frequency
     * @return Noise value in range [-1, 1]
     */
    float fbm(float x, float y, float z, int octaves = 6,
             float persistence = 0.5f, float lacunarity = 2.0f,
             float frequency = 1.0f) const;

    /**
     * @brief Generates 2D ridged multi-fractal noise
     * @param x X coordinate
     * @param y Y coordinate
     * @param octaves Number of octaves
     * @param persistence Persistence factor
     * @param lacunarity Lacunarity factor
     * @param frequency Base frequency
     * @return Noise value in range [0, 1]
     */
    float ridged_multi(float x, float y, int octaves = 6,
                      float persistence = 0.5f, float lacunarity = 2.0f,
                      float frequency = 1.0f) const;

    /**
     * @brief Generates 2D worley/cellular noise
     * @param x X coordinate
     * @param y Y coordinate
     * @param frequency Noise frequency
     * @return Noise value in range [0, 1]
     */
    float worley(float x, float y, float frequency = 1.0f) const;

    /*
     * @brief Generates a 2D noise map
     * @param width Width of the noise map
     * @param height Height of the noise map
     * @param noise_type Type of noise to generate (0=Perlin, 1=Simplex, 2=fBm, 3=Ridged)
     * @param scale Scale factor for the noise
     * @param octaves Number of octaves (for fractal noise)
     * @param persistence Persistence factor (for fractal noise)
     * @param lacunarity Lacunarity factor (for fractal noise)
     * @return 2D vector of noise values
     */
    std::vector<std::vector<float>> generate_noise_map(
        int width, int height,
        int noise_type = 2,
        float scale = 1.0f,
        int octaves = 6,
        float persistence = 0.5f,
        float lacunarity = 2.0f);

    /*
     * @brief Generates a heightmap suitable for terrains
     * @param width Width of the heightmap
     * @param height Height of the heightmap
     * @param roughness Roughness factor (0-1)
     * @param min_height Minimum height value
     * @param max_height Maximum height value
     * @return 1D vector of height values (row-major)
     */
    std::vector<float> generate_heightmap(
        int width, int height,
        float roughness = 0.5f,
        float min_height = 0.0f,
        float max_height = 1.0f);

    /*
     * @brief Applies terrain erosion to a heightmap
     * @param heightmap Height data to erode (modified in place)
     * @param width Width of the heightmap
     * @param height Height of the heightmap
     * @param iterations Number of erosion iterations
     * @param rain_amount Amount of rain per iteration
     * @param solubility Solubility of the terrain
     * @param evaporation Evaporation rate
     */
    void apply_erosion(
        std::vector<float>& heightmap,
        int width, int height,
        int iterations = 50000,
        float rain_amount = 0.01f,
        float solubility = 0.01f,
        float evaporation = 0.5f);

private:
    std::mt19937 _random_generator;
    std::vector<int> _permutation_table;

    /*
     * @brief Initializes the permutation table for noise generation
     */
    void _initialize_permutation_table();

    /*
     * @brief Helper for gradients in Perlin noise
     */
    float _gradient(int hash, float x, float y, float z) const;

    /*
     * @brief Smoothing function for noise
     */
    inline float _fade(float t) const {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    /*
     * @brief Linear interpolation helper
     */
    inline float _lerp(float a, float b, float t) const {
        return a + t * (b - a);
    }
};
