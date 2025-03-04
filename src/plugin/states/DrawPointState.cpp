#include "DrawPointState.hpp"

using namespace plugin::primitive;

namespace plugin::states {

void DrawPointState::enter() {}

void DrawPointState::update() {}

void DrawPointState::mousePressed(int x, int y, int button) {}

void DrawPointState::mouseReleased(int x, int y, int button)
{
    Canvas *canvas = Canvas::getInstance();
    Node<Primitive2D> *parent = canvas->getChildById(selectedPrimitiveId);

    Primitive2DParams params;
    params.position = mousePressedPosition;
    params.fillColor = fillColor;
    params.outlineColor = outlineColor;
    params.outlineWidth = outlineWidth;
    params.isFilled = isFilled;

    Point2D *point = new Point2D(params, outlineWidth);
    Node<Primitive2D> *node = new Node<Primitive2D>(point);

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

void DrawPointState::exit() {}

void DrawPointState::drawCursor()
{
    // Decallage du point par rapport au curseur.
    glm::vec2 offset = glm::vec2(30, 30);

    // Taille et couleur.
    ofSetColor(0);
    ofFill();
    float radius = 10.0f;

    // On dessine le point.
    ofDrawCircle(mousePosition + offset, radius);
}

// On dessine le preview du point avec de la transparence.
void DrawPointState::drawPreview()
{
    ofColor previewColor = fillColor;
    previewColor.a = 127;

    ofSetColor(previewColor);
    ofSetLineWidth(1);
    ofFill();
    ofDrawCircle(mousePosition, outlineWidth);
}

} // namespace plugin::states
