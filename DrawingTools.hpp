#pragma once

/*
C'est une classe temporaire de UI juste pour donner une id�e de comment l'impl�menter.
*/

#include "ofxImGui.h"

class Controller2D;

class DrawingTools {
public:
    void setup(Controller2D *_controller);
    void draw();

private:
    ofxImGui::Gui gui;
    Controller2D *controller;
};
