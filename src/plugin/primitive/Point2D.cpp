#include "Point2D.hpp"

namespace plugin::primitive {

Point2D::Point2D(PrimitiveParams _params, float _size) : Primitive(_params)
{
    size = _size;
}

void Point2D::draw()
{
    ofSetColor(param.fillColor);
    ofFill();
    ofDrawCircle(param.position, size);
}

bool Point2D::isInside(const glm::vec3 &point)
{
    float distance = glm::distance(param.position, point);
    return distance < size;
}

} // namespace plugin::primitive
