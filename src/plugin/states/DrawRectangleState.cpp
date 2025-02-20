#include "DrawRectangleState.hpp"

namespace plugin::states {

void DrawRectangleState::enter() { std::cout << "On entre dans le DrawRectangleState." << std::endl; }

void DrawRectangleState::mousePressed(int x, int y, int button) {}

void DrawRectangleState::mouseReleased(int x, int y, int button)
{
    Canvas *canvas = Canvas::getInstance();

    // On calcule la largeur et la hauteur du rectangle.
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

    plugin::primitive::Rectangle *rectangle = new plugin::primitive::Rectangle(position, color, glm::vec2(width, height));
    Node2D *node = new Node2D(rectangle);
    Node2D *parent = canvas->getChildById(selectedPrimitiveId);

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
    glm::vec2 upOffset = glm::vec2(50, 10);
    glm::vec2 downOffset = glm::vec2(25, 50);

    ofFill();
    ofSetColor(ofColor::black);

    // On dessine le rectangle
    ofDrawRectangle(mousePosition + upOffset, 20, 20);
}

void DrawRectangleState::drawPreview()
{
    if (isMousePressed)
    {
        ofColor previewColor = color;
        previewColor.a = 127;
        ofSetColor(previewColor);

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

        ofDrawRectangle(position, width, height);
    }
}

} // namespace plugin::states
