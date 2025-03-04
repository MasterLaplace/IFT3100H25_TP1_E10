#pragma once

/*
C'est une classe temporaire de UI juste pour donner une idée de comment l'implémenter.
*/

#include "Node.hpp"
#include "ofxImGui.h"
#include <unordered_map>
#include "plugin/primitive/primitive.hpp"

class Controller2D;

class DrawingTools {
public:
    enum tool {
        SELECT,
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

    void drawMenuBar();
    void drawToolsPanel();
    void drawDynamicPanel();
    void drawSceneGraph();
    void displayNode(Node<Primitive2D> *node, int indentLevel = 0);
    void drawProprietiesPanel();
    
    void onToolSelected(tool _tool);
    
    void drawPointProperties(Point2D* point);
    void drawLineProperties(Line2D* line);
    void drawRectangleProperties(Rectangle* rectangle);
    void drawEllipseProperties(Ellipse* ellipse);
    void drawPolygonProperties(plugin::primitive::Polygon* polygon);

    // Attributs générique
    float outlineWidth = 1.0f;
    float fillColor[3] = {0.0f, 0.0f, 0.0f};
    float outlineColor[3] = {0.0f, 0.0f, 0.0f};
    bool isFilled = true;
    
    
};
