#pragma once

#include "Primitive2D.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Point2D : public Primitive2D {
public:
    Point2D(glm::vec2 _position, ofColor _color, float _size);

    void draw() override;
    bool isInside(glm::vec2 *point) override;

    float size;
};

} // namespace plugin::primitive
