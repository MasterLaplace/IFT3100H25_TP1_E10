#include "DrawPointState.h"

void DrawPointState::enter() { 
	std::cout << "On entre dans le DrawPointState." << std::endl; 
}

void DrawPointState::update() {}

void DrawPointState::draw() {

	drawCursor();

}

void DrawPointState::exit() { 
	std::cout << "On sort du DrawPointState." << std::endl; }

void DrawPointState::drawCursor() {
	
	//Decallage du point par rapport au curseur.
    glm::vec2 offset = glm::vec2(30, 30);

	//Taille et couleur.
    ofSetColor(0);
    float radius = 10.0f;

	//On dessine le point.
    ofDrawCircle(mousePosition + offset, radius);
}
