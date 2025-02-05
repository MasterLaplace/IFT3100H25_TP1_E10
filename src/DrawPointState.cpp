#include "DrawPointState.h"

void DrawPointState::enter() { 
	std::cout << "On entre dans le DrawPointState." << std::endl; 
}

void DrawPointState::update() {}

void DrawPointState::draw() {}

void DrawPointState::exit() { 
	std::cout << "On sort du DrawPointState." << std::endl;
}
