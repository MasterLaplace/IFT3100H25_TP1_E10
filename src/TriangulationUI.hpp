#pragma once

#include "ofxImGui.h"
#include "Delauney.hpp"

class Controller;

class TriangulationUI {
public:
    void setup(Controller *_controller);
    void draw();
    void shuffle() { delauney.shuffle(); }

    void onMousePressed(int x, int y) { delauney.onMousePressed(x, y); }
    void onMouseDragged(int x, int y) { delauney.onMouseDragged(x, y); }
    void onMouseReleased() { delauney.onMouseReleased(); }

private:
    ofxImGui::Gui gui;
    Controller *controller;

    Delauney delauney;

    void drawOptionPanel();
};
