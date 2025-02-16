#include "Line2D.hpp"

namespace plugin::primitive {

void Line2D::draw()
{
    ofSetLineWidth(strokeWidth);
    ofSetColor(color);
    ofDrawLine(position, endPosition);
}

} // namespace plugin::primitive