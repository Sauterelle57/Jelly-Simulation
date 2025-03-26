#ifndef _SOURCES_HPP
#define _SOURCES_HPP

#include "../cmake/imgui_impl_glfw.h"
#include "../cmake/imgui_impl_opengl3.h"
#include <igl/opengl/glfw/Viewer.h>
#include <Eigen/Core>

inline Eigen::MatrixXd V;
inline Eigen::MatrixXi F;
inline Eigen::MatrixXd V_ground;
inline Eigen::MatrixXi F_ground;
inline Eigen::MatrixXd faceNormals;
inline igl::opengl::glfw::Viewer viewer;

inline Eigen::Vector3d rotationGoal(0, 0, 0); // Rotation cible (en radians)
inline Eigen::Matrix3d rotation = Eigen::Matrix3d::Identity(); // Matrice de rotation
inline Eigen::Vector3d position(0, 4, 0); // Position initiale
inline bool falling = false; // Indique si le dé tombe
inline double velocity = -0.02; // Vitesse de chute
inline Eigen::Vector3d targetNormal; // Rotation cible
inline float floorPosition = 0; // Position du sol

void dice_4();
void dice_6();
void dice_8();
void dice_12();
void dice_20();
bool key_down_callback(igl::opengl::glfw::Viewer &viewer, unsigned char key, int modifier);
void updateTransform();
void create_ground();

#endif // _SOURCES_HPP