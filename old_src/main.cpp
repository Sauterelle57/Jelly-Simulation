#include <igl/opengl/glfw/Viewer.h>
#include <igl/readOBJ.h>
#include <iostream>
#include <imgui.h>
#include <GLFW/glfw3.h>

#include "sources.hpp"

void compute_normals()
{
    faceNormals.resize(F.rows(), 3);
    for (int i = 0; i < F.rows(); ++i) {
        Eigen::Vector3d v0 = V.row(F(i, 0));
        Eigen::Vector3d v1 = V.row(F(i, 1));
        Eigen::Vector3d v2 = V.row(F(i, 2));
        faceNormals.row(i) = (v1 - v0).cross(v2 - v0).normalized();
    }
}

void init(int nb_faces)
{
    switch (nb_faces) {
        case 4: dice_4(); break;
        case 6: dice_6(); break;
        case 8: dice_8(); break;
        case 12: dice_12(); break;
        case 20: dice_20(); break;
        default: dice_6(); break;
    }

    static int dice_layer = viewer.append_mesh();

    viewer.data(dice_layer).clear();
    viewer.data(dice_layer).set_mesh(V, F);

    compute_normals();

    create_ground();
}

void updateTransform()
{
    Eigen::MatrixXd transformedV = V * rotation.transpose();
    for (int i = 0; i < V.rows(); ++i) {
        transformedV.row(i) += position.transpose();
    }
    viewer.data(1).set_vertices(transformedV);
    viewer.data(1).compute_normals();
}

// Eigen::Vector3d findNearestFaceDynamic()
// {
//     Eigen::Vector3d upVector = rotation * Eigen::Vector3d(0, 1, 0); // Normale actuelle du haut

//     int bestFaceIndex = -1;
//     double bestDot = -1.0;

//     // Vérifier toutes les faces
//     for (int i = 0; i < F.rows(); i++) {
//         Eigen::Vector3d v0 = V.row(F(i, 0));
//         Eigen::Vector3d v1 = V.row(F(i, 1));
//         Eigen::Vector3d v2 = V.row(F(i, 2));

//         // Calcul de la normale de la face
//         Eigen::Vector3d normal = (v1 - v0).cross(v2 - v0).normalized();

//         // Trouver la face la plus "vers le haut"
//         double dot = upVector.dot(normal);
//         if (dot > bestDot) {
//             bestDot = dot;
//             bestFaceIndex = i;
//         }
//     }

//     // Retourner la normale de la meilleure face
//     if (bestFaceIndex != -1) {
//         Eigen::Vector3d v0 = V.row(F(bestFaceIndex, 0));
//         Eigen::Vector3d v1 = V.row(F(bestFaceIndex, 1));
//         Eigen::Vector3d v2 = V.row(F(bestFaceIndex, 2));
//         return (v1 - v0).cross(v2 - v0).normalized();
//     }

//     return Eigen::Vector3d(0, 1, 0); // Valeur par défaut si problème
// }

int findFaceClosestToGround() {
    int bestFace = 0;
    double bestAlignment = -1.0;

    for (int i = 0; i < F.rows(); i++) {
        // Normale transformée dans l'espace monde
        Eigen::Vector3d normal = rotation * faceNormals.row(i).transpose();

        // Plus la normale est alignée avec -Y, plus cette face touche le sol
        double alignment = normal.dot(Eigen::Vector3d(0, -1, 0));

        if (alignment > bestAlignment) {
            bestAlignment = alignment;
            bestFace = i;
        }
    }
    return bestFace;
}

bool preDrawCallback(igl::opengl::glfw::Viewer &) {
    if (falling) {
        // Appliquer la gravité
        position[1] += velocity;
        velocity -= 0.005;  // Accélération gravitationnelle

        // Appliquer une légère rotation
        Eigen::AngleAxisd rotStep(0.05, Eigen::Vector3d::UnitX());
        rotation = rotStep.toRotationMatrix() * rotation;

        // Check if the dice has hit the ground
        if (position[1] <= floorPosition) {
            position[1] = floorPosition;
            falling = false;

            // Align the dice to the nearest face
            int bestFace = findFaceClosestToGround();
            Eigen::Vector3d normal = faceNormals.row(bestFace);
            // Eigen::Vector3d targetNormal(0, 1, 0);

            Eigen::Quaterniond quat = Eigen::Quaterniond::FromTwoVectors(normal, targetNormal);
            rotation = quat.toRotationMatrix();
        }

        updateTransform();
    }
    return false;
}







int main(int argc, char *argv[])
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    viewer.launch_init();

    ImGui_ImplGlfw_InitForOpenGL(viewer.window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // init(argc > 1 ? std::stoi(argv[1]) : 6);

    // viewer.callback_key_down = key_down_callback;
    // viewer.callback_pre_draw = preDrawCallback;

    // updateTransform();

    test();

    while (!glfwWindowShouldClose(viewer.window)) {
        viewer.draw();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwPollEvents();
        glfwSwapBuffers(viewer.window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
