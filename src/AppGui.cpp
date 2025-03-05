#include "AppGui.hpp"
#include "Controller.hpp"

void AppGui::setup(Controller *_controller)
{
    controller = _controller; // Pointeur vers le controlleur pour communiquer avec lui.
    selectedTool = tool::POINT;
    gui.setup(); // On initialise le gui.
}

void AppGui::draw()
{
    gui.begin();
    drawMenuBar();

    if (controller->is3d)
        drawToolsPanel3D(), drawDynamicPanel3D();
    else
        drawToolsPanel2D(), drawDynamicPanel2D();

    drawProprietiesPanel();
    drawSceneGraph();
    gui.end();
}

// Sert a dessiner le menu de la barre de menu
void AppGui::drawMenuBar()
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

        if (ImGui::BeginMenu("Vues"))
        {
            string view = controller->is3d ? "Aller 2D" : "Aller 3D";

            if (ImGui::MenuItem(view.c_str()))
            {
                controller->onToolSelected(tool::SELECT);
                controller->toggleCanvas();
            }

            if (controller->is3d)
            {
                string isOrthographic = controller->isCameraOrthographic() ? "Vers Perspective" : "Vers Orthographique";
                if (ImGui::MenuItem(isOrthographic.c_str()))
                {
                    controller->toggleCameraProjection();
                }
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
void AppGui::drawToolsPanel2D()
{
    float sceneGraphWidth = ofGetWidth() / 6 + 20;
    float propertiesPanelWidth = ofGetWidth() / 6 + 20;
    float panelWidth = (ofGetWidth() - sceneGraphWidth - propertiesPanelWidth) / 2 - 15;
    float panelHeight = 150;

    ImGui::SetNextWindowPos(ImVec2(sceneGraphWidth, 30), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);
    ImGui::Begin("Outils de dessin");

    // bool buttonClicked = false;

    if (ImGui::Button("Selection"))
    {
        onToolSelected(tool::SELECT);
    }

    if (ImGui::Button("Arriere plan"))
    {
        onToolSelected(tool::BACKGROUND);
    }

    // Si le bouton "Point" est activé.
    if (ImGui::Button("Point"))
    {
        onToolSelected(tool::POINT);
    }

    // Même chose pour la ligne.
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

void AppGui::drawToolsPanel3D()
{
    float sceneGraphWidth = ofGetWidth() / 6 + 20;
    float propertiesPanelWidth = ofGetWidth() / 6 + 20;
    float panelWidth = (ofGetWidth() - sceneGraphWidth - propertiesPanelWidth) / 2 - 15;
    float panelHeight = 150;

    ImGui::SetNextWindowPos(ImVec2(sceneGraphWidth, 30), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);
    ImGui::Begin("Outils de dessin");

    if (ImGui::Button("Selection"))
    {
        onToolSelected(tool::SELECT);
    }

    if (ImGui::Button("Arriere plan"))
    {
        onToolSelected(tool::BACKGROUND);
    }

    if (ImGui::Button("Box"))
    {
        onToolSelected(tool::BOX);
    }

    if (ImGui::Button("Ellipsoid"))
    {
        onToolSelected(tool::ELLIPSOID);
    }

    ImGui::End();
}

// Sert a dessiner le panel dynamique
void AppGui::drawDynamicPanel2D()
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
    case AppGui::SELECT: ImGui::Text("Selection");

    case AppGui::POINT:
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

    case AppGui::LINE:
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

    case AppGui::RECTANGLE:
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

    case AppGui::ELLIPSE:
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
    case AppGui::POLYGON:
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

    case AppGui::BACKGROUND:
        ImGui::Text("Option de fond");

        if (ImGui::ColorEdit3("Couleur de fond", (float *) &backgroundColor))
        {
            controller->onBackgroundColorChanged(
                ofColor(backgroundColor[0] * 255, backgroundColor[1] * 255, backgroundColor[2] * 255));
        }
        break;

    default: break;
    }

    if (propertiesChanged)
    {
        PrimitiveParams params;
        params.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        params.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
        params.outlineWidth = outlineWidth;
        params.isFilled = isFilled;

        controller->onPrimitivePropertiesChanged(params);
    }

    ImGui::End();
}

void AppGui::drawDynamicPanel3D()
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
    case AppGui::SELECT: ImGui::Text("Selection");

    case AppGui::BOX:
        ImGui::Text("Option de box");

        if (ImGui::Checkbox("Remplir", &isFilled))
        {
            propertiesChanged = true;
        }

        if (isFilled && ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
        {
            propertiesChanged = true;
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

    case AppGui::ELLIPSOID:
        ImGui::Text("Option de ellipsoid");

        if (ImGui::Checkbox("Remplir", &isFilled))
        {
            propertiesChanged = true;
        }

        if (isFilled && ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
        {
            propertiesChanged = true;
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

    case AppGui::BACKGROUND:
        ImGui::Text("Option de fond");

        if (ImGui::ColorEdit3("Couleur de fond", (float *) &backgroundColor))
        {
            controller->onBackgroundColorChanged(
                ofColor(backgroundColor[0] * 255, backgroundColor[1] * 255, backgroundColor[2] * 255));
        }
        break;

    default: break;
    }

    if (propertiesChanged)
    {
        PrimitiveParams params;
        params.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        params.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
        params.outlineWidth = outlineWidth;
        params.isFilled = isFilled;

        controller->onPrimitivePropertiesChanged(params);
    }

    ImGui::End();
}

// Sert a dessiner le graphe de scene
void AppGui::drawSceneGraph()
{
    float panelWidth = ofGetWidth() / 6;
    float panelHeight = ofGetHeight() - 40;

    ImGui::SetNextWindowPos(ImVec2(10, 30), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);
    ImGui::Begin("Graphe de scene");

    ImGui::Text("Primitive :");
    ImGui::Separator();

    for (auto &node : controller->getCanvasNodes())
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
void AppGui::displayNode(NodePrimitive *node, uint32_t indentLevel)
{
    ImGui::Indent(indentLevel * 10.0f);
    std::string nodeLabel = node->getName();
    int selectedNodeId = controller->getSelectedNodeId();
    if (ImGui::Selectable(nodeLabel.c_str(), selectedNodeId == static_cast<int>(node->getId())))
    {
        controller->onPrimitiveSelected(node->getId());
    }

    for (auto &child : node->getChildren())
    {
        displayNode(child, indentLevel + 1);
    }
    ImGui::Unindent(indentLevel * 10.0f);
}

// Sert a dessiner le panel des proprietes
void AppGui::drawProprietiesPanel()
{
    // Les settings de la fenetre
    float panelWidth = ofGetWidth() / 6;
    float panelHeight = ofGetHeight() - 40;

    ImGui::SetNextWindowPos(ImVec2(ofGetWidth() - panelWidth - 10, 30), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);
    ImGui::Begin("Propriétés");

    ImGui::Text("Propriétés :");
    ImGui::Separator();

    // On va chercher la node selectionnee.
    int selectedNodeId = controller->getSelectedNodeId();
    NodePrimitive *node = controller->getNodeById(selectedNodeId);

    // On s'occupe des proprietes generiques en premier.

    // Si la node selectionnee est valide on affiche les proprietes de base des Primitives2D.
    if (node != nullptr)
    {
        ImGui::Text(node->getName().c_str());
        ImGui::Separator();
        auto &primitive = node->getPrimitive();

        if (dynamic_cast<Point2D *>(primitive.get()) != nullptr)
        {
            drawPointProperties(std::dynamic_pointer_cast<Point2D>(primitive));
        }
        else if (dynamic_cast<Line2D *>(primitive.get()) != nullptr)
        {
            drawLineProperties(std::dynamic_pointer_cast<Line2D>(primitive));
        }
        else if (dynamic_cast<plugin::primitive::Rectangle *>(primitive.get()) != nullptr)
        {
            drawRectangleProperties(std::dynamic_pointer_cast<plugin::primitive::Rectangle>(primitive));
        }
        else if (dynamic_cast<plugin::primitive::Ellipse *>(primitive.get()) != nullptr)
        {
            drawEllipseProperties(std::dynamic_pointer_cast<plugin::primitive::Ellipse>(primitive));
        }
        else if (dynamic_cast<plugin::primitive::Polygon *>(primitive.get()) != nullptr)
        {
            drawPolygonProperties(std::dynamic_pointer_cast<plugin::primitive::Polygon>(primitive));
        }
        else if (dynamic_cast<plugin::primitive::Box *>(primitive.get()) != nullptr)
        {
            drawBoxProperties(std::dynamic_pointer_cast<plugin::primitive::Box>(primitive));
        }
        else if (dynamic_cast<plugin::primitive::Ellipsoid *>(primitive.get()) != nullptr)
        {
            drawEllipsoidProperties(std::dynamic_pointer_cast<plugin::primitive::Ellipsoid>(primitive));
        }

        // Pour supprimer une primitive.
        if (ImGui::Button("Supprimer", ImVec2(panelWidth - 20, 50)))
        {
            controller->deletePrimitiveButtonPressed(selectedNodeId);
        }
    }

    ImGui::End();
}

void AppGui::onToolSelected(tool tool)
{
    selectedTool = tool;
    controller->onToolSelected(tool);

    PrimitiveParams params;
    params.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
    params.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    params.outlineWidth = outlineWidth;
    params.isFilled = isFilled;

    controller->onPrimitivePropertiesChanged(params);
}

void AppGui::drawPointProperties(const std::shared_ptr<Point2D> &point)
{
    drawTransformProperties2D(point); // On dessine les proprietes de transformation generales.

    float size = point->size;
    float color[3] = {point->param.fillColor.r / 255.0f, point->param.fillColor.g / 255.0f,
                      point->param.fillColor.b / 255.0f};

    ImGui::Text("Taille :");
    if (ImGui::SliderFloat("Taille", &size, 1.0f, 30.0f))
    {
        point->size = size;
    }

    ImGui::Text("Couleur :");
    if (ImGui::ColorEdit3("Couleur", &color[0]))
    {
        point->param.fillColor = ofColor(color[0] * 255, color[1] * 255, color[2] * 255);
    }
}

void AppGui::drawLineProperties(const std::shared_ptr<Line2D> &line)
{
    drawTransformProperties2D(line); // On dessine les proprietes de transformation generales.

    float width = line->param.outlineWidth;
    float color[3] = {line->param.fillColor.r / 255.0f, line->param.fillColor.g / 255.0f,
                      line->param.fillColor.b / 255.0f};

    ImGui::Text("Epaisseur :");
    if (ImGui::SliderFloat("Epaisseur", &width, 1.0f, 30.0f))
    {
        line->param.outlineWidth = width;
    }

    ImGui::Text("Couleur :");
    if (ImGui::ColorEdit3("Couleur", &color[0]))
    {
        line->param.fillColor = ofColor(color[0] * 255, color[1] * 255, color[2] * 255);
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

void AppGui::drawRectangleProperties(const std::shared_ptr<plugin::primitive::Rectangle> &rectangle)
{
    drawTransformProperties2D(rectangle); // On dessine les proprietes de transformation generales.

    float width = rectangle->param.outlineWidth;
    float fillColor[3] = {rectangle->param.fillColor.r / 255.0f, rectangle->param.fillColor.g / 255.0f,
                          rectangle->param.fillColor.b / 255.0f};
    float outlineColor[3] = {rectangle->param.outlineColor.r / 255.0f, rectangle->param.outlineColor.g / 255.0f,
                             rectangle->param.outlineColor.b / 255.0f};
    bool filled = rectangle->param.isFilled;

    ImGui::Text("Epaisseur du contour :");
    if (ImGui::SliderFloat("Epaisseur du contour", &width, 1.0f, 30.0f))
    {
        rectangle->param.outlineWidth = width;
    }

    ImGui::Text("Couleur du contour :");
    if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
    {
        rectangle->param.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    }

    ImGui::Text("Remplir :");
    if (ImGui::Checkbox("Remplir", &filled))
    {
        rectangle->param.isFilled = filled;
    }

    if (filled)
    {
        ImGui::Text("Couleur de remplissage :");
        if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
        {
            rectangle->param.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        }
    }
}

void AppGui::drawEllipseProperties(const std::shared_ptr<plugin::primitive::Ellipse> &ellipse)
{
    drawTransformProperties2D(ellipse); // On dessine les proprietes de transformation generales.

    float width = ellipse->param.outlineWidth;
    float fillColor[3] = {ellipse->param.fillColor.r / 255.0f, ellipse->param.fillColor.g / 255.0f,
                          ellipse->param.fillColor.b / 255.0f};
    float outlineColor[3] = {ellipse->param.outlineColor.r / 255.0f, ellipse->param.outlineColor.g / 255.0f,
                             ellipse->param.outlineColor.b / 255.0f};
    bool filled = ellipse->param.isFilled;

    ImGui::Text("Epaisseur du contour :");
    if (ImGui::SliderFloat("Epaisseur du contour", &width, 1.0f, 30.0f))
    {
        ellipse->param.outlineWidth = width;
    }

    ImGui::Text("Couleur du contour :");
    if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
    {
        ellipse->param.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    }

    ImGui::Text("Remplir :");
    if (ImGui::Checkbox("Remplir", &filled))
    {
        ellipse->param.isFilled = filled;
    }

    if (filled)
    {
        ImGui::Text("Couleur de remplissage :");
        if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
        {
            ellipse->param.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        }
    }

    ImGui::Text("Rayon Horizontal :");
    if (ImGui::DragFloat("Rayon Horizontal", &ellipse->radius.x, 0.1f))
    {
        ellipse->radius.x = ellipse->radius.x;
    }

    ImGui::Text("Rayon Vertical :");
    ImGui::DragFloat("Rayon Vertical", &ellipse->radius.y, 0.1f);
}

void AppGui::drawPolygonProperties(const std::shared_ptr<plugin::primitive::Polygon> &polygon)
{
    drawTransformProperties2D(polygon); // On dessine les proprietes de transformation generales.

    float width = polygon->param.outlineWidth;
    float fillColor[3] = {polygon->param.fillColor.r / 255.0f, polygon->param.fillColor.g / 255.0f,
                          polygon->param.fillColor.b / 255.0f};
    float outlineColor[3] = {polygon->param.outlineColor.r / 255.0f, polygon->param.outlineColor.g / 255.0f,
                             polygon->param.outlineColor.b / 255.0f};
    bool filled = polygon->param.isFilled;

    ImGui::Text("Epaisseur du contour :");
    if (ImGui::SliderFloat("Epaisseur du contour", &width, 1.0f, 30.0f))
    {
        polygon->param.outlineWidth = width;
    }

    ImGui::Text("Couleur du contour :");
    if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
    {
        polygon->param.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    }

    ImGui::Text("Remplir :");
    if (ImGui::Checkbox("Remplir", &filled))
    {
        polygon->param.isFilled = filled;
    }

    if (filled)
    {
        ImGui::Text("Couleur de remplissage :");
        if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
        {
            polygon->param.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        }
    }
}

void AppGui::drawEllipsoidProperties(const std::shared_ptr<plugin::primitive::Ellipsoid> &ellipsoid)
{
    drawTransformProperties3D(ellipsoid);

    float width = ellipsoid->param.outlineWidth;
    float fillColor[3] = {ellipsoid->param.fillColor.r / 255.0f, ellipsoid->param.fillColor.g / 255.0f,
                          ellipsoid->param.fillColor.b / 255.0f};
    float outlineColor[3] = {ellipsoid->param.outlineColor.r / 255.0f, ellipsoid->param.outlineColor.g / 255.0f,
                             ellipsoid->param.outlineColor.b / 255.0f};
    bool filled = ellipsoid->param.isFilled;

    ImGui::Text("Epaisseur du contour :");
    if (ImGui::SliderFloat("Epaisseur du contour", &width, 1.0f, 30.0f))
    {
        ellipsoid->param.outlineWidth = width;
    }

    ImGui::Text("Couleur du contour :");
    if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
    {
        ellipsoid->param.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    }

    ImGui::Text("Remplir :");
    if (ImGui::Checkbox("Remplir", &filled))
    {
        ellipsoid->param.isFilled = filled;
    }

    if (filled)
    {
        ImGui::Text("Couleur de remplissage :");
        if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
        {
            ellipsoid->param.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        }
    }

    ImGui::Text("Taille :");
    if (ImGui::DragFloat3("Taille", &ellipsoid->getRadius().x, 0.1f))
        ;
}

void AppGui::drawBoxProperties(const std::shared_ptr<plugin::primitive::Box> &box)
{
    drawTransformProperties3D(box);

    float width = box->param.outlineWidth;
    float fillColor[3] = {box->param.fillColor.r / 255.0f, box->param.fillColor.g / 255.0f,
                          box->param.fillColor.b / 255.0f};
    float outlineColor[3] = {box->param.outlineColor.r / 255.0f, box->param.outlineColor.g / 255.0f,
                             box->param.outlineColor.b / 255.0f};
    bool filled = box->param.isFilled;

    ImGui::Text("Epaisseur du contour :");
    if (ImGui::SliderFloat("Epaisseur du contour", &width, 1.0f, 30.0f))
    {
        box->param.outlineWidth = width;
    }

    ImGui::Text("Couleur du contour :");
    if (ImGui::ColorEdit3("Couleur du contour", &outlineColor[0]))
    {
        box->param.outlineColor = ofColor(outlineColor[0] * 255, outlineColor[1] * 255, outlineColor[2] * 255);
    }

    ImGui::Text("Remplir :");
    if (ImGui::Checkbox("Remplir", &filled))
    {
        box->param.isFilled = filled;
    }

    if (filled)
    {
        ImGui::Text("Couleur de remplissage :");
        if (ImGui::ColorEdit3("Couleur de remplissage", &fillColor[0]))
        {
            box->param.fillColor = ofColor(fillColor[0] * 255, fillColor[1] * 255, fillColor[2] * 255);
        }
    }

    ImGui::Text("Taille :");
    if (ImGui::DragFloat3("Taille", &box->getSize().x, 0.1f))
        ;
}

void AppGui::drawTransformProperties2D(const std::shared_ptr<Primitive> &primitive)
{
    glm::vec3 position = primitive->param.position;
    glm::vec3 rotation = primitive->param.rotation;
    glm::vec3 scale = primitive->param.scale;

    ImGui::Text("Position :");
    if (ImGui::DragFloat2("Position", &position.x, 0.1f))
    {
        primitive->param.position = position;
    }

    ImGui::Text("Rotation :");
    if (ImGui::DragFloat("Rotation", &rotation.z, 0.1f))
    {
        primitive->param.rotation.z = rotation.z;
    }

    ImGui::Text("Echelle :");
    if (ImGui::DragFloat2("Echelle", &scale.x, 0.1f))
    {
        primitive->param.scale = scale;
    }
}

void AppGui::drawTransformProperties3D(const std::shared_ptr<Primitive> &primitive)
{
    glm::vec3 position = primitive->param.position;
    glm::vec3 rotation = primitive->param.rotation;
    glm::vec3 scale = primitive->param.scale;

    ImGui::Text("Position :");
    if (ImGui::DragFloat3("Position", &position.x, 0.1f))
    {
        primitive->param.position = position;
    }

    ImGui::Text("Rotation :");
    if (ImGui::DragFloat3("Rotation", &rotation.x, 0.1f))
    {
        primitive->param.rotation = rotation;
    }

    ImGui::Text("Echelle :");
    if (ImGui::DragFloat3("Echelle", &scale.x, 0.1f))
    {
        primitive->param.scale = scale;
    }
}
