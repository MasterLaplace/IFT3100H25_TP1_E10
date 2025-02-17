#include "StateMachine.hpp"

namespace plugin::states {

StateMachine::StateMachine() { currentState = nullptr; }

StateMachine::~StateMachine()
{
    if (currentState)
    {
        delete currentState;
    }
}

void StateMachine::changeState(State *newState)
{
    if (currentState)
    {
        currentState->exit();
        delete currentState;
    }

    currentState = newState;

    if (currentState)
    {
        currentState->enter();
    }
}

void StateMachine::update()
{
    if (currentState)
    {
        currentState->mousePosition = mousePosition;
        currentState->mousePressedPosition = mousePressedPosition;
        currentState->isMousePressed = isMousePressed;
        currentState->update();
    }
}

void StateMachine::mousePressed(int x, int y, int button)
{
    // On transmet la position de la sourie à l'état.
    // L'input provient de Application.
    mousePressedPosition = glm::vec2(x, y);
    isMousePressed = true;

    currentState->mousePressed(x, y, button);
}

void StateMachine::mouseReleased(int x, int y, int button)
{
    isMousePressed = false;
    currentState->mouseReleased(x, y, button);
}

void StateMachine::draw()
{
    if (currentState)
    {
        currentState->draw();
    }
}

void StateMachine::onStrokeSizeChanged(float newSize) { currentState->strokeSize = newSize; }

void StateMachine::onColorChanged(ofColor newColor) { currentState->color = newColor; }

void StateMachine::onPrimitiveSelected(int id) { currentState->selectedPrimitiveId = id; }

} // namespace plugin::states
