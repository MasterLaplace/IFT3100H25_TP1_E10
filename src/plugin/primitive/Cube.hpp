#pragma once

#include "Primitive.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Cube : public Primitive {
public:
    Cube(PrimitiveParams params, float _size);
    ~Cube() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

    float size;

private:
    void drawFill();
    void drawOutline();
};

} // namespace plugin::primitive
