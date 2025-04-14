#pragma once

#include "ofMain.h"

namespace plugin::primitive {

struct PrimitiveParams {
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    float outlineWidth;
    bool isFilled;
    ofColor fillColor;
    ofColor ambientColor;
    ofColor diffuseColor;
    ofColor specularColor;
    float shininess;
    ofColor outlineColor;
    std::string imageName = "";
    bool drawGizmo = false;

    PrimitiveParams()
        : outlineWidth(1.0f), isFilled(true), fillColor(ofColor::white), outlineColor(ofColor::black),
          ambientColor(ofColor::black), diffuseColor(ofColor::lightGray), specularColor(ofColor::white),
          shininess(32.0f)
    {
    }
};

class Primitive {
public:
    Primitive(const PrimitiveParams &params) : param(params) {}
    virtual ~Primitive() = default;

    virtual void draw() = 0;
    virtual bool isInside(const glm::vec3 &point) = 0;

    PrimitiveParams param;
};

} // namespace plugin::primitive
