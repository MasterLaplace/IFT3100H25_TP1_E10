#pragma once

#include "Primitive.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Ellipse : public Primitive {
public:
    Ellipse(PrimitiveParams params, glm::vec2 _radius);
    Ellipse(const Ellipse &other) = default;
    Ellipse(Ellipse &&other) = default;
    ~Ellipse() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

    std::shared_ptr<Primitive> clone() const override { return std::make_shared<Ellipse>(*this); }

    glm::vec2 radius;

private:
    void drawFill();
    void drawOutline();
};

} // namespace plugin::primitive
