#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

class Transform {
public:
    virtual void apply(glm::mat4& modelMatrix) = 0; 
};

#endif
