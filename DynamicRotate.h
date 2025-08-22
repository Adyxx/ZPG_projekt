#ifndef DYNAMIC_ROTATE_H
#define DYNAMIC_ROTATE_H

#include "DynamicTransform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class DynamicRotate : public DynamicTransform {
private:
    glm::vec3 axis;            
    float totalAngle;
    float duration;   
    float elapsedTime;

public:

    DynamicRotate(glm::vec3 axis, float totalAngle, float duration)
        : axis(axis), totalAngle(totalAngle), duration(duration), elapsedTime(0.0f) {}

    void apply(glm::mat4& matrix) override {}

    void apply(glm::mat4& cumulativeTransform, float time) override {
        elapsedTime += time;

        if (elapsedTime >= duration) {
            elapsedTime = duration; 
        }

        float angleToRotate = (totalAngle * (elapsedTime / duration)); 
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angleToRotate), axis);

        cumulativeTransform *= rotationMatrix;
    }
};



#endif
