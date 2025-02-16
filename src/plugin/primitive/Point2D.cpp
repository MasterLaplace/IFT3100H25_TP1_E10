#include "Point2D.hpp"

namespace plugin::primitive {

void Point2D::draw()
{
    ofSetColor(color);
    ofDrawCircle(position, size);
}

} // namespace plugin::primitive