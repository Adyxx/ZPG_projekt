#ifndef SKYBOX_H
#define SKYBOX_H

#include <GL/glew.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>

class Skybox {
public:
    Skybox(const std::vector<std::string>& faces);
    void draw(GLuint shaderProgram, const glm::mat4& view, const glm::mat4& projection);

private:
    GLuint VAO, VBO, textureID;
    GLuint loadCubemap(const std::vector<std::string>& faces);

    ~Skybox();
};


#endif