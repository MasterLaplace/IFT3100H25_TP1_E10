#include "Rectangle.hpp"

namespace plugin::primitive {
Rectangle::Rectangle(Primitive2DParams _params, glm::vec2 _dimensions) : Primitive2D(_params)
{
    dimensions = _dimensions;
    name = "Rectangle " + std::to_string(id);
}

void Rectangle::draw()
{
    if (isFilled)
    {
        drawFill();
    }

    drawOutline();
}

void Rectangle::drawFill()
{
    ofSetColor(fillColor);
    ofSetLineWidth(1);
    ofFill();
    
    ofDrawRectangle(position.x, position.y, dimensions.x, dimensions.y);
}

void Rectangle::drawOutline()
{
    ofSetColor(outlineColor);
    ofSetLineWidth(outlineWidth);
    ofNoFill();
    
    ofDrawRectangle(position.x, position.y, dimensions.x, dimensions.y);
}

bool Rectangle::isInside(glm::vec2 *point)
{
    return point->x > position.x && point->x < position.x + dimensions.x && point->y > position.y &&
           point->y < position.y + dimensions.y;
}

} // namespace plugin::primitive
