#include "Polygon.hpp"
#include "../image/ResourceManager.hpp"

namespace plugin::primitive {

Polygon::Polygon(PrimitiveParams params, std::vector<glm::vec2> _points) : Primitive(params) { points = _points; }

void Polygon::draw()
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

void Polygon::drawFill()
{
    bool hasTexture = false;
    std::optional<std::shared_ptr<ofImage>> image;
    if (!param.imageName.empty())
    {
        image = image::ResourceManager::instance()->getImage(param.imageName);
        if (image.has_value())
        {
            ofSetColor(255);
            image->get()->getTexture().bind();
            hasTexture = true;
        }
        else
        {
            ofSetColor(param.fillColor);
            ofSetLineWidth(1);
            ofFill();
        }
    }

    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);

    for (const auto &point : points)
    {
        mesh.addVertex(glm::vec3(point, 0));
    }

    if (hasTexture)
    {
        for (const auto &point : points)
        {
            float u = (point.x - param.position.x) / param.scale.x * image->get()->getWidth();
            float v = (point.y - param.position.y) / param.scale.y * image->get()->getHeight();
            mesh.addTexCoord(glm::vec2(u, v));
        }
    }

    mesh.draw();

    if (hasTexture)
    {
        image->get()->getTexture().unbind();
    }
}

void Polygon::drawOutline()
{
    ofSetColor(param.outlineColor);
    ofSetLineWidth(param.outlineWidth);
    ofNoFill();

    ofBeginShape();
    for (auto &point : points)
    {
        ofVertex(point);
    }
    ofEndShape(true);
}

bool Polygon::isInside(const glm::vec3 &mousePosition)
{
    int xMax = INT16_MIN, yMax = INT16_MIN;
    int xMin = INT16_MAX, yMin = INT16_MAX;

    for (auto &point : points)
    {
        int absolute_vx = point.x + param.position.x;
        int absolute_vy = point.y + param.position.y;

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

    if (mousePosition.x < xMin || mousePosition.x > xMax || mousePosition.y < yMin || mousePosition.y > yMax)
    {
        return false;
    }

    bool isInside = false;
    for (size_t i = 0; i < points.size(); i++)
    {
        int horizontal_line_y = mousePosition.y;

        glm::vec2 a = points[i] + param.position;
        glm::vec2 b = points[(i + 1) % points.size()] + param.position;

        if ((a.y > horizontal_line_y && b.y > horizontal_line_y) ||
            (a.y < horizontal_line_y && b.y < horizontal_line_y))
        {
            continue;
        }

        float slope = (b.y - a.y) / (b.x - a.x);
        float x = a.x + (horizontal_line_y - a.y) / slope;

        if (x > mousePosition.x)
        {
            isInside = !isInside;
        }
    }

    return isInside;
}

} // namespace plugin::primitive
