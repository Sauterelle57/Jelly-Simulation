#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>

#include "sources.hpp"

void resetSimulation() {
    auto &g = Global::getInstance();
    auto &V = g.V;

    V = g.V_original;
    g.F = g.F_original;
    g.selected_vertex = -1;
    g.viewer.data().set_vertices(V);
    g.dt = 0.1f; // 0.05
    g.stiffness = 5.0; // 20
    g.damping = 0.2; // 0.05
    g.playing = false;
    g.velocity = Eigen::MatrixXd::Zero(V.rows(), 3);
}

void menu()
{
    auto &g = Global::getInstance();
    auto &playing = g.playing;

    // igl::opengl::glfw::imgui::ImGuiPlugin plugin;
    g.viewer.plugins.push_back(&g.plugin);
    // igl::opengl::glfw::imgui::ImGuiMenu menu;
    g.plugin.widgets.push_back(&g.menu);

    g.menu.callback_draw_viewer_menu = [&]() {
        if (ImGui::CollapsingHeader("Simulation", ImGuiTreeNodeFlags_DefaultOpen)) {
            if (ImGui::Button(playing ? "Pause" : "Play", ImVec2(-1, 0))) {
                playing = !playing;
            }
            ImGui::SliderFloat("Speed", &g.dt, 0.01f, 0.5f);
            ImGui::SliderFloat("Stiffness", &g.stiffness, 0.1f, 30.0f);
            ImGui::SliderFloat("Damping", &g.damping, 0.01f, 0.5f);
            if (ImGui::Button("Reset", ImVec2(-1, 0))) {
                resetSimulation();
            }
        }
    };
}
