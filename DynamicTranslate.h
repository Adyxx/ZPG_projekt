#ifndef DYNAMIC_TRANSLATE_H
#define DYNAMIC_TRANSLATE_H

#include "DynamicTransform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class DynamicTranslation : public DynamicTransform {
private:
    glm::vec3 startPosition; 
    glm::vec3 endPosition;
    float duration; 
    float elapsedTime;

public:
    DynamicTranslation(glm::vec3 startPosition, glm::vec3 endPosition, float duration)
        : startPosition(startPosition), endPosition(endPosition), duration(duration), elapsedTime(0.0f) {}

    void apply(glm::mat4& matrix) override {}


    void apply(glm::mat4& cumulativeTransform, float time) override {
        elapsedTime += time;

        if (elapsedTime >= duration) {
            elapsedTime = duration; 
        }

        glm::vec3 translation = glm::mix(startPosition, endPosition, elapsedTime / duration);

        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), translation);
        cumulativeTransform *= translationMatrix;
    }
};


#endif