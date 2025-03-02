#pragma once
// First include GLM with specific configurations
#include <iostream>
#include <chrono>
#include "glm_wrapper.h"

class ProceduralTerrain {
private:
    int width, height;
    std::vector<float> heightmap;
    std::vector<glm::vec3> normals;
    int indexCount;

    // Random number generator
    std::mt19937 rng;

    // Helper method to get height at a specific point
    float getHeight(int x, int z) const;

    // Helper method to set height at a specific point
    void setHeight(int x, int z, float h);

    // Calculate normals for lighting
    void calculateNormals();

public:
    ProceduralTerrain(int width, int height);

    // Diamond-Square algorithm for realistic mountain generation
    void generateDiamondSquare(float roughness, float maxHeight);

    // Create mesh for rendering
    void createMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices);

    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getIndexCount() const { return indexCount; }
};
