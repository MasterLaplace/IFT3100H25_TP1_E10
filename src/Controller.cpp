#include "Controller.hpp"

void Controller::setup()
{
    canvas2d = new Canvas();
    canvas3d = new Canvas3D();

    // On initialise l'�tat du Controlleur pour dessiner des points.
    // On pourrait changer l'�tat initial au besoin.
    stateMachine.changeState(new DrawPointState());

    // C'est ici qu'on va initialiser l'interface pour le 2D.
    gui.setup(this);
    histogramUI.setup(this);
    curveUI.setup(this);
    triangulationUI.setup(this);
    mappingScene.setup();
    pbrScene.setup();
}

void Controller::update()
{
    stateMachine.update();
    camera.update();
}

void Controller::draw()
{
    ofEnableDepthTest();
    if (dynamic_cast<DrawHistogramState *>(stateMachine.getCurrentState()) != nullptr)
    {
        stateMachine.draw();
        histogramUI.draw();
    }
    else if (dynamic_cast<DrawCoonsState *>(stateMachine.getCurrentState()) != nullptr)
    {
        stateMachine.draw();
        curveUI.draw();
    }
    else if (currentView == VIEW_3D)
    {
        camera.begin();
        canvas3d->setViewMatrix(camera.getModelViewMatrix());
        canvas3d->draw();
        camera.end();
        exporter.setPixels();
        stateMachine.draw();
        gui.draw();
    }
    else if (currentView == VIEW_TRIANGULATION)
    {
        gui.getGui()->begin();
        triangulationUI.draw();
        gui.drawMenu();
        gui.getGui()->end();
    }
    else if (currentView == VIEW_MAPPING)
    {
        gui.getGui()->begin();
        mappingScene.draw();
        gui.drawMenu();
        gui.getGui()->end();
    }
    else if (currentView == VIEW_PBR)
    {
        gui.getGui()->begin();
        pbrScene.draw();
        gui.drawMenu();
        gui.getGui()->end();
    }
    else if (currentView == VIEW_2D)
    {
        canvas2d->draw();
        exporter.setPixels();
        stateMachine.draw();
        gui.draw();
    }
    else if (currentView == VIEW_RAYTRACING)
    {
        gui.getGui()->begin();
        raytracingScene.draw();
        gui.drawMenu();
        gui.getGui()->end();
    }
    ofDisableDepthTest();
}

void Controller::exit() {}

void Controller::keyReleased(int key)
{
    // C'est les raccourcis claviers.
    // Les input proviennent de Application.
    switch (key)
    {
    case 'p':
    case 'P':
        drawPointButtonPressed();
        gui.selectedTool = AppGui::tool::POINT;
        break;
    case 'l':
    case 'L':
        drawLineButtonPressed();
        gui.selectedTool = AppGui::tool::LINE;
        break;
    case 'r':
    case 'R':
        drawRectangleButtonPressed();
        gui.selectedTool = AppGui::tool::RECTANGLE;
        break;
    case 'e':
    case 'E':
        drawEllipseButtonPressed();
        gui.selectedTool = AppGui::tool::ELLIPSE;
        break;
    case 'g':
    case 'G':
        drawPolygonButtonPressed();
        gui.selectedTool = AppGui::tool::POLYGON;
        break;
    default: break;
    }
}

void Controller::mouseMoved(glm::vec2 pos)
{
    if (currentView == VIEW_TRIANGULATION)
    {
        triangulationUI.onMouseDragged(pos.x, pos.y);
    }
    // On transmet la position de la sourie � l'�tat.
    // L'input provient de Application.
    stateMachine.mousePosition = pos;
}

void Controller::mousePressed(int x, int y, int button)
{
    if (currentView == VIEW_TRIANGULATION)
    {
        triangulationUI.onMousePressed(x, y);
    }
    stateMachine.mousePressed(x, y, button);
}

void Controller::mouseReleased(int x, int y, int button)
{
    if (currentView == VIEW_TRIANGULATION)
    {
        triangulationUI.onMouseReleased();
    }
    stateMachine.mouseReleased((currentView == VIEW_3D) ? canvas3d : canvas2d);
}

void Controller::toggleCanvas()
{
    if (currentView == VIEW_3D)
    {
        currentView = VIEW_2D;
    }
    else
    {
        currentView = VIEW_3D;
    }
}

void Controller::importImage() { plugin::image::Importing::importImage(); }

void Controller::importModel() { plugin::image::Importing::importModel(); }

void Controller::exportImage() { exporter.exportImage(); }

void Controller::importCubemap() { plugin::image::Importing::importCubeMap(); }

// Cette méthode change les propriétés de la primitive à dessiner.
void Controller::onPrimitivePropertiesChanged(plugin::primitive::PrimitiveParams params)
{
    stateMachine.onOutlineWidthChanged(params.outlineWidth);
    stateMachine.onFillColorChanged(params.fillColor);
    stateMachine.onAmbientColorChanged(params.ambientColor);
    stateMachine.onDiffuseColorChanged(params.diffuseColor);
    stateMachine.onSpecularColorChanged(params.specularColor);
    stateMachine.onShininessChanged(params.shininess);
    stateMachine.onOutlineColorChanged(params.outlineColor);
    stateMachine.onFilledChanged(params.isFilled);
}

// Cette méthode change les propriétés d'une primitive existante.
void Controller::onPrimitivePropertiesChanged(uint32_t id, plugin::primitive::PrimitiveParams params)
{
    NodePrimitive *node = getNodeById(id);
    if (!node)
        return;

    node->getPrimitive()->param.position = params.position;
    node->getPrimitive()->param.fillColor = params.fillColor;
    node->getPrimitive()->param.ambientColor = params.ambientColor;
    node->getPrimitive()->param.diffuseColor = params.diffuseColor;
    node->getPrimitive()->param.specularColor = params.specularColor;
    node->getPrimitive()->param.shininess = params.shininess;
    node->getPrimitive()->param.outlineColor = params.outlineColor;
    node->getPrimitive()->param.outlineWidth = params.outlineWidth;
    node->getPrimitive()->param.isFilled = params.isFilled;
}

void Controller::onBackgroundColorChanged(ofColor color)
{
    (currentView == VIEW_3D) ? canvas3d->setBackgroundColor(color) : canvas2d->setBackgroundColor(color);
}

void Controller::onPrimitiveSelected(uint32_t id) { stateMachine.onPrimitiveSelected(id); }
void Controller::onImageSelected(const std::string &name) { stateMachine.onImageSelected(name); }
void Controller::onModelSelected(const std::string &name) { stateMachine.onModelSelected(name); }
void Controller::onPrefabSelected(const std::string &name) { stateMachine.onPrefabSelected(name); }
void Controller::onCubeMapSelected(const std::string &name) { skybox.load(name); }
void Controller::onLightSelected(int i) { stateMachine.onLightSelected(i); }

std::vector<uint32_t> Controller::getPrimitiveId()
{
    std::vector<uint32_t> ids;
    for (auto &node : (currentView == VIEW_3D) ? canvas3d->nodes : canvas2d->nodes)
    {
        collectPrimitiveId(node, ids);
    }
    return ids;
}

const std::vector<NodePrimitive *> &Controller::getCanvasNodes()
{
    return (currentView == VIEW_3D) ? canvas3d->nodes : canvas2d->nodes;
}

NodePrimitive *Controller::getNodeById(const uint32_t id)
{
    return (currentView == VIEW_3D) ? canvas3d->getChildById(id) : canvas2d->getChildById(id);
}

void Controller::collectPrimitiveId(NodePrimitive *node, std::vector<uint32_t> &ids)
{
    ids.push_back(node->getId());

    for (auto &child : node->getChildren())
    {
        collectPrimitiveId(child, ids);
    }
}

int Controller::getSelectedNodeId() { return stateMachine.getSelectedNodeId(); }

int Controller::getSelectedLight() { return stateMachine.getSelectedLight(); }

std::string &Controller::getSelectedImageName() { return stateMachine.getSelectedImageName(); }

std::string &Controller::getSelectedModelName() { return stateMachine.getSelectedModelName(); }

std::string &Controller::getSelectedPrefabName() { return stateMachine.getSelectedPrefabName(); }

void Controller::onToolSelected(AppGui::tool _tool)
{
    switch (_tool)
    {
    case AppGui::tool::SELECT: stateMachine.changeState(new SelectionState()); break;
    case AppGui::tool::POINT: stateMachine.changeState(new DrawPointState()); break;
    case AppGui::tool::LINE: stateMachine.changeState(new DrawLineState()); break;
    case AppGui::tool::RECTANGLE: stateMachine.changeState(new DrawRectangleState()); break;
    case AppGui::tool::ELLIPSE: stateMachine.changeState(new DrawEllipseState()); break;
    case AppGui::tool::POLYGON: stateMachine.changeState(new DrawPolygonState()); break;
    case AppGui::tool::BOX: stateMachine.changeState(new DrawBoxState()); break;
    case AppGui::tool::ELLIPSOID: stateMachine.changeState(new DrawEllipsoidState()); break;
    default: break;
    }
}

void Controller::selectionButtonPressed() { stateMachine.changeState(new SelectionState()); }

void Controller::drawPointButtonPressed() { stateMachine.changeState(new DrawPointState()); }

void Controller::drawLineButtonPressed() { stateMachine.changeState(new DrawLineState()); }

void Controller::drawRectangleButtonPressed() { stateMachine.changeState(new DrawRectangleState()); }

void Controller::drawEllipseButtonPressed() { stateMachine.changeState(new DrawEllipseState()); }

void Controller::drawPolygonButtonPressed() { stateMachine.changeState(new DrawPolygonState()); }

void Controller::deletePrimitiveButtonPressed(uint32_t id)
{
    (currentView == VIEW_3D) ? canvas3d->removeNode(id) : canvas2d->removeNode(id);
    stateMachine.onPrimitiveSelected(-1);
}

void Controller::createPrefabButtonPressed(const std::shared_ptr<plugin::primitive::Primitive> &primitive,
                                           const std::string &name)
{
    bool result = plugin::image::ResourceManager::instance()->addPrefab(primitive, name);
    if (!result)
    {
        ofLogError("Controller") << "Failed to create prefab";
    }
}

void Controller::drawHistogram(int color)
{
    if (dynamic_cast<DrawHistogramState *>(stateMachine.getCurrentState()) == nullptr)
    {
        stateMachine.changeState(new DrawHistogramState(color));
    }
    else
    {
        DrawHistogramState *state = dynamic_cast<DrawHistogramState *>(stateMachine.getCurrentState());
        state->setColor(color);
    }
}

void Controller::drawCurve(curveType type) { stateMachine.changeState(new DrawCoonsState(type)); }

void Controller::drawTriangulation() { currentView = VIEW_TRIANGULATION; }

void Controller::drawMapping() { currentView = VIEW_MAPPING; }

void Controller::drawPBR() { currentView = VIEW_PBR; }

void Controller::drawRaytracing() {
    currentView = VIEW_RAYTRACING;

    plugin::raytracing::Raytracing::CreateInfo raytracingParams;
    raytracingParams.position = glm::dvec3(0, 0, 0);
    raytracingParams.direction = glm::dvec3(0, 0, -1);
    raytracingParams.background_color = glm::dvec3(0.0);
    raytracingParams.fov = 0.5135; // ~30 degrés
    raytracingParams.depth = 5;
    raytracingParams.width = 800;
    raytracingParams.height = 600;
    raytracingParams.ray_per_pixel = 16;

    raytracingScene.setup(raytracingParams, canvas3d->getPrimitives());
}

void Controller::toggleCameraProjection() { camera.toggleProjection(); }

bool Controller::isCameraOrthographic() { return camera.isOrthographic; }

void Controller::setImageColorSpace(const std::string &name, plugin::image::ColourSpaces::Type colorSpace)
{
    auto image = plugin::image::ResourceManager::instance()->getImage(name);
    if (image.has_value())
    {
        image->get()->convert(colorSpace);
    }
}

void Controller::setImageExposure(const std::string &name, float exposure)
{
    auto image = plugin::image::ResourceManager::instance()->getImage(name);
    if (image.has_value())
    {
        image->get()->setExposure(exposure);
    }
}

void Controller::setImageGamma(const std::string &name, float gamma)
{
    auto image = plugin::image::ResourceManager::instance()->getImage(name);
    if (image.has_value())
    {
        image->get()->setGamma(gamma);
    }
}

void Controller::setImageToneMapping(const std::string &name, plugin::image::ToneMapping::Type toneMapping)
{
    auto image = plugin::image::ResourceManager::instance()->getImage(name);
    if (image.has_value())
    {
        image->get()->setToneMapping(toneMapping);
    }
}

curveType Controller::getCurveType()
{
    if (dynamic_cast<DrawCoonsState *>(stateMachine.getCurrentState()) == nullptr)
    {
        std::cerr << "Erreur : La fonction getCurveType() du controleur ne peut pas etre appelee si l'etat n'est "
                     "pas un DrawCoonsState."
                  << std::endl;
        return curveType::NONE;
    }
    else
    {
        DrawCoonsState *state = dynamic_cast<DrawCoonsState *>(stateMachine.getCurrentState());
        return state->getCurveType();
    }
}

ofPoint Controller::getCurvePoint()
{
    if (dynamic_cast<DrawCoonsState *>(stateMachine.getCurrentState()) == nullptr)
    {
        std::cerr << "Erreur : La fonction getCurvePoint() du controleur ne peut pas etre appelee si l'etat n'est "
                     "pas un DrawCoonsState."
                  << std::endl;
        return ofPoint();
    }
    else
    {
        DrawCoonsState *state = dynamic_cast<DrawCoonsState *>(stateMachine.getCurrentState());
        return state->getSelectedPoint();
    }
}

void Controller::setCurveType(curveType _type)
{
    if (dynamic_cast<DrawCoonsState *>(stateMachine.getCurrentState()) == nullptr)
    {
        std::cerr << "Erreur : La fonction setCurveType() du controleur ne peut pas etre appelee si l'etat n'est "
                     "pas un DrawCoonsState."
                  << std::endl;
    }
    else
    {
        DrawCoonsState *state = dynamic_cast<DrawCoonsState *>(stateMachine.getCurrentState());
        state->setCurveType(_type);
    }
}

void Controller::setCurvePoint(ofPoint newPoint)
{
    if (dynamic_cast<DrawCoonsState *>(stateMachine.getCurrentState()) == nullptr)
    {
        std::cerr << "Erreur : La fonction setCurvePoint() du controleur ne peut pas etre appelee si l'etat n'est "
                     "pas un DrawCoonsState."
                  << std::endl;
    }
    else
    {
        DrawCoonsState *state = dynamic_cast<DrawCoonsState *>(stateMachine.getCurrentState());
        state->setPoint(newPoint);
    }
}

void Controller::addPoint()
{
    if (dynamic_cast<DrawCoonsState *>(stateMachine.getCurrentState()) == nullptr)
    {
        std::cerr << "Erreur : La fonction addPoint() du controleur ne peut pas etre appelee si l'etat n'est "
                     "pas un DrawCoonsState."
                  << std::endl;
    }
    else
    {
        DrawCoonsState *state = dynamic_cast<DrawCoonsState *>(stateMachine.getCurrentState());
        state->addPoint();
    }
}

void Controller::convertCurve()
{
    if (dynamic_cast<DrawCoonsState *>(stateMachine.getCurrentState()) == nullptr)
    {
        std::cerr << "Erreur : La fonction convertCurve() du controleur ne peut pas etre appelee si l'etat n'est "
                     "pas un DrawCoonsState."
                  << std::endl;
    }
    else
    {
        DrawCoonsState *state = dynamic_cast<DrawCoonsState *>(stateMachine.getCurrentState());
        state->convertCurve();
    }
}

void Controller::createModelButtonPressed(const std::string &modelName)
{
    auto model = plugin::image::ResourceManager::instance()->getModel(modelName);
    if (model.has_value())
    {
        PrimitiveParams params;
        params.position = glm::vec3(0, 0, 0);
        params.fillColor = ofColor(100, 100, 0);
        params.outlineColor = ofColor(0, 0, 0);
        params.outlineWidth = 1.0f;
        params.isFilled = true;

        auto node = new NodePrimitive(std::make_shared<plugin::primitive::ObjModel>(params, *model), "Model");
        (currentView == VIEW_3D) ? canvas3d->addNode(node) : canvas2d->addNode(node);
    }
}
