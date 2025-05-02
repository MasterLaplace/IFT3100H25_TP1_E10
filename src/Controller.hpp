#pragma once

#include "AppGui.hpp"
#include "Camera.hpp"
#include "Canvas.hpp"
#include "Canvas3D.hpp"
#include "Controller.hpp"
#include "CurveUI.hpp"
#include "HistogramUI.hpp"
#include "MappingScene.hpp"
#include "Node.hpp"
#include "PBRScene.hpp"
#include "TriangulationUI.hpp"
#include "plugin/image/images.hpp"
#include "plugin/light/Light.hpp"
#include "plugin/states/states.hpp"
#include "plugin/texture/texture.hpp"
#include <string>
#include <vector>

using namespace plugin::states;
using namespace plugin::image;
using namespace plugin::texture;

enum View {
    VIEW_2D,
    VIEW_3D,
    VIEW_TRIANGULATION,
    VIEW_MAPPING,
    VIEW_PBR,
    VIEW_RAYTACING,
};

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
    void importCubemap();
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
    void drawCurve(curveType type);
    void drawTriangulation();
    void drawMapping();
    void drawPBR();
    void drawRaytracing();

    void onPrimitivePropertiesChanged(plugin::primitive::PrimitiveParams params);
    void onPrimitivePropertiesChanged(uint32_t id, plugin::primitive::PrimitiveParams params);
    void onBackgroundColorChanged(ofColor color);

    void onPrimitiveSelected(uint32_t id);
    void onImageSelected(const std::string &name);
    void onModelSelected(const std::string &name);
    void onPrefabSelected(const std::string &name);
    void onCubeMapSelected(const std::string &name);
    void onLightSelected(int i);

    void toggleCameraProjection();
    bool isCameraOrthographic();

    [[nodiscard]] std::vector<uint32_t> getPrimitiveId();
    [[nodiscard]] const std::vector<NodePrimitive *> &getCanvasNodes();
    [[nodiscard]] NodePrimitive *getNodeById(const uint32_t id);

    void collectPrimitiveId(NodePrimitive *node, std::vector<uint32_t> &ids);
    [[nodiscard]] int getSelectedNodeId();
    [[nodiscard]] int getSelectedLight();
    [[nodiscard]] std::string &getSelectedImageName();
    [[nodiscard]] std::string &getSelectedModelName();
    [[nodiscard]] std::string &getSelectedPrefabName();

    // Setter pour le mappage tonal et les couleurs.
    void setImageColorSpace(const std::string &name, plugin::image::ColourSpaces::Type colorSpace);
    void setImageExposure(const std::string &name, float exposure);
    void setImageGamma(const std::string &name, float gamma);
    void setImageToneMapping(const std::string &name, plugin::image::ToneMapping::Type toneMapping);

    // Getter pour la lumiere.
    plugin::light::Light::ModelType getLightModel() { return canvas3d->getLightModel(); }
    plugin::light::Light::LightType getLightType() { return canvas3d->getLightType(); }
    glm::vec3 getLightPosition() { return canvas3d->getLightPosition(); }
    glm::vec3 getLightDirection() { return canvas3d->getLightDirection(); }
    glm::vec3 getAmbientColor() { return canvas3d->getAmbientColor(); }
    glm::vec3 getDiffuseColor() { return canvas3d->getDiffuseColor(); }
    glm::vec3 getSpecularColor() { return canvas3d->getSpecularColor(); }
    float getLightAngle() { return canvas3d->getLightAngle(); }
    float getLightIntensity() { return canvas3d->getLightRange(); }

    // Setter pour la lumiere.
    void setLightModel(plugin::light::Light::ModelType lightModel) { canvas3d->setLightModel(lightModel); }
    void setLightType(plugin::light::Light::LightType lightType) { canvas3d->setLightType(lightType); }
    void setLightPosition(const glm::vec3 lightPosition) { canvas3d->setLightPosition(lightPosition); }
    void setLightDirection(const glm::vec3 lightDirection) { canvas3d->setLightDirection(lightDirection); }
    void setAmbientColor(const glm::vec3 ambientColor) { canvas3d->setAmbientColor(ambientColor); }
    void setDiffuseColor(const glm::vec3 diffuseColor) { canvas3d->setDiffuseColor(diffuseColor); }
    void setSpecularColor(const glm::vec3 specularColor) { canvas3d->setSpecularColor(specularColor); }
    void setLightAngle(float angle) { canvas3d->setLightAngle(angle); }
    void setLightIntensity(float intensity) { canvas3d->setLightRange(intensity); }

    // Getter pour les courbes.
    curveType getCurveType();
    ofPoint getCurvePoint();

    // Setter pour les courbes.
    void setCurveType(curveType _type);
    void setCurvePoint(ofPoint newPoint);
    void addPoint();
    void convertCurve();

    void createModelButtonPressed(const std::string &modelName);
    void createPrefabButtonPressed(const std::shared_ptr<plugin::primitive::Primitive> &primitive,
                                   const std::string &name);

    View currentView = VIEW_2D;

private:
    StateMachine stateMachine;
    Canvas *canvas2d;
    Canvas3D *canvas3d;
    AppGui gui;
    HistogramUI histogramUI;
    CurveUI curveUI;
    TriangulationUI triangulationUI;
    MappingScene mappingScene;
    PBRScene pbrScene;
    Exporting exporter;
    Camera camera;
    Skybox skybox;
};
#pragma once
