#include <glad/glad.h>
#include <iostream>
#include "Renderer.h"
//#include <glm/gtc/type_ptr.hpp>

// Shader sources
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aNormal;

    out vec3 FragPos;
    out vec3 Normal;
    out float Height;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main() {
        FragPos = vec3(model * vec4(aPos, 1.0));
        Normal = mat3(transpose(inverse(model))) * aNormal;
        Height = aPos.y;
        gl_Position = projection * view * model * vec4(aPos, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;

    in vec3 FragPos;
    in vec3 Normal;
    in float Height;

    uniform vec3 lightPos;
    uniform vec3 viewPos;

    void main() {
        // Height-based coloring
        vec3 mountainColor;
        if (Height < 10.0) {
            mountainColor = mix(vec3(0.0, 0.3, 0.0), vec3(0.2, 0.5, 0.1), Height / 10.0); // Forest green
        } else if (Height < 25.0) {
            mountainColor = mix(vec3(0.2, 0.5, 0.1), vec3(0.5, 0.4, 0.3), (Height - 10.0) / 15.0); // Green to brown
        } else if (Height < 40.0) {
            mountainColor = mix(vec3(0.5, 0.4, 0.3), vec3(0.7, 0.7, 0.7), (Height - 25.0) / 15.0); // Brown to gray
        } else {
            mountainColor = mix(vec3(0.7, 0.7, 0.7), vec3(1.0, 1.0, 1.0), (Height - 40.0) / 20.0); // Gray to white (snow)
        }

        // Lighting calculations
        vec3 lightColor = vec3(1.0, 1.0, 1.0);

        // Ambient
        float ambientStrength = 0.3;
        vec3 ambient = ambientStrength * lightColor;

        // Diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        // Specular
        float specularStrength = 0.5;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * lightColor;

        vec3 result = (ambient + diffuse + specular) * mountainColor;
        FragColor = vec4(result, 1.0);
    }
)";

unsigned int OpenGLRenderer::compileShader(
    const char* vertexShaderSource, const char* fragmentShaderSource) {
    // Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Shader Program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    // Delete shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

OpenGLRenderer::~OpenGLRenderer() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}

void OpenGLRenderer::initialize() {
    // Compile shaders
    shaderProgram = compileShader(vertexShaderSource, fragmentShaderSource);

    // Generate buffers and arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
}

void OpenGLRenderer::setTerrain(ProceduralTerrain* newTerrain) {
    terrain = newTerrain;

    // Only proceed if we have valid terrain data
    if (!terrain) return;

    // Generate mesh data from terrain
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    terrain->createMesh(vertices, indices);

    // Bind vertex array
    glBindVertexArray(VAO);

    // Load vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);

    // Load indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(unsigned int),
                 indices.data(), GL_STATIC_DRAW);

    // Position attribute (3 floats)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal attribute (3 floats)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void OpenGLRenderer::render(
    const glm::mat4& view, const glm::mat4& projection
) {
    if (!terrain) return;

    // Use shader program
    glUseProgram(shaderProgram);

    // Set uniforms
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,
                           glm::vec3(-terrain->getWidth()/2.0f, 0.0f,
                                     -terrain->getHeight()/2.0f));

    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // Set light position (above terrain)
    unsigned int lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
    glm::vec3 lightPos(0.0f, 200.0f, 0.0f);
    glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));

    // Set view position for specular calculations
    unsigned int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
    glUniform3fv(viewPosLoc, 1, glm::value_ptr(glm::vec3(view[3])));

    // Draw terrain
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, terrain->getIndexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
