#pragma once

#include "Primitive2D.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Line2D : public Primitive2D {
public:
    Line2D(glm::vec2 _startPosition, glm::vec2 _endPosition, ofColor _color, float _strokeWidth)
        : Primitive2D(_startPosition, _color)
    {
        endPosition = _endPosition;
        strokeWidth = _strokeWidth;
    }

    void draw() override;

    glm::vec2 endPosition;
    float strokeWidth;
};

} // namespace plugin::primitive
