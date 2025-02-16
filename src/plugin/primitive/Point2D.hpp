#pragma once

#include "Primitive2D.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Point2D : public Primitive2D {
public:
    Point2D(glm::vec2 _position, ofColor _color, float _size) : Primitive2D(_position, _color) { size = _size; }

    void draw() override;

    float size;
};

} // namespace plugin::primitive
