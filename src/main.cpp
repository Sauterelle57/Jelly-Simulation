#include <igl/opengl/glfw/Viewer.h>
#include <igl/edges.h>
#include <Eigen/Dense>
#include <vector>

#include "sources.hpp"

int main() {
    generate_cube(2, V, F);
    // generate_icosahedron(1, V, F);
    // igl::readOFF("bumpy.off", V, F);
    V.rowwise() += Eigen::RowVector3d(0.0, 2.0, 0.0);

    Eigen::MatrixXd V_ground;
    Eigen::MatrixXi F_ground;
    generate_ground(10.0, V_ground, F_ground);

    Eigen::MatrixXi E;
    igl::edges(F, E);

    Eigen::MatrixXd velocity = Eigen::MatrixXd::Zero(V.rows(), 3);
    Eigen::MatrixXd V_prev = V;
    double dt = 0.1; // 0.05

    igl::opengl::glfw::Viewer viewer;
    int model_layer = viewer.append_mesh();
    viewer.data(model_layer).set_mesh(V, F);
    viewer.core().is_animating = true;

    int ground_layer = viewer.append_mesh();
    viewer.data(ground_layer).set_mesh(V_ground, F_ground);
    viewer.data(ground_layer).set_colors(Eigen::RowVector3d(0.9, 0.9, 0.9));

    viewer.callback_pre_draw = [&](igl::opengl::glfw::Viewer& viewer) -> bool {
        if (selected_vertex == -1) {
            Eigen::MatrixXd forces = compute_spring_forces(V, E, 1.0, 0.1); //20 0.05

            velocity *= 0.98;

            // double current_volume = approximate_volume(V, F);
            // static double rest_volume = current_volume;
            // double volume_ratio = current_volume / rest_volume;

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
