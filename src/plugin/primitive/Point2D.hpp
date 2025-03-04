#pragma once

#include "Primitive.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Point2D : public Primitive {
public:
    Point2D(PrimitiveParams params, float _size);
    ~Point2D() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

    float size;
};

} // namespace plugin::primitive
