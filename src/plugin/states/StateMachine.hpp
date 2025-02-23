#pragma once

#include "Canvas.hpp"
#include "State.hpp"

namespace plugin::states {

class StateMachine {
public:
    glm::vec2 mousePosition;
    glm::vec2 mousePressedPosition;
    bool isMousePressed = false;

    StateMachine();
    ~StateMachine();

    State *getCurrentState();

    void changeState(State *newState);
    void update();
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void draw();

    void onStrokeSizeChanged(float newSize);
    void onColorChanged(ofColor newColor);
    void onPrimitiveSelected(int id);

private:
    State *currentState;
};

} // namespace plugin::states
