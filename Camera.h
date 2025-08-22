#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Subject.h"

class Camera : public Subject {
public:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
    float fov, aspectRatio, nearClip, farClip;

    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov, float aspectRatio, float nearClip, float farClip);

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    glm::vec3 getPosition() const;

    void updateDirection(float alpha, float fi);

    void moveForward(float speed);
    void moveBackward(float speed);
    void moveLeft(float speed);
    void moveRight(float speed);

    void setAspectRatio(float newAspectRatio);

    glm::vec3 unProject(const glm::vec3& screenPos);
};

#endif