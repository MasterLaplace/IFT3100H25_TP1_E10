#pragma once

#include "State.h"

class StateMachine {
public:
    StateMachine();
    ~StateMachine();

    void changeState(State *newState);
    void update();
    void draw();

private:
    State *currentState;

};
