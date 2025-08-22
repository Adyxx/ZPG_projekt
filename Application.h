#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <chrono>

#include "Rotate.h"
#include "Scale.h"
#include "SceneFactory.h"
#include "Camera.h"
#include "Light.h"


class Application {
private:
    GLFWwindow* window;
    Scene* currentScene;
    bool spacePressed;
    int currentSceneId;

    Camera* camera;
    std::vector<Light*> lights;

    double lastX, lastY;
    bool firstMouse = true;
    float yaw = -90.0f;
    float pitch = 0.0f;


    float lastTreeTime;
public:
    Application();

    static void error_callback(int error, const char* description);

    bool init();
    void switchScene();

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    void run();

    GLFWwindow* getWindow() const;

    ~Application();


    void moveLight(float deltaTime);

    static void resize_callback(GLFWwindow* window, int width, int height);

    void updateFlashlight(const glm::vec3& cameraPos, const glm::vec3& cameraDir);

};

#endif
