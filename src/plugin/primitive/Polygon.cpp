#include "Polygon.hpp"

namespace plugin::primitive {

void Polygon::draw()
{
    ofSetColor(color);
    ofFill();
    ofBeginShape();
    for (glm::vec2 &point : points)
    {
        ofVertex(point + position);
    }
    ofEndShape(true);
}

} // namespace plugin::primitive
