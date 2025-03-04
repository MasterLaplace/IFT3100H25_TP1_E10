#pragma once

#include "Primitive2D.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Point2D : public Primitive2D {
public:
    Point2D(Primitive2DParams params, float _size);
    ~Point2D() override = default;

    void draw() override;
    bool isInside(glm::vec2 *point) override;

    float size;
};

} // namespace plugin::primitive
