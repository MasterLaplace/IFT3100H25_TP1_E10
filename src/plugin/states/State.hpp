#pragma once

#include "ofMain.h"
#include <iostream>
#include "Canvas.hpp"

namespace plugin::states {

class State {
public:
    virtual ~State() = default;
    virtual void enter() = 0;
    virtual void update() = 0;
    virtual void mousePressed(int x, int y, int button) = 0;
    virtual void mouseReleased(Canvas *canvas) = 0;
    virtual void draw() = 0;
    virtual void exit() = 0;

public:
    glm::vec2 mousePosition;
    glm::vec2 mousePressedPosition;
    bool isMousePressed = false;
    int selectedPrimitiveId = -1;
    std::string selectedImageName = "";
    std::string selectedModelName = "";
    std::string selectedPrefabName = "";

    float outlineWidth = 1.0f;
    ofColor fillColor = ofColor::black;
    ofColor outlineColor = ofColor::black;
    bool isFilled = true;
};

} // namespace plugin::states
