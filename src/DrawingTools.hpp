#pragma once

/*
C'est une classe temporaire de UI juste pour donner une idée de comment l'implémenter.
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
    enum tool {
        POINT,
        LINE
    };

    tool selectedTool;
    void drawToolsPanel();
    void drawDynamicPanel();

    // Attributs du point.
    float pointSize = 5.0f;
    ofColor pointColor = ofColor::black;

    // Attributs de la ligne.
    float lineWidth = 2.0f;
    float lineColor[3] = {1.0f, 1.0f, 1.0f};
};
