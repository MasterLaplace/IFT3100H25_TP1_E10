#pragma once

#include "AppGui.hpp"
#include "Camera.hpp"
#include "Canvas.hpp"
#include "Canvas3D.hpp"
#include "Controller.hpp"
#include "CurveUI.hpp"
#include "HistogramUI.hpp"
#include "Node.hpp"
#include "plugin/image/images.hpp"
#include "plugin/light/light_header.hpp"
#include "plugin/states/states.hpp"
#include "plugin/texture/texture.hpp"
#include <string>
#include <vector>

using namespace plugin::states;
using namespace plugin::image;
using namespace plugin::texture;

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
    plugin::light::LightModel::Type getLightModel(int i);
    plugin::light::Light::lightType getLightType(int i);
    int getLightId(int i);
    int getSelectedLightId();
    glm::vec3 getLightPosition(int i);
    glm::vec3 getLightDirection(int i);
    glm::vec3 getLightColor(int i);
    glm::vec3& getAmbientColor(int i);
    glm::vec3 getDiffuseColor(int i);
    glm::vec3 getSpecularColor(int i);
    float getShininess(int i);
    float getLightAngle(int i);
    float getLightIntensity(int i);

    // Setter pour la lumiere.
    void setLightModel(plugin::light::LightModel::Type lightModel, int i);
    void setLightType(plugin::light::Light::lightType lightType, int i);
    void setLightPosition(const glm::vec3 lightPosition, int i);
    void setLightDirection(const glm::vec3 lightDirection, int i);
    void setLightColor(const glm::vec3 lightColor, int i);
    void setAmbientColor(const glm::vec3 ambientColor, int i);
    void setDiffuseColor(const glm::vec3 diffuseColor, int i);
    void setSpecularColor(const glm::vec3 specularColor, int i);
    void setShininess(float shininess, int i);
    void setLightAngle(float angle, int i);
    void setLightIntensity(float intensity, int i);

    // Ajouter et supprimer des lumieres
    std::vector<plugin::light::Light *> getLights() { return canvas3d->getLights(); }
    void addLight(plugin::light::Light::lightType type, plugin::light::LightModel::Type model);
    void deleteLight(int i);

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

    bool is3d = false;

private:
    StateMachine stateMachine;
    Canvas *canvas2d;
    Canvas3D *canvas3d;
    AppGui gui;
    HistogramUI histogramUI;
    CurveUI curveUI;
    Exporting exporter;
    Camera camera;
    Skybox skybox;
};
#pragma once
