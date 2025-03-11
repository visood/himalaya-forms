// noise_generator.cpp
#include "noise_generator.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <numeric>

NoiseGenerator::NoiseGenerator(unsigned int seed) : _random_generator(seed) {
    _initialize_permutation_table();
}

void NoiseGenerator::set_seed(unsigned int seed) {
    _random_generator.seed(seed);
    _initialize_permutation_table();
}

float NoiseGenerator::perlin(float x, float y, float frequency) const {
    throw std::runtime_error("NoiseGenerator::perlin not implemented");
}

float NoiseGenerator::perlin(float x, float y, float z, float frequency) const {
    throw std::runtime_error("NoiseGenerator::perlin not implemented");
}

float NoiseGenerator::simplex(float x, float y, float frequency) const {
    throw std::runtime_error("NoiseGenerator::simplex not implemented");
}

float NoiseGenerator::simplex(float x, float y, float z, float frequency) const {
    throw std::runtime_error("NoiseGenerator::simplex not implemented");
}

float NoiseGenerator::fbm(float x, float y, int octaves,
                        float persistence, float lacunarity,
                        float frequency) const {
    throw std::runtime_error("NoiseGenerator::fbm not implemented");
}

float NoiseGenerator::fbm(float x, float y, float z, int octaves,
                        float persistence, float lacunarity,
                        float frequency) const {
    throw std::runtime_error("NoiseGenerator::fbm not implemented");
}

float NoiseGenerator::ridged_multi(float x, float y, int octaves,
                                 float persistence, float lacunarity,
                                 float frequency) const {
    throw std::runtime_error("NoiseGenerator::ridged_multi not implemented");
}

float NoiseGenerator::worley(float x, float y, float frequency) const {
    throw std::runtime_error("NoiseGenerator::worley not implemented");
}

std::vector<std::vector<float>> NoiseGenerator::generate_noise_map(
    int width, int height,
    int noise_type,
    float scale,
    int octaves,
    float persistence,
    float lacunarity) {
    throw std::runtime_error("NoiseGenerator::generate_noise_map not implemented");
}

std::vector<float> NoiseGenerator::generate_heightmap(
    int width, int height,
    float roughness,
    float min_height,
    float max_height) {
    throw std::runtime_error("NoiseGenerator::generate_heightmap not implemented");
}

void NoiseGenerator::apply_erosion(
    std::vector<float>& heightmap,
    int width, int height,
    int iterations,
    float rain_amount,
    float solubility,
    float evaporation) {
    throw std::runtime_error("NoiseGenerator::apply_erosion not implemented");
}

void NoiseGenerator::_initialize_permutation_table() {
    throw std::runtime_error("NoiseGenerator::_initialize_permutation_table not implemented");
}

float NoiseGenerator::_gradient(int hash, float x, float y, float z) const {
    throw std::runtime_error("NoiseGenerator::_gradient not implemented");
}
