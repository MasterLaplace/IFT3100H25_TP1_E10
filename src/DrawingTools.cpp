#include "DrawingTools.hpp"
#include "Controller2D.hpp"

void DrawingTools::setup(Controller2D *_controller)
{

    controller = _controller; // Pointeur vers le controlleur pour communiquer avec lui.
    gui.setup();              // On initialise le gui.
}

void DrawingTools::draw()
{
    gui.begin();
    ImGui::Begin("Outils de dessin");

    // Si le bouton "Point" est activé.
    if (ImGui::Button("Point"))
    {
        // On appelle la méthode "drawPointButttonPressed" sur le controleur.
        controller->drawPointButtonPressed();
    }

    // Même chose pour la ligne.
    if (ImGui::Button("Ligne"))
    {
        controller->drawLineButtonPressed();
    }

    ImGui::End();
    gui.end();
}
