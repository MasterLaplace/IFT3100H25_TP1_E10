#include "DrawEllipsoidState.hpp"

using namespace plugin::primitive;

namespace plugin::states {

void DrawEllipsoidState::enter() {}

void DrawEllipsoidState::mousePressed(int x, int y, int button) {}

void DrawEllipsoidState::mouseReleased(Canvas *canvas)
{
    // On calcule le rayon de l'ellipse.
    float radiusX = abs(mousePressedPosition.x - mousePosition.x);
    float radiusY = abs(mousePressedPosition.y - mousePosition.y);

    if (radiusX == 0 || radiusY == 0)
        return;

    int invertX = (mousePosition.x < mousePressedPosition.x) ? -1 : 1;
    int invertY = (mousePosition.y < mousePressedPosition.y) ? -1 : 1;

    // On calcule le centre de l'ellipse.
    glm::vec3 center =
        glm::vec3(mousePressedPosition.x + invertX * radiusX / 2, mousePressedPosition.y + invertY * radiusY / 2, 0);

    // On cree l'ellipse.
    PrimitiveParams params;
    params.position = center;
    params.fillColor = fillColor;
    params.outlineWidth = outlineWidth;
    params.outlineColor = outlineColor;
    params.isFilled = isFilled;

    auto ellipse = std::make_shared<plugin::primitive::Ellipsoid>(params, glm::vec3(radiusX, radiusY, radiusX));

    // On cree le noeud.
    auto node = new NodePrimitive(ellipse, "Ellipsoid");
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

void DrawEllipsoidState::update() {}

void DrawEllipsoidState::draw()
{
    drawCursor();
    drawPreview();
}

void DrawEllipsoidState::exit() {}

void DrawEllipsoidState::drawCursor()
{
    // Le decallage de l'icone par rapport au curseur
    glm::vec2 upOffset = glm::vec2(50, 10);

    ofFill();
    ofSetColor(ofColor::black);

    // On dessine l'ellipse.
    ofDrawEllipse(mousePosition + upOffset, 10, 10);
}

void DrawEllipsoidState::drawPreview()
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
