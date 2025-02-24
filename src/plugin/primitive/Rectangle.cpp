#include "Rectangle.hpp"

namespace plugin::primitive {

void Rectangle::draw()
{
    ofSetColor(color);
    ofFill();
    ofDrawRectangle(position, dimensions.x, dimensions.y);
}

bool Rectangle::isInside(glm::vec2* point) {
    return point->x > position.x &&
    point->x < position.x + dimensions.x &&
    point->y > position.y &&
    point->y < position.y + dimensions.y;
}

} // namespace plugin::primitive
