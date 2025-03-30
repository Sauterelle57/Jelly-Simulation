#include <igl/opengl/glfw/Viewer.h>
#include <igl/edges.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>

#include <vector>

#include "sources.hpp"

void init() {
    auto &g = Global::getInstance();
    auto &viewer = g.viewer;
    auto &V = g.V;
    auto &F = g.F;

    load_models(Model::ICOSAHEDRON, V, F);
    g.V_original = V;
    g.F_original = F;
    Eigen::MatrixXd V_ground;
    Eigen::MatrixXi F_ground;
    load_models(Model::GROUND, V_ground, F_ground);
    igl::edges(F, g.E);

    g.dt = 0.1f; // 0.05
    g.stiffness = 5.0; // 20
    g.damping = 0.2; // 0.05
    g.velocity = Eigen::MatrixXd::Zero(V.rows(), 3);

    viewer.data(g.model_layer).set_mesh(V, F);
    viewer.core().is_animating = true;

    static int ground_layer = viewer.append_mesh();
    viewer.data(ground_layer).set_mesh(V_ground, F_ground);
    viewer.data(ground_layer).set_colors(Eigen::RowVector3d(0.9, 0.9, 0.9));
}

int main() {
    init();

    auto &g = Global::getInstance();
    auto &viewer = g.viewer;
    auto &V = g.V;
    auto &velocity = g.velocity;
    auto &dt = g.dt;
    auto &playing = g.playing;

    viewer.callback_key_down = [&](igl::opengl::glfw::Viewer &, unsigned int key, int) -> bool {
        if (key == 'A') playing = !playing;
        return false;
    };

    menu();
    // igl::opengl::glfw::imgui::ImGuiPlugin plugin;
    // g.viewer.plugins.push_back(&plugin);
    // igl::opengl::glfw::imgui::ImGuiMenu menu;
    // plugin.widgets.push_back(&menu);
    //
    // menu.callback_draw_viewer_menu = [&]() {
    //     if (ImGui::CollapsingHeader("Simulation", ImGuiTreeNodeFlags_DefaultOpen)) {
    //         if (ImGui::Button(playing ? "Pause" : "Play", ImVec2(-1, 0))) {
    //             playing = !playing;
    //         }
    //         ImGui::SliderFloat("Speed", &g.dt, 0.01f, 0.5f);
    //         ImGui::SliderFloat("Stiffness", &g.stiffness, 0.1f, 30.0f);
    //         ImGui::SliderFloat("Damping", &g.damping, 0.01f, 0.5f);
    //         // if (ImGui::Button("Reset", ImVec2(-1, 0))) {
    //         //     resetSimulation();
    //         // }
    //     }
    // };

    viewer.callback_pre_draw = [&](igl::opengl::glfw::Viewer &viewer_ptr) -> bool {
        if (!playing) return false;

        const Eigen::MatrixXd forces = compute_spring_forces(g.V, g.E, g.stiffness, g.damping);

        velocity *= 0.98;
        velocity += g.dt * forces;
        g.V += g.dt * velocity;

        for (int i = 0; i < g.V.rows(); ++i) {
            if (g.V(i, 1) < -1.0) {
                g.V(i, 1) = -1.0;
                velocity(i, 1) *= -0.03;
                velocity(i, 0) *= 0.5;
                velocity(i, 2) *= 0.5;
            }
        }

        viewer_ptr.data(g.model_layer).set_vertices(g.V);
        viewer_ptr.data(g.model_layer).compute_normals();
        return false;
    };

    viewer.launch();
    return 0;
}
