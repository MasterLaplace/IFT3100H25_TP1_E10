#include "StateMachine.hpp"

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
        currentState->update();
    }
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
