#include "DrawLineState.hpp"

using namespace plugin::primitive;

namespace plugin::states {

void DrawLineState::enter() {}

void DrawLineState::mousePressed(int x, int y, int button) {}

void DrawLineState::mouseReleased(int x, int y, int button)
{
    Canvas *canvas = Canvas::getInstance();
    Node<Primitive2D> *parent = canvas->getChildById(selectedPrimitiveId);

    Primitive2DParams params;
    params.position = mousePressedPosition;
    params.fillColor = fillColor;
    params.outlineColor = outlineColor;
    params.outlineWidth = outlineWidth;

    Line2D *line = new Line2D(params, mousePosition);
    Node<Primitive2D> *node = new Node<Primitive2D>(line);

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
