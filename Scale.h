#ifndef SCALE_H
#define SCALE_H

#include "Transform.h"

class Scale : public Transform {
private:
    glm::vec3 scaleFactor;

public:
    Scale(const glm::vec3& scaleFactor);
    void apply(glm::mat4& modelMatrix) override;
};

#endif
