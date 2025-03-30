#ifndef _SOURCES_HPP
#define _SOURCES_HPP

#include <Eigen/Dense>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>

enum class Model
{
    CUBE,
    ICOSAHEDRON,
    PYRAMID,
    CONE1,
    CONE2,
    CYLINDER,
        SPHERE1,
        SPHERE2,
        SPHERE3,
        TORUS,
    GROUND
};

class Global
{
    public:
        static Global& getInstance() {
            static Global instance;
            return instance;
        }
        Eigen::MatrixXd V;
        Eigen::MatrixXi F{};
        Eigen::MatrixXi E{};
        igl::opengl::glfw::Viewer viewer;
        float ground_level = 0.0f;
        int model_layer = -1;
        Model model = Model::CUBE;
        float height = 2.0f;

        bool playing = false;
        float dt = 0.1f; // 0.05
        float stiffness = 5.0; // 20
        float damping = 0.2; // 0.05
        Eigen::MatrixXd velocity = Eigen::MatrixXd::Zero(V.rows(), 3);

        igl::opengl::glfw::imgui::ImGuiPlugin plugin;
        igl::opengl::glfw::imgui::ImGuiMenu menu;

    private:
        Global() {}
        ~Global() {}
        Global(const Global&) = delete;
        Global& operator=(const Global&) = delete;
        Global(Global&&) = delete;
        Global& operator=(Global&&) = delete;
};

void load_models(Model model, Eigen::MatrixXd& V_src, Eigen::MatrixXi& F_src);

Eigen::MatrixXd compute_spring_forces(
    const Eigen::MatrixXd& V,
    const Eigen::MatrixXi& E,
    double stiffness = 1.0,
    double damping = 0.1,
    const Eigen::MatrixXd& V_prev = Eigen::MatrixXd()
);
double approximate_volume(const Eigen::MatrixXd& V, const Eigen::MatrixXi& F);

void menu();

void init();

#endif // _SOURCES_HPP
