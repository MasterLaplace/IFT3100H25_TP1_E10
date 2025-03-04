#include "DrawingTools.hpp"
#include "Controller2D.hpp"

void DrawingTools::setup(Controller2D *_controller)
{
    controller = _controller; // Pointeur vers le controlleur pour communiquer avec lui.
    selectedTool = tool::POINT;
    gui.setup(); // On initialise le gui.
    // controller->onSizeChanged(pointSize);
    // controller->onColorChanged(pointColor);
}

void DrawingTools::draw()
{
    gui.begin();
    drawMenuBar();
    drawToolsPanel();
    drawDynamicPanel();
    drawSceneGraph();
    drawProprietiesPanel();
    gui.end();
}

// Sert a dessiner le menu de la barre de menu
void DrawingTools::drawMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Fichier"))
        {
            if (ImGui::MenuItem("Importer image"))
            {
                controller->importImage();
            }

            if (ImGui::MenuItem("Exporter image"))
            {
                controller->exportImage();
            }

            if (ImGui::MenuItem("Quitter"))
            {
                ofExit();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Histogram"))
        {
            if (ImGui::MenuItem("Rouge"))
            {
                controller->drawHistogram(0);
            }

            if (ImGui::MenuItem("Vert"))
            {
                controller->drawHistogram(1);
            }

            if (ImGui::MenuItem("Bleu"))
            {
                controller->drawHistogram(2);
            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

// Sert a dessiner le panel des outils de dessin
void DrawingTools::drawToolsPanel()
{
    float sceneGraphWidth = ofGetWidth() / 6 + 20;
    float propertiesPanelWidth = ofGetWidth() / 6 + 20;
    float panelWidth = (ofGetWidth() - sceneGraphWidth - propertiesPanelWidth) / 2 - 15;
    float panelHeight = 150;

    ImGui::SetNextWindowPos(ImVec2(sceneGraphWidth, 30), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);
    ImGui::Begin("Outils de dessin");

    bool buttonClicked = false;

    if (ImGui::Button("Selection"))
    {
        onToolSelected(tool::SELECT);
    }

    // Si le bouton "Point" est activ�.
    if (ImGui::Button("Point"))
    {
        onToolSelected(tool::POINT);
    }

    // M�me chose pour la ligne.
    if (ImGui::Button("Ligne"))
    {
        onToolSelected(tool::LINE);
    }

    // Si le bouton "Rectangle" est activé.
    if (ImGui::Button("Rectangle"))
    {
        onToolSelected(tool::RECTANGLE);
    }

    if (ImGui::Button("Ellipse"))
    {
        onToolSelected(tool::ELLIPSE);
    }

    if (ImGui::Button("Polygone"))
    {
        onToolSelected(tool::POLYGON);
    }

    ImGui::End();
}

// Sert a dessiner le panel dynamique
void DrawingTools::drawDynamicPanel()
{
    float sceneGraphWidth = ofGetWidth() / 6 + 20;
    float propertiesPanelWidth = ofGetWidth() / 6 + 20;
    float panelWidth = (ofGetWidth() - sceneGraphWidth - propertiesPanelWidth) / 2 - 15;
    float panelHeight = 150;

    ImGui::SetNextWindowPos(ImVec2(sceneGraphWidth + panelWidth + 10, 30), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);
    ImGui::Begin("Option de dessin");
    bool propertiesChanged = false;

    switch (selectedTool)
    {
    case DrawingTools::SELECT: ImGui::Text("Selection");

    case DrawingTools::POINT:
        ImGui::Text("Option pour le point");

        // Si on change la taille du point.
        if (ImGui::SliderFloat("Taille", &outlineWidth, 1.0f, 30.0f))
        {
            propertiesChanged = true;
        }

        // Si on change la couleur du point.
        if (ImGui::ColorEdit3("Couleur", (float *) &fillColor))
        {
            propertiesChanged = true;
        }
        break;

    case DrawingTools::LINE:
        ImGui::Text("Option de ligne");

        // Si on change la taille de la ligne.
        if (ImGui::SliderFloat("Epaisseur", &outlineWidth, 1.0f, 30.0f))
        {
            propertiesChanged = true;
        }

        // Si on change la couleur de la ligne.
        if (ImGui::ColorEdit3("Couleur", &fillColor[0]))
        {
            propertiesChanged = true;
        }
        break;

    case DrawingTools::RECTANGLE:
        ImGui::Text("Option de rectangle");

        if (ImGui::Checkbox("Remplir", &isFilled))
        {
            propertiesChanged = true;
        }

        if (isFilled)
        {
            if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
            {
                propertiesChanged = true;
            }
        }

        if (ImGui::SliderFloat("Epaisseur du contour", &outlineWidth, 1.0f, 10.0f))
        {
            propertiesChanged = true;
        }

        if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
        {
            propertiesChanged = true;
        }
        break;

    case DrawingTools::ELLIPSE:
        ImGui::Text("Option de ellipse");

        if (ImGui::Checkbox("Remplir", &isFilled))
        {
            propertiesChanged = true;
        }

        if (isFilled)
        {
            if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
            {
                propertiesChanged = true;
            }
        }

        if (ImGui::SliderFloat("Epaisseur du contour", &outlineWidth, 1.0f, 10.0f))
        {
            propertiesChanged = true;
        }

        if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
        {
            propertiesChanged = true;
        }
        break;
    case DrawingTools::POLYGON:
        ImGui::Text("Option de polygone");

        if (ImGui::Checkbox("Remplir", &isFilled))
        {
            propertiesChanged = true;
        }

        if (isFilled)
        {
            if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
            {
                propertiesChanged = true;
            }
        }

        if (ImGui::SliderFloat("Epaisseur du contour", &outlineWidth, 1.0f, 10.0f))
        {
            propertiesChanged = true;
        }

        if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
        {
            propertiesChanged = true;
        }
        break;

    default: break;
    }

    if (propertiesChanged)
    {
        Primitive2DParams params;
        params.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        params.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
        params.outlineWidth = outlineWidth;
        params.isFilled = isFilled;

        ofLog() << params.outlineColor;

        controller->onPrimitivePropertiesChanged(params);
    }

    ImGui::End();
}

// Sert a dessiner le graphe de scene
void DrawingTools::drawSceneGraph()
{
    float panelWidth = ofGetWidth() / 6;
    float panelHeight = ofGetHeight() - 40;

    ImGui::SetNextWindowPos(ImVec2(10, 30), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);
    ImGui::Begin("Graphe de scene");

    ImGui::Text("Primitive :");
    ImGui::Separator();

    std::vector<Node<Primitive2D> *> nodes = controller->getCanvasNodes();
    for (Node<Primitive2D> *node : nodes)
    {
        displayNode(node, 0);
        // cout << "Node : " << node->primitive->id << endl;
    }

    if (ImGui::Button("deselectionner"))
    {
        controller->onPrimitiveSelected(-1);
    }

    ImGui::End();
}

// Sert a afficher les noeuds du graphe de scene
void DrawingTools::displayNode(Node<Primitive2D> *node, int indentLevel)
{
    ImGui::Indent(indentLevel * 10.0f);
    std::string nodeLabel = node->primitive->name;
    int selectedNodeId = controller->getSelectedNodeId();
    if (ImGui::Selectable(nodeLabel.c_str(), selectedNodeId == node->primitive->id))
    {
        controller->onPrimitiveSelected(node->primitive->id);
    }

    for (Node<Primitive2D> *child : node->children)
    {
        displayNode(child, indentLevel + 1);
    }
    ImGui::Unindent(indentLevel * 10.0f);
}

// Sert a dessiner le panel des proprietes
void DrawingTools::drawProprietiesPanel()
{
    // Les setting de la fenetre
    float panelWidth = ofGetWidth() / 6;
    float panelHeight = ofGetHeight() - 40;

    ImGui::SetNextWindowPos(ImVec2(ofGetWidth() - panelWidth - 10, 30), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);
    ImGui::Begin("Propriétés");

    ImGui::Text("Propriétés :");
    ImGui::Separator();

    // On va chercher la node selectionnee.
    int selectedNodeId = controller->getSelectedNodeId();
    Node<Primitive2D> *node = controller->getNodeById(selectedNodeId);

    // On s'occupe des proprietes generiques en premier.

    // Si la node selectionnee est valide on affiche les proprietes de base des Primitives2D.
    if (node != nullptr)
    {
        ImGui::Text(node->primitive->name.c_str());
        ImGui::Separator();

        if (Point2D *point = dynamic_cast<Point2D *>(node->primitive))
        {
            drawPointProperties(point);
        }

        if (Line2D *line = dynamic_cast<Line2D *>(node->primitive))
        {
            drawLineProperties(line);
        }

        if (plugin::primitive::Rectangle *rectangle = dynamic_cast<plugin::primitive::Rectangle *>(node->primitive))
        {
            drawRectangleProperties(rectangle);
        }

        if (plugin::primitive::Ellipse *ellipse = dynamic_cast<plugin::primitive::Ellipse *>(node->primitive))
        {
            drawEllipseProperties(ellipse);
        }

        if (plugin::primitive::Polygon *polygon = dynamic_cast<plugin::primitive::Polygon *>(node->primitive))
        {
            drawPolygonProperties(polygon);
        }

        // Pour supprimer une primitive.
        if (ImGui::Button("Supprimer", ImVec2(panelWidth - 20, 50)))
        {
            controller->deletePrimitiveButtonPressed(selectedNodeId);
        }
    }

    ImGui::End();
}

void DrawingTools::onToolSelected(tool tool)
{
    selectedTool = tool;
    controller->onToolSelected(tool);

    Primitive2DParams params;
    params.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
    params.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    params.outlineWidth = outlineWidth;
    params.isFilled = isFilled;

    controller->onPrimitivePropertiesChanged(params);
}

void DrawingTools::drawPointProperties(Point2D *point)
{
    float size = point->size;
    float color[3] = {point->fillColor.r / 255.0f, point->fillColor.g / 255.0f, point->fillColor.b / 255.0f};

    ImGui::Text("Taille :");
    if (ImGui::SliderFloat("Taille", &size, 1.0f, 30.0f))
    {
        point->size = size;
    }

    ImGui::Text("Couleur :");
    if (ImGui::ColorEdit3("Couleur", &color[0]))
    {
        point->fillColor = ofColor(color[0] * 255, color[1] * 255, color[2] * 255);
    }
}

void DrawingTools::drawLineProperties(Line2D *line)
{
    float width = line->outlineWidth;
    float color[3] = {line->fillColor.r / 255.0f, line->fillColor.g / 255.0f, line->fillColor.b / 255.0f};

    ImGui::Text("Epaisseur :");
    if (ImGui::SliderFloat("Epaisseur", &width, 1.0f, 30.0f))
    {
        line->outlineWidth = width;
    }

    ImGui::Text("Couleur :");
    if (ImGui::ColorEdit3("Couleur", &color[0]))
    {
        line->fillColor = ofColor(color[0] * 255, color[1] * 255, color[2] * 255);
    }

    ImGui::Text("Debut :");
    if (ImGui::DragFloat2("Debut", &line->startPosition.x, 0.1f))
    {
        line->startPosition = line->startPosition;
    }

    ImGui::Text("Fin :");
    if (ImGui::DragFloat2("Fin", &line->endPosition.x, 0.1f))
    {
        line->endPosition = line->endPosition;
    }
}

void DrawingTools::drawRectangleProperties(plugin::primitive::Rectangle *rectangle)
{
    float width = rectangle->outlineWidth;
    float fillColor[3] = {rectangle->fillColor.r / 255.0f, rectangle->fillColor.g / 255.0f,
                          rectangle->fillColor.b / 255.0f};
    float outlineColor[3] = {rectangle->outlineColor.r / 255.0f, rectangle->outlineColor.g / 255.0f,
                             rectangle->outlineColor.b / 255.0f};
    bool filled = rectangle->isFilled;

    ImGui::Text("Epaisseur du contour :");
    if (ImGui::SliderFloat("Epaisseur du contour", &width, 1.0f, 30.0f))
    {
        rectangle->outlineWidth = width;
    }

    ImGui::Text("Couleur du contour :");
    if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
    {
        rectangle->outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    }

    ImGui::Text("Remplir :");
    if (ImGui::Checkbox("Remplir", &filled))
    {
        rectangle->isFilled = filled;
    }

    if (filled)
    {
        ImGui::Text("Couleur de remplissage :");
        if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
        {
            rectangle->fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        }
    }
}

void DrawingTools::drawEllipseProperties(plugin::primitive::Ellipse *ellipse)
{
    float width = ellipse->outlineWidth;
    float fillColor[3] = {ellipse->fillColor.r / 255.0f, ellipse->fillColor.g / 255.0f, ellipse->fillColor.b / 255.0f};
    float outlineColor[3] = {ellipse->outlineColor.r / 255.0f, ellipse->outlineColor.g / 255.0f,
                             ellipse->outlineColor.b / 255.0f};
    bool filled = ellipse->isFilled;

    ImGui::Text("Epaisseur du contour :");
    if (ImGui::SliderFloat("Epaisseur du contour", &width, 1.0f, 30.0f))
    {
        ellipse->outlineWidth = width;
    }

    ImGui::Text("Couleur du contour :");
    if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
    {
        ellipse->outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    }

    ImGui::Text("Remplir :");
    if (ImGui::Checkbox("Remplir", &filled))
    {
        ellipse->isFilled = filled;
    }

    if (filled)
    {
        ImGui::Text("Couleur de remplissage :");
        if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
        {
            ellipse->fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        }
    }
}

void DrawingTools::drawPolygonProperties(plugin::primitive::Polygon *polygon)
{
    float width = polygon->outlineWidth;
    float fillColor[3] = {polygon->fillColor.r / 255.0f, polygon->fillColor.g / 255.0f, polygon->fillColor.b / 255.0f};
    float outlineColor[3] = {polygon->outlineColor.r / 255.0f, polygon->outlineColor.g / 255.0f,
                             polygon->outlineColor.b / 255.0f};
    bool filled = polygon->isFilled;

    ImGui::Text("Epaisseur du contour :");
    if (ImGui::SliderFloat("Epaisseur du contour", &width, 1.0f, 30.0f))
    {
        polygon->outlineWidth = width;
    }

    ImGui::Text("Couleur du contour :");
    if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
    {
        polygon->outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    }

    ImGui::Text("Remplir :");
    if (ImGui::Checkbox("Remplir", &filled))
    {
        polygon->isFilled = filled;
    }

    if (filled)
    {
        ImGui::Text("Couleur de remplissage :");
        if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
        {
            polygon->fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        }
    }
}
