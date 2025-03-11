// mesh_utils.hpp
#pragma once

#include <vector>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

/**
 * @class MeshUtils
 * @brief Utility functions for generating and manipulating 3D meshes
 */
class MeshUtils {
public:
    /**
     * @brief Structure to hold vertex data
     */
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 tex_coords;
        glm::vec3 tangent;
        glm::vec3 bitangent;
    };

    /**
     * @brief Structure to hold mesh data
     */
    struct Mesh {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        GLuint vao;
        GLuint vbo;
        GLuint ibo;
    };

    /**
     * @brief Creates a plane mesh
     * @param width Width of the plane
     * @param length Length of the plane
     * @param width_segments Number of width segments
     * @param length_segments Number of length segments
     * @return Plane mesh data
     */
    static Mesh create_plane(float width, float length,
                            int width_segments = 1, int length_segments = 1);

    /**
     * @brief Creates a cube mesh
     * @param size Size of the cube
     * @return Cube mesh data
     */
    static Mesh create_cube(float size);

    /**
     * @brief Creates a sphere mesh
     * @param radius Radius of the sphere
     * @param rings Number of horizontal rings
     * @param sectors Number of vertical sectors
     * @return Sphere mesh data
     */
    static Mesh create_sphere(float radius, int rings = 16, int sectors = 32);

    /**
     * @brief Creates a cylinder mesh
     * @param radius Radius of the cylinder
     * @param height Height of the cylinder
     * @param segments Number of segments around the cylinder
     * @return Cylinder mesh data
     */
    static Mesh create_cylinder(float radius, float height, int segments = 32);

    /*
     * @brief Creates a cone mesh
     * @param radius Base radius of the cone
     * @param height Height of the cone
     * @param segments Number of segments around the cone
     * @return Cone mesh data
     */
    static Mesh create_cone(float radius, float height, int segments = 32);

    /*
     * @brief Generates a terrain mesh from a heightmap
     * @param heights Height values as 2D array
     * @param width Width of the heightmap
     * @param length Length of the heightmap
     * @param scale_x X scale factor for vertex spacing
     * @param scale_y Y scale factor for height values
     * @param scale_z Z scale factor for vertex spacing
     * @return Terrain mesh data
     */
    static Mesh create_terrain_from_heightmap(const std::vector<float>& heights,
                                            int width, int length,
                                            float scale_x = 1.0f, float scale_y = 1.0f,
                                            float scale_z = 1.0f);

    /*
     * @brief Creates a quad mesh (2 triangles forming a rectangle)
     * @return Quad mesh data
     */
    static Mesh create_quad();

    /*
     * @brief Creates a billboard quad (always facing camera)
     * @param width Width of the billboard
     * @param height Height of the billboard
     * @return Billboard mesh data
     */
    static Mesh create_billboard(float width, float height);

    /*
     * @brief Calculates smooth normals for a mesh
     * @param vertices Mesh vertices
     * @param indices Mesh indices
     */
    static void calculate_normals(std::vector<Vertex>& vertices,
                                 const std::vector<unsigned int>& indices);

    /*
     * @brief Calculates tangents and bitangents for a mesh (for normal mapping)
     * @param vertices Mesh vertices
     * @param indices Mesh indices
     */
    static void calculate_tangents(std::vector<Vertex>& vertices,
                                  const std::vector<unsigned int>& indices);

    /*
     * @brief Creates OpenGL buffers for a mesh
     * @param mesh Mesh to create buffers for
     */
    static void create_buffers(Mesh& mesh);

    /*
     * @brief Deletes OpenGL buffers for a mesh
     * @param mesh Mesh to delete buffers for
     */
    static void delete_buffers(Mesh& mesh);

    /*
     * @brief Generates a path mesh along specified points
     * @param path_points Points defining the path
     * @param width Width of the path
     * @param up Up vector for path orientation
     * @return Path mesh data
     */
    static Mesh create_path(const std::vector<glm::vec3>& path_points,
                           float width, const glm::vec3& up = glm::vec3(0, 1, 0));

    /*
     * @brief Creates a water surface mesh with wave displacement
     * @param width Width of the water surface
     * @param length Length of the water surface
     * @param resolution Grid resolution
     * @return Water surface mesh data
     */
    static Mesh create_water_surface(float width, float length, int resolution = 32);
};
