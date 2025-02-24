#include "Line2D.hpp"

namespace plugin::primitive {

void Line2D::draw()
{
    ofSetLineWidth(strokeWidth);
    ofSetColor(color);
    ofDrawLine(position, endPosition + position);
}

bool Line2D::isInside(glm::vec2* point) {
    // On calcule la distance entre le clic et la ligne :https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
    // Si la distance est en-dessous d'une certaine limite, return true
    // Sinon, return false

    float startx = position.x;
    float starty = position.y;

    float endx = endPosition.x + position.x;
    float endy = endPosition.y + position.y;

    if (startx > endx && starty > endy) {
        float temp = startx;
        startx = endx;
        endx = temp;
        temp = starty;
        starty = endy;
        endy = temp;
    }

    float x = point->x;
    float y = point->y;

    float num = abs((endy - starty) * x - (endx - startx) * y + endx * starty - endy * startx);
    float den = sqrt(pow(endy - starty, 2) + pow(endx - startx, 2));

    float distance = num / den;

    float maxX = startx > endx ? startx : endx;
    float minX = startx < endx ? startx : endx;

    float maxY = starty > endy ? starty : endy;
    float minY = starty < endy ? starty : endy;

    if (distance <= 5 && x >= minX && x <= maxX && y >= minY && y <= maxY) {
        return true;
    }

    return false;
}

    
} // namespace plugin::primitive
