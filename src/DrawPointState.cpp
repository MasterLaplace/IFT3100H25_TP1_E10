#include "DrawPointState.hpp"

void DrawPointState::enter() { std::cout << "On entre dans le DrawPointState." << std::endl; }

void DrawPointState::update() {}

void DrawPointState::draw() { 
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
void DrawPointState::drawPreview() {
    ofColor previewColor = color;
    previewColor.a = 127;

    ofSetColor(previewColor);
    ofDrawCircle(mousePosition, strokeSize);

}
