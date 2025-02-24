#pragma once

#include "Canvas.hpp"
#include "Controller.hpp"
#include "DrawingTools.hpp"
#include "Importation.hpp"
#include "plugin/image/image.hpp"
#include "plugin/states/states.hpp"
#include <string>
#include <vector>

using namespace plugin::states;
using namespace plugin::image;

class Controller2D : public Controller {

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

    // Methodes pour parler avec le gui.
    void importImage();
    void exportImage();

    void drawPointButtonPressed();
    void drawLineButtonPressed();
    void drawRectangleButtonPressed();
    void drawHistogram(int color);

    void onSizeChanged(float newSize);
    void onSizeChanged(int id, float newSize);
    void onColorChanged(float _newColor[3]);
    void onColorChanged(int id, float _newColor[3]);
    void onPrimitiveSelected(int id);
    void onPositionChanged(int id, glm::vec2 newPos);
    void onEndPositionChanged(int id, glm::vec2 newPos);

    std::vector<int> getPrimitiveId();
    std::vector<Node2D *> getCanvasNodes();
    Node2D *getNodeById(const int id);
    void getNodeColor(const int id, float color[3]);
    void collectPrimitiveId(Node2D *node, std::vector<int> &ids);

private:
    StateMachine stateMachine;
    Canvas *canvas;
    DrawingTools gui;
    Importation importer;
    Exporting exporter;
    
};
