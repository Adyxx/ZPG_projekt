#include "Scene.h"
#include <functional> 

void Scene::addObject(DrawableObject* object) {
    objects.push_back(object);
}


void Scene::render(float time) {
    glEnable(GL_STENCIL_TEST);
    glClear(GL_STENCIL_BUFFER_BIT); 

    for (DrawableObject* obj : objects) {
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); 

        GLuint objectID = obj->getID();
        glStencilFunc(GL_ALWAYS, objectID, 0xFF);  

        obj->draw(time); 

    }
    glDisable(GL_STENCIL_TEST);
}

DrawableObject* Scene::getObjectByID(GLuint id) {
    for (DrawableObject* obj : objects) {
        if (obj->getID() == id) {
            return obj;
        }
    }
    return nullptr;  
}

void Scene::removeObject(DrawableObject* object) {
    printf("Non-Zero ID... Removing Clicked object...\n");
    auto it = std::find(objects.begin(), objects.end(), object);
    if (it != objects.end()) {
        objects.erase(it); 
        delete object;  
    }
}


Scene::~Scene() {
    for (auto light : lights) {
        delete light;
    }
    for (auto obj : objects) {
        delete obj;
    }
}

