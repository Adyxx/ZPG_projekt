#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* model) : model(model) {}

void DrawableObject::addTransformation(Transform* transform) {
    staticTransformations.push_back(transform);
}

void DrawableObject::addDynamicTransformation(DynamicTransform* transform) {
    dynamicTransformations.push_back(transform);
}

void DrawableObject::setTexture(Texture* texture) {
    textures.clear();
    textures.push_back(texture);
}

void DrawableObject::addTexture(Texture* texture) {
    textures.push_back(texture);
}

void DrawableObject::draw(float time) {
    glm::mat4 cumulativeTransform = glm::mat4(1.0f);

    for (Transform* transform : staticTransformations) {
        transform->apply(cumulativeTransform);
    }

    for (DynamicTransform* transform : dynamicTransformations) {
        transform->apply(cumulativeTransform, time);
    }

    model->draw(cumulativeTransform, textures);
}

DrawableObject::~DrawableObject() {
    for (Texture* texture : textures) {
        delete texture;
    }
    delete model;
}
