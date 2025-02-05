#include "DrawLineState.h"

void DrawLineState::enter() { std::cout << "On entre dans le DrawLineState." << std::endl; }

void DrawLineState::update() {}

void DrawLineState::draw() { drawCursor(); }

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
