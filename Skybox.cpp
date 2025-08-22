
#include "Skybox.h"
#include <iostream>
#include <SOIL.h>
#include <glm/gtc/type_ptr.hpp>


Skybox::Skybox(const std::vector<std::string>& faces) {
    float skyboxVertices[] = {
        -100.0f,  100.0f, -100.0f,  -100.0f, -100.0f, -100.0f,   100.0f, -100.0f, -100.0f,
         100.0f, -100.0f, -100.0f,   100.0f,  100.0f, -100.0f,  -100.0f,  100.0f, -100.0f,

        -100.0f, -100.0f,  100.0f,  -100.0f, -100.0f, -100.0f,  -100.0f,  100.0f, -100.0f,
        -100.0f,  100.0f, -100.0f,  -100.0f,  100.0f,  100.0f,  -100.0f, -100.0f,  100.0f,

         100.0f, -100.0f, -100.0f,   100.0f, -100.0f,  100.0f,   100.0f,  100.0f,  100.0f,
         100.0f,  100.0f,  100.0f,   100.0f,  100.0f, -100.0f,   100.0f, -100.0f, -100.0f,

        -100.0f, -100.0f,  100.0f,  -100.0f,  100.0f,  100.0f,   100.0f,  100.0f,  100.0f,
         100.0f,  100.0f,  100.0f,   100.0f, -100.0f,  100.0f,  -100.0f, -100.0f,  100.0f,

        -100.0f,  100.0f, -100.0f,   100.0f,  100.0f, -100.0f,   100.0f,  100.0f,  100.0f,
         100.0f,  100.0f,  100.0f,  -100.0f,  100.0f,  100.0f,  -100.0f,  100.0f, -100.0f,

        -100.0f, -100.0f, -100.0f,  -100.0f, -100.0f,  100.0f,   100.0f, -100.0f, -100.0f,
         100.0f, -100.0f, -100.0f,  -100.0f, -100.0f,  100.0f,   100.0f, -100.0f,  100.0f
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);

    textureID = loadCubemap(faces);
}
void Skybox::draw(GLuint shaderProgram, const glm::mat4& view, const glm::mat4& projection) {
    glDepthFunc(GL_LEQUAL); 

    glUseProgram(shaderProgram);


    glm::mat4 viewNoTranslate = glm::mat4(glm::mat3(view)); 
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewNoTranslate));


    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewNoTranslate));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);


    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);


}



GLuint Skybox::loadCubemap(const std::vector<std::string>& faces) {
    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

    int width, height, channels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = SOIL_load_image(faces[i].c_str(), &width, &height, &channels, SOIL_LOAD_RGB);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            SOIL_free_image_data(data);
        }
        else {
            std::cerr << "Failed to load cubemap texture: " << faces[i] << std::endl;
        }
    }


    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


    return texID;
}


