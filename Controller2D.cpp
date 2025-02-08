#include "Controller2D.hpp"

void Controller2D::setup() {

	stateMachine.changeState(new DrawPointState());

	//C'est ici qu'on va initialiser l'interface pour le 2D.

}

void Controller2D::update() {

	stateMachine.update();

}

void Controller2D::draw() {

	stateMachine.draw();

}

void Controller2D::exit() {}

void Controller2D::keyPressed(int key) {

	if (key == 'p')
	{
        stateMachine.changeState(new DrawPointState());
	}

	if (key == 'l')
    {
        stateMachine.changeState(new DrawLineState());
    }

}

void Controller2D::mouseMoved(glm::vec2 pos) {

	stateMachine.mousePosition = pos;

}
