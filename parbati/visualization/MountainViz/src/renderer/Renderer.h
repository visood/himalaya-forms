#pragma once

//#include "glm/glm.hpp"
#include "../terrain/ProceduralTerrain.h"

// Abstract renderer interface
class Renderer {
public:
    virtual ~Renderer() {}
    virtual void initialize() = 0;
    virtual void setTerrain(ProceduralTerrain* terrain) = 0;
    virtual void render(const glm::mat4& view,
                        const glm::mat4& projection) = 0;
};

// OpenGL implementation
class OpenGLRenderer : public Renderer {
private:
    unsigned int shaderProgram;
    unsigned int VAO, VBO, EBO;
    ProceduralTerrain* terrain;

    // Helper to compile shaders
    unsigned int compileShader(const char* vertexShaderSource,
                               const char* fragmentShaderSource);

public:
    OpenGLRenderer() : terrain(nullptr) {}
    ~OpenGLRenderer();

    void initialize() override;
    void setTerrain(ProceduralTerrain* terrain) override;
    void render(const glm::mat4& view,
                const glm::mat4& projection) override;
};
