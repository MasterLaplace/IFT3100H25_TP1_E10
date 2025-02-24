#pragma once

#include "ofMain.h"

namespace plugin::primitive {

class Primitive2D {
public:
    Primitive2D(glm::vec2 _position, ofColor _color)
    {
        position = _position;
        color = _color;
        id = nextId;
        nextId++;
    }

    virtual void draw() = 0;
    virtual bool isInside(glm::vec2* point) = 0;

    int id;
    glm::vec2 position;
    ofColor color;

private:
    static int nextId;
};

} // namespace plugin::primitive
