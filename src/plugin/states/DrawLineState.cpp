#include "DrawLineState.hpp"

using namespace plugin::primitive;

namespace plugin::states {

void DrawLineState::enter() { std::cout << "On entre dans le DrawLineState." << std::endl; }

void DrawLineState::mousePressed(int x, int y, int button) {}

void DrawLineState::mouseReleased(int x, int y, int button)
{
    Canvas *canvas = Canvas::getInstance();
    Line2D *line = new Line2D(mousePressedPosition, mousePosition, color, strokeSize);
    Node2D *node = new Node2D(line);
    canvas->addNode(node);
}

void DrawLineState::update() {}

void DrawLineState::draw()
{
    drawCursor();
    drawPreview();
}

void DrawLineState::exit() { std::cout << "On sort du DrawLineState." << std::endl; }

void DrawLineState::drawCursor()
{

    // Le decallage de l'icone par rapport au curseur.
    glm::vec2 upOffset = glm::vec2(50, 10);
    glm::vec2 downOffset = glm::vec2(25, 50);

    // J'aurais aime faire un trait plus large mais meme si j'augmente a 100 ca ne change rien.
    ofSetLineWidth(5);
    ofSetColor(0);

    // On dessine la ligne.
    ofDrawLine(mousePosition + upOffset, mousePosition + downOffset);
}

void DrawLineState::drawPreview()
{
    if (isMousePressed)
    {
        ofColor previewColor = color;
        previewColor.a = 127;
        ofSetColor(previewColor);
        ofSetLineWidth(strokeSize);
        ofDrawLine(mousePressedPosition, mousePosition);
        std::cout << mousePosition << std::endl;
    }
}

} // namespace plugin::states
