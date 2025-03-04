#pragma once

#include "Primitive2D.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Rectangle : public Primitive2D {
public:
    Rectangle(Primitive2DParams _params, glm::vec2 _dimensions);
    ~Rectangle() override = default;

    void draw() override;
    bool isInside(glm::vec2 *point) override;

    glm::vec2 dimensions;

private:
    void drawFill();
    void drawOutline();
};

} // namespace plugin::primitive
