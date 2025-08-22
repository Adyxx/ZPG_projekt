#include "Model.h"

Model::Model(const float* vertexData, size_t vertexCount, bool hasUV)
    : shaderIndex(0), material(nullptr), hasUV(hasUV) {

    numVertices = hasUV ? vertexCount / 8 : vertexCount / 6;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertexData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (hasUV ? 8 : 6) * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (hasUV ? 8 : 6) * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    if (hasUV) {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Model::setShaderIndex(int index) {
    shaderIndex = index;
}

void Model::draw(const glm::mat4& transformMatrix, const std::vector<Texture*>& textures) {
    ShaderProgram* shaderProgram = ShaderProgram::getShaderByIndex(shaderIndex);
    if (shaderProgram) {
        shaderProgram->use();

        GLint modelLoc = glGetUniformLocation(shaderProgram->getProgramID(), "modelMatrix");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &transformMatrix[0][0]);

        if (material) {
            GLint ambientLoc = glGetUniformLocation(shaderProgram->getProgramID(), "material.ambient");
            GLint diffuseLoc = glGetUniformLocation(shaderProgram->getProgramID(), "material.diffuse");
            GLint specularLoc = glGetUniformLocation(shaderProgram->getProgramID(), "material.specular");
            GLint shininessLoc = glGetUniformLocation(shaderProgram->getProgramID(), "material.shininess");

            glUniform3fv(ambientLoc, 1, glm::value_ptr(material->getAmbient()));
            glUniform3fv(diffuseLoc, 1, glm::value_ptr(material->getDiffuse()));
            glUniform3fv(specularLoc, 1, glm::value_ptr(material->getSpecular()));
            glUniform1f(shininessLoc, material->getShininess());
        }

        for (size_t i = 0; i < textures.size(); ++i) {
            if (textures[i]) {
                glActiveTexture(GL_TEXTURE0 + static_cast<GLint>(i));
                glBindTexture(GL_TEXTURE_2D, textures[i]->getID());
                std::string uniformName = "textureDiffuse" + std::to_string(i);
                GLint textureLoc = glGetUniformLocation(shaderProgram->getProgramID(), uniformName.c_str());
                glUniform1i(textureLoc, static_cast<GLint>(i));
            }
        }

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, numVertices);

        glUseProgram(0);
        glBindVertexArray(0);
    }
}


Model::~Model() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


Model::Model(const std::string& filePath)
    : shaderIndex(0), material(nullptr), hasUV(true) { 
    loadFromFile(filePath);
}


void Model::loadFromFile(const std::string& filePath) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filePath,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        std::cerr << "Assimp Error: " << importer.GetErrorString() << std::endl;
        return;
    }

    const aiMesh* mesh = scene->mMeshes[0]; 

    std::vector<float> vertexData;
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        vertexData.push_back(mesh->mVertices[i].x);
        vertexData.push_back(mesh->mVertices[i].y);
        vertexData.push_back(mesh->mVertices[i].z);

        if (mesh->HasNormals()) {
            vertexData.push_back(mesh->mNormals[i].x);
            vertexData.push_back(mesh->mNormals[i].y);
            vertexData.push_back(mesh->mNormals[i].z);
        }

        if (mesh->mTextureCoords[0]) {
            vertexData.push_back(mesh->mTextureCoords[0][i].x);
            vertexData.push_back(mesh->mTextureCoords[0][i].y);
        }
        else {
            vertexData.push_back(0.0f);
            vertexData.push_back(0.0f);
        }
    }

    numVertices = vertexData.size() / (hasUV ? 8 : 6);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (hasUV ? 8 : 6) * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (hasUV ? 8 : 6) * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    if (hasUV) {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

