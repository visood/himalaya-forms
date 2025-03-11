// shader_manager.cpp
#include "shader_manager.hpp"
#include "file_utils.hpp"
#include <stdexcept>
#include <iostream>

ShaderManager::ShaderManager() : _current_shader(0) {
    // Stub implementation
}

ShaderManager::~ShaderManager() {
    unload_all();
}

GLuint ShaderManager::load_shader(const std::string& name,
                                const std::string& vertex_path,
                                const std::string& fragment_path,
                                const std::string& geometry_path) {
    throw std::runtime_error("ShaderManager::load_shader not implemented");
}

GLuint ShaderManager::compile_shader(const std::string& name,
                                   const std::string& vertex_source,
                                   const std::string& fragment_source,
                                   const std::string& geometry_source) {
    throw std::runtime_error("ShaderManager::compile_shader not implemented");
}

GLuint ShaderManager::get_shader(const std::string& name) const {
    throw std::runtime_error("ShaderManager::get_shader not implemented");
}

bool ShaderManager::use_shader(const std::string& name) {
    throw std::runtime_error("ShaderManager::use_shader not implemented");
}

void ShaderManager::unload_shader(const std::string& name) {
    throw std::runtime_error("ShaderManager::unload_shader not implemented");
}

void ShaderManager::unload_all() {
    throw std::runtime_error("ShaderManager::unload_all not implemented");
}

void ShaderManager::set_bool(const std::string& name, bool value) const {
    throw std::runtime_error("ShaderManager::set_bool not implemented");
}

void ShaderManager::set_int(const std::string& name, int value) const {
    throw std::runtime_error("ShaderManager::set_int not implemented");
}

void ShaderManager::set_float(const std::string& name, float value) const {
    throw std::runtime_error("ShaderManager::set_float not implemented");
}

void ShaderManager::set_vec2(const std::string& name, const glm::vec2& value) const {
    throw std::runtime_error("ShaderManager::set_vec2 not implemented");
}

void ShaderManager::set_vec3(const std::string& name, const glm::vec3& value) const {
    throw std::runtime_error("ShaderManager::set_vec3 not implemented");
}

void ShaderManager::set_vec4(const std::string& name, const glm::vec4& value) const {
    throw std::runtime_error("ShaderManager::set_vec4 not implemented");
}

void ShaderManager::set_mat2(const std::string& name, const glm::mat2& value) const {
    throw std::runtime_error("ShaderManager::set_mat2 not implemented");
}

void ShaderManager::set_mat3(const std::string& name, const glm::mat3& value) const {
    throw std::runtime_error("ShaderManager::set_mat3 not implemented");
}

void ShaderManager::set_mat4(const std::string& name, const glm::mat4& value) const {
    throw std::runtime_error("ShaderManager::set_mat4 not implemented");
}

GLuint ShaderManager::_compile_shader_stage(const std::string& shader_code, GLenum type) {
    throw std::runtime_error("ShaderManager::_compile_shader_stage not implemented");
}

GLuint ShaderManager::_link_shader_program(GLuint vertex_shader, GLuint fragment_shader,
                                         GLuint geometry_shader) {
    throw std::runtime_error("ShaderManager::_link_shader_program not implemented");
}

std::string ShaderManager::_check_shader_errors(GLuint shader, bool is_program) {
    throw std::runtime_error("ShaderManager::_check_shader_errors not implemented");
}
