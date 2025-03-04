#include "DrawPolygonState.hpp"

using namespace plugin::primitive;

namespace plugin::states {

void DrawPolygonState::enter() {}

void DrawPolygonState::mousePressed(int x, int y, int button) {}

void DrawPolygonState::mouseReleased(int x, int y, int button)
{
    if (points.size() < 3)
    {
        points.push_back(mousePosition);
        return;
    }

    float distanceFromFirst = glm::distance(mousePosition, points[0]);
    if (distanceFromFirst > 5)
    {
        points.push_back(mousePosition);
        return;
    }

    Canvas *canvas = Canvas::getInstance();

    glm::vec2 position = points[0];

    // On fait en sorte que les points soient relativement a la position
    for (int i = points.size() - 1; i > 0; i--)
    {
        points[i] -= position;
    }
    points[0] = glm::vec2(0, 0);

    PrimitiveParams params;
    params.position = glm::vec3(position.x, position.y, 0);
    params.fillColor = fillColor;
    params.outlineColor = outlineColor;
    params.outlineWidth = outlineWidth;
    params.isFilled = isFilled;

    // On cree le noeud.
    auto node = new NodePrimitive(std::make_shared<Polygon>(params, points), "Polygon");
    NodePrimitive *parent = Canvas::getInstance()->getChildById(selectedPrimitiveId);

    if (!parent)
    {
        canvas->addNode(node);
    }
    else
    {
        parent->addChild(node);
    }

    // On vide les points.
    points.clear();
}

void DrawPolygonState::update() {}

void DrawPolygonState::draw()
{
    drawCursor();
    drawPreview();
}

void DrawPolygonState::exit() {}

void DrawPolygonState::drawCursor()
{
    // Le decallage de l'icone par rapport au curseur
    glm::vec2 upOffset = glm::vec2(50, 10);

    ofFill();
    ofSetColor(ofColor::black);

    // On dessine le polygone.
    glm::vec2 p1 = mousePosition + upOffset;
    glm::vec2 p2 = mousePosition + upOffset + glm::vec2(10, 0);
    glm::vec2 p3 = mousePosition + upOffset + glm::vec2(5, 5);
    glm::vec2 p4 = mousePosition + upOffset + glm::vec2(10, 10);
    glm::vec2 p5 = mousePosition + upOffset + glm::vec2(0, 10);

    ofBeginShape();
    ofVertex(p1.x, p1.y);
    ofVertex(p2.x, p2.y);
    ofVertex(p3.x, p3.y);
    ofVertex(p4.x, p4.y);
    ofVertex(p5.x, p5.y);
    ofEndShape(true);
}

void DrawPolygonState::drawPreview()
{
    if (points.size() == 0)
    {
        return;
    }

    ofColor previewColor = fillColor;
    previewColor.a = 127;
    ofSetColor(previewColor);
    ofSetLineWidth(outlineWidth);

    for (size_t i = 0; i < points.size(); i++)
    {
        ofDrawCircle(points[i], 5);
    }

    for (size_t i = 0; i < points.size() - 1; i++)
    {
        ofDrawLine(points[i], points[i + 1]);
    }

    ofDrawLine(points[points.size() - 1], mousePosition);
}

} // namespace plugin::states
