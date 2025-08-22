
#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include "Texture.h"

class Material {
private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

public:
    Material(const glm::vec3& ambient = glm::vec3(0.2f),
        const glm::vec3& diffuse = glm::vec3(0.8f),
        const glm::vec3& specular = glm::vec3(1.0f),
        float shininess = 32.0f,
        Texture* texture = nullptr)
        : ambient(ambient), diffuse(diffuse), specular(specular),
        shininess(shininess) {}

    const glm::vec3& getAmbient() const { return ambient; }
    const glm::vec3& getDiffuse() const { return diffuse; }
    const glm::vec3& getSpecular() const { return specular; }
    float getShininess() const { return shininess; }
    void setAmbient(const glm::vec3& ambient) { this->ambient = ambient; }
    void setDiffuse(const glm::vec3& diffuse) { this->diffuse = diffuse; }
    void setSpecular(const glm::vec3& specular) { this->specular = specular; }
    void setShininess(float shininess) { this->shininess = shininess; }

    static const Material RedPlastic;
    static const Material Grass;
    static const Material Leaves;
    static const Material UseTexture;
};

#endif



