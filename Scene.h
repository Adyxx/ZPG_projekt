#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <functional>
#include "DrawableObject.h"

class Scene {
private:
    std::vector<DrawableObject*> objects;

    std::function<void(float)> updateFunc;

    std::vector<Light*> lights;


public:   
    void render(float time);  
    void addObject(DrawableObject* object);
    ~Scene();

    void addLight(Light* light) {
        lights.push_back(light);
    }

    const std::vector<Light*>& getLights() const {
        return lights;
    }

    void updateLights(ShaderProgram* shader, const glm::vec3& cameraPosition) {
        shader->updateLights(lights, cameraPosition);
    }

    DrawableObject* getObjectByID(GLuint id);
    void removeObject(DrawableObject* object);


};

#endif
