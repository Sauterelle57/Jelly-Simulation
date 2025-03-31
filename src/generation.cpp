#include <Eigen/Dense>

#include "sources.hpp"

void generate_ground(double size, Eigen::MatrixXd &V_src, Eigen::MatrixXi &F_src) {
    auto &g = Global::getInstance();
    double ground_level = g.ground_level;

    V_src.resize(4, 3);
    F_src.resize(2, 3);

    size /= 2.0;

    V_src << -size, ground_level, -size,
            size, ground_level, -size,
            size, ground_level, size,
            -size, ground_level, size;

    F_src << 0, 2, 1,
            0, 3, 2;
}

void generate_cube(double size, Eigen::MatrixXd &V_src, Eigen::MatrixXi &F_src) {
    auto &g = Global::getInstance();
    V_src.resize(8, 3);
    F_src.resize(12, 3);

    size /= 2.0;

    V_src << -size, -size, -size,
            size, -size, -size,
            size, size, -size,
            -size, size, -size,
            -size, -size, size,
            size, -size, size,
            size, size, size,
            -size, size, size;

    F_src << 0, 1, 2,
            0, 2, 3,
            4, 5, 6,
            4, 6, 7,
            0, 4, 7,
            0, 7, 3,
            1, 5, 6,
            1, 6, 2,
            0, 1, 5,
            0, 5, 4,
            3, 2, 6,
            3, 6, 7;
}

void generate_icosahedron(double size, Eigen::MatrixXd &V_src, Eigen::MatrixXi &F_src) {
    const double phi = (1.0 + std::sqrt(5.0)) / 2.0;
    const double a = size / std::sqrt(1 + phi * phi);
    const double b = a * phi;

    V_src.resize(12, 3);
    V_src << -a, b, 0,
            a, b, 0,
            -a, -b, 0,
            a, -b, 0,
            0, -a, b,
            0, a, b,
            0, -a, -b,
            0, a, -b,
            b, 0, -a,
            b, 0, a,
            -b, 0, -a,
            -b, 0, a;

    F_src.resize(26, 3);
    F_src << 0, 11, 5,
            0, 5, 1,
            0, 1, 7,
            0, 7, 10,
            0, 10, 11,
            1, 5, 9,
            5, 11, 4,
            11, 10, 2,
            10, 7, 6,
            7, 1, 8,
            3, 9, 4,
            3, 4, 2,
            3, 2, 6,
            3, 6, 8,
            3, 8, 9,
            4, 9, 5,
            2, 4, 11,
            6, 2, 10,
            8, 6, 7,
            9, 8, 1,
            0, 3, 6,
            1, 2, 7,
            4, 7, 10,
            5, 6, 11,
            8, 11, 3,
            9, 10, 2;

    V_src *= size;
}

void generate_cylinder(double radius, double height, int segments, Eigen::MatrixXd& V_src, Eigen::MatrixXi& F_src) {
    int num_vertices = 2 * segments + 2;
    int num_faces = 4 * segments + segments;
    V_src.resize(num_vertices, 3);
    F_src.resize(num_faces, 3);

    V_src.row(0) = Eigen::Vector3d(0, height / 2.0, 0);
    V_src.row(1) = Eigen::Vector3d(0, -height / 2.0, 0);

    for (int i = 0; i < segments; i++) {
        double angle = 2.0 * M_PI * i / segments;
        double x = radius * cos(angle);
        double z = radius * sin(angle);

        V_src.row(2 + i) = Eigen::Vector3d(x, height / 2.0, z);
        V_src.row(2 + segments + i) = Eigen::Vector3d(x, -height / 2.0, z);
    }

    for (int i = 0; i < segments; i++) {
        int next = (i + 1) % segments;
        F_src.row(i) = Eigen::Vector3i(0, 2 + next, 2 + i);
        F_src.row(i + segments) = Eigen::Vector3i(1, 2 + segments + i, 2 + segments + next);
    }

    for (int i = 0; i < segments; i++) {
        int next = (i + 1) % segments;
        F_src.row(2 * segments + 2 * i) = Eigen::Vector3i(2 + i, 2 + next, 2 + segments + next);
        F_src.row(2 * segments + 2 * i + 1) = Eigen::Vector3i(2 + i, 2 + segments + next, 2 + segments + i);
    }

    for (int i = 0; i < segments; i++) {
        int opposite = (i + segments / 2) % segments;
        F_src.row(4 * segments + i) = Eigen::Vector3i(2 + i, 2 + segments + opposite, 1);
    }
}


void load_models(Model model, Eigen::MatrixXd &V_src, Eigen::MatrixXi &F_src) {
    auto &g = Global::getInstance();

    g.ground_level = -1.02;
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
        case Model::CONE:
            igl::readOBJ("cone.obj", V_src, F_src);
            break;
        case Model::CYLINDER:
            generate_cylinder(1.0, 2.0, 20, V_src, F_src);
        break;
        case Model::PENTAGON:
            generate_cylinder(1.0, 1.0, 5, V_src, F_src);
        break;
        case Model::GROUND:
            generate_ground(15.0, V_src, F_src);
            return;
        default:
            std::cerr << "Unknown model type!" << std::endl;
            return;
    }

    V_src.rowwise() += Eigen::RowVector3d(0.0, g.height, 0.0);
}
