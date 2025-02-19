#include "Rectangle.hpp"

namespace plugin::primitive {

void Rectangle::draw()
{
    ofSetColor(color);
    ofDrawRectangle(position, dimensions.x, dimensions.y);
}

} // namespace plugin::primitive
