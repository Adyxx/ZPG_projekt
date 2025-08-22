
#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderProgram.h"
#include "Material.h"
#include <glm/gtc/type_ptr.hpp> 

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model {
private:
    GLuint VAO, VBO;
    int numVertices;
    int shaderIndex;
    Material* material;
    bool hasUV;

    void loadFromFile(const std::string& filePath);

public:
    Model(const float* vertexData, size_t vertexCount, bool hasUV);

    Model(const std::string& filePath);

    void setShaderIndex(int index);
    void draw(const glm::mat4& transformMatrix, const std::vector<Texture*>& textures);
    void setMaterial(Material* mat) { material = mat; }
    Material* getMaterial() const { return material; }
    ~Model();
};
#endif