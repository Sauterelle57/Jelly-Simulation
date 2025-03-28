#ifndef _SOURCES_HPP
#define _SOURCES_HPP

#include <Eigen/Dense>

inline int selected_vertex = -1;
inline Eigen::MatrixXd V;
inline Eigen::MatrixXi F;
inline Eigen::MatrixXd V_original;
inline Eigen::MatrixXi F_original;
inline bool initialized_diagonals = false;
inline Eigen::MatrixXi E_diag;

void generate_cube(double size, Eigen::MatrixXd& V, Eigen::MatrixXi& F);
void generate_icosahedron(double size, Eigen::MatrixXd& V, Eigen::MatrixXi& F);
void generate_ground(double size, Eigen::MatrixXd& V, Eigen::MatrixXi& F);

Eigen::MatrixXd compute_spring_forces(
    const Eigen::MatrixXd& V,
    const Eigen::MatrixXi& E,
    double stiffness = 1.0,
    double damping = 0.1,
    const Eigen::MatrixXd& V_prev = Eigen::MatrixXd()
);
double approximate_volume(const Eigen::MatrixXd& V, const Eigen::MatrixXi& F);

bool mouse_down_callback(igl::opengl::glfw::Viewer& viewer, int button, int modifier);
bool mouse_move_callback(igl::opengl::glfw::Viewer& viewer, int mouse_x, int mouse_y);
bool mouse_up_callback(igl::opengl::glfw::Viewer& viewer, int button, int modifier);

#endif // _SOURCES_HPP
