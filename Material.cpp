#include "Material.h"

const Material Material::RedPlastic(
    glm::vec3(0.3f, 0.0f, 0.0f),
    glm::vec3(0.6f, 0.0f, 0.0f),
    glm::vec3(0.8f, 0.6f, 0.6f),
    32.0f
);

const Material Material::Grass(
    glm::vec3(0.0f, 0.2f, 0.0f),
    glm::vec3(0.2f, 0.6f, 0.2f),
    glm::vec3(0.1f, 0.2f, 0.1f)
);

const Material Material::Leaves(
    glm::vec3(0.0f, 0.1f, 0.0f),
    glm::vec3(0.3f, 0.5f, 0.2f),
    glm::vec3(0.1f, 0.3f, 0.1f),
    16.0f
);

const Material Material::UseTexture(
    glm::vec3(1.0f, 1.0f, 1.0f), 
    glm::vec3(1.0f, 1.0f, 1.0f), 
    glm::vec3(1.0f, 1.0f, 1.0f), 
    32.0f
);
