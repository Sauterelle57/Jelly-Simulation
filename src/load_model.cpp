#include <iostream>
#include <igl/readOBJ.h>

#include "sources.hpp"

void load_models(Model model, Eigen::MatrixXd& V_src, Eigen::MatrixXi& F_src)
{
    auto &g = Global::getInstance();

    g.ground_level -= 2;
    switch (model) {
        case Model::CUBE:
            generate_cube(2, V_src, F_src);
            break;
        case Model::ICOSAHEDRON:
            generate_icosahedron(1, V_src, F_src);
            break;
        case Model::PYRAMID:
            igl::readOBJ("pyramid.obj", V_src, F_src);
            break;
        case Model::CONE1:
            igl::readOBJ("cone1.obj", V_src, F_src);
            break;
        case Model::CONE2:
            igl::readOBJ("cone2.obj", V_src, F_src);
            break;
        case Model::CYLINDER:
            igl::readOBJ("cylinder.obj", V_src, F_src);
            break;
        case Model::SPHERE1:
            igl::readOBJ("sphere1.obj", V_src, F_src);
            break;
        case Model::SPHERE2:
            igl::readOBJ("sphere2.obj", V_src, F_src);
            break;
        case Model::SPHERE3:
            igl::readOBJ("sphere3.obj", V_src, F_src);
            break;
        case Model::TORUS:
            igl::readOBJ("torus.obj", V_src, F_src);
            break;
        case Model::GROUND:
            generate_ground(10.0, V_src, F_src);
            break;
        default:
            std::cerr << "Unknown model type!" << std::endl;
            break;
    }

    V_src.rowwise() += Eigen::RowVector3d(0.0, 5.0, 0.0);
}
