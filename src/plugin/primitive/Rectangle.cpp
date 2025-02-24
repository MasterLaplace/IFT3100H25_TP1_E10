#include "Rectangle.hpp"

namespace plugin::primitive {
Rectangle::Rectangle(glm::vec2 _position, ofColor _color, glm::vec2 _dimensions) : Primitive2D(_position, _color)
{
    dimensions = _dimensions;
    name = "Rectangle " + std::to_string(id);
}

void Rectangle::draw()
{
    ofSetColor(color);
    ofFill();
    ofDrawRectangle(position, dimensions.x, dimensions.y);
}

bool Rectangle::isInside(glm::vec2 *point)
{
    return point->x > position.x && point->x < position.x + dimensions.x && point->y > position.y &&
           point->y < position.y + dimensions.y;
}

} // namespace plugin::primitive
