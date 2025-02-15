#pragma once

#include "State.hpp"

class StateMachine {
public:
    glm::vec2 mousePosition;
    glm::vec2 mousePressedPosition;
    bool isMousePressed = false;

    StateMachine();
    ~StateMachine();

    void changeState(State *newState);
    void update();
    void draw();

    void onStrokeSizeChanged(float newSize);
    void onColorChanged(ofColor newColor);

private:
    State *currentState;
};
