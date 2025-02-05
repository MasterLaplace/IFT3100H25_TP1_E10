#pragma once

#include "State.h"

class StateMachine {
public:
    glm::vec2 mousePosition;

    StateMachine();
    ~StateMachine();

    void changeState(State *newState);
    void update();
    void draw();

private:
    State *currentState;

};
