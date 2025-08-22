#include "Scale.h"

Scale::Scale(const glm::vec3& scaleFactor) : scaleFactor(scaleFactor) {}

void Scale::apply(glm::mat4& modelMatrix) {
    modelMatrix = glm::scale(modelMatrix, scaleFactor);  
}
