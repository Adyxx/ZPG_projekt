#ifndef ROTATE_H
#define ROTATE_H

#include "Transform.h"

class Rotate : public Transform {
private:
    float angle;
    glm::vec3 axis;

public:
    Rotate(float angle, const glm::vec3& axis);
    void apply(glm::mat4& modelMatrix) override;
};

#endif
