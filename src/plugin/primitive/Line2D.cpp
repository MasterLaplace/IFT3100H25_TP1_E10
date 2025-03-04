#include "Line2D.hpp"

namespace plugin::primitive {
Line2D::Line2D(PrimitiveParams _params, glm::vec2 _endPosition) : Primitive(_params)
{
    startPosition = glm::vec2(0, 0);
    endPosition = _endPosition - param.position;
}

void Line2D::draw()
{
    ofSetColor(param.fillColor);
    ofSetLineWidth(param.outlineWidth);
    ofDrawLine(param.position, endPosition + param.position);
}

bool Line2D::isInside(const glm::vec3 &point)
{
    // On calcule la distance entre le clic et la ligne :https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
    // Si la distance est en-dessous d'une certaine limite, return true
    // Sinon, return false

    float startx = param.position.x;
    float starty = param.position.y;

    float endx = endPosition.x + param.position.x;
    float endy = endPosition.y + param.position.y;

    if (startx > endx && starty > endy)
    {
        float temp = startx;
        startx = endx;
        endx = temp;
        temp = starty;
        starty = endy;
        endy = temp;
    }

    float x = point.x;
    float y = point.y;

    float num = abs((endy - starty) * x - (endx - startx) * y + endx * starty - endy * startx);
    float den = sqrt(pow(endy - starty, 2) + pow(endx - startx, 2));

    float distance = num / den;

    float maxX = startx > endx ? startx : endx;
    float minX = startx < endx ? startx : endx;

    float maxY = starty > endy ? starty : endy;
    float minY = starty < endy ? starty : endy;

    if (distance <= 5 && x >= minX && x <= maxX && y >= minY && y <= maxY)
    {
        return true;
    }

    return false;
}

} // namespace plugin::primitive
