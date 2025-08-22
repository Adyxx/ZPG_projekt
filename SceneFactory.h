#ifndef SCENE_FACTORY_H
#define SCENE_FACTORY_H

#include "Scene.h"
#include "Light.h"
#include <vector>
#include "Skybox.h"

class SceneFactory {
public:
    static Scene* createScene(int sceneType);
    static void updateFlashlight(Scene* scene, const glm::vec3& cameraPos, const glm::vec3& cameraDir);
    static void addTreeToScene(Scene* scene, const glm::vec3& position);

private:
    static void createLights(Scene* scene, int sceneType);


};

#endif
