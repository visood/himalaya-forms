// height_map.cpp
#include "height_map.hpp"
#include <stdexcept>
#include <iostream>

HeightMap::HeightMap(int resolution)
    : _resolution(resolution)
{
    _height_data.resize(resolution * resolution, 0.0f);
    _normals.resize(resolution * resolution, glm::vec3(0.0f, 1.0f, 0.0f));
}

HeightMap::~HeightMap() {
    // Stub implementation
}

bool HeightMap::load_from_image(const std::string& filepath) {
    throw std::runtime_error("HeightMap::load_from_image not implemented");
}

bool HeightMap::generate_procedural(unsigned int seed, float roughness, int num_octaves) {
    throw std::runtime_error("HeightMap::generate_procedural not implemented");
}

float HeightMap::get_height(int x, int y) const {
    if (x < 0 || x >= _resolution || y < 0 || y >= _resolution) {
        return 0.0f; // Return 0 for out-of-bounds access
    }
    return _height_data[_index(x, y)];
}

void HeightMap::set_height(int x, int y, float height) {
    if (x < 0 || x >= _resolution || y < 0 || y >= _resolution) {
        return; // Ignore out-of-bounds access
    }
    _height_data[_index(x, y)] = height;
}

void HeightMap::modify_height_area(int center_x, int center_y, float height_delta,
                                 float radius, float falloff) {
    throw std::runtime_error("HeightMap::modify_height_area not implemented");
}

bool HeightMap::save_to_image(const std::string& filepath) const {
    throw std::runtime_error("HeightMap::save_to_image not implemented");
}

glm::vec3 HeightMap::get_normal(int x, int y) const {
    if (x < 0 || x >= _resolution || y < 0 || y >= _resolution) {
        return glm::vec3(0.0f, 1.0f, 0.0f); // Return up vector for out-of-bounds
    }
    return _normals[_index(x, y)];
}

void HeightMap::calculate_normals() {
    throw std::runtime_error("HeightMap::calculate_normals not implemented");
}

void HeightMap::apply_erosion(int iterations, float rain_rate,
                            float solubility, float evaporation) {
    throw std::runtime_error("HeightMap::apply_erosion not implemented");
}

float HeightMap::_sample_bilinear(float x, float y) const {
    throw std::runtime_error("HeightMap::_sample_bilinear not implemented");
}

void HeightMap::_apply_thermal_erosion(float talus_angle) {
    throw std::runtime_error("HeightMap::_apply_thermal_erosion not implemented");
}

void HeightMap::_apply_hydraulic_erosion(float rain_rate, float solubility, float evaporation) {
    throw std::runtime_error("HeightMap::_apply_hydraulic_erosion not implemented");
}
