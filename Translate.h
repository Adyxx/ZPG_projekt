#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "Transform.h"
#include <iostream>

class Translate : public Transform {
private:
    glm::vec3 translation;

public:
    Translate(const glm::vec3& translation);
    void apply(glm::mat4& modelMatrix) override;
};

#endif
