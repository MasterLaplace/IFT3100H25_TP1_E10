#pragma once

#include "AppGui.hpp"
#include "Camera.hpp"
#include "Canvas.hpp"
#include "Canvas3D.hpp"
#include "Controller.hpp"
#include "HistogramUI.hpp"
#include "Node.hpp"
#include "plugin/image/images.hpp"
#include "plugin/light/light.hpp"
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
    void importModel();
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
    void onImageSelected(const std::string &name);
    void onModelSelected(const std::string &name);
    void onPrefabSelected(const std::string &name);
    void onEndPositionChanged(uint32_t id, glm::vec2 newPos);

    void toggleCameraProjection();
    bool isCameraOrthographic();

    [[nodiscard]] std::vector<uint32_t> getPrimitiveId();
    [[nodiscard]] const std::vector<NodePrimitive *> &getCanvasNodes();
    [[nodiscard]] NodePrimitive *getNodeById(const uint32_t id);

    void collectPrimitiveId(NodePrimitive *node, std::vector<uint32_t> &ids);
    [[nodiscard]] int getSelectedNodeId();
    [[nodiscard]] std::string &getSelectedImageName();
    [[nodiscard]] std::string &getSelectedModelName();
    [[nodiscard]] std::string &getSelectedPrefabName();

    // Setter pour le mappage tonal et les couleurs.
    void setImageColorSpace(const std::string &name, plugin::image::ColourSpaces::Type colorSpace);
    void setImageExposure(const std::string &name, float exposure);
    void setImageGamma(const std::string &name, float gamma);
    void setImageToneMapping(const std::string &name, plugin::image::ToneMapping::Type toneMapping);

    // Getter pour la lumiere.
    plugin::light::LightModel::Type getLightModel();
    float *getAmbientColor();
    float *getDiffuseColor();

    // Setter pour la lumiere.
    void setLightModel(plugin::light::LightModel::Type lightModel);
    void setAmbientColor(const float *ambientColor);
    void setDiffuseColor(const float *diffuseColor);

    void createModelButtonPressed(const std::string &modelName);
    void createPrefabButtonPressed(const std::shared_ptr<plugin::primitive::Primitive> &primitive,
                                   const std::string &name);

    bool is3d = false;

private:
    StateMachine stateMachine;
    Canvas *canvas2d;
    Canvas3D *canvas3d;
    AppGui gui;
    HistogramUI histogramUI;
    Exporting exporter;
    Camera camera;
};
#pragma once
