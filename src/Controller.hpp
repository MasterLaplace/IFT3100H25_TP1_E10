#pragma once

/*
Une classe virtuelle de controlleur pour pouvoir un controller2D et, éventuellement, un Controller3D.
*/

#include "StateMachine.hpp"
#include "ofMain.h"
#include "ofxImGui.h"

class Controller {
public:
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void exit() = 0;

    virtual void keyPressed(int key) = 0;
    virtual void mouseMoved(glm::vec2 pos) = 0;
};
