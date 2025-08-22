#ifndef DYNAMIC_BEZIER_ROTATE_H
#define DYNAMIC_BEZIER_ROTATE_H

#include "DynamicTransform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class DynamicBezierRotate : public DynamicTransform {
private:
    glm::vec3 axis;
    float startAngle, endAngle;  
    float duration; 
    float elapsedTime; 

public:

    DynamicBezierRotate(glm::vec3 axis, float startAngle, float endAngle, float duration);

    void apply(glm::mat4& matrix) override;
    void apply(glm::mat4& cumulativeTransform, float time) override;
};

#endif
