#ifndef OBSERVER_H
#define OBSERVER_H

#include <glm/glm.hpp>

class Observer {
public:
    virtual void update(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;
    virtual ~Observer() = default;
};

#endif
