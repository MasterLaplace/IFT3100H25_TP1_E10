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
    void onAmbientColorChanged(ofColor newColor) { currentState->ambientColor = newColor; }
    void onDiffuseColorChanged(ofColor newColor) { currentState->diffuseColor = newColor; }
    void onSpecularColorChanged(ofColor newColor) { currentState->specularColor = newColor; }
    void onShininessChanged(float newShininess) { currentState->shininess = newShininess; }
    void onOutlineColorChanged(ofColor newColor);
    void onFilledChanged(bool isFilled);
    void onPrimitiveSelected(int id);
    void onLightSelected(int i);
    void onImageSelected(const std::string &name);
    void onModelSelected(const std::string &name);
    void onPrefabSelected(const std::string &name);

    [[nodiscard]] int getSelectedNodeId();
    [[nodiscard]] std::string &getSelectedImageName();
    [[nodiscard]] std::string &getSelectedModelName();
    [[nodiscard]] std::string &getSelectedPrefabName();
    [[nodiscard]] int getSelectedLight();

private:
    State *currentState;
};

} // namespace plugin::states
