#include "Polygon.hpp"

namespace plugin::primitive {

Polygon::Polygon(glm::vec2 _position, ofColor _color, std::vector<glm::vec2> _points) : Primitive2D(_position, _color)
{
    points = _points;
    name = "Polygon " + std::to_string(id);
}

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

bool Polygon::isInside(glm::vec2 *mousePosition)
{
    int xMax = INT16_MIN, yMax = INT16_MIN;
    int xMin = INT16_MAX, yMin = INT16_MAX;

    for (auto &point : points)
    {
        int absolute_vx = point.x + position.x;
        int absolute_vy = point.y + position.y;

        if (absolute_vx > xMax)
        {
            xMax = absolute_vx;
        }

        if (absolute_vx < xMin)
        {
            xMin = absolute_vx;
        }

        if (absolute_vy > yMax)
        {
            yMax = absolute_vy;
        }

        if (absolute_vy < yMin)
        {
            yMin = absolute_vy;
        }
    }

    if (mousePosition->x < xMin || mousePosition->x > xMax || mousePosition->y < yMin || mousePosition->y > yMax)
    {
        return false;
    }

    bool isInside = false;
    for (int i = 0; i < points.size(); i++)
    {
        int horizontal_line_y = mousePosition->y;

        glm::vec2 a = points[i] + position;
        glm::vec2 b = points[(i + 1) % points.size()] + position;

        if ((a.y > horizontal_line_y && b.y > horizontal_line_y) ||
            (a.y < horizontal_line_y && b.y < horizontal_line_y))
        {
            continue;
        }

        float slope = (b.y - a.y) / (b.x - a.x);
        float x = a.x + (horizontal_line_y - a.y) / slope;

        if (x > mousePosition->x)
        {
            isInside = !isInside;
        }
    }

    return isInside;
}

} // namespace plugin::primitive
