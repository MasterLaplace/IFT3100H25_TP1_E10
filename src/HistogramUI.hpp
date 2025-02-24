#pragma once

#include "ofxImGui.h"

class Controller2D;

class HistogramUI {
public:
    void setup(Controller2D *_controller);
    void draw();

private:
    ofxImGui::Gui gui;
    Controller2D *controller;

    void drawOptionPanel();
};
