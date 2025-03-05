#pragma once

#include "AppGui.hpp"
#include "Camera.hpp"
#include "Canvas.hpp"
#include "Controller.hpp"
#include "HistogramUI.hpp"
#include "Importation.hpp"
#include "Node.hpp"
#include "plugin/image/image.hpp"
#include "plugin/states/states.hpp"
#include <string>
#include <vector>

using namespace plugin::states;
using namespace plugin::image;

class Controller {
public:
    void setup();
    void update();
    void draw();
    void exit();

    // Methodes pour que "Application.cpp" puisse parler au Controlleur.
    void keyReleased(int key);
    void mouseMoved(glm::vec2 pos);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    void toggleCanvas();

    // Methodes pour parler avec le gui.
    void importImage();
    void exportImage();

    void onToolSelected(AppGui::tool tool);
    void selectionButtonPressed();
    void drawPointButtonPressed();
    void drawLineButtonPressed();
    void drawRectangleButtonPressed();
    void drawEllipseButtonPressed();
    void drawPolygonButtonPressed();
    void deletePrimitiveButtonPressed(uint32_t id);
    void drawHistogram(int color);

    void onPrimitivePropertiesChanged(plugin::primitive::PrimitiveParams params);
    void onPrimitivePropertiesChanged(uint32_t id, plugin::primitive::PrimitiveParams params);
    void onBackgroundColorChanged(ofColor color);

    void onPrimitiveSelected(uint32_t id);
    void onEndPositionChanged(uint32_t id, glm::vec2 newPos);
    
    void toggleCameraProjection();
    bool isCameraOrthographic();

    [[nodiscard]] std::vector<uint32_t> getPrimitiveId();
    [[nodiscard]] const std::vector<NodePrimitive *> &getCanvasNodes();
    [[nodiscard]] NodePrimitive *getNodeById(const uint32_t id);

    void collectPrimitiveId(NodePrimitive *node, std::vector<uint32_t> &ids);
    [[nodiscard]] int getSelectedNodeId();

    bool is3d = false;

private:
    StateMachine stateMachine;
    Canvas *canvas2d;
    Canvas *canvas3d;
    AppGui gui;
    HistogramUI histogramUI;
    Importation importer;
    Exporting exporter;
    Camera camera;
};
