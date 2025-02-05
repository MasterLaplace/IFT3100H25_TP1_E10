#pragma once

#include "ofMain.h"

class State {
public:
    virtual void enter() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void exit() = 0;
    virtual void keyPressed(int key) = 0;
};