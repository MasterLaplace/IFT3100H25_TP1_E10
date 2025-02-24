#pragma once

#include "Primitive2D.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Rectangle : public Primitive2D {
public:
    Rectangle(glm::vec2 _position, ofColor _color, glm::vec2 _dimensions) : Primitive2D(_position, _color)
    {
        dimensions = _dimensions;
    }

    void draw() override;
    bool isInside(glm::vec2* point) override;

    glm::vec2 dimensions;
};

} // namespace plugin::primitive
