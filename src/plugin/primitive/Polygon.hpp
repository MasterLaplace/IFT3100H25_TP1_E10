#pragma once

#include "Primitive2D.hpp"
#include "ofMain.h"
#include <vector>

namespace plugin::primitive {

class Polygon : public Primitive2D {
public:
    Polygon(glm::vec2 _position, ofColor _color, vector<glm::vec2> _points) : Primitive2D(_position, _color)
    {
        points = _points;
    }

    void draw() override;

    vector<glm::vec2> points;
};

} // namespace plugin::primitive
