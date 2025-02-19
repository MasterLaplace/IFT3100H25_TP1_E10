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
    drawToolsPanel();
    drawDynamicPanel();
    drawSceneGraph();
    gui.end();
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
        controller->onColorChanged(pointColor);
    }

    // M�me chose pour la ligne.
    if (ImGui::Button("Ligne"))
    {
        selectedTool = tool::LINE;
        controller->drawLineButtonPressed();
        controller->onSizeChanged(lineWidth);
        controller->onColorChanged(lineColor);
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
        if (ImGui::ColorEdit3("Couleur", (float *) &pointColor))
            ;
        {
            // On envoie le tableau de couleur au controleur.
            // C'est le Controlleur qui va transformer ce tableau en ofColor
            // pour ensuite l'envoyer � l'�tat.
            controller->onColorChanged(pointColor);
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
        if (ImGui::ColorEdit3("Couleur", lineColor))
        {
            // On envoie le tableau de couleur au controleur.
            // C'est le Controlleur qui va transformer ce tableau en ofColor
            // pour ensuite l'envoyer � l'�tat.
            controller->onColorChanged(lineColor);
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

    std::unordered_multimap<int, Node2D *> displayedNodes;
    displayedNodes.clear();

    std::vector<int> ids = controller->getPrimitiveId();
    for (int id : ids)
    {
        Node2D *node = controller->getNodeById(id);
        if (node)
        {
            displayNode(node, 0, displayedNodes);
        }
    }

    ImGui::End();
}

void DrawingTools::displayNode(Node2D *node, int indentLevel, std::unordered_multimap<int, Node2D *> displayedNodes)
{
    if (displayedNodes.find(node->primitive->id) != displayedNodes.end())
    {
        return;
    }

    displayedNodes.insert(std::make_pair(node->primitive->id, node));

    ImGui::Indent(indentLevel * 10.0f);
    std::string nodeLabel = "Primitive " + std::to_string(node->primitive->id);
    if (ImGui::Selectable(nodeLabel.c_str(), selectedPrimitiveId == node->primitive->id))
    {
        selectedPrimitiveId = node->primitive->id;
        controller->onPrimitiveSelected(node->primitive->id);
    }

    for (Node2D *child : node->children)
    {
        displayNode(child, indentLevel + 1, displayedNodes);
    }
    ImGui::Unindent(indentLevel * 10.0f);
}
