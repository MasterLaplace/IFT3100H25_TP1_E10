#include "Controller2D.hpp"

void Controller2D::setup() {

	//On initialise l'état du Controlleur pour dessiner des points.
	//On pourrait changer l'état initial au besoin.
	stateMachine.changeState(new DrawPointState());

	//C'est ici qu'on va initialiser l'interface pour le 2D.
    gui.setup(this);

}

void Controller2D::update() {

	stateMachine.update();

}

void Controller2D::draw() {

	//C'est Controlleur qui demande à son état de dessiner des choses en lien avec l'état.
	//Par exemple, si on est dans l'état DrawRectangleState, on va dessiner le fantome du rectangle.
	stateMachine.draw();

	//C'est le Controlleur qui demande au GUI de s'afficher aussi.
    gui.draw();

	//C'est probablement le Controlleur qui va aussi demander au Canvas de s'afficher.
	//TODO

}

void Controller2D::exit() {}

void Controller2D::keyPressed(int key) {

	//C'est les racourcies claviers.
	//Les input proviennent de Application.
	if (key == 'p')
	{
        drawPointButtonPressed();
	}

	if (key == 'l')
    {
        drawLineButtonPressed();
    }

}

void Controller2D::mouseMoved(glm::vec2 pos) {

	//On transmet la position de la sourie à l'état.
	//L'input provient de Application.
	stateMachine.mousePosition = pos;

}

void Controller2D::drawPointButtonPressed() {

	stateMachine.changeState(new DrawPointState());

}

void Controller2D::drawLineButtonPressed() {

	stateMachine.changeState(new DrawLineState());

}
