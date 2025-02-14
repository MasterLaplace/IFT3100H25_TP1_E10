#pragma once

#include "Controller.hpp"
#include "Canvas.hpp"
#include "DrawLineState.hpp"
#include "DrawPointState.hpp"
#include "DrawingTools.hpp"

class Controller2D : public Controller {

public:
    void setup();
    void update();
    void draw();
    void exit();

    // Methodes pour que "Application.cpp" puisse parler au Controlleur.
    void keyPressed(int key);
    void mouseMoved(glm::vec2 pos);

    // Methodes pour parler avec le gui.
    void drawPointButtonPressed();
    void onPointSizeChanged(float newSize);
    void onPointColorChanged(ofColor newColor);

    void drawLineButtonPressed();

private:
    StateMachine stateMachine;
    Canvas canvas;
    DrawingTools gui;
};
