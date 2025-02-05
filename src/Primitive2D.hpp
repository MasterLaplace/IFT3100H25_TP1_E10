#pragma once

#include "ofMain.h"

class Primitive2D {
public:
    Primitive2D(glm::vec2 _position, ofColor _color)
    {
        position = _position;
        color = _color;
    }

    glm::vec2 position;
    ofColor color;
};
