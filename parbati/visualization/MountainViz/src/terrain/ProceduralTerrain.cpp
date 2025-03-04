#include "ProceduralTerrain.h"
//#include <iostream>
//#include <cmath>
//#include <random>
//#include <chrono>

ProceduralTerrain::ProceduralTerrain(
    int width, int height) : width(width), height(height), indexCount(0)
{
    // Initialize RNG with time-based seed
    rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    // Initialize heightmap with zeros
    heightmap.resize(width * height, 0.0f);

    // Initialize normals
    normals.resize(width * height, glm::vec3(0.0f, 1.0f, 0.0f));
}

float ProceduralTerrain::getHeight(int x, int z) const {
    if (x < 0 || x >= width || z < 0 || z >= height) {
        return 0.0f;
    }
    return heightmap[z * width + x];
}

void ProceduralTerrain::setHeight(int x, int z, float h) {
    if (x < 0 || x >= width || z < 0 || z >= height) {
        return;
    }
    heightmap[z * width + x] = h;
}

void ProceduralTerrain::calculateNormals() {
    for (int z = 0; z < height; z++) {
        for (int x = 0; x < width; x++) {
            // Get heights of neighboring vertices
            float hL = getHeight(x-1, z);
            float hR = getHeight(x+1, z);
            float hD = getHeight(x, z-1);
            float hU = getHeight(x, z+1);

            // Calculate normal using central difference
            glm::vec3 normal(
                hL - hR,
                2.0f,  // Fixed y component for smoother normals
                hD - hU
            );

            normals[z * width + x] = glm::normalize(normal);
        }
    }
}

void ProceduralTerrain::generateDiamondSquare(float roughness, float maxHeight) {
    // Make sure width and height are 2^n + 1
    int size = width;  // Assuming width == height for this algorithm

    // Set up distribution for random values
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    // Set corner points
    setHeight(0, 0, 0);
    setHeight(0, size-1, 0);
    setHeight(size-1, 0, 0);
    setHeight(size-1, size-1, 0);

    // Run the diamond-square algorithm
    int step = size - 1;
    float scale = maxHeight;

    while (step > 1) {
        int halfStep = step / 2;

        // Diamond step
        for (int z = 0; z < size-1; z += step) {
            for (int x = 0; x < size-1; x += step) {
                float avg = (
                    getHeight(x, z) +
                    getHeight(x + step, z) +
                    getHeight(x, z + step) +
                    getHeight(x + step, z + step)
                ) / 4.0f;

                float offset = std::fabs(dist(rng)) * scale;
                setHeight(x + halfStep, z + halfStep, avg + offset);
            }
        }

        // Square step
        for (int z = 0; z < size; z += halfStep) {
            for (int x = (z + halfStep) % step; x < size; x += step) {
                float avg = 0.0f;
                int count = 0;

                // Check the four adjacent cells
                if (x >= halfStep) {
                    avg += getHeight(x - halfStep, z);
                    count++;
                }
                if (x + halfStep < size) {
                    avg += getHeight(x + halfStep, z);
                    count++;
                }
                if (z >= halfStep) {
                    avg += getHeight(x, z - halfStep);
                    count++;
                }
                if (z + halfStep < size) {
                    avg += getHeight(x, z + halfStep);
                    count++;
                }

                avg /= count;
                float offset = dist(rng) * scale;
                setHeight(x, z, std::fabs(avg + offset));
            }
        }

        // Reduce the random variation as we get finer detail
        scale *= roughness;
        step = halfStep;
    }

    // Calculate normals for lighting
    calculateNormals();
}

void ProceduralTerrain::createMesh(
    std::vector<float>& vertices, std::vector<unsigned int>& indices
) {
    vertices.clear();
    indices.clear();

    // Generate vertices (position + normal for each point)
    for (int z = 0; z < height; z++) {
        for (int x = 0; x < width; x++) {
            // Position
            vertices.push_back(static_cast<float>(x));                 // x
            vertices.push_back(getHeight(x, z));                       // y (height)
            vertices.push_back(static_cast<float>(z));                 // z

            // Normal
            glm::vec3 normal = normals[z * width + x];
            vertices.push_back(normal.x);
            vertices.push_back(normal.y);
            vertices.push_back(normal.z);
        }
    }

    // Generate indices for triangles
    for (int z = 0; z < height - 1; z++) {
        for (int x = 0; x < width - 1; x++) {
            unsigned int topLeft = z * width + x;
            unsigned int topRight = topLeft + 1;
            unsigned int bottomLeft = (z + 1) * width + x;
            unsigned int bottomRight = bottomLeft + 1;

            // First triangle (top-left, bottom-left, bottom-right)
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);

            // Second triangle (top-left, bottom-right, top-right)
            indices.push_back(topLeft);
            indices.push_back(bottomRight);
            indices.push_back(topRight);
        }
    }

    // Store index count for rendering
    indexCount = indices.size();
}
