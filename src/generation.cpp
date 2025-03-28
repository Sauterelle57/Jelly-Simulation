
#include <Eigen/Dense>

void generate_ground(double size, Eigen::MatrixXd& V_ground, Eigen::MatrixXi& F_ground)
{
    V_ground.resize(4, 3);
    F_ground.resize(2, 3);

    size /= 2.0;

    V_ground << -size, -1, -size,
          size, -1, -size,
          size, -1, size,
         -size, -1, size;

    F_ground << 0, 2, 1,
         0, 3, 2;
}

// Génère un cube centré en (0,0,0) avec une taille donnée
void generate_cube(double size, Eigen::MatrixXd& V, Eigen::MatrixXi& F) {
    V.resize(8, 3);
    F.resize(12, 3);

    size /= 2.0;

    V << -size, -size, -size,
          size, -size, -size,
          size,  size, -size,
         -size,  size, -size,
         -size, -size,  size,
          size, -size,  size,
          size,  size,  size,
         -size,  size,  size;

    F << 0, 1, 2,
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

void generate_icosahedron(double size, Eigen::MatrixXd& V, Eigen::MatrixXi& F) {
    // Constante pour le nombre d'or
    const double phi = (1.0 + std::sqrt(5.0)) / 2.0;
    const double a = size / std::sqrt(1 + phi * phi);
    const double b = a * phi;

    V.resize(12, 3);
    V << -a,  b,  0,
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

    F.resize(20, 3);
    F <<  0, 11,  5,
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

    V *= size;
}