#include "sources.hpp"

void create_ground()
{
    double ground_size = 3.0;
    V_ground.resize(4, 3);
    F_ground.resize(2, 3);

    V_ground << -ground_size, 0, -ground_size,
    ground_size, 0, -ground_size,
    ground_size, 0, ground_size,
    -ground_size, 0, ground_size;

    F_ground << 0, 1, 2,
    0, 2, 3;

    static int ground_layer = viewer.append_mesh();
    viewer.data(ground_layer).set_mesh(V_ground, F_ground);
    viewer.data(ground_layer).set_colors(Eigen::RowVector3d(0.9, 0.9, 0.9));
}
