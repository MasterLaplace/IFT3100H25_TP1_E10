#pragma once

#include "Primitive.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Ellipse : public Primitive {
public:
    Ellipse(PrimitiveParams params, glm::vec2 _radius);
    ~Ellipse() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

    glm::vec2 radius;

private:
    void drawFill();
    void drawOutline();
};

} // namespace plugin::primitive
