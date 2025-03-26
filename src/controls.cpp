#include "sources.hpp"

bool key_down_callback(igl::opengl::glfw::Viewer &viewer, unsigned char key, int modifier)
{
    switch (key) {
        case 'A': rotation = Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitY()) * rotation; break;//left
        case 'D': rotation = Eigen::AngleAxisd(-0.1, Eigen::Vector3d::UnitY()) * rotation; break;//right
        case 'S': rotation = Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitX()) * rotation; break;//down
        case 'W': rotation = Eigen::AngleAxisd(-0.1, Eigen::Vector3d::UnitX()) * rotation; break;//up
        case 'Q': rotation = Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitZ()) * rotation; break;//anti-horaire
        case 'E': rotation = Eigen::AngleAxisd(-0.1, Eigen::Vector3d::UnitZ()) * rotation; break;//horaire
        case 1: std::cout << "Dé lâché !" << std::endl; falling = true; break;
        default: return false;
    }
    updateTransform();

    return true;
}
