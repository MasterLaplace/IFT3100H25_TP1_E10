#include "DrawingTools.hpp"
#include "Controller2D.hpp"

void DrawingTools::setup(Controller2D *_controller)
{

    controller = _controller; // Pointeur vers le controlleur pour communiquer avec lui.
    selectedTool = tool::POINT;
    controller->onPointSizeChanged(pointSize);
    controller->onPointColorChanged(pointColor);
    gui.setup(); // On initialise le gui.
}

void DrawingTools::draw()
{

    gui.begin();
    drawToolsPanel();
    drawDynamicPanel();
    gui.end();
}

void DrawingTools::drawToolsPanel()
{

    ImGui::Begin("Outils de dessin");

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

    // Si le bouton "Point" est activé.
    if (ImGui::Button("Point"))
    {
        selectedTool = tool::POINT;
        // On appelle la méthode "drawPointButttonPressed" sur le controleur.
        controller->drawPointButtonPressed();
        controller->onPointSizeChanged(pointSize);
        controller->onPointColorChanged(pointColor);
    }

    // Même chose pour la ligne.
    if (ImGui::Button("Ligne"))
    {
        selectedTool = tool::LINE;
        controller->drawLineButtonPressed();
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
        if (ImGui::SliderFloat("Taille", &pointSize, 1.0f, 50.0f))
        {
            controller->onPointSizeChanged(pointSize);
        }
        if (ImGui::ColorEdit3("Couleur", (float *) &pointColor))
            ;
        {
            controller->onPointColorChanged(pointColor);
        }
        break;

    case DrawingTools::LINE:
        ImGui::Text("Option de ligne");
        ImGui::SliderFloat("Epaisseur", &lineWidth, 1.0f, 10.0f);
        ImGui::ColorEdit3("Couleur", lineColor);
        break;

    default: break;
    }

    ImGui::End();
}
