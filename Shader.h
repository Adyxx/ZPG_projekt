#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera; 

class Shader {
public:
    Shader(GLenum type, const std::string& source);
    GLuint getShaderID() const;
    void setMatrix(const std::string& name, const glm::mat4& matrix); 
    void setCamera(Camera* camera); 
    void use() const;  

    ~Shader();

private:
    GLuint shaderID;
    GLuint programID; 
    Camera* m_camera;  

    void checkCompileErrors(GLuint shader, std::string type);
};

#endif 
