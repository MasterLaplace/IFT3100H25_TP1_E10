#include "DrawLineState.hpp"

using namespace plugin::primitive;

namespace plugin::states {

void DrawLineState::enter() {}

void DrawLineState::mousePressed(int x, int y, int button) {}

void DrawLineState::mouseReleased(Canvas* canvas)
{
    NodePrimitive *parent = canvas->getChildById(selectedPrimitiveId);

    PrimitiveParams params;
    params.position = glm::vec3(mousePressedPosition.x, mousePressedPosition.y, 0.0f);
    params.fillColor = fillColor;
    params.outlineColor = outlineColor;
    params.outlineWidth = outlineWidth;

    auto node = new NodePrimitive(std::make_shared<Line2D>(params, mousePosition), "Line");

    if (!parent)
    {
        canvas->addNode(node);
    }

    else
    {
        parent->addChild(node);
    }
}

void DrawLineState::update() {}

void DrawLineState::draw()
{
    drawCursor();
    drawPreview();
}

void DrawLineState::exit() {}

void DrawLineState::drawCursor()
{

    // Le decallage de l'icone par rapport au curseur.
    glm::vec2 upOffset = glm::vec2(50, 10);
    glm::vec2 downOffset = glm::vec2(25, 50);

    ofSetLineWidth(1);
    ofSetColor(0);

    // On dessine la ligne.
    ofDrawLine(mousePosition + upOffset, mousePosition + downOffset);
}

void DrawLineState::drawPreview()
{
    if (isMousePressed)
    {
        ofColor previewColor = fillColor;
        previewColor.a = 127;
        ofSetColor(previewColor);
        ofSetLineWidth(outlineWidth);
        ofDrawLine(mousePressedPosition, mousePosition);
        std::cout << mousePosition << std::endl;
    }
}

} // namespace plugin::states
