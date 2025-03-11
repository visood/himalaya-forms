// mesh_utils.cpp
#include "mesh_utils.hpp"
#include <stdexcept>
#include <iostream>
#include <cmath>

MeshUtils::Mesh MeshUtils::create_plane(float width, float length,
                                      int width_segments, int length_segments) {
    throw std::runtime_error("MeshUtils::create_plane not implemented");
}

MeshUtils::Mesh MeshUtils::create_cube(float size) {
    throw std::runtime_error("MeshUtils::create_cube not implemented");
}

MeshUtils::Mesh MeshUtils::create_sphere(float radius, int rings, int sectors) {
    throw std::runtime_error("MeshUtils::create_sphere not implemented");
}

MeshUtils::Mesh MeshUtils::create_cylinder(float radius, float height, int segments) {
    throw std::runtime_error("MeshUtils::create_cylinder not implemented");
}

MeshUtils::Mesh MeshUtils::create_cone(float radius, float height, int segments) {
    throw std::runtime_error("MeshUtils::create_cone not implemented");
}

MeshUtils::Mesh MeshUtils::create_terrain_from_heightmap(const std::vector<float>& heights,
                                                      int width, int length,
                                                      float scale_x, float scale_y,
                                                      float scale_z) {
    throw std::runtime_error("MeshUtils::create_terrain_from_heightmap not implemented");
}

MeshUtils::Mesh MeshUtils::create_quad() {
    throw std::runtime_error("MeshUtils::create_quad not implemented");
}

MeshUtils::Mesh MeshUtils::create_billboard(float width, float height) {
    throw std::runtime_error("MeshUtils::create_billboard not implemented");
}

void MeshUtils::calculate_normals(std::vector<Vertex>& vertices,
                               const std::vector<unsigned int>& indices) {
    throw std::runtime_error("MeshUtils::calculate_normals not implemented");
}

void MeshUtils::calculate_tangents(std::vector<Vertex>& vertices,
                                const std::vector<unsigned int>& indices) {
    throw std::runtime_error("MeshUtils::calculate_tangents not implemented");
}

void MeshUtils::create_buffers(Mesh& mesh) {
    throw std::runtime_error("MeshUtils::create_buffers not implemented");
}

void MeshUtils::delete_buffers(Mesh& mesh) {
    throw std::runtime_error("MeshUtils::delete_buffers not implemented");
}

MeshUtils::Mesh MeshUtils::create_path(const std::vector<glm::vec3>& path_points,
                                     float width, const glm::vec3& up) {
    throw std::runtime_error("MeshUtils::create_path not implemented");
}

MeshUtils::Mesh MeshUtils::create_water_surface(float width, float length, int resolution) {
    throw std::runtime_error("MeshUtils::create_water_surface not implemented");
}
