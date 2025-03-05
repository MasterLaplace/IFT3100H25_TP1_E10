#include "Rectangle.hpp"

namespace plugin::primitive {
Rectangle::Rectangle(PrimitiveParams _params, glm::vec2 _dimensions) : Primitive(_params) { dimensions = _dimensions; }

void Rectangle::draw()
{
    ofPushMatrix();
    ofTranslate(param.position.x, param.position.y);
    ofRotateXDeg(param.rotation.x);
    ofRotateYDeg(param.rotation.y);
    ofRotateZDeg(param.rotation.z);
    ofScale(param.scale.x, param.scale.y);

    if (param.isFilled)
    {
        drawFill();
    }

    drawOutline();

    ofPopMatrix();
}

void Rectangle::drawFill()
{
    ofSetColor(param.fillColor);
    ofSetLineWidth(1);
    ofFill();

    ofDrawRectangle(0, 0, dimensions.x, dimensions.y);
}

void Rectangle::drawOutline()
{
    ofSetColor(param.outlineColor);
    ofSetLineWidth(param.outlineWidth);
    ofNoFill();

    ofDrawRectangle(0, 0, dimensions.x, dimensions.y);
}

bool Rectangle::isInside(const glm::vec3 &point)
{
    return point.x > param.position.x && point.x < param.position.x + dimensions.x && point.y > param.position.y &&
           point.y < param.position.y + dimensions.y;
}

} // namespace plugin::primitive
