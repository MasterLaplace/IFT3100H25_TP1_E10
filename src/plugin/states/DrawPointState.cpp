#include "DrawPointState.hpp"

using namespace plugin::primitive;

namespace plugin::states {

void DrawPointState::enter() {}

void DrawPointState::update() {}

void DrawPointState::mousePressed(int x, int y, int button) {}

void DrawPointState::mouseReleased(int x, int y, int button)
{
    Canvas *canvas = Canvas::getInstance();
    Node2D *parent = canvas->getChildById(selectedPrimitiveId);
    Point2D *point = new Point2D(mousePosition, color, strokeSize);
    Node2D *node = new Node2D(point);

    if (!parent)
    {
        canvas->addNode(node);
    }

    else
    {
        parent->addChild(node);
    }
}

void DrawPointState::draw()
{
    drawCursor();
    drawPreview();
}

void DrawPointState::exit() { std::cout << "On sort du DrawPointState." << std::endl; }

void DrawPointState::drawCursor()
{

    // Decallage du point par rapport au curseur.
    glm::vec2 offset = glm::vec2(30, 30);

    // Taille et couleur.
    ofSetColor(0);
    float radius = 10.0f;

    // On dessine le point.
    ofDrawCircle(mousePosition + offset, radius);
}

// On dessine le preview du point avec de la transparence.
void DrawPointState::drawPreview()
{
    ofColor previewColor = color;
    previewColor.a = 127;

    ofSetColor(previewColor);
    ofDrawCircle(mousePosition, strokeSize);
}

} // namespace plugin::states
