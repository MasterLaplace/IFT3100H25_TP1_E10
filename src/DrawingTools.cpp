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
