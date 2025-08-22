#include "Application.h"
#include <iostream>
#include <fstream>

Application::Application()
    : window(nullptr), currentScene(nullptr), spacePressed(false),
    currentSceneId(1), camera(nullptr), lights(),
    lastX(0.0), lastY(0.0), firstMouse(true), yaw(-90.0f), pitch(0.0f),
    lastTreeTime(0.0f) {
}


void Application::error_callback(int error, const char* description) {
    fputs(description, stderr);
}


void Application::resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    app->camera->setAspectRatio(aspectRatio);

    for (int i = 0; i < ShaderProgram::getShadersCount(); ++i) {
        ShaderProgram* shader = ShaderProgram::getShaderByIndex(i);
        if (shader) {
            shader->setProjectionMatrix(app->camera->getProjectionMatrix());
        }
    }
}


bool Application::init() {

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return false;
    }
    window = glfwCreateWindow(1200, 900, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;
    glewInit();
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    camera = new Camera(glm::vec3(0.0f, 0.1f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 60.0f, 4.0f / 3.0f, 0.1f, 100.0f);

    glfwSetFramebufferSizeCallback(window, resize_callback);

        ShaderProgram* staticShader = new ShaderProgram();
        staticShader->loadShaders("shaders/vertexFileLMScv5.txt", "shaders/fragmentFileStatic.txt");
        ShaderProgram* lambertShader = new ShaderProgram();
        lambertShader->loadShaders("shaders/vertexFileLMScv5.txt", "shaders/fragmentFileLambert.txt");
        ShaderProgram* phongShader = new ShaderProgram();
        phongShader->loadShaders("shaders/vertexFileLMScv5.txt", "shaders/fragmentFilePhong.txt");
        ShaderProgram* blinnPhongShader = new ShaderProgram();
        blinnPhongShader->loadShaders("shaders/vertexFileLMScv5.txt", "shaders/fragmentFileBlinnPhong.txt");
        ShaderProgram* flashlightShader = new ShaderProgram();
        flashlightShader->loadShaders("shaders/vertexFileLMScv5.txt", "shaders/fragmentFilePhongFlashlight.txt");

        ShaderProgram* SkyShader = new ShaderProgram();
        SkyShader->loadShaders("shaders/skyboxVertex.txt", "shaders/skyboxFragment.txt");


        ShaderProgram::addShader(staticShader);
        ShaderProgram::addShader(lambertShader);
        ShaderProgram::addShader(phongShader);
        ShaderProgram::addShader(blinnPhongShader);
        ShaderProgram::addShader(flashlightShader);

        ShaderProgram::addShader(SkyShader);


    for (int i = 0; i < ShaderProgram::getShadersCount(); ++i) {
        ShaderProgram* shader = ShaderProgram::getShaderByIndex(i);
        if (shader) {
            shader->setViewMatrix(camera->getViewMatrix());
            shader->setProjectionMatrix(camera->getProjectionMatrix());
            camera->addObserver(shader);
        }
    }

    return true;
}


void Application::switchScene() {
    currentSceneId = (currentSceneId % 4) + 1;
    if (currentScene) {
        delete currentScene;
        currentScene = nullptr;
    }
    currentScene = SceneFactory::createScene(currentSceneId);
    if (!currentScene) {
        std::cerr << "Failed to switch to scene ID: " << currentSceneId << std::endl;
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}


void Application::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

    float currentTime = glfwGetTime();

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && currentTime - app->lastTreeTime > 0.2f) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        float x = (2.0f * xpos) / width - 1.0f;
        float y = 1.0f - (2.0f * ypos) / height;

        GLbyte color[4];
        GLfloat depth;
        GLuint index;

        GLint newY = static_cast<GLint>(height) - static_cast<GLint>(ypos);

        glReadPixels(xpos, newY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
        glReadPixels(xpos, newY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
        glReadPixels(xpos, newY, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

        printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth % f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);

        if (static_cast<int>(index) != 00) {
            printf("xxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
            DrawableObject* clickedObject = app->currentScene->getObjectByID(index);

            if (clickedObject) {
                app->currentScene->removeObject(clickedObject);
            }
        }
        else {
            glm::vec3 screenPos(x, y, depth);
            glm::vec3 worldPos = app->camera->unProject(screenPos);

            if (app->currentScene) {
                SceneFactory::addTreeToScene(app->currentScene, worldPos);
            }
        }

        app->lastTreeTime = currentTime;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if (app->firstMouse) {
            app->lastX = xpos;
            app->lastY = ypos;
            app->firstMouse = false;
        }

        float xoffset = static_cast<float>(xpos - app->lastX);
        float yoffset = static_cast<float>(app->lastY - ypos);

        app->lastX = xpos;
        app->lastY = ypos;

        const float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        if (fabs(xoffset) > 0.1f || fabs(yoffset) > 0.1f) {
            app->yaw += xoffset;
            app->pitch -= yoffset;

            if (app->pitch > 89.0f) app->pitch = 89.0f;
            if (app->pitch < -89.0f) app->pitch = -89.0f;

            app->camera->updateDirection(glm::radians(app->pitch), glm::radians(app->yaw));
        }
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
        app->firstMouse = true;
    }
}



void Application::moveLight(float deltaTime) {
    if (!currentScene) return;

    static float angle = 0.0f;
    float radius = 5.0f;
    angle += deltaTime * 72.0f;
    if (angle > 360.0f) angle -= 360.0f;

    float lightX = radius * cos(glm::radians(angle));
    float lightZ = radius * sin(glm::radians(angle));

    glm::vec3 newLightPosition(lightX, 2.0f, lightZ);

    auto& lights = currentScene->getLights();
    if (!lights.empty()) {
        lights[0]->setPosition(newLightPosition);
    }

    for (int i = 0; i < ShaderProgram::getShadersCount(); ++i) {
        ShaderProgram* shader = ShaderProgram::getShaderByIndex(i);
        if (shader) {
            shader->updateLights(lights, camera->getPosition());
        }
    }
}



GLFWwindow* Application::getWindow() const {
    return window;
}

Application::~Application() {
    if (currentScene) delete currentScene;
    if (camera) delete camera;
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void Application::run() {
    glEnable(GL_DEPTH_TEST);

    float lastTime = glfwGetTime();
    const float cameraSpeed = 0.01f;

    
    std::vector<std::string> faces = {
        "textures/cubemap/posx.jpg",
        "textures/cubemap/negx.jpg",
        "textures/cubemap/posy.jpg",
        "textures/cubemap/negy.jpg",
        "textures/cubemap/posz.jpg",
        "textures/cubemap/negz.jpg"
    };
    Skybox* skybox = new Skybox(faces);

    ShaderProgram* skyboxShader = ShaderProgram::getShaderByIndex(ShaderProgram::getShadersCount() - 1);
        

    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spacePressed) {
            switchScene();
            spacePressed = true;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
            spacePressed = false;
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera->moveForward(cameraSpeed);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera->moveBackward(cameraSpeed);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera->moveLeft(cameraSpeed);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera->moveRight(cameraSpeed);
        

        if (currentScene) {
            currentScene->render(deltaTime);
            SceneFactory::updateFlashlight(currentScene, camera->getPosition(), camera->target);
            moveLight(deltaTime);
        }


        glm::mat4 viewMatrix = camera->getViewMatrix();
        glm::mat4 projectionMatrix = camera->getProjectionMatrix();
        
        if (skyboxShader) {
            GLuint shaderProgram = skyboxShader->getProgramID();
            skybox->draw(shaderProgram, viewMatrix, projectionMatrix);
        
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

