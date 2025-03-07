#pragma once

#include "../geometry/BoundaryBox.hpp"
#include "Primitive.hpp"
#include "ofMain.h"

namespace plugin::primitive {

class Box : public Primitive {
public:
    Box(PrimitiveParams params, glm::vec3 size);
    // Box(const Box &other);
    ~Box() override = default;

    void draw() override;
    bool isInside(const glm::vec3 &point) override;

    void setSize(const glm::vec3 &size) { _size = size; }
    [[nodiscard]] glm::vec3 &getSize() { return _size; }

private:
    void drawFill();
    void drawOutline();
    void drawBox();

private:
    glm::vec3 _size;
    // geometry::BoundaryBox bbox;
};

} // namespace plugin::primitive
