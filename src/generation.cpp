
#include <Eigen/Dense>

#include "sources.hpp"

void generate_ground(double size, Eigen::MatrixXd& V_src, Eigen::MatrixXi& F_src)
{
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

void generate_cube(double size, Eigen::MatrixXd& V_src, Eigen::MatrixXi& F_src)
{
    auto &g = Global::getInstance();
    V_src.resize(8, 3);
    F_src.resize(12, 3);

    size /= 2.0;

    V_src << -size, -size, -size,
          size, -size, -size,
          size,  size, -size,
         -size,  size, -size,
         -size, -size,  size,
          size, -size,  size,
          size,  size,  size,
         -size,  size,  size;

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

void generate_icosahedron(double size, Eigen::MatrixXd& V_src, Eigen::MatrixXi& F_src) {
    const double phi = (1.0 + std::sqrt(5.0)) / 2.0;
    const double a = size / std::sqrt(1 + phi * phi);
    const double b = a * phi;

    V_src.resize(12, 3);
    V_src << -a,  b,  0,
          a,  b,  0,
          -a, -b,  0,
          a, -b,  0,
          0, -a,  b,
          0,  a,  b,
          0, -a, -b,
          0,  a, -b,
          b,  0, -a,
          b,  0,  a,
          -b,  0, -a,
          -b,  0,  a;

    F_src.resize(20, 3);
    F_src <<  0, 11,  5,
          0,  5,  1,
          0,  1,  7,
          0,  7, 10,
          0, 10, 11,
          1,  5,  9,
          5, 11,  4,
          11, 10,  2,
          10,  7,  6,
          7,  1,  8,
          3,  9,  4,
          3,  4,  2,
          3,  2,  6,
          3,  6,  8,
          3,  8,  9,
          4,  9,  5,
          2,  4, 11,
          6,  2, 10,
          8,  6,  7,
          9,  8,  1;

    V_src *= size;
}