#pragma once

#include "Primitive.hpp"
#include "ofMain.h"
#include <vector>

namespace plugin::primitive {

class Polygon : public Primitive {
public:
    Polygon(PrimitiveParams params, std::vector<glm::vec2> _points);
    ~Polygon() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

    std::vector<glm::vec2> points;

private:
    void drawFill();
    void drawOutline();
};

} // namespace plugin::primitive
