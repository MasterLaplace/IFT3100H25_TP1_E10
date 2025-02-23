#include "DrawingTools.hpp"
#include "Controller2D.hpp"

void DrawingTools::setup(Controller2D *_controller)
{

    controller = _controller; // Pointeur vers le controlleur pour communiquer avec lui.
    selectedTool = tool::POINT;
    controller->onSizeChanged(pointSize);
    controller->onColorChanged(pointColor);
    gui.setup(); // On initialise le gui.
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
                // controller->exporter.setPixels();
                controller->exportImage();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void DrawingTools::drawToolsPanel()
{

    ImGui::Begin("Outils de dessin");

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

    // Si le bouton "Point" est activ�.
    if (ImGui::Button("Point"))
    {
        selectedTool = tool::POINT;
        // On appelle la m�thode "drawPointButttonPressed" sur le controleur.
        controller->drawPointButtonPressed();
        controller->onSizeChanged(pointSize);
        controller->onColorChanged(fillColor);
    }

    // M�me chose pour la ligne.
    if (ImGui::Button("Ligne"))
    {
        selectedTool = tool::LINE;
        controller->drawLineButtonPressed();
        controller->onSizeChanged(lineWidth);
        controller->onColorChanged(fillColor);
    }

    // Si le bouton "Rectangle" est activé.
    if (ImGui::Button("Rectangle"))
    {
        selectedTool = tool::RECTANGLE;
        controller->drawRectangleButtonPressed();
        controller->onColorChanged(fillColor);
    }

    ImGui::End();
}

void DrawingTools::drawDynamicPanel()
{
    ImGui::SetNextWindowPos(ImVec2(200, 10), ImGuiCond_FirstUseEver);
    ImGui::Begin("Option de dessin");

    switch (selectedTool)
    {
    case DrawingTools::POINT:
        ImGui::Text("Option pour le point");

        // Si on change la taille du point.
        if (ImGui::SliderFloat("Taille", &pointSize, 1.0f, 50.0f))
        {
            // On envoie l'information au controleur concernant la nouvelle taille du point.
            controller->onSizeChanged(pointSize);
        }

        // Si on change la couleur du point.
        if (ImGui::ColorEdit3("Couleur", (float *) &fillColor))
            ;
        {
            // On envoie le tableau de couleur au controleur.
            // C'est le Controlleur qui va transformer ce tableau en ofColor
            // pour ensuite l'envoyer � l'�tat.
            controller->onColorChanged(fillColor);
        }
        break;

    case DrawingTools::LINE:
        ImGui::Text("Option de ligne");

        // Si on change la taille de la ligne.
        if (ImGui::SliderFloat("Epaisseur", &lineWidth, 1.0f, 10.0f))
        {
            // On envoie l'information au controleur concernant la nouvelle taille de la ligne.
            controller->onSizeChanged(lineWidth);
        }

        // Si on change la couleur de la ligne.
        if (ImGui::ColorEdit3("Couleur", &fillColor[0]))
        {
            // On envoie le tableau de couleur au controleur.
            // C'est le Controlleur qui va transformer ce tableau en ofColor
            // pour ensuite l'envoyer � l'�tat.
            controller->onColorChanged(fillColor);
        }
        break;

    case DrawingTools::RECTANGLE:
        ImGui::Text("Option de rectangle");

        // Si on change la couleur de la ligne.
        if (ImGui::ColorEdit3("Couleur", &fillColor[0]))
        {
            // On envoie le tableau de couleur au controleur.
            // C'est le Controlleur qui va transformer ce tableau en ofColor
            // pour ensuite l'envoyer � l'�tat.
            controller->onColorChanged(fillColor);
        }
        break;

    default: break;
    }

    ImGui::End();
}

void DrawingTools::drawSceneGraph()
{
    float panelWidth = ofGetWidth() / 6;
    float panelHeight = ofGetHeight() / 2;

    ImGui::SetNextWindowPos(ImVec2(400, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(panelHeight, panelWidth), ImGuiCond_FirstUseEver);
    ImGui::Begin("Graphe de scene");

    ImGui::Text("Primitive :");
    ImGui::Separator();

    std::vector<Node2D *> nodes = controller->getCanvasNodes();
    for (Node2D *node : nodes)
    {
        displayNode(node, 0);
        // cout << "Node : " << node->primitive->id << endl;
    }

    if (ImGui::Button("deselectionner"))
    {
        selectedPrimitiveId = -1;
        controller->onPrimitiveSelected(-1);
    }

    ImGui::End();
}

void DrawingTools::displayNode(Node2D *node, int indentLevel)
{
    ImGui::Indent(indentLevel * 10.0f);
    std::string nodeLabel = "Primitive " + std::to_string(node->primitive->id);
    if (ImGui::Selectable(nodeLabel.c_str(), selectedPrimitiveId == node->primitive->id))
    {
        selectedPrimitiveId = node->primitive->id;
        controller->onPrimitiveSelected(node->primitive->id);
    }

    for (Node2D *child : node->children)
    {
        displayNode(child, indentLevel + 1);
    }
    ImGui::Unindent(indentLevel * 10.0f);
}

void DrawingTools::drawProprietiesPanel()
{
    // Les setting de la fenetre
    ImGui::SetNextWindowPos(ImVec2(600, 10), ImGuiCond_FirstUseEver);
    ImGui::Begin("Propriétés");
    ImGui::Text("Propriétés :");
    ImGui::Separator();

    // On va chercher la node selectionnee.
    Node2D *node = controller->getNodeById(selectedPrimitiveId);

    // Si la node selectionnee est valide on affiche les proprietes de base des Primitives2D.
    if (node != nullptr)
    {
        ImGui::Text("Primitive %d", selectedPrimitiveId);
        ImGui::Separator();

        // Pour modifier la position de la primitive.
        ImGui::Text("Position :");
        if (ImGui::DragFloat2("Position", &node->primitive->position.x, 0.1f))
        {
            controller->onPositionChanged(selectedPrimitiveId, node->primitive->position);
        }

        // Pour modifier la couleur de la primitive.
        float nodeColor[3];
        controller->getNodeColor(selectedPrimitiveId, nodeColor);
        ImGui::Text("Couleur :");
        if (ImGui::ColorEdit3("Couleur", nodeColor))
        {
            controller->onColorChanged(selectedPrimitiveId, nodeColor);
        }
        ImGui::Separator();

        // Si la primitive selectionnee est de type Point2D.
        if (Point2D *point = dynamic_cast<Point2D *>(node->primitive))
        {
            ImGui::Text("Taille :");
            if (ImGui::DragFloat("Taille", &point->size, 0.1f))
            {
                controller->onSizeChanged(selectedPrimitiveId, point->size);
            }
        }

        // Si la primitive selectionnee est de type Rectangle.
        if (plugin::primitive::Rectangle *rectangle = dynamic_cast<plugin::primitive::Rectangle *>(node->primitive))
        {
            ImGui::Text("Dimensions :");
            if (ImGui::DragFloat2("Dimensions", &rectangle->dimensions.x, 0.1f))
            {
                controller->onSizeChanged(selectedPrimitiveId, rectangle->dimensions.x);
            }
        }
    }

    ImGui::End();
}
