#include <Eigen/Dense>


Eigen::MatrixXd compute_spring_forces(
    const Eigen::MatrixXd& V,         // Positions des sommets (n x 3)
    const Eigen::MatrixXi& E,         // Arêtes (ressorts) (m x 2)
    double stiffness = 1.0,           // Raideur des ressorts (k)
    double damping = 0.1,             // Amortissement visqueux
    const Eigen::MatrixXd& V_prev = Eigen::MatrixXd() // Vitesses (optionnel)
) {
    Eigen::MatrixXd forces = Eigen::MatrixXd::Zero(V.rows(), 3);

    // Si aucune arête n'est fournie, utiliser les arêtes du maillage de surface
    if (E.rows() == 0) {
        // (Optionnel: générer les arêtes à partir des faces F si nécessaire)
        // igl::edges(F, E); // Si vous avez accès à libigl
    }

    // Parcourir toutes les arêtes (ressorts)
    for (int i = 0; i < E.rows(); ++i) {
        int v0 = E(i, 0); // Sommet source
        int v1 = E(i, 1); // Sommet cible

        // Vecteur entre les sommets
        Eigen::Vector3d delta = V.row(v1) - V.row(v0);
        double distance = delta.norm();

        // Éviter la division par zéro
        if (distance < 1e-10) continue;

        // Longueur au repos (stockée ou calculée initialement)
        static std::vector<double> rest_lengths;
        if (rest_lengths.empty()) {
            rest_lengths.resize(E.rows());
            for (int j = 0; j < E.rows(); ++j) {
                rest_lengths[j] = (V.row(E(j, 1)) - V.row(E(j, 0))).norm();
            }
        }
        double L0 = rest_lengths[i];

        // Force élastique (loi de Hooke)
        double f_magnitude = stiffness * (distance - L0);
        Eigen::Vector3d f_spring = f_magnitude * delta.normalized();

        // Amortissement visqueux (si V_prev est fourni)
        if (V_prev.rows() == V.rows()) {
            Eigen::Vector3d vel_rel = (V_prev.row(v1) - V_prev.row(v0));
            double damping_magnitude = damping * vel_rel.dot(delta.normalized());
            Eigen::Vector3d f_damping = damping_magnitude * delta.normalized();
            f_spring += f_damping;
        }

        // Appliquer les forces (action-réaction)
        forces.row(v0) += f_spring;
        forces.row(v1) -= f_spring;
    }

    // Ajouter d'autres forces (gravité, collisions, etc.)
    forces.col(1).array() -= 9.81 * 0.01; // Gravité faible (ajustable) (9.81 * 0.01)

    return forces;
}
