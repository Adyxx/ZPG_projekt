#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float aspectRatio, float nearClip, float farClip)
    : position(position), target(target), up(up), fov(fov), aspectRatio(aspectRatio), nearClip(nearClip), farClip(farClip) {}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + target, up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
}

void Camera::moveForward(float speed) {
    position += target * speed;
    notifyObservers(getViewMatrix(), getProjectionMatrix()); 
}

void Camera::moveBackward(float speed) {
    position -= target * speed;
    notifyObservers(getViewMatrix(), getProjectionMatrix()); 
}

void Camera::moveLeft(float speed) {
    glm::vec3 left = glm::normalize(glm::cross(up, target));
    position += left * speed;
    notifyObservers(getViewMatrix(), getProjectionMatrix()); 
}

void Camera::moveRight(float speed) {
    glm::vec3 right = glm::normalize(glm::cross(target, up));
    position += right * speed;
    notifyObservers(getViewMatrix(), getProjectionMatrix()); 
}

void Camera::updateDirection(float alpha, float fi) {
    target.x = sin(alpha) * cos(fi);
    target.z = sin(alpha) * sin(fi);
    target.y = cos(alpha);
    notifyObservers(getViewMatrix(), getProjectionMatrix()); 
}


glm::vec3 Camera::getPosition() const {
    return position;
}

void Camera::setAspectRatio(float newAspectRatio) {
    aspectRatio = newAspectRatio;
    notifyObservers(getViewMatrix(), getProjectionMatrix());
}


glm::vec3 Camera::unProject(const glm::vec3& screenPos) {
    glm::mat4 inverseProjection = glm::inverse(getProjectionMatrix());
    glm::mat4 inverseView = glm::inverse(getViewMatrix());

    glm::vec4 eyeCoords = inverseProjection * glm::vec4(screenPos, 1.0f);
    eyeCoords /= eyeCoords.w;

    glm::vec4 worldCoords = inverseView * eyeCoords;

    return glm::vec3(worldCoords);
}
