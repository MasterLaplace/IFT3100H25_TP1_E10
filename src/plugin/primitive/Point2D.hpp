#pragma once

#include "Primitive.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Point2D : public Primitive {
public:
    Point2D(PrimitiveParams params, float _size);
    Point2D(const Point2D &other) = default;
    Point2D(Point2D &&other) = default;
    ~Point2D() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

    std::shared_ptr<Primitive> clone() const override { return std::make_shared<Point2D>(*this); }

    float size;
};

} // namespace plugin::primitive
