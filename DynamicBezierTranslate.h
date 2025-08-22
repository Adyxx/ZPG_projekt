#ifndef DYNAMIC_BEZIER_TRANSLATE_H
#define DYNAMIC_BEZIER_TRANSLATE_H

#include "DynamicTransform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class DynamicBezierTranslate : public DynamicTransform {
private:
    glm::vec3 startPosition;
    glm::vec3 endPosition; 
    glm::vec3 control1; 
    glm::vec3 control2; 
    float duration;
    float elapsedTime;

public:
    DynamicBezierTranslate(glm::vec3 startPosition, glm::vec3 endPosition, glm::vec3 control1, glm::vec3 control2, float duration);

    void apply(glm::mat4& matrix) override;
    void apply(glm::mat4& cumulativeTransform, float time) override;
};

#endif
