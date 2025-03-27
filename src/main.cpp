#include <igl/opengl/glfw/Viewer.h>
#include <igl/edges.h>
#include <Eigen/Dense>
#include <vector>

#include "sources.hpp"

int main() {
    // 1. Générer un cube
    Eigen::MatrixXd V;
    Eigen::MatrixXi F;
    generate_cube(0.5, V, F);
    // Générer le sol
    Eigen::MatrixXd V_ground;
    Eigen::MatrixXi F_ground;
    generate_ground(3.0, V_ground, F_ground);

    // 3. Extraire les arêtes pour les ressorts
    Eigen::MatrixXi E;
    igl::edges(F, E);

    // 3. Initialiser la simulation
    Eigen::MatrixXd velocity = Eigen::MatrixXd::Zero(V.rows(), 3);
    Eigen::MatrixXd V_prev = V;
    double dt = 0.05;

    // 4. Afficher avec libigl
    igl::opengl::glfw::Viewer viewer;
    int cube_layer = viewer.append_mesh();
    viewer.data(cube_layer).set_mesh(V, F);
    viewer.core().is_animating = true;

    int ground_layer = viewer.append_mesh();
    viewer.data(ground_layer).set_mesh(V_ground, F_ground);
    viewer.data(ground_layer).set_colors(Eigen::RowVector3d(0.9, 0.9, 0.9));

    // 5. Boucle de simulation
    viewer.callback_pre_draw = [&](igl::opengl::glfw::Viewer& viewer) -> bool {
        Eigen::MatrixXd forces = compute_spring_forces(V, E, 20.0, 0.01, V_prev);

        velocity += dt * forces;
        V += dt * velocity;
        V_prev = V;

        for (int i = 0; i < V.rows(); ++i) {
            if (V(i, 1) < -1.0) {
                V(i, 1) = -1.0;
                velocity(i, 1) *= -0.3;
            }
        }

        viewer.data(cube_layer).set_vertices(V);
        viewer.data(cube_layer).compute_normals();
        return false;
    };

    viewer.launch();
    return 0;
}
