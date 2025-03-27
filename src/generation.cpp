
#include <Eigen/Dense>

void generate_ground(double size, Eigen::MatrixXd& V, Eigen::MatrixXi& F)
{
    V.resize(4, 3);
    F.resize(2, 3);

    size /= 2.0;

    V << -size, -1, -size,
          size, -1, -size,
          size, -1, size,
         -size, -1, size;

    F << 0, 2, 1,
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

    F << 0, 1, 2,  0, 2, 3,
         4, 5, 6,  4, 6, 7,
         0, 4, 7,  0, 7, 3,
         1, 5, 6,  1, 6, 2,
         0, 1, 5,  0, 5, 4,
         3, 2, 6,  3, 6, 7;
}
