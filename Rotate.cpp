#include "Rotate.h"

Rotate::Rotate(float angle, const glm::vec3& axis) : angle(angle), axis(axis) {}

void Rotate::apply(glm::mat4& modelMatrix) {
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis); 
}
