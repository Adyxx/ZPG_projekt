#ifndef TEXTURE_H
#define TEXTURE_H



#include <string>
#include <GL/glew.h>
#include <SOIL.h>
#include <iostream>



class Texture {
private:
    GLuint textureID;

public:
    Texture(const std::string& filePath) {
        
        textureID = SOIL_load_OGL_texture(
            filePath.c_str(),
            SOIL_LOAD_RGBA,
            SOIL_CREATE_NEW_ID,
            0
        );
        
        if (textureID == 0) {
            std::cerr << "Error loading texture: " << filePath << std::endl;
            std::cerr << "SOIL Error: " << SOIL_last_result() << std::endl;
        }
        else {
            std::cout << "Successfully loaded texture: " << filePath << ", ID: " << textureID << std::endl;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLuint getID() const {
        if (textureID == 0) {
            std::cerr << "Warning: Attempting to access invalid texture ID" << std::endl;
        }
        return textureID;
    }

    void bind(GLuint unit) const {
        if (textureID == 0) {
            std::cerr << "Error: Attempting to bind an invalid texture" << std::endl;
            return;
        }
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
    ~Texture() {
        glDeleteTextures(1, &textureID);
    }




};

#endif
