#include "Translate.h"

Translate::Translate(const glm::vec3& translation) : translation(translation) {}

void Translate::apply(glm::mat4& modelMatrix) {
    modelMatrix = glm::translate(modelMatrix, translation);
}
