#pragma once

/*
C'est une classe temporaire de UI juste pour donner une idée de comment l'implémenter.
*/

#include "Node.hpp"
#include "ofxImGui.h"
#include "plugin/primitive/primitive.hpp"
#include <unordered_map>

using namespace plugin::primitive;

class Controller;

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

    void setup(Controller *_controller);
    void draw();

private:
    ofxImGui::Gui gui;
    Controller *controller;

    void drawMenuBar();
    void drawToolsPanel();
    void drawDynamicPanel();
    void drawSceneGraph();
    void displayNode(NodePrimitive *node, uint32_t indentLevel = 0);
    void drawProprietiesPanel();

    void onToolSelected(tool _tool);

    void drawPointProperties(const std::shared_ptr<Point2D> &point);
    void drawLineProperties(const std::shared_ptr<Line2D> &line);
    void drawRectangleProperties(const std::shared_ptr<Rectangle> &rectangle);
    void drawEllipseProperties(const std::shared_ptr<Ellipse> &ellipse);
    void drawPolygonProperties(const std::shared_ptr<Polygon> &polygon);

    // Attributs générique
    float outlineWidth = 1.0f;
    float fillColor[3] = {0.0f, 0.0f, 0.0f};
    float outlineColor[3] = {0.0f, 0.0f, 0.0f};
    bool isFilled = true;
};
