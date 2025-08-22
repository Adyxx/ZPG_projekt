#include "DynamicBezierTranslate.h"

DynamicBezierTranslate::DynamicBezierTranslate(glm::vec3 startPosition, glm::vec3 endPosition, glm::vec3 control1, glm::vec3 control2, float duration)
    : startPosition(startPosition), endPosition(endPosition), control1(control1), control2(control2), duration(duration), elapsedTime(0.0f) {}


void DynamicBezierTranslate::apply(glm::mat4& matrix) {
}

void DynamicBezierTranslate::apply(glm::mat4& cumulativeTransform, float time) {
    elapsedTime += time;

    if (elapsedTime >= duration) {
        elapsedTime = duration;
    }

    float t = elapsedTime / duration;

    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    glm::vec3 interpolatedPosition = uuu * startPosition + 3 * uu * t * control1 + 3 * u * tt * control2 + ttt * endPosition;

    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), interpolatedPosition);
    cumulativeTransform *= translationMatrix;
}
