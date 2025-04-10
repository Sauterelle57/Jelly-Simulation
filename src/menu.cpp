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
                if (g.custom_model != nullptr) g.model = Model::CUSTOM;
                init();
            }
            if (ImGui::SliderFloat("Height", &g.height, 0.5f, 10.0f)) {
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
            if (ImGui::Button("Cone", ImVec2(-1, 0))) {
                g.model = Model::CONE;
                init();
            }
            if (ImGui::Button("Pentagon", ImVec2(-1, 0))) {
                g.model = Model::PENTAGON;
                init();
            }
            if (ImGui::Button("Cylinder", ImVec2(-1, 0))) {
                g.model = Model::CYLINDER;
                init();
            }
        }
    };
}
