#include <igl/opengl/glfw/Viewer.h>
#include <igl/edges.h>
#include <igl/opengl/glfw/imgui/ImGuiHelpers.h>

#include <vector>

#include "sources.hpp"

void init()
{
    auto &g = Global::getInstance();
    auto &viewer = g.viewer;

    g.ground_level = -1.02;

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

int main(int argc, char **argv) {
    auto &g = Global::getInstance();
    auto &viewer = g.viewer;

    if (argc > 1) {
        g.model = Model::CUSTOM;
        g.custom_model = argv[1];
    }

    init();


    viewer.callback_key_down = [&](igl::opengl::glfw::Viewer &, unsigned int key, int) -> bool {
        auto &global = Global::getInstance();
        if (key == 'A') global.playing = !global.playing;
        if (key == 'R') {
            if (global.custom_model != nullptr)
                global.model = Model::CUSTOM;
            init();
        }
        return false;
    };

    menu();

    viewer.callback_pre_draw = [&](igl::opengl::glfw::Viewer &viewer_ptr) -> bool {
        auto &global = Global::getInstance();

        if (!global.playing) return false;

        const Eigen::MatrixXd forces = compute_spring_forces(global.V, global.E, global.stiffness, global.damping);

        global.velocity += global.dt * forces;
        global.V += global.dt * global.velocity;

        for (int i = 0; i < global.V.rows(); ++i) {
            if (global.V(i, 1) < global.ground_level+0.02) {
                global.V(i, 1) = global.ground_level+0.02;
                global.velocity(i, 1) *= -0.03;
                global.velocity(i, 0) *= 0.45;
                global.velocity(i, 2) *= 0.55;
            }
        }

        viewer_ptr.data(global.model_layer).set_vertices(global.V);
        viewer_ptr.data(global.model_layer).compute_normals();
        return false;
    };

    viewer.launch();
    return 0;
}
