#ifndef _SOURCES_HPP
#define _SOURCES_HPP

#include <Eigen/Dense>
#include <igl/opengl/glfw/Viewer.h>
#include <igl/opengl/glfw/imgui/ImGuiPlugin.h>
#include <igl/opengl/glfw/imgui/ImGuiMenu.h>

class Global
{
    public:
        static Global& getInstance() {
            static Global instance;
            return instance;
        }
        int selected_vertex = -1;
        Eigen::MatrixXd V;
        Eigen::MatrixXi F{};
        Eigen::MatrixXi E{};
        Eigen::MatrixXd V_original{};
        Eigen::MatrixXi F_original{};
        igl::opengl::glfw::Viewer viewer;
        float ground_level = -2.02f;
        int model_layer = viewer.append_mesh();

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

void load_models(Model model, Eigen::MatrixXd& V_src, Eigen::MatrixXi& F_src);

void generate_cube(double size, Eigen::MatrixXd& V, Eigen::MatrixXi& F);
void generate_icosahedron(double size, Eigen::MatrixXd& V, Eigen::MatrixXi& F);
void generate_ground(double size, Eigen::MatrixXd& V, Eigen::MatrixXi& F);

Eigen::MatrixXd compute_spring_forces(
    const Eigen::MatrixXd& V,
    const Eigen::MatrixXi& E,
    double stiffness = 1.0,
    double damping = 0.1,
    const Eigen::MatrixXd& V_prev = Eigen::MatrixXd()
);
double approximate_volume(const Eigen::MatrixXd& V, const Eigen::MatrixXi& F);

void menu();

bool mouse_down_callback(igl::opengl::glfw::Viewer& viewer, int button, int modifier);
bool mouse_move_callback(igl::opengl::glfw::Viewer& viewer, int mouse_x, int mouse_y);
bool mouse_up_callback(igl::opengl::glfw::Viewer& viewer, int button, int modifier);

#endif // _SOURCES_HPP
