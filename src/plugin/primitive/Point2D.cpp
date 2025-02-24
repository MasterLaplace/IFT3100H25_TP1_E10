#include "Point2D.hpp"

namespace plugin::primitive {

Point2D::Point2D(glm::vec2 _position, ofColor _color, float _size) : Primitive2D(_position, _color)
{
    size = _size;
    name = "Point " + std::to_string(id);
}

void Point2D::draw()
{
    ofSetColor(color);
    ofDrawCircle(position, size);
}

bool Point2D::isInside(glm::vec2 *point)
{
    float distance = glm::distance(position, *point);
    return distance < size;
}

} // namespace plugin::primitive
