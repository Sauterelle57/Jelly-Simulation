#include <iostream>

#include "sources.hpp"

double approximate_volume(const Eigen::MatrixXd& V, const Eigen::MatrixXi& F)
{
    double vol = 0.0;
    for (int i = 0; i < F.rows(); i++) {
        const Eigen::RowVector3d& v1 = V.row(F(i, 0));
        const Eigen::RowVector3d& v2 = V.row(F(i, 1));
        const Eigen::RowVector3d& v3 = V.row(F(i, 2));
        vol += v1.dot(v2.cross(v3)) / 6.0;
    }
    return std::abs(vol);
}

Eigen::MatrixXd compute_spring_forces(
    const Eigen::MatrixXd& V,
    const Eigen::MatrixXi& E,
    double stiffness,
    double damping,
    const Eigen::MatrixXd& V_prev
) {
    auto &g = Global::getInstance();
    static Model model_used = g.model;
    Eigen::MatrixXd forces = Eigen::MatrixXd::Zero(V.rows(), 3);

    for (int i = 0; i < E.rows(); ++i) {
        int v0 = E(i, 0);
        int v1 = E(i, 1);

        Eigen::Vector3d delta = V.row(v1) - V.row(v0);
        double distance = delta.norm();

        if (distance < 1e-10) continue;

        static std::vector<double> rest_lengths;
        if (model_used != g.model || rest_lengths.size() != E.rows()) {
            rest_lengths.resize(E.rows());
            for (int j = 0; j < E.rows(); ++j) {
                rest_lengths[j] = (V.row(E(j, 1)) - V.row(E(j, 0))).norm();
            }
            model_used = g.model;
        }
        if (rest_lengths.empty()) {
            rest_lengths.resize(E.rows());
            for (int j = 0; j < E.rows(); ++j) {
                rest_lengths[j] = (V.row(E(j, 1)) - V.row(E(j, 0))).norm();
            }
        }
        double L0 = rest_lengths[i];

        double f_magnitude = stiffness * (distance - L0);
        Eigen::Vector3d f_spring = f_magnitude * delta.normalized();

        if (V_prev.rows() == V.rows()) {
            Eigen::Vector3d vel_rel = (V_prev.row(v1) - V_prev.row(v0));
            double damping_magnitude = damping * vel_rel.dot(delta.normalized());
            const Eigen::Vector3d f_damping = damping_magnitude * delta.normalized();
            f_spring += f_damping;
        }

        forces.row(v0) += f_spring;
        forces.row(v1) -= f_spring;
    }

    forces.col(1).array() -= 9.81 * 0.01;

    return forces;
}
