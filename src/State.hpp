#pragma once

#include "ofMain.h"
#include <iostream>

class State {
public:
    glm::vec2 mousePosition;
    glm::vec2 mousePressedPosition;
    bool isMousePressed = false;
    float strokeSize;
    ofColor color;

    virtual void enter() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void exit() = 0;
};
