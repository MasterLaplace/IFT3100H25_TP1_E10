#pragma once

#include "Primitive.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Line2D : public Primitive {
public:
    Line2D(PrimitiveParams params, glm::vec2 _endPosition);
    Line2D(const Line2D &other) = default;
    Line2D(Line2D &&other) = default;
    ~Line2D() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

    std::shared_ptr<Primitive> clone() const override { return std::make_shared<Line2D>(*this); }

    glm::vec2 startPosition;
    glm::vec2 endPosition;
};

} // namespace plugin::primitive
