#pragma once

/*
C'est une classe temporaire de UI juste pour donner une idée de comment l'implémenter.
*/

#include "Node.hpp"
#include "ofxImGui.h"
#include "plugin/image/ResourceManager.hpp"
#include <unordered_map>

using namespace plugin::primitive;

class Controller;

class AppGui {
public:
    enum tool : uint8_t {
        SELECT,
        POINT,
        LINE,
        RECTANGLE,
        ELLIPSE,
        POLYGON,
        BOX,
        ELLIPSOID,
        BACKGROUND,
        LIGHT
    };
    tool selectedTool;

    void setup(Controller *_controller);
    void draw();

private:
    ofxImGui::Gui gui;
    Controller *controller;

    void drawMenuBar();
    void drawToolsPanel2D();
    void drawToolsPanel3D();
    void drawDynamicPanel2D();
    void drawDynamicPanel3D();
    void drawSceneGraph();
    void displayNode(NodePrimitive *node, uint32_t indentLevel = 0);
    void drawProprietiesPanel();

    void onToolSelected(tool _tool);

    void drawPointProperties(const std::shared_ptr<Point2D> &point);
    void drawLineProperties(const std::shared_ptr<Line2D> &line);
    void drawRectangleProperties(const std::shared_ptr<plugin::primitive::Rectangle> &rectangle);
    void drawEllipseProperties(const std::shared_ptr<plugin::primitive::Ellipse> &ellipse);
    void drawPolygonProperties(const std::shared_ptr<plugin::primitive::Polygon> &polygon);
    void drawTransformProperties2D(const std::shared_ptr<Primitive> &primitive);
    void drawTransformProperties3D(const std::shared_ptr<Primitive> &primitive);
    void drawEllipsoidProperties(const std::shared_ptr<plugin::primitive::Ellipsoid> &ellipsoid);
    void drawBoxProperties(const std::shared_ptr<plugin::primitive::Box> &box);
    void drawObjModelProperties(const std::shared_ptr<plugin::primitive::ObjModel> &model);
    void drawImageProperties(const std::shared_ptr<plugin::image::Image> &image, const std::string &imageName);
    void drawModelProperties(const std::shared_ptr<plugin::primitive::ObjModel> &model, const std::string &modelName);
    void drawPrefabProperties(const std::shared_ptr<plugin::primitive::Primitive> &prefab,
                              const std::string &prefabName);

    // Attributs générique
    float backgroundColor[3] = {1.0f, 1.0f, 1.0f};
    float outlineWidth = 1.0f;
    float fillColor[3] = {0.0f, 0.0f, 0.0f};
    float outlineColor[3] = {0.0f, 0.0f, 0.0f};
    bool isFilled = true;
};
