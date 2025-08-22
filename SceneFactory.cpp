
#include "SceneFactory.h"
#include "models/sphere.h"  

#include "models/tree.h"
#include "models/bushes.h" 
#include "models/skycube.h" 

#include "DrawableObject.h"
   
#include <ctime>

#include "models/triangle.h" 
#include "models/plain.h"

void SceneFactory::addTreeToScene(Scene* scene, const glm::vec3& position) {

   // Model* treeModel = new Model("C:/Users/Doma/Desktop/ZPG/ukol1/cv02/cv02/Models/tree.obj");
    Model* treeModel = new Model(tree, 92814 * 6, false);
    treeModel->setShaderIndex(2);

    treeModel->setMaterial(new Material(Material::UseTexture));

    DrawableObject* tree = new DrawableObject(treeModel);

    tree->addTransformation(new Translate(position));
    tree->addTransformation(new Scale(glm::vec3(0.2f)));

   // Texture* treeTexture = new Texture("textures/tree.png");
   // tree->setTexture(treeTexture);

    scene->addObject(tree);
    
}

void SceneFactory::updateFlashlight(Scene* scene, const glm::vec3& cameraPos, const glm::vec3& cameraDir) {
    for (int i = 0; i < ShaderProgram::getShadersCount(); ++i) {
        ShaderProgram* shader = ShaderProgram::getShaderByIndex(i);
        if (shader) {
            shader->use();
            shader->setVec3("flashlightPos", cameraPos);
            shader->setVec3("flashlightDir", cameraDir);
            shader->setFloat("flashlightInnerCutoff", cos(glm::radians(12.5f)));
            shader->setFloat("flashlightOuterCutoff", cos(glm::radians(17.5f)));
            shader->setVec3("flashlightColor", glm::vec3(1.0f, 1.0f, 1.0f));
            shader->setFloat("flashlightIntensity", 1.0f);
            glUseProgram(0);
        }
    }
}

void SceneFactory::createLights(Scene* scene, int sceneType) {
    std::vector<Light*> lights;

    if (sceneType == 3) {

    }
    else {
        
        lights.push_back(new Light(
            Light::POINT,
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(0.0f),           
            glm::vec3(1.0f, 1.0f, 1.0f), 
            1.0f, 1.0f, 0.09f, 0.032f  
        ));
        
        lights.push_back(new Light(
            Light::SPOTLIGHT,
            glm::vec3(2.0f, 2.0f, 2.0f), 
            glm::vec3(-0.5f, -1.0f, -0.5f), 
            glm::vec3(1.0f, 1.0f, 1.0f),
            1.0f, 1.0f, 0.09f, 0.032f,  
            glm::cos(glm::radians(12.5f)), 
            glm::cos(glm::radians(17.5f))  
        ));
        

    }

    for (Light* light : lights) {
        scene->addLight(light);
    }
    cout << lights.size() << endl;

}

Scene* SceneFactory::createScene(int sceneType) {
    Scene* scene = new Scene();

    if (sceneType == 1) {
        // Test triangle
        
        Model* triangleModel = new Model(plain, 18, false);
        triangleModel->setShaderIndex(0);
        DrawableObject* triangle = new DrawableObject(triangleModel);

        scene->addObject(triangle);
        
        
    }
    else if (sceneType == 2) {
        // Forest
        srand(static_cast<unsigned int>(time(0)));



        Model* objModel = new Model("C:/Users/Doma/Desktop/ZPG/ukol1/cv02/cv02/Models/house.obj");
        objModel->setShaderIndex(2);

        objModel->setMaterial(new Material(Material::UseTexture));

        DrawableObject* obj = new DrawableObject(objModel);
        obj->addTransformation(new Scale(glm::vec3(0.5f)));
        obj->addTransformation(new Translate(glm::vec3(2.0f, 0.0f, -5.0f)));

        Texture* houseTexture = new Texture("textures/house.png");

        obj->setTexture(houseTexture);

        scene->addObject(obj);



        Model* objModelLogin = new Model("C:/Users/Doma/Desktop/ZPG/ukol1/cv02/cv02/Models/login.obj");
        objModelLogin->setShaderIndex(2);

        objModelLogin->setMaterial(new Material(Material::RedPlastic));

        DrawableObject* objLogin = new DrawableObject(objModelLogin);
        objLogin->addTransformation(new Translate(glm::vec3(6.0f, 4.0f, -7.0f)));
        objLogin->addTransformation(new Scale(glm::vec3(0.05f)));

        scene->addObject(objLogin);

        Model* plainModel = new Model(plain, 48, true);
        plainModel->setShaderIndex(2);
        plainModel->setMaterial(new Material(Material::Grass));

        DrawableObject* plain = new DrawableObject(plainModel);
        plain->addTransformation(new Scale(glm::vec3(10.0f)));

        Texture* grassTexture = new Texture("textures/2.png");
        plain->setTexture(grassTexture);

        scene->addObject(plain);
        

        for (int i = 0; i < 50; ++i) {

            Model* treeModel = new Model("C:/Users/Doma/Desktop/ZPG/ukol1/cv02/cv02/Models/tree.obj");
            // Model* treeModel = new Model(tree, 92814 * 6, false);
            treeModel->setShaderIndex(2);

            // treeModel->setMaterial(new Material(Material::Leaves));
            treeModel->setMaterial(new Material(Material::UseTexture));


            DrawableObject* tree = new DrawableObject(treeModel);

            float randomX = static_cast<float>(rand()) / RAND_MAX * 15.0f - 5.0f;
            float randomZ = static_cast<float>(rand()) / RAND_MAX * 15.0f - 5.0f;

            tree->addTransformation(new Translate(glm::vec3(randomX, 0.0f, randomZ)));
            tree->addTransformation(new Scale(glm::vec3(0.03f)));

            Texture* treeTexture = new Texture("textures/tree.png");

            tree->setTexture(treeTexture);

            //// EXAMPLE BEZIER TRANSFORMATION ////
            
            glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 1.0f); 
            float startAngle = 0.0f;                             
            float endAngle = 3600.0f;                            
            float duration = 50.0f;                             
            DynamicBezierRotate* bezierRotate = new DynamicBezierRotate(rotationAxis, startAngle, endAngle, duration);

            tree->addDynamicTransformation(bezierRotate);

            glm::vec3 startPos(0.0f, 0.0f, 0.0f);
            glm::vec3 control1(100.0f, 100.0f, 100.0f);
            glm::vec3 control2(-100.0f, -100.0f, 70.0f);
            glm::vec3 endPos(0.0f, 0.0f, 0.0f);
            duration = 50.0f;
            DynamicBezierTranslate* bezierTranslate = new DynamicBezierTranslate(startPos, endPos, control1, control2, duration);

            tree->addDynamicTransformation(bezierTranslate);
            
            scene->addObject(tree);
        }

        for (int i = 0; i < 500; ++i) {
            Model* bushModel = new Model(bushes, sizeof(bushes) / sizeof(bushes[0]) / 3, false);
            bushModel->setShaderIndex(2);

            DrawableObject* bush = new DrawableObject(bushModel);

            float randomX = static_cast<float>(rand()) / RAND_MAX * 20.0f - 10.0f;
            float randomZ = static_cast<float>(rand()) / RAND_MAX * 20.0f - 10.0f;

            bush->addTransformation(new Translate(glm::vec3(randomX, 0.0f, randomZ)));
            bush->addTransformation(new Scale(glm::vec3(0.1f)));
            scene->addObject(bush);
        }

    }
    else if (sceneType == 3) {


        // Forest with fl
        srand(static_cast<unsigned int>(time(0)));

        Model* plainModel = new Model(plain, 48, true);
        plainModel->setShaderIndex(4);
        plainModel->setMaterial(new Material(Material::Grass));

        DrawableObject* plain = new DrawableObject(plainModel);
        plain->addTransformation(new Scale(glm::vec3(10.0f)));

        Texture* grassTexture = new Texture("textures/2.png");
        plain->setTexture(grassTexture);

        scene->addObject(plain);

        for (int i = 0; i < 50; ++i) {

            //Model* treeModel = new Model("C:/Users/Doma/Desktop/ZPG/ukol1/cv02/cv02/Models/tree.obj");
             Model* treeModel = new Model(tree, 92814 * 6, false);
             treeModel->setShaderIndex(4);

             treeModel->setMaterial(new Material(Material::Leaves));
            //treeModel->setMaterial(new Material(Material::UseTexture));


            DrawableObject* tree = new DrawableObject(treeModel);

            float randomX = static_cast<float>(rand()) / RAND_MAX * 15.0f - 5.0f;
            float randomZ = static_cast<float>(rand()) / RAND_MAX * 15.0f - 5.0f;

            tree->addTransformation(new Translate(glm::vec3(randomX, 0.0f, randomZ)));
            tree->addTransformation(new Scale(glm::vec3(0.2f)));

           // Texture* treeTexture = new Texture("textures/tree.png");

           // tree->setTexture(treeTexture);
            scene->addObject(tree);
        }

        for (int i = 0; i < 500; ++i) {
            Model* bushModel = new Model(bushes, sizeof(bushes) / sizeof(bushes[0]) / 3, false);
            bushModel->setShaderIndex(4);

            DrawableObject* bush = new DrawableObject(bushModel);

            float randomX = static_cast<float>(rand()) / RAND_MAX * 20.0f - 10.0f;
            float randomZ = static_cast<float>(rand()) / RAND_MAX * 20.0f - 10.0f;

            bush->addTransformation(new Translate(glm::vec3(randomX, 0.0f, randomZ)));
            bush->addTransformation(new Scale(glm::vec3(0.1f)));
            scene->addObject(bush);
        }

    }
    else if (sceneType == 4) {
        // 4 spheres, phong shading
        for (int i = 0; i < 4; ++i) {
            Model* sphereModel = new Model(sphere, 2880 * 6, false);
            sphereModel->setShaderIndex(2);

            DrawableObject* sphere = new DrawableObject(sphereModel);

            float X = (i == 0) ? 2.0f : (i == 1) ? 0.0f : (i == 2) ? -2.0f : 0.0f;
            float Y = (i == 3) ? 2.0f : (i == 1) ? -2.0f : 0.0f;
            sphereModel->setMaterial(new Material(Material::RedPlastic));
            sphere->addTransformation(new Translate(glm::vec3(X, Y, 0.0f)));

            Texture* plainTexture = new Texture("textures/3.png");

            sphere->setTexture(plainTexture);


            scene->addObject(sphere);
        }

    }



    createLights(scene, sceneType);

    return scene;
}

