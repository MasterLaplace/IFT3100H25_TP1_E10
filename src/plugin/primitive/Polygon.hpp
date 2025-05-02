#pragma once

#include "Primitive.hpp"
#include "ofMain.h"
#include <vector>

namespace plugin::primitive {

class Polygon : public Primitive {
public:
    Polygon(PrimitiveParams params, std::vector<glm::vec2> _points);
    Polygon(const Polygon &other) = default;
    Polygon(Polygon &&other) = default;
    ~Polygon() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

    std::shared_ptr<Primitive> clone() const override { return std::make_shared<Polygon>(*this); }

    std::vector<glm::vec2> points;

private:
    void drawFill();
    void drawOutline();
};

} // namespace plugin::primitive
