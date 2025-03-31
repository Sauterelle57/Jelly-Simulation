#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>

#include "sources.hpp"

void menu()
{
    auto &g = Global::getInstance();
    auto &playing = g.playing;

    g.viewer.plugins.push_back(&g.plugin);
    g.plugin.widgets.push_back(&g.menu);

    g.menu.callback_draw_viewer_menu = [&]() {
        if (ImGui::CollapsingHeader("Simulation", ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ImGui::Button(playing ? "Pause" : "Play", ImVec2(-1, 0))) {
                playing = !playing;
            }
            if (ImGui::Button("Reset", ImVec2(-1, 0))) {
                init();
            }
            if (ImGui::SliderFloat("Height", &g.height, 0.5f, 30.0f)) {
                init();
            }
            if (ImGui::Button("Cube", ImVec2(-1, 0))) {
                g.model = Model::CUBE;
                init();
            }
            if (ImGui::Button("Icosahedron", ImVec2(-1, 0))) {
                g.model = Model::ICOSAHEDRON;
                init();
            }
            if (ImGui::Button("Pyramid", ImVec2(-1, 0))) {
                g.model = Model::PYRAMID;
                init();
            }
            if (ImGui::Button("Cone 1", ImVec2(-1, 0))) {
                g.model = Model::CONE1;
                init();
            }
            if (ImGui::Button("Cone 2", ImVec2(-1, 0))) {
                g.model = Model::CONE2;
                init();
            }
            if (ImGui::Button("Cylinder", ImVec2(-1, 0))) {
                g.model = Model::CYLINDER;
                init();
            }
        }
    };
}
