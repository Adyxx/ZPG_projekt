#include "Shader.h"
#include "Camera.h"
#include <iostream>

Shader::Shader(GLenum type, const std::string& source) {
    shaderID = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        std::cerr << "ERROR: Shader compilation failed\n" << infoLog << std::endl;
    }

    programID = glCreateProgram();
    glAttachShader(programID, shaderID);
    glLinkProgram(programID);

    checkCompileErrors(programID, "PROGRAM");
}

GLuint Shader::getShaderID() const {
    return shaderID;
}

void Shader::use() const {
    glUseProgram(programID);
}

void Shader::setMatrix(const std::string& name, const glm::mat4& matrix) {
    GLint loc = glGetUniformLocation(programID, name.c_str());

    if (loc == -1) {
        std::cerr << "ERROR: Uniform " << name << " not found in shader" << std::endl;
        return; 
    }
    glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
}


void Shader::setCamera(Camera* camera) {
    m_camera = camera;
    if (m_camera) {
        setMatrix("viewMatrix", m_camera->getViewMatrix()); 
        setMatrix("projectionMatrix", m_camera->getProjectionMatrix());  
    }
}

Shader::~Shader() {
    glDeleteShader(shaderID);  
}


void Shader::checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
