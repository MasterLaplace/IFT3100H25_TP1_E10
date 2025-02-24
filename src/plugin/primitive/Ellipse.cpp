#include "Ellipse.hpp"

namespace plugin::primitive {

void Ellipse::draw()
{
    ofSetColor(color);
    ofFill();
    ofDrawEllipse(position.x, position.y, radius.x, radius.y);
}

bool Ellipse::isInside(glm::vec2 *point)
{
    // Voici ma méthode pour trouver l'intérieur d'une ellipse.
    // https://math.stackexchange.com/questions/76457/check-if-a-point-is-within-an-ellipse
    // (x - h)^2 / a^2 + (y - k)^2 / b^2 <= 1

    float a = radius.x;
    float b = radius.y;
    float h = position.x;
    float k = position.y;

    float x = point->x;
    float y = point->y;

    float result = pow((x - h) / a, 2) + pow((y - k) / b, 2);

    if (result <= 1)
    {
        return true;
    }

    return false;
}

} // namespace plugin::primitive
