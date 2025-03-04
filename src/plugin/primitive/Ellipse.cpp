#include "Ellipse.hpp"

namespace plugin::primitive {

Ellipse::Ellipse(PrimitiveParams _params, glm::vec2 _radius) : Primitive(_params)
{
    radius = _radius;
}

void Ellipse::draw()
{
    ofEnableAntiAliasing();
    if (param.isFilled)
    {
        drawFill();
    }

    drawOutline();
    ofDisableAntiAliasing();
}

void Ellipse::drawOutline()
{
    ofLog() << param.outlineColor;
    ofSetColor(param.outlineColor);
    ofNoFill();
    ofSetLineWidth(param.outlineWidth);

    ofDrawEllipse(param.position.x, param.position.y, radius.x, radius.y);
}

void Ellipse::drawFill()
{
    ofSetColor(param.fillColor);
    ofSetLineWidth(1);
    ofFill();

    ofDrawEllipse(param.position.x, param.position.y, radius.x, radius.y);
}

bool Ellipse::isInside(const glm::vec3 &point)
{
    // Voici ma méthode pour trouver l'intérieur d'une ellipse.
    // https://math.stackexchange.com/questions/76457/check-if-a-point-is-within-an-ellipse
    // (x - h)^2 / a^2 + (y - k)^2 / b^2 <= 1

    float a = radius.x;
    float b = radius.y;
    float h = param.position.x;
    float k = param.position.y;

    float x = point.x;
    float y = point.y;

    float result = pow((x - h) / a, 2) + pow((y - k) / b, 2);

    if (result <= 1)
    {
        return true;
    }

    return false;
}

} // namespace plugin::primitive
