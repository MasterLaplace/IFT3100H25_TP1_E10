#include "Rectangle.hpp"

namespace plugin::primitive {

void Rectangle::draw()
{
    ofSetColor(color);
    ofFill();
    ofDrawRectangle(position, dimensions.x, dimensions.y);
}

} // namespace plugin::primitive
