#include <igl/opengl/glfw/Viewer.h>
#include <igl/project.h>
#include <igl/unproject.h>

#include "sources.hpp"

bool mouse_down_callback(igl::opengl::glfw::Viewer& viewer, int button, int modifier)
{
    auto &g = Global::getInstance();
    auto &V = g.V;

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        double x = viewer.current_mouse_x;
        double y = viewer.core().viewport(3) - viewer.current_mouse_y;

        Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
        Eigen::Matrix4f modelview = viewer.core().view * model;

        int closest_vertex = -1;
        float min_dist = std::numeric_limits<float>::max();

        for (int i = 0; i < V.rows(); ++i) {
            Eigen::Vector3f pos = V.row(i).cast<float>();
            Eigen::Vector3f proj = igl::project(pos, modelview, viewer.core().proj, viewer.core().viewport);
            float dist = (proj.head<2>() - Eigen::Vector2f(x, y)).norm();
            if (dist < min_dist) {
                min_dist = dist;
                closest_vertex = i;
            }
        }
        g.selected_vertex = closest_vertex;
        return true;
    }
    return false;
}

bool mouse_move_callback(igl::opengl::glfw::Viewer& viewer, int mouse_x, int mouse_y)
{
    auto &g = Global::getInstance();
    auto &V = g.V;

    if (g.selected_vertex != -1) {
        float x = viewer.current_mouse_x;
        float y = viewer.core().viewport[3] - viewer.current_mouse_y;

        Eigen::Vector3f win(x, y, 0.5f); // 0.5 = profondeur arbitraire entre near/far

        Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
        Eigen::Matrix4f modelview = viewer.core().view * model;

        Eigen::Vector3f pos_3d = igl::unproject(
            win,
            modelview,
            viewer.core().proj,
            viewer.core().viewport
        );
        V.row(g.selected_vertex) = pos_3d.cast<double>();
        viewer.data().set_vertices(V);
        return true;
    }
    return false;
}

bool mouse_up_callback(igl::opengl::glfw::Viewer& viewer, int button, int modifier)
{
    auto &g = Global::getInstance();

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        g.selected_vertex = -1;
        return true;
    }
    return false;
}
