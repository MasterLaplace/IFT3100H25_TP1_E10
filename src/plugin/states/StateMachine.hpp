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
    void mouseReleased(Canvas *canvas);
    void draw();

    void onOutlineWidthChanged(float newWidth);
    void onFillColorChanged(ofColor newColor);
    void onOutlineColorChanged(ofColor newColor);
    void onFilledChanged(bool isFilled);
    void onPrimitiveSelected(int id);
    int getSelectedNodeId();

private:
    State *currentState;
};

} // namespace plugin::states
