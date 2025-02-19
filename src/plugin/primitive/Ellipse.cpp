#include "Ellipse.hpp"

namespace plugin::primitive {

void Ellipse::draw() {
    ofSetColor(color);
    ofDrawEllipse(position.x, position.y, radius.x, radius.y);
}

} // namespace plugin::primitive
