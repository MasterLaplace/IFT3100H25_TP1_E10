#pragma once

#include "Primitive2D.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Ellipse : public Primitive2D {
public:
    Ellipse(Primitive2DParams params, glm::vec2 _radius);
    ~Ellipse() override = default;

    void draw() override;
    bool isInside(glm::vec2 *point) override;

    glm::vec2 radius;
private:
    void drawFill();
    void drawOutline();
};

} // namespace plugin::primitive
