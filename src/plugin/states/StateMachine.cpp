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

State *StateMachine::getCurrentState() { return currentState; }

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
    // On transmet la position de la sourie � l'�tat.
    // L'input provient de Application.
    mousePressedPosition = glm::vec2(x, y);
    isMousePressed = true;

    currentState->mousePressed(x, y, button);
}

void StateMachine::mouseReleased(Canvas *canvas)
{
    isMousePressed = false;
    currentState->mouseReleased(canvas);
}

void StateMachine::draw()
{
    if (currentState)
    {
        currentState->draw();
    }
}

void StateMachine::onOutlineWidthChanged(float newSize) { currentState->outlineWidth = newSize; }

void StateMachine::onFillColorChanged(ofColor newColor) { currentState->fillColor = newColor; }

void StateMachine::onOutlineColorChanged(ofColor newColor) { currentState->outlineColor = newColor; }

void StateMachine::onFilledChanged(bool isFilled) { currentState->isFilled = isFilled; }

void StateMachine::onPrimitiveSelected(int id)
{
    currentState->selectedPrimitiveId = id;
    currentState->selectedLight = -1;
    currentState->selectedImageName = "";
    currentState->selectedModelName = "";
    currentState->selectedPrefabName = "";
}
void StateMachine::onLightSelected(int i) 
{
    currentState->selectedPrimitiveId = -1;
    currentState->selectedLight = i;
    currentState->selectedImageName = "";
    currentState->selectedModelName = "";
    currentState->selectedPrefabName = "";
}
void StateMachine::onImageSelected(const std::string &name)
{
    currentState->selectedPrimitiveId = -1;
    currentState->selectedLight = -1;
    currentState->selectedImageName = name;
    currentState->selectedModelName = "";
    currentState->selectedPrefabName = "";
}
void StateMachine::onModelSelected(const std::string &name)
{
    currentState->selectedPrimitiveId = -1;
    currentState->selectedLight = -1;
    currentState->selectedImageName = "";
    currentState->selectedModelName = name;
    currentState->selectedPrefabName = "";
}
void StateMachine::onPrefabSelected(const std::string &name)
{
    currentState->selectedPrimitiveId = -1;
    currentState->selectedLight = -1;
    currentState->selectedImageName = "";
    currentState->selectedModelName = "";
    currentState->selectedPrefabName = name;
}

int StateMachine::getSelectedNodeId() { return currentState->selectedPrimitiveId; }
std::string &StateMachine::getSelectedImageName() { return currentState->selectedImageName; }
std::string &StateMachine::getSelectedModelName() { return currentState->selectedModelName; }
std::string &StateMachine::getSelectedPrefabName() { return currentState->selectedPrefabName; }

int StateMachine::getSelectedLight() { return currentState->selectedLight; }

} // namespace plugin::states
