#pragma once

#include "Primitive.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Rectangle : public Primitive {
public:
    Rectangle(PrimitiveParams _params, glm::vec2 _dimensions);
    ~Rectangle() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

    glm::vec2 dimensions;

private:
    void drawFill();
    void drawOutline();
};

} // namespace plugin::primitive
