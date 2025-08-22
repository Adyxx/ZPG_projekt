#ifndef LIGHT_H 
#define LIGHT_H

#include <glm/glm.hpp>
#include "Subject.h"

class Light : public Subject {
public:
    enum LightType { POINT = 0, DIRECTIONAL = 1, SPOTLIGHT = 2 }; 

    LightType type;         
    glm::vec3 position;      
    glm::vec3 direction;     
    glm::vec3 color;
    float intensity;

    float constant;
    float linear;
    float quadratic;

    float innerCutoff;
    float outerCutoff;

    Light(LightType t, const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& col, float intens,
        float constAtt = 1.0f, float linAtt = 0.09f, float quadAtt = 0.032f,
        float innerCut = glm::cos(glm::radians(12.5f)), float outerCut = glm::cos(glm::radians(17.5f)))
        : type(t), position(pos), direction(dir), color(col), intensity(intens),
        constant(constAtt), linear(linAtt), quadratic(quadAtt),
        innerCutoff(innerCut), outerCutoff(outerCut) {}

    void setPosition(const glm::vec3& newPosition) {
        position = newPosition;
        //notifyObservers();
    }
    void setDirection(const glm::vec3& newDirection) {
        direction = newDirection;
        //notifyObservers();
    }

    void setIntensity(float i) {
        intensity = i;
    }
};

#endif
