#pragma once

#include "Primitive2D.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Ellipse : public Primitive2D {
public:
    Ellipse(glm::vec2 _position, ofColor _color, glm::vec2 _radius) : Primitive2D(_position, _color) {
        radius = _radius;
    }

    void draw() override;

    glm::vec2 radius;
};

} // namespace plugin::primitive

