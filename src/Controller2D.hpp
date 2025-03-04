#pragma once

#include "Canvas.hpp"
#include "Controller.hpp"
#include "DrawingTools.hpp"
#include "HistogramUI.hpp"
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

    void onToolSelected(DrawingTools::tool tool);
    void selectionButtonPressed();
    void drawPointButtonPressed();
    void drawLineButtonPressed();
    void drawRectangleButtonPressed();
    void drawEllipseButtonPressed();
    void drawPolygonButtonPressed();
    void deletePrimitiveButtonPressed(int id);
    void drawHistogram(int color);
    
    void onPrimitivePropertiesChanged(Primitive2DParams params);
    void onPrimitivePropertiesChanged(int id, Primitive2DParams params);
    
    void onPrimitiveSelected(int id);
    void onEndPositionChanged(int id, glm::vec2 newPos);

    std::vector<int> getPrimitiveId();
    std::vector<Node<Primitive2D> *> getCanvasNodes();
    Node<Primitive2D> *getNodeById(const int id);
    
    void collectPrimitiveId(Node<Primitive2D> *node, std::vector<int> &ids);
    int getSelectedNodeId();

private:
    StateMachine stateMachine;
    Canvas *canvas;
    DrawingTools gui;
    HistogramUI histogramUI;
    Importation importer;
    Exporting exporter;
};
