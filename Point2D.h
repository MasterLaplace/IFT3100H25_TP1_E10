#pragma once

#include "ofMain.h"
#include "Primitive2D.h"

class Point2D : public Primitive2D {
public:
    Point2D(glm::vec2 _position, ofColor _color, float _size) : 
        Primitive2D(_position, _color) { 
        size = _size; 
    }

    float size;
};