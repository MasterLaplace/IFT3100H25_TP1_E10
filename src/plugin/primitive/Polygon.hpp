#pragma once

#include "Primitive2D.hpp"
#include "ofMain.h"
#include <vector>

namespace plugin::primitive {

class Polygon : public Primitive2D {
public:
    Polygon(Primitive2DParams params, vector<glm::vec2> _points);
    ~Polygon() override = default;

    void draw() override;
    bool isInside(glm::vec2 *point) override;

    vector<glm::vec2> points;
    
private:
    void drawFill();
    void drawOutline();
};

} // namespace plugin::primitive
