#pragma once

#include "ofMain.h"

namespace plugin::primitive {

struct PrimitiveParams {
    glm::vec3 position;
    float outlineWidth;
    bool isFilled;
    ofColor fillColor;
    ofColor outlineColor;
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
