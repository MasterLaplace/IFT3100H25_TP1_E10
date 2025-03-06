#include "Controller.hpp"

void Controller::setup()
{
    canvas2d = new Canvas();
    canvas3d = new Canvas();

    // Test pour voir un cube
    PrimitiveParams param;
    param.position = glm::vec3(0, 0, 0);
    param.outlineWidth = 1.0f;
    param.fillColor = ofColor(100, 100, 0);
    param.outlineColor = ofColor(0, 0, 0);
    param.isFilled = true;

    // On initialise l'�tat du Controlleur pour dessiner des points.
    // On pourrait changer l'�tat initial au besoin.
    stateMachine.changeState(new DrawPointState());

    // C'est ici qu'on va initialiser l'interface pour le 2D.
    gui.setup(this);
    histogramUI.setup(this);

    importer.setup();
}

void Controller::update()
{
    importer.update();
    stateMachine.update();
    camera.update();
}

void Controller::draw()
{
    if (is3d)
    {
        camera.begin();
        canvas3d->draw();
        camera.end();
    }
    else
    {
        canvas2d->draw();
        // On dessine ensuite l'image import�e.
        importer.draw();
    }

    // On sauvegarde les pixels de l'image et des formes sans le ui et la souris
    exporter.setPixels();

    // C'est Controlleur qui demande � son �tat de dessiner des choses en lien avec l'�tat.
    // Par exemple, si on est dans l'�tat DrawRectangleState, on va dessiner le fantome du rectangle.
    stateMachine.draw();

    // C'est le Controlleur qui demande au GUI de s'afficher aussi en fonction de l'etat.
    if (dynamic_cast<DrawHistogramState *>(stateMachine.getCurrentState()) != nullptr)
    {
        histogramUI.draw();
    }

    else
    {
        gui.draw();
    }
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
    case 'i':
    case 'I': importer.importImage(); break;
    case 'e':
    case 'E': exporter.exportImage(); break;
    default: break;
    }
}

void Controller::mouseMoved(glm::vec2 pos)
{

    // On transmet la position de la sourie � l'�tat.
    // L'input provient de Application.
    stateMachine.mousePosition = pos;
}

void Controller::mousePressed(int x, int y, int button) { stateMachine.mousePressed(x, y, button); }

void Controller::mouseReleased(int x, int y, int button) { stateMachine.mouseReleased((is3d) ? canvas3d : canvas2d); }

void Controller::toggleCanvas() { is3d = !is3d; }

void Controller::importImage() { plugin::image::Importing::importImage(); }

void Controller::importModel() { plugin::image::Importing::importModel(); }

void Controller::exportImage() { exporter.exportImage(); }

// Cette méthode change les propriétés de la primitive à dessiner.
void Controller::onPrimitivePropertiesChanged(plugin::primitive::PrimitiveParams params)
{
    stateMachine.onOutlineWidthChanged(params.outlineWidth);
    stateMachine.onFillColorChanged(params.fillColor);
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
    node->getPrimitive()->param.outlineColor = params.outlineColor;
    node->getPrimitive()->param.outlineWidth = params.outlineWidth;
    node->getPrimitive()->param.isFilled = params.isFilled;
}

void Controller::onBackgroundColorChanged(ofColor color)
{
    (is3d) ? canvas3d->setBackgroundColor(color) : canvas2d->setBackgroundColor(color);
}

void Controller::onPrimitiveSelected(uint32_t id) { stateMachine.onPrimitiveSelected(id); }
void Controller::onImageSelected(const std::string &name) { stateMachine.onImageSelected(name); }
void Controller::onModelSelected(const std::string &name) { stateMachine.onModelSelected(name); }
void Controller::onPrefabSelected(const std::string &name) { stateMachine.onPrefabSelected(name); }

std::vector<uint32_t> Controller::getPrimitiveId()
{
    std::vector<uint32_t> ids;
    for (auto &node : (is3d) ? canvas3d->nodes : canvas2d->nodes)
    {
        collectPrimitiveId(node, ids);
    }
    return ids;
}

const std::vector<NodePrimitive *> &Controller::getCanvasNodes() { return (is3d) ? canvas3d->nodes : canvas2d->nodes; }

NodePrimitive *Controller::getNodeById(const uint32_t id)
{
    return (is3d) ? canvas3d->getChildById(id) : canvas2d->getChildById(id);
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
    (is3d) ? canvas3d->removeNode(id) : canvas2d->removeNode(id);
    stateMachine.onPrimitiveSelected(-1);
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
