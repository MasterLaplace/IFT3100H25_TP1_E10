#pragma once

#include "ofMain.h"
#include <iostream>

namespace plugin::states {

class State {
public:
    glm::vec2 mousePosition;
    glm::vec2 mousePressedPosition;
    bool isMousePressed = false;
    int selectedPrimitiveId = -1;
    float strokeSize;
    ofColor color;

    virtual void enter() = 0;
    virtual void update() = 0;
    virtual void mousePressed(int x, int y, int button) = 0;
    virtual void mouseReleased(int x, int y, int button) = 0;
    virtual void draw() = 0;
    virtual void exit() = 0;
};

} // namespace plugin::states
