#pragma once

#include "Canvas.hpp"
#include "Controller.hpp"
#include "DrawingTools.hpp"
#include "plugin/states/states.hpp"
#include <vector>
#include <string>

using namespace plugin::states;

class Controller2D : public Controller {

public:
    void setup();
    void update();
    void draw();
    void exit();

    // Methodes pour que "Application.cpp" puisse parler au Controlleur.
    void keyPressed(int key);
    void mouseMoved(glm::vec2 pos);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    // Methodes pour parler avec le gui.
    void drawPointButtonPressed();
    void onSizeChanged(float newSize);
    void onColorChanged(float _newColor[3]);
    void drawLineButtonPressed();
    std::vector<int> getPrimitiveId();
    void collectPrimitiveId(Node2D *node, std::vector<int> &ids);

private:
    StateMachine stateMachine;
    Canvas *canvas;
    DrawingTools gui;
};
