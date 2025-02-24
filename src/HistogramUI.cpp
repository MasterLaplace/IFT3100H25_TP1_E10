#include "HistogramUI.hpp"
#include "Controller2D.hpp"

void HistogramUI::setup(Controller2D *_controller)
{
    controller = _controller;
    gui.setup();
}

void HistogramUI::draw()
{
    gui.begin();
    drawOptionPanel();
    gui.end();
}

void HistogramUI::drawOptionPanel()
{
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 200, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(200, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);

    ImGui::Begin("Options de l'histogramme");

    ImGui::SetNextItemWidth(180);
    if (ImGui::Button("Rouge", ImVec2(180, 40)))
    {
        controller->drawHistogram(0);
    }

    ImGui::Spacing();

    ImGui::SetNextItemWidth(180);
    if (ImGui::Button("Vert", ImVec2(180, 40)))
    {
        controller->drawHistogram(1);
    }

    ImGui::Spacing();

    ImGui::SetNextItemWidth(180);
    if (ImGui::Button("Bleu", ImVec2(180, 40)))
    {
        controller->drawHistogram(2);
    }

    ImGui::Spacing();

    ImGui::SetNextItemWidth(180);
    if (ImGui::Button("Exporter", ImVec2(180, 40)))
    {
        controller->exportImage();
    }

    ImGui::Spacing();

    ImGui::SetNextItemWidth(180);
    if (ImGui::Button("Retour", ImVec2(180, 40)))
    {
        controller->drawPointButtonPressed();
    }

    ImGui::End();
}
