#pragma once

#include "Primitive2D.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Line2D : public Primitive2D {
public:
    Line2D(Primitive2DParams params, glm::vec2 _endPosition);
    ~Line2D() override = default;

    void draw() override;
    bool isInside(glm::vec2 *point) override;

    glm::vec2 startPosition;
    glm::vec2 endPosition;
};

} // namespace plugin::primitive
