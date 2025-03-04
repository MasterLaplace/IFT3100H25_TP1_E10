#pragma once

#include "Primitive.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Line2D : public Primitive {
public:
    Line2D(PrimitiveParams params, glm::vec2 _endPosition);
    ~Line2D() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

    glm::vec2 startPosition;
    glm::vec2 endPosition;
};

} // namespace plugin::primitive
