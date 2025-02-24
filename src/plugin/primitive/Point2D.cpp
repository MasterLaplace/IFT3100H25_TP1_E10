#include "Point2D.hpp"

namespace plugin::primitive {

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
