#pragma once

#include "Primitive2D.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Line2D : public Primitive2D {
public:
    Line2D(glm::vec2 _position, glm::vec2 _endPosition, ofColor _color, float _strokeWidth);

    void draw() override;
    bool isInside(glm::vec2 *point) override;

    glm::vec2 startPosition;
    glm::vec2 endPosition;
    float strokeWidth;
};

} // namespace plugin::primitive
