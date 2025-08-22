#ifndef DYNAMIC_TRANSFORM_H
#define DYNAMIC_TRANSFORM_H

#include "Transform.h"

class DynamicTransform : public Transform {
public:
    virtual void apply(glm::mat4& matrix, float time) = 0; 
};

#endif
