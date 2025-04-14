#pragma once

#include "Canvas.hpp"
#include "ofMain.h"
#include <iostream>

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
    int selectedLight = -1;
    std::string selectedImageName = "";
    std::string selectedModelName = "";
    std::string selectedPrefabName = "";

    float outlineWidth = 1.0f;
    ofColor fillColor = ofColor::black;
    ofColor ambientColor = ofColor{0, 0, 0};
    ofColor diffuseColor = ofColor{0.2f * 255, 0.2f * 255, 0.2f * 255};
    ofColor specularColor = ofColor{255, 255, 255};
    float shininess = 32.0f;
    ofColor outlineColor = ofColor::black;
    bool isFilled = true;
};

} // namespace plugin::states
