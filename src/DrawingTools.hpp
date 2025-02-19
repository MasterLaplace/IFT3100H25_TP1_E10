#pragma once

/*
C'est une classe temporaire de UI juste pour donner une idée de comment l'implémenter.
*/

#include "Node2D.hpp"
#include "ofxImGui.h"
#include <unordered_map>

class Controller2D;

class DrawingTools {
public:
    enum tool {
        POINT,
        LINE,
        RECTANGLE,
        ELLIPSE,
        POLYGON
    };
    tool selectedTool;

    void setup(Controller2D *_controller);
    void draw();

private:
    ofxImGui::Gui gui;
    Controller2D *controller;

    void drawToolsPanel();
    void drawDynamicPanel();
    void drawSceneGraph();
    void displayNode(Node2D *node, int indentLevel = 0,
                     std::unordered_multimap<int, Node2D *> &displayedNodes = std::unordered_multimap<int, Node2D *>());

    int selectedPrimitiveId = -1;

    // Attributs générique
    float fillColor[3] = {0.0f, 0.0f, 0.0f};

    // Attributs du point.
    float pointSize = 5.0f;
    float pointColor[3] = {0.0f, 0.0f, 0.0f};

    // Attributs de la ligne.
    float lineWidth = 2.0f;
    float lineColor[3] = {0.0f, 0.0f, 0.0f};
};
