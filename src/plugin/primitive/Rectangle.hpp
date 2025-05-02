#pragma once

#include "Primitive.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Rectangle : public Primitive {
public:
    Rectangle(PrimitiveParams _params, glm::vec2 _dimensions);
    Rectangle(const Rectangle &other) = default;
    Rectangle(Rectangle &&other) = default;
    ~Rectangle() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

    std::shared_ptr<Primitive> clone() const override { return std::make_shared<Rectangle>(*this); }

    glm::vec2 dimensions;

private:
    void drawFill();
    void drawOutline();
};

} // namespace plugin::primitive
