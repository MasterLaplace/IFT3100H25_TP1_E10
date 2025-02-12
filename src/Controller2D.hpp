#pragma once

#include "Controller.hpp"
#include "DrawLineState.hpp"
#include "DrawPointState.hpp"
#include "DrawingTools.hpp"

class Controller2D : public Controller {

public:
    void setup() override;
    void update() override;
    void draw() override;
    void exit() override;

    // Methodes pour que "Application.cpp" puisse parler au Controlleur.
    void keyPressed(int key) override;
    void mouseMoved(glm::vec2 pos) override;

    // Methodes pour parler avec le gui.
    void drawPointButtonPressed();
    void drawLineButtonPressed();

private:
    StateMachine stateMachine;
    DrawingTools gui;
};
