#include "DynamicBezierRotate.h"


DynamicBezierRotate::DynamicBezierRotate(glm::vec3 axis, float startAngle, float endAngle, float duration)
    : axis(axis), startAngle(startAngle), endAngle(endAngle), duration(duration), elapsedTime(0.0f) {}


void DynamicBezierRotate::apply(glm::mat4& matrix) {

}

void DynamicBezierRotate::apply(glm::mat4& cumulativeTransform, float time) {
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

    float angle = uuu * startAngle;
    angle += 3 * uu * t * startAngle;
    angle += 3 * u * tt * endAngle;
    angle += ttt * endAngle;

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
    cumulativeTransform *= rotationMatrix;
}
