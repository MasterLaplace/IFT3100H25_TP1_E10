#pragma once

#include "ofxImGui.h"

class Controller;

class CurveUI {
public:
    void setup(Controller *_controller);
    void draw();

private:
    ofxImGui::Gui gui;
    Controller *controller;

    void drawOptionPanel();
};
