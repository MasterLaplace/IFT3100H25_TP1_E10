#pragma once

/*
Une classe virtuelle de controlleur pour pouvoir un controller2D et, éventuellement, un Controller3D.
*/

#include "ofMain.h"
#include "ofxImGui.h"

class Controller {
public:
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void exit() = 0;

    virtual void keyReleased(int key) = 0;
    virtual void mouseMoved(glm::vec2 pos) = 0;
    virtual void mousePressed(int x, int y, int button) = 0;
    virtual void mouseReleased(int x, int y, int button) = 0;
};
