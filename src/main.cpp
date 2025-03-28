#include <igl/opengl/glfw/Viewer.h>
#include <igl/edges.h>
#include <Eigen/Dense>
#include <vector>
#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>

#include "sources.hpp"

// void resetSimulation(igl::opengl::glfw::Viewer &viewer) {
//     V = V_original;
//     F = F_original;
//     selected_vertex = -1;
//     viewer.data().set_vertices(V);
// }

int main() {
    generate_cube(2, V, F);
    // generate_icosahedron(1, V, F);
    // igl::readOFF("bumpy.off", V, F);
    V.rowwise() += Eigen::RowVector3d(0.0, 5.0, 0.0);

    V_original = V;
    F_original = F;
    bool playing = false;

    Eigen::MatrixXd V_ground;
    Eigen::MatrixXi F_ground;
    generate_ground(10.0, V_ground, F_ground);

    Eigen::MatrixXi E;
    igl::edges(F, E);

    Eigen::MatrixXd velocity = Eigen::MatrixXd::Zero(V.rows(), 3);
    Eigen::MatrixXd V_prev = V;
    double dt = 0.1; // 0.05
    double stiffness = 5.0; // 20
    double damping = 0.2; // 0.05

    igl::opengl::glfw::Viewer viewer;

    int model_layer = viewer.append_mesh();
    viewer.data(model_layer).set_mesh(V, F);
    viewer.core().is_animating = true;

    int ground_layer = viewer.append_mesh();
    viewer.data(ground_layer).set_mesh(V_ground, F_ground);
    viewer.data(ground_layer).set_colors(Eigen::RowVector3d(0.9, 0.9, 0.9));

    // igl::opengl::glfw::imgui::ImGuiPlugin plugin;
    // viewer.plugins.push_back(&plugin);
    // igl::opengl::glfw::imgui::ImGuiMenu menu;
    // plugin.widgets.push_back(&menu);
    //
    // menu.callback_draw_viewer_menu = [&]()
    // {
    //     if (ImGui::CollapsingHeader("Simulation", ImGuiTreeNodeFlags_DefaultOpen)) {
    //         if (ImGui::Button(playing ? "Pause" : "Play", ImVec2(-1, 0))) {
    //             playing = !playing;
    //         }
    //         static float simulation_speed = 0.1f;
    //         if (ImGui::SliderFloat("Speed", &simulation_speed, 0.01f, 0.5f)) {
    //             dt = simulation_speed;
    //         }
    //         static float simulation_stiffness = 0.1f;
    //         if (ImGui::SliderFloat("Stiffness", &simulation_stiffness, 0.1f, 30.0f)) {
    //             stiffness = simulation_stiffness;
    //         }
    //         static float simulation_damping = 0.1f;
    //         if (ImGui::SliderFloat("Damping", &simulation_damping, 0.01f, 0.5f)) {
    //             damping = simulation_damping;
    //         }
    //         if (ImGui::Button("Réinitialiser", ImVec2(-1, 0))) {
    //             resetSimulation(viewer);
    //         }
    //     }
    // };

    viewer.callback_pre_draw = [&](igl::opengl::glfw::Viewer& viewer) -> bool {
        if (selected_vertex == -1) {
            Eigen::MatrixXd forces = compute_spring_forces(V, E, stiffness, damping);

            velocity *= 0.98;

            double current_volume = approximate_volume(V, F);
            static double rest_volume = current_volume;
            double volume_ratio = current_volume / rest_volume;

            // std::cout << "Volume actuel: " << current_volume << "\n";
            // std::cout << "Volume de repos: " << rest_volume << "\n";
            // std::cout << "Ratio de volume: " << volume_ratio << "\n";
            // if (volume_ratio != 1.0) {
            //     double intensity = (1.0 - volume_ratio) * 30.0;
            //     Eigen::RowVector3d center = V.colwise().mean();
            //     Eigen::MatrixXd expansion_force = Eigen::MatrixXd::Zero(V.rows(), 3);

            //     for (int i = 0; i < V.rows(); ++i) {
            //         Eigen::RowVector3d dir = (V.row(i) - center).normalized();
            //         expansion_force.row(i) = dir * intensity;
            //     }
            //     forces += expansion_force;
            // }

            velocity += dt * forces;
            V += dt * velocity;

            for (int i = 0; i < V.rows(); ++i) {
                if (V(i, 1) < -1.0) {
                    V(i, 1) = -1.0;
                    velocity(i, 1) *= -0.03;
                    velocity(i, 0) *= 0.5;
                    velocity(i, 2) *= 0.5;
                }
            }
        }
        viewer.data(model_layer).set_vertices(V);
        viewer.data(model_layer).compute_normals();
        return false;
    };

    viewer.launch();
    return 0;
}
