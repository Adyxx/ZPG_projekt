#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include <glm/glm.hpp>
#include <vector>
#include "Model.h"
#include "Scale.h"
#include "Translate.h"
#include "Rotate.h"
#include "DynamicRotate.h"
#include "DynamicTranslate.h"
#include "DynamicBezierRotate.h"
#include "DynamicBezierTranslate.h"
#include "Texture.h"

class DrawableObject {
private:
    Model* model;
    std::vector<Texture*> textures;
    std::vector<Transform*> staticTransformations;
    std::vector<DynamicTransform*> dynamicTransformations;
    GLuint id; 
public:
    DrawableObject(Model* model);

    void addTransformation(Transform* transform);
    void addDynamicTransformation(DynamicTransform* transform);

    void setTexture(Texture* texture);
    void addTexture(Texture* texture);

    void draw(float time);

    void setID(GLuint objectID) {
        id = objectID;
    }

    GLuint getID() const {
        return id;
    }


    ~DrawableObject();

};

#endif
