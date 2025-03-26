#include "sources.hpp"

#include <igl/opengl/glfw/Viewer.h>
#include <Eigen/Core>
#include <cmath>

void dice_4()
{
    double size = 0.2;
    V.resize(4, 3);
    F.resize(4, 3);

    V << size,  size,  size,
        -size, -size,  size,
        -size,  size, -size,
        size, -size, -size;

    F << 0, 1, 2,
        0, 1, 3,
        0, 2, 3,
        1, 2, 3;

    targetNormal = Eigen::Vector3d(0, -1, 0);
    floorPosition = size/2+0.03;
}

void dice_6()
{
    double size = 0.2;
    V.resize(8, 3);
    F.resize(12, 3);

    V << -size, -size, -size,
         size, -size, -size,
         size,  size, -size,
        -size,  size, -size,
        -size, -size,  size,
         size, -size,  size,
         size,  size,  size,
        -size,  size,  size;

    F << 0, 1, 2,  2, 3, 0,
         1, 5, 6,  6, 2, 1,
         5, 4, 7,  7, 6, 5,
         4, 0, 3,  3, 7, 4,
         3, 2, 6,  6, 7, 3,
         4, 5, 1,  1, 0, 4;

    targetNormal = Eigen::Vector3d(0, -1, 0);
    floorPosition = size+0.01;
}

void dice_8() {
    double size = 0.2;
    V.resize(6, 3);
    F.resize(8, 3);

    V <<  size,  0,  0,
         -size,  0,  0,
          0,  size,  0,
          0, -size,  0,
          0,  0,  size,
          0,  0, -size;

    F << 0, 2, 4,
         2, 1, 4,
         1, 3, 4,
         3, 0, 4,
         0, 5, 2,
         2, 5, 1,
         1, 5, 3,
         3, 5, 0;

    targetNormal = Eigen::Vector3d(0, 1, 0);
    floorPosition = size-0.08;
}

void dice_12() {
    V.resize(20, 3);
    F.resize(12, 5);

    double phi = (1.0 + sqrt(5.0)) / 2.0;
    double inv_phi = 1.0 / phi;

    V << -1.0, -1.0, -1.0,   1.0, -1.0, -1.0,   -1.0,  1.0, -1.0,   1.0,  1.0, -1.0,
         -1.0, -1.0,  1.0,   1.0, -1.0,  1.0,   -1.0,  1.0,  1.0,   1.0,  1.0,  1.0,
          0.0, -inv_phi, -phi,   0.0,  inv_phi, -phi,   0.0, -inv_phi,  phi,   0.0,  inv_phi,  phi,
         -inv_phi, -phi,  0.0,   inv_phi, -phi,  0.0,   -inv_phi,  phi,  0.0,   inv_phi,  phi,  0.0,
         -phi,  0.0, -inv_phi,   phi,  0.0, -inv_phi,   -phi,  0.0,  inv_phi,   phi,  0.0,  inv_phi;

    F <<  0,  8,  4, 14, 12,
          0, 12,  2, 10,  8,
          1,  9, 11, 17, 15,
          1, 15,  7, 19,  9,
          2, 10,  6, 16, 18,
          2, 18,  3, 11, 10,
          3, 11,  1, 17, 19,
          3, 19,  7, 16, 18,
          4,  8, 10,  6, 16,
          4, 16,  5, 13, 14,
          5, 13, 15,  7, 16,
          5, 17, 11,  9, 13;

    targetNormal = Eigen::Vector3d(0, -1, 0);
    floorPosition = -0.5;
}

void dice_20()
{
    double size = 0.2;
    V.resize(12, 3);
    F.resize(20, 3);

    double phi = ((1 + sqrt(5)) / 2.0) /5;
    V << -size,  phi,  0,
        size,  phi,  0,
        -size, -phi,  0,
        size, -phi,  0,
        0, -size,  phi,
        0,  size,  phi,
        0, -size, -phi,
        0,  size, -phi,
        phi,  0, -size,
        phi,  0,  size,
        -phi,  0, -size,
        -phi,  0,  size;

    F << 0, 11, 5,
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
        9, 8, 1;

    targetNormal = Eigen::Vector3d(0, -1, 0);
    floorPosition = size+0.11;
}