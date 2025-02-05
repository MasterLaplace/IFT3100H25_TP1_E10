#include "DrawLineState.h"

void DrawLineState::enter() { 
	std::cout << "On entre dans le DrawLineState." << std::endl; 
}

void DrawLineState::update() {


}

void DrawLineState::draw() {}

void DrawLineState::exit() {
	std::cout << "On sort du DrawLineState." << std::endl;
}
