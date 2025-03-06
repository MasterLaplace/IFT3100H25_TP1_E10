#include "DrawRectangleState.hpp"

using namespace plugin::primitive;

namespace plugin::states {

void DrawRectangleState::enter() {}

void DrawRectangleState::mousePressed(int x, int y, int button) {}

void DrawRectangleState::mouseReleased(Canvas *canvas)
{
    // On calcule la largeur et la hauteur du rectangle.
    float width = abs(mousePressedPosition.x - mousePosition.x);
    float height = abs(mousePressedPosition.y - mousePosition.y);

    // Position is always the top left corner
    glm::vec3 position = glm::vec3(mousePressedPosition.x, mousePressedPosition.y, 0.0f);

    if (mousePosition.x < mousePressedPosition.x)
    {
        position.x = mousePosition.x;
    }
    if (mousePosition.y < mousePressedPosition.y)
    {
        position.y = mousePosition.y;
    }

    PrimitiveParams params;
    params.position = position;
    params.fillColor = fillColor;
    params.outlineColor = outlineColor;
    params.outlineWidth = outlineWidth;
    params.isFilled = isFilled;

    auto rectangle = std::make_shared<plugin::primitive::Rectangle>(params, glm::vec2(width, height));
    auto node = new NodePrimitive(rectangle, "Rectangle");
    NodePrimitive *parent = canvas->getChildById(selectedPrimitiveId);

    if (!parent)
    {
        canvas->addNode(node);
    }
    else
    {
        parent->addChild(node);
    }
}

void DrawRectangleState::update() {}

void DrawRectangleState::draw()
{
    drawCursor();
    drawPreview();
}

void DrawRectangleState::exit() { std::cout << "On sort du DrawRectangleState." << std::endl; }

void DrawRectangleState::drawCursor()
{
    // Le decallage de l'icone par rapport au curseur
    glm::vec2 upOffset = glm::vec2(30, 30);
    // glm::vec2 downOffset = glm::vec2(25, 50);

    ofFill();
    ofSetColor(ofColor::black);

    // On dessine le rectangle
    ofDrawRectangle(mousePosition + upOffset, 20, 20);
}

void DrawRectangleState::drawPreview()
{
    if (!isMousePressed)
        return;

    ofColor fillPreview = fillColor;
    fillPreview.a = 127;
    ofSetColor(fillPreview);

    // On calcule la largeur et la hauteur du rectangle
    float width = abs(mousePressedPosition.x - mousePosition.x);
    float height = abs(mousePressedPosition.y - mousePosition.y);

    // Position is always the top left corner
    glm::vec2 position = glm::vec2(mousePressedPosition.x, mousePressedPosition.y);

    if (mousePosition.x < mousePressedPosition.x)
    {
        position.x = mousePosition.x;
    }
    if (mousePosition.y < mousePressedPosition.y)
    {
        position.y = mousePosition.y;
    }

    ofSetLineWidth(outlineWidth);
    ofDrawRectangle(position, width, height);

    ofColor outlinePreview = outlineColor;
    outlinePreview.a = 127;
    ofSetColor(outlinePreview);
    ofNoFill();
    ofDrawRectangle(position, width, height);
}

} // namespace plugin::states
