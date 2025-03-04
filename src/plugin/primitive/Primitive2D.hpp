#pragma once

#include "ofMain.h"

namespace plugin::primitive {

struct Primitive2DParams {
    glm::vec2 position;
    float outlineWidth;
    bool isFilled;
    ofColor fillColor;
    ofColor outlineColor;
};

class Primitive2D {
public:
    Primitive2D(Primitive2DParams params)
    {
        position = params.position;
        outlineWidth = params.outlineWidth;
        isFilled = params.isFilled;
        outlineColor = params.outlineColor;
        fillColor = params.fillColor;
        id = nextId;
        nextId++;
    }
    virtual ~Primitive2D() = default;

    virtual void draw() = 0;
    virtual bool isInside(glm::vec2 *point) = 0;

    int id;
    string name = "Primitive2D";
    glm::vec2 position;
    
    float outlineWidth;
    bool isFilled = false;
    ofColor fillColor;
    ofColor outlineColor;

private:
    static int nextId;
};

} // namespace plugin::primitive
