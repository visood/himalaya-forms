// texture_manager.cpp
#include "texture_manager.hpp"
#include "file_utils.hpp"
#include <stdexcept>
#include <iostream>

TextureManager::TextureManager() {
    // Stub implementation
}

TextureManager::~TextureManager() {
    unload_all();
}

GLuint TextureManager::load_texture(const std::string& name,
                                  const std::string& filepath,
                                  bool generate_mipmaps,
                                  bool flip_vertically) {
    throw std::runtime_error("TextureManager::load_texture not implemented");
}

GLuint TextureManager::create_empty_texture(const std::string& name,
                                          int width, int height,
                                          GLenum internal_format,
                                          GLenum format,
                                          GLenum type) {
    throw std::runtime_error("TextureManager::create_empty_texture not implemented");
}

GLuint TextureManager::create_3d_texture(const std::string& name,
                                       int width, int height, int depth,
                                       const float* data) {
    throw std::runtime_error("TextureManager::create_3d_texture not implemented");
}

GLuint TextureManager::create_cube_map(const std::string& name,
                                     const std::vector<std::string>& filepaths) {
    throw std::runtime_error("TextureManager::create_cube_map not implemented");
}

GLuint TextureManager::get_texture(const std::string& name) const {
    throw std::runtime_error("TextureManager::get_texture not implemented");
}

bool TextureManager::bind_texture(const std::string& name, unsigned int unit) {
    throw std::runtime_error("TextureManager::bind_texture not implemented");
}

void TextureManager::unload_texture(const std::string& name) {
    throw std::runtime_error("TextureManager::unload_texture not implemented");
}

void TextureManager::unload_all() {
    throw std::runtime_error("TextureManager::unload_all not implemented");
}

bool TextureManager::update_texture(const std::string& name,
                                  int x, int y,
                                  int width, int height,
                                  const void* data) {
    throw std::runtime_error("TextureManager::update_texture not implemented");
}

unsigned char* TextureManager::_load_image(const std::string& filepath,
                                         int& width, int& height, int& channels,
                                         bool flip_vertically) {
    throw std::runtime_error("TextureManager::_load_image not implemented");
}
