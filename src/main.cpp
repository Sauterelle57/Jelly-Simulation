#include <igl/opengl/glfw/Viewer.h>
#include <igl/edges.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>

#include <vector>

#include "sources.hpp"

void init2()
{
    auto &g = Global::getInstance();
    auto &viewer = g.viewer;
    auto &V = g.V;
    auto &F = g.F;
    auto &E = g.E;

    V = Eigen::MatrixXd();
    F = Eigen::MatrixXi();
    E = Eigen::MatrixXi();

    // viewer.data().clear();
    viewer.data(g.model_layer).clear();

    // V = Eigen::MatrixXd();
    // F = Eigen::MatrixXi();
    // std::cout << "V: "<< V << std::endl;
    load_models(g.model, V, F);

    g.playing = false;
    g.dt = 0.1f; // 0.05
    g.stiffness = 5.0; // 20
    g.damping = 0.2; // 0.05
    g.velocity = Eigen::MatrixXd::Zero(V.rows(), 3);

    viewer.data(g.model_layer).set_mesh(V, F);
    viewer.core().is_animating = true;
    igl::edges(F, E);

    static int ground_layer = -1;
    // if (ground_layer != -1) return;
    ground_layer = viewer.append_mesh();
    Eigen::MatrixXd V_ground;
    Eigen::MatrixXi F_ground;
    load_models(Model::GROUND, V_ground, F_ground);

    viewer.data(ground_layer).set_mesh(V_ground, F_ground);
    viewer.data(ground_layer).set_colors(Eigen::RowVector3d(0.9, 0.9, 0.9));
}

void init()
{
    auto &g = Global::getInstance();
    auto &viewer = g.viewer;

    if (g.model_layer == -1) {
        g.model_layer = viewer.append_mesh();
    }

    g.V.resize(0, 0);
    g.F.resize(0, 0);
    g.E.resize(0, 0);

    viewer.data(g.model_layer).clear();

    load_models(g.model, g.V, g.F);

    igl::edges(g.F, g.E);

    g.playing = false;
    g.dt = 0.1f;
    g.stiffness = 5.0;
    g.damping = 0.2;
    g.velocity = Eigen::MatrixXd::Zero(g.V.rows(), 3);

    viewer.data(g.model_layer).set_mesh(g.V, g.F);
    viewer.core().is_animating = true;

    static int ground_layer = -1;
    if (ground_layer == -1) {
        ground_layer = viewer.append_mesh();
    }

    Eigen::MatrixXd V_ground;
    Eigen::MatrixXi F_ground;
    load_models(Model::GROUND, V_ground, F_ground);

    viewer.data(ground_layer).set_mesh(V_ground, F_ground);
    viewer.data(ground_layer).set_colors(Eigen::RowVector3d(0.9, 0.9, 0.9));
}

int main() {
    init();

    auto &g = Global::getInstance();
    auto &viewer = g.viewer;

    viewer.callback_key_down = [&](igl::opengl::glfw::Viewer &, unsigned int key, int) -> bool {
        auto &global = Global::getInstance();
        if (key == 'A') global.playing = !global.playing;
        return false;
    };

    menu();

    viewer.callback_pre_draw = [&](igl::opengl::glfw::Viewer &viewer_ptr) -> bool {
        auto &global = Global::getInstance();
        static float height = g.height;

        // if (global.V.rows() > 0 && V_original.rows() == 0) {
        //     V_original = global.V;
        // }

        // if (global.height != height) {
        //     init();
        // }
        if (!global.playing) return false;

        const Eigen::MatrixXd forces = compute_spring_forces(global.V, global.E, global.stiffness, global.damping);

        global.velocity *= 0.98;
        global.velocity += global.dt * forces;
        global.V += global.dt * global.velocity;

        for (int i = 0; i < global.V.rows(); ++i) {
            if (global.V(i, 1) < -1.0) {
                global.V(i, 1) = -1.0;
                global.velocity(i, 1) *= -0.03;
                global.velocity(i, 0) *= 0.5;
                global.velocity(i, 2) *= 0.5;
            }
        }

        viewer_ptr.data(global.model_layer).set_vertices(global.V);
        viewer_ptr.data(global.model_layer).compute_normals();
        return false;
    };

    viewer.launch();
    return 0;
}
