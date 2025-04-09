#include "CurveUI.hpp"
#include "Controller.hpp"

void CurveUI::setup(Controller *_controller)
{
    controller = _controller;
    gui.setup();
}

void CurveUI::draw()
{
    gui.begin();
    drawOptionPanel();
    gui.end();
}

void CurveUI::drawOptionPanel()
{
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 200, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);

    ImGui::Begin("Options de courbe");

    ImGui::SetNextItemWidth(180);
    ImGui::Text("Type de courbes : ");

    ImGui::SetNextItemWidth(180);
    if (ImGui::Button("Bezier", ImVec2(180, 40)))
    {
        controller->setCurveType(plugin::states::BEZIER);
    }

    ImGui::Spacing();

    ImGui::SetNextItemWidth(180);
    if (ImGui::Button("Catmull-Rom", ImVec2(180, 40)))
    {
        controller->setCurveType(plugin::states::CATMULL_ROM);
    }

    ImGui::Spacing();

    ImGui::SetNextItemWidth(180);
    if (ImGui::Button("Coons", ImVec2(180, 40)))
    {
        controller->setCurveType(plugin::states::COONS);
    }

    ImGui::Spacing();

    ImGui::SetNextItemWidth(180);
    if (ImGui::Button("Retour", ImVec2(180, 40)))
    {
        controller->drawPointButtonPressed();
    }

    ImGui::SetNextItemWidth(180);
    ofPoint selectedPoint = controller->getCurvePoint();
    if (selectedPoint == ofPoint(-1.0f, -1.0f, -1.0f))
    {
        ImGui::Text("Aucun point selectionne");
    }
    else
    {
        ImGui::Text("Point selectionne :");
        if (ImGui::SliderFloat("X", &selectedPoint.x, 0.0f, 2000.0f) ||
            ImGui::SliderFloat("Y", &selectedPoint.y, 0.0f, 2000.0f) ||
            ImGui::SliderFloat("Z", &selectedPoint.z, 0.0f, 1000.0f))
        {
            controller->setCurvePoint(selectedPoint);
        }
    }

    if (controller->getCurveType() == plugin::states::BEZIER)
    {
        ImGui::SetNextItemWidth(180);
        if (ImGui::Button("Convertir", ImVec2(180, 40)))
        {
            controller->convertCurve();
        }
    }

    if (controller->getCurveType() == plugin::states::CATMULL_ROM)
    {
        ImGui::SetNextItemWidth(180);
        if (ImGui::Button("Ajouter un point", ImVec2(180, 40)))
        {
            controller->addPoint();
        }
    }

    ImGui::End();
}
