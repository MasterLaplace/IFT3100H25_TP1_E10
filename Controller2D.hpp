#pragma once

#include "Controller.hpp"
#include "DrawLineState.hpp"
#include "DrawPointState.hpp"

class Controller2D : public Controller {

	public:
        void setup();
        void update();
        void draw();
        void exit();

        void keyPressed(int key);
        void mouseMoved(glm::vec2 pos);

    private:
        StateMachine stateMachine;
};
