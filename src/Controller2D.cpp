#include "Controller2D.hpp"

void Controller2D::setup()
{
    // On configure l'instance du Canvas dans la scène par le singleton
    // pour qu'on puisse y accéder de n'importe où.
    canvas = Canvas::getInstance();

    // On initialise l'état du Controlleur pour dessiner des points.
    // On pourrait changer l'état initial au besoin.
    stateMachine.changeState(new DrawPointState());

    // C'est ici qu'on va initialiser l'interface pour le 2D.
    gui.setup(this);

    importer.setup();
}

void Controller2D::update()
{
    importer.update();
    stateMachine.update();
}

void Controller2D::draw()
{
    // On dessine le canvas en premier.
    canvas->draw();

    // On dessine ensuite l'image importée.
    importer.draw();

    // On sauvegarde les pixels de l'image et des formes sans le ui et la souris
    exporter.setPixels();

    // C'est Controlleur qui demande à son état de dessiner des choses en lien avec l'état.
    // Par exemple, si on est dans l'état DrawRectangleState, on va dessiner le fantome du rectangle.
    stateMachine.draw();

    // C'est le Controlleur qui demande au GUI de s'afficher aussi.
    gui.draw();
}

void Controller2D::exit() {}

void Controller2D::keyReleased(int key)
{

    // C'est les racourcies claviers.
    // Les input proviennent de Application.
    if (key == 'p')
    {
        drawPointButtonPressed();
        gui.selectedTool = DrawingTools::tool::POINT;
    }

    if (key == 'l')
    {
        drawLineButtonPressed();
        gui.selectedTool = DrawingTools::tool::LINE;
    }

    if (key == 'i')
    {
        importer.importImage();
    }

    if (key == 'e')
    {
        exporter.exportImage();
    }
}

void Controller2D::mouseMoved(glm::vec2 pos)
{

    // On transmet la position de la sourie à l'état.
    // L'input provient de Application.
    stateMachine.mousePosition = pos;
}

void Controller2D::mousePressed(int x, int y, int button) { stateMachine.mousePressed(x, y, button); }

void Controller2D::mouseReleased(int x, int y, int button) { stateMachine.mouseReleased(x, y, button); }

void Controller2D::importImage() { importer.importImage(); }

void Controller2D::exportImage() { exporter.exportImage(); }

void Controller2D::onSizeChanged(float newSize) { stateMachine.onStrokeSizeChanged(newSize); }

void Controller2D::onSizeChanged(int id, float newSize)
{
    Node2D *node = getNodeById(id);
    if (Point2D *p = dynamic_cast<Point2D *>(node->primitive))
    {
        p->size = newSize;
    }
}

// Cette méthode reçoit un tableau de trois float parce que c'est ce que ImGui utilise.
// On transforme ce tableau en un ofColor pour l'envoyer à l'état.
void Controller2D::onColorChanged(float _newColor[3])
{

    ofColor newColor = ofColor(_newColor[0] * 255, _newColor[1] * 255, _newColor[2] * 255);
    stateMachine.onColorChanged(newColor);
}

void Controller2D::onColorChanged(int id, float _newColor[3])
{
    Node2D *node = getNodeById(id);
    if (node)
    {
        ofColor newColor = ofColor(_newColor[0] * 255, _newColor[1] * 255, _newColor[2] * 255);
        node->primitive->color = newColor;
    }
}

void Controller2D::onPrimitiveSelected(int id) { stateMachine.onPrimitiveSelected(id); }

void Controller2D::onPositionChanged(int id, glm::vec2 newPos)
{
    Node2D *node = getNodeById(id);
    if (node)

    {
        node->primitive->position = newPos;
    }
}

void Controller2D::onEndPositionChanged(int id, glm::vec2 newPos) 
{
    Node2D *node = getNodeById(id);
    if (Line2D *line = dynamic_cast<Line2D *>(node->primitive))

    {
        line->endPosition = newPos;
    }
}

std::vector<int> Controller2D::getPrimitiveId()
{
    std::vector<int> ids;
    for (auto node : canvas->nodes)
    {
        collectPrimitiveId(node, ids);
    }
    return ids;
}

std::vector<Node2D *> Controller2D::getCanvasNodes() { return canvas->nodes; }

Node2D *Controller2D::getNodeById(const int id) { return canvas->getChildById(id); }

void Controller2D::getNodeColor(const int id, float color[3])
{
    Node2D *node = getNodeById(id);

    if (node)
    {
        color[0] = node->primitive->color.r / 255.0f;
        color[1] = node->primitive->color.g / 255.0f;
        color[2] = node->primitive->color.b / 255.0f;
    }
}

void Controller2D::collectPrimitiveId(Node2D *node, std::vector<int> &ids)
{
    if (node->primitive != nullptr)
    {
        ids.push_back(node->primitive->id);
    }

    for (auto child : node->children)
    {
        collectPrimitiveId(child, ids);
    }
}

void Controller2D::drawPointButtonPressed() { stateMachine.changeState(new DrawPointState()); }

void Controller2D::drawLineButtonPressed() { stateMachine.changeState(new DrawLineState()); }

void Controller2D::drawRectangleButtonPressed() { stateMachine.changeState(new DrawRectangleState()); }
