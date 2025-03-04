#include "Controller2D.hpp"

void Controller2D::setup()
{
    // On configure l'instance du Canvas dans la sc�ne par le singleton
    // pour qu'on puisse y acc�der de n'importe o�.
    canvas = Canvas::getInstance();

    // On initialise l'�tat du Controlleur pour dessiner des points.
    // On pourrait changer l'�tat initial au besoin.
    stateMachine.changeState(new DrawPointState());

    // C'est ici qu'on va initialiser l'interface pour le 2D.
    gui.setup(this);
    histogramUI.setup(this);

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

    // On dessine ensuite l'image import�e.
    importer.draw();

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

    // On transmet la position de la sourie � l'�tat.
    // L'input provient de Application.
    stateMachine.mousePosition = pos;
}

void Controller2D::mousePressed(int x, int y, int button) { stateMachine.mousePressed(x, y, button); }

void Controller2D::mouseReleased(int x, int y, int button) { stateMachine.mouseReleased(x, y, button); }

void Controller2D::importImage() { importer.importImage(); }

void Controller2D::exportImage() { exporter.exportImage(); }


// Cette méthode change les propriétés de la primitive à dessiner.
void Controller2D::onPrimitivePropertiesChanged(Primitive2DParams params)
{
    stateMachine.onOutlineWidthChanged(params.outlineWidth);
    stateMachine.onFillColorChanged(params.fillColor);
    stateMachine.onOutlineColorChanged(params.outlineColor);
    stateMachine.onFilledChanged(params.isFilled);
}

// Cette méthode change les propriétés d'une primitive existante.
void Controller2D::onPrimitivePropertiesChanged(int id, Primitive2DParams params)
{
    Node<Primitive2D> *node = getNodeById(id);
    if (node)
    {
        node->primitive->position = params.position;
        node->primitive->fillColor = params.fillColor;
        node->primitive->outlineColor = params.outlineColor;
        node->primitive->outlineWidth = params.outlineWidth;
        node->primitive->isFilled = params.isFilled;
    }
}

void Controller2D::onPrimitiveSelected(int id) { stateMachine.onPrimitiveSelected(id); }

std::vector<int> Controller2D::getPrimitiveId()
{
    std::vector<int> ids;
    for (auto node : canvas->nodes)
    {
        collectPrimitiveId(node, ids);
    }
    return ids;
}

std::vector<Node<Primitive2D> *> Controller2D::getCanvasNodes() { return canvas->nodes; }

Node<Primitive2D> *Controller2D::getNodeById(const int id) { return canvas->getChildById(id); }

void Controller2D::collectPrimitiveId(Node<Primitive2D> *node, std::vector<int> &ids)
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

int Controller2D::getSelectedNodeId() { return stateMachine.getSelectedNodeId(); }

void Controller2D::onToolSelected(DrawingTools::tool _tool)
{
    switch (_tool)
    {
        case DrawingTools::tool::SELECT:
            stateMachine.changeState(new SelectionState());
            break;
        case DrawingTools::tool::POINT:
            stateMachine.changeState(new DrawPointState());
            break;
        case DrawingTools::tool::LINE:
            stateMachine.changeState(new DrawLineState());
            break;
        case DrawingTools::tool::RECTANGLE:
            stateMachine.changeState(new DrawRectangleState());
            break;
        case DrawingTools::tool::ELLIPSE:
            stateMachine.changeState(new DrawEllipseState());
            break;
        case DrawingTools::tool::POLYGON:
            stateMachine.changeState(new DrawPolygonState());
            break;
    }
}

void Controller2D::selectionButtonPressed() { stateMachine.changeState(new SelectionState()); }

void Controller2D::drawPointButtonPressed() { stateMachine.changeState(new DrawPointState()); }

void Controller2D::drawLineButtonPressed() { stateMachine.changeState(new DrawLineState()); }

void Controller2D::drawRectangleButtonPressed() { stateMachine.changeState(new DrawRectangleState()); }

void Controller2D::drawEllipseButtonPressed() { stateMachine.changeState(new DrawEllipseState()); }

void Controller2D::drawPolygonButtonPressed() { stateMachine.changeState(new DrawPolygonState()); }

void Controller2D::deletePrimitiveButtonPressed(int id)
{
    canvas->removeNode(id);
    stateMachine.onPrimitiveSelected(-1);
}

void Controller2D::drawHistogram(int color)
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
