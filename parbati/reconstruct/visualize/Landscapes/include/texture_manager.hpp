// texture_manager.hpp
#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <glad/glad.h>
#include <glm/glm.hpp>

/*
 * @class TextureManager
 * @brief Manages loading, storing and binding of textures
 */
class TextureManager {
public:
    /*
     * @brief Constructor
     */
    TextureManager();

    /*
     * @brief Destructor
     */
    ~TextureManager();

    /*
     * @brief Loads a texture from file
     * @param name Unique name for the texture
     * @param filepath Path to the texture file
     * @param generate_mipmaps Whether to generate mipmaps
     * @param flip_vertically Whether to flip the image vertically
     * @return Texture ID or 0 if failed
     */
    GLuint load_texture(const std::string& name,
                        const std::string& filepath,
                        bool generate_mipmaps = true,
                        bool flip_vertically = true);

    /*
     * @brief Creates an empty texture
     * @param name Unique name for the texture
     * @param width Width of the texture
     * @param height Height of the texture
     * @param internal_format Internal format (GL_RGB, GL_RGBA, etc.)
     * @param format Pixel format (GL_RGB, GL_RGBA, etc.)
     * @param type Pixel data type (GL_UNSIGNED_BYTE, etc.)
     * @return Texture ID or 0 if failed
     */
    GLuint create_empty_texture(const std::string& name,
                                int width, int height,
                                GLenum internal_format = GL_RGBA,
                                GLenum format = GL_RGBA,
                                GLenum type = GL_UNSIGNED_BYTE);

    /*
     * @brief Creates a 3D texture for volumetric effects
     * @param name Unique name for the texture
     * @param width Width of the texture
     * @param height Height of the texture
     * @param depth Depth of the texture
     * @param data Optional texture data
     * @return Texture ID or 0 if failed
     */
    GLuint create_3d_texture(const std::string& name,
                             int width, int height, int depth,
                             const float* data = nullptr);

    /*
     * @brief Creates a cube map texture
     * @param name Unique name for the texture
     * @param filepaths Paths to the 6 faces (right, left, top, bottom, front, back)
     * @return Texture ID or 0 if failed
     */
    GLuint create_cube_map(const std::string& name,
                          const std::vector<std::string>& filepaths);

    /*
     * @brief Gets a texture by name
     * @param name Name of the texture
     * @return Texture ID or 0 if not found
     */
    GLuint get_texture(const std::string& name) const;

    /*
     * @brief Binds a texture to a specific texture unit
     * @param name Name of the texture
     * @param unit Texture unit to bind to
     * @return True if successful
     */
    bool bind_texture(const std::string& name, unsigned int unit = 0);

    /**
     * @brief Unloads and deletes a texture
     * @param name Name of the texture
     */
    void unload_texture(const std::string& name);

    /**
     * @brief Unloads all textures
     */
    void unload_all();

    /**
     * @brief Updates a portion of an existing texture
     * @param name Name of the texture
     * @param x X coordinate of the region to update
     * @param y Y coordinate of the region to update
     * @param width Width of the region to update
     * @param height Height of the region to update
     * @param data Pixel data to update with
     * @return True if successful
     */
    bool update_texture(const std::string& name,
                       int x, int y,
                       int width, int height,
                       const void* data);

private:
    std::unordered_map<std::string, GLuint> _textures;
    std::unordered_map<std::string, GLenum> _texture_types;

    /**
     * @brief Internal method to load image data from file
     * @param filepath Path to the image file
     * @param width Reference to store the image width
     * @param height Reference to store the image height
     * @param channels Reference to store the number of channels
     * @param flip_vertically Whether to flip the image vertically
     * @return Image data or nullptr if loading failed
     */
    unsigned char* _load_image(const std::string& filepath,
                              int& width, int& height, int& channels,
                              bool flip_vertically);
};
