#include "DrawEllipseState.hpp"

using namespace plugin::primitive;

namespace plugin::states {

void DrawEllipseState::enter() {}

void DrawEllipseState::mousePressed(int x, int y, int button) {}

void DrawEllipseState::mouseReleased(Canvas *canvas)
{
    // On calcule le rayon de l'ellipse.
    float radiusX = abs(mousePressedPosition.x - mousePosition.x);
    float radiusY = abs(mousePressedPosition.y - mousePosition.y);

    if (radiusX == 0 || radiusY == 0)
        return;

    // On cree l'ellipse.
    PrimitiveParams params;
    params.position = {0, 0, 0};
    params.fillColor = fillColor;
    params.outlineWidth = outlineWidth;
    params.outlineColor = outlineColor;
    params.isFilled = isFilled;

    auto ellipse = std::make_shared<plugin::primitive::Ellipse>(params, glm::vec2(radiusX, radiusY));

    // On cree le noeud.
    auto node = new NodePrimitive(ellipse, "Ellipse");
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

void DrawEllipseState::update() {}

void DrawEllipseState::draw()
{
    drawCursor();
    drawPreview();
}

void DrawEllipseState::exit() {}

void DrawEllipseState::drawCursor()
{
    // Le decallage de l'icone par rapport au curseur
    glm::vec2 upOffset = glm::vec2(30, 30);

    ofFill();
    ofSetColor(ofColor::black);

    // On dessine l'ellipse.
    ofDrawEllipse(mousePosition + upOffset, 30, 15);
}

void DrawEllipseState::drawPreview()
{
    if (!isMousePressed)
        return;

    ofColor previewColor = fillColor;
    previewColor.a = 127;

    ofSetColor(previewColor);
    ofSetLineWidth(outlineWidth);

    float radiusX = abs(mousePressedPosition.x - mousePosition.x);
    float radiusY = abs(mousePressedPosition.y - mousePosition.y);

    // Cette partie du code est un peu étrange
    // C'est pour placer le center de l'ellipse au bon endroit si jamais on dessine l'ellipse à l'envers.
    int invertX = (mousePosition.x < mousePressedPosition.x) ? -1 : 1;
    int invertY = (mousePosition.y < mousePressedPosition.y) ? -1 : 1;

    glm::vec2 center =
        glm::vec2(mousePressedPosition.x + invertX * radiusX / 2, mousePressedPosition.y + invertY * radiusY / 2);

    ofDrawEllipse(center, radiusX, radiusY);

    ofColor outlinePreview = outlineColor;
    outlinePreview.a = 127;
    ofSetColor(outlinePreview);

    ofNoFill();
    ofDrawEllipse(center, radiusX, radiusY);
}

} // namespace plugin::states
