#include "TriangulationUI.hpp"
#include "Controller.hpp"

void TriangulationUI::setup(Controller *_controller) 
{
    controller = _controller;
    delauney.setup();
    gui.setup();
}

void TriangulationUI::draw()
{
    delauney.draw();
    drawOptionPanel();
}

void TriangulationUI::drawOptionPanel()
{
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 200, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);

    if (ImGui::Begin("Options du diagramme"))
    {
        Point selectedPoint = delauney.getSelectedPoint();
        ImGui::SetNextItemWidth(180);
        if (selectedPoint == Point(-1.0f, -1.0f))
        {
            ImGui::Text("Aucun point selectionne");
        }
        else
        {
            ImGui::Text("Point selectionne :");
            ImGui::Text("x: %.2f", selectedPoint.x);
            ImGui::Text("y: %.2f", selectedPoint.y);

            if (ImGui::Button("Supprimer", ImVec2(180, 50)))
            {
                delauney.removeSelectedPoint();
            }
        }

        if (ImGui::Button("Ajouter un point", ImVec2(180, 50)))
        {
            delauney.addPoint();
        }

        if (ImGui::Button("Melanger les points", ImVec2(180, 50)))
        {
            delauney.shuffle();
        }
    }
    ImGui::End();
}
