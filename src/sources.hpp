#ifndef _SOURCES_HPP
#define _SOURCES_HPP

#include <Eigen/Dense>


void generate_cube(double size, Eigen::MatrixXd& V, Eigen::MatrixXi& F);
// void generate_cube(double size, int sub_division, Eigen::MatrixXd& V, Eigen::MatrixXi& F);
void generate_ground(double size, Eigen::MatrixXd& V, Eigen::MatrixXi& F);

Eigen::MatrixXd compute_spring_forces(
    const Eigen::MatrixXd& V,
    const Eigen::MatrixXi& E,
    double stiffness = 1.0,
    double damping = 0.1,
    const Eigen::MatrixXd& V_prev = Eigen::MatrixXd()
);

bool callback_pre_draw(igl::opengl::glfw::Viewer& viewer);

#endif // _SOURCES_HPP