// shader_manager.hpp
#pragma once

#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>

/*
 * @class ShaderManager
 * @brief Manages compilation, linking and usage of GLSL shader programs
 */
class ShaderManager {
public:
    /*
     * @brief Constructor
     */
    ShaderManager();

    /*
     * @brief Destructor
     */
    ~ShaderManager();

    /*
     * @brief Loads and compiles a shader from file
     * @param name Unique name for the shader program
     * @param vertex_path Path to vertex shader file
     * @param fragment_path Path to fragment shader file
     * @param geometry_path Optional path to geometry shader file
     * @return Shader program ID or 0 if failed
     */
    GLuint load_shader(const std::string& name,
                      const std::string& vertex_path,
                      const std::string& fragment_path,
                      const std::string& geometry_path = "");

    /*
     * @brief Compiles shader from source strings
     * @param name Unique name for the shader program
     * @param vertex_source Vertex shader source code
     * @param fragment_source Fragment shader source code
     * @param geometry_source Optional geometry shader source code
     * @return Shader program ID or 0 if failed
     */
    GLuint compile_shader(const std::string& name,
                         const std::string& vertex_source,
                         const std::string& fragment_source,
                         const std::string& geometry_source = "");

    /*
     * @brief Gets a shader program by name
     * @param name Name of the shader
     * @return Shader program ID or 0 if not found
     */
    GLuint get_shader(const std::string& name) const;

    /*
     * @brief Activates a shader program for rendering
     * @param name Name of the shader
     * @return True if successful
     */
    bool use_shader(const std::string& name);

    /*
     * @brief Unloads and deletes a shader program
     * @param name Name of the shader
     */
    void unload_shader(const std::string& name);

    /*
     * @brief Unloads all shader programs
     */
    void unload_all();

    // Uniform setters
    void set_bool(const std::string& name, bool value) const;
    void set_int(const std::string& name, int value) const;
    void set_float(const std::string& name, float value) const;
    void set_vec2(const std::string& name, const glm::vec2& value) const;
    void set_vec3(const std::string& name, const glm::vec3& value) const;
    void set_vec4(const std::string& name, const glm::vec4& value) const;
    void set_mat2(const std::string& name, const glm::mat2& value) const;
    void set_mat3(const std::string& name, const glm::mat3& value) const;
    void set_mat4(const std::string& name, const glm::mat4& value) const;

private:
    std::unordered_map<std::string, GLuint> _shader_programs;
    GLuint _current_shader;

    /*
     * @brief Compiles an individual shader
     * @param shader_code Shader source code
     * @param type Shader type (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc.)
     * @return Shader ID or 0 if compilation failed
     */
    GLuint _compile_shader_stage(const std::string& shader_code, GLenum type);

    /*
     * @brief Links shader stages into a program
     * @param vertex_shader Vertex shader ID
     * @param fragment_shader Fragment shader ID
     * @param geometry_shader Optional geometry shader ID
     * @return Shader program ID or 0 if linking failed
     */
    GLuint _link_shader_program(GLuint vertex_shader, GLuint fragment_shader,
                               GLuint geometry_shader = 0);

    /*
     * @brief Checks shader compilation/linking errors
     * @param shader Shader/program ID
     * @param is_program True if checking program, false if checking shader
     * @return Error message or empty string if no errors
     */
    std::string _check_shader_errors(GLuint shader, bool is_program);
};
