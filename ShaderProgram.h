#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include "Shader.h"
#include <iostream>

#include "ShaderLoader.h"
#include "Light.h" 

class ShaderProgram : public Observer {
private:
    GLuint programID;
    static std::vector<ShaderProgram*> shaders;
    Shader* currentShader;

    ShaderLoader shaderLoader;

public:
    ShaderProgram();

    void loadShaders(const char* vertexFile, const char* fragmentFile);

    void init();
    void attachShader(const Shader& shader);
    void link();
    void use() const;
    GLuint getProgramID() const;

    void setViewMatrix(const glm::mat4& viewMatrix);
    void setProjectionMatrix(const glm::mat4& projectionMatrix);

    ~ShaderProgram();

    static void cleanup();
    static void addShader(ShaderProgram* shaderProgram);

    static int getShadersCount();
    static ShaderProgram* getShaderByIndex(int index);
    static void checkCompilation(GLuint shaderID);

    GLuint getShaderID() const;

    void setMatrix(const std::string& name, const glm::mat4& matrix);

    void setVec3(const std::string& name, const glm::vec3& value) {
        glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
    }

    void setFloat(const std::string& name, float value) {
        glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
    }


    void setInt(const std::string& name, int value) {
        glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
    }

    void update(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override {
        setViewMatrix(viewMatrix);
        setProjectionMatrix(projectionMatrix);
    }

    void updateLights(const std::vector<Light*>& lights, const glm::vec3& viewPos);
};

#endif 
