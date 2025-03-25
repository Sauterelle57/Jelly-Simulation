#include <igl/opengl/glfw/Viewer.h>
#include <igl/readOBJ.h>
#include <iostream>
#include <imgui.h>
#include <GLFW/glfw3.h>

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
    viewer.data(ground_layer).set_colors(Eigen::RowVector3d(0.5, 0.5, 0.5)); // Gris
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

    // Compute face normals
    faceNormals.resize(F.rows(), 3);
    for (int i = 0; i < F.rows(); ++i) {
        Eigen::Vector3d v0 = V.row(F(i, 0));
        Eigen::Vector3d v1 = V.row(F(i, 1));
        Eigen::Vector3d v2 = V.row(F(i, 2));
        faceNormals.row(i) = (v1 - v0).cross(v2 - v0).normalized();
    }

    create_ground();
}

void updateTransform() {
    Eigen::MatrixXd transformedV = V * rotation.transpose();
    for (int i = 0; i < V.rows(); ++i) {
        transformedV.row(i) += position.transpose();
    }
    viewer.data(1).set_vertices(transformedV);
    viewer.data(1).compute_normals();
}

bool key_down_callback(igl::opengl::glfw::Viewer &viewer, unsigned char key, int modifier)
{
    switch (key) {
        case 'A': rotation = Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitY()) * rotation; break;//left
        case 'D': rotation = Eigen::AngleAxisd(-0.1, Eigen::Vector3d::UnitY()) * rotation; break;//right
        case 'S': rotation = Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitX()) * rotation; break;//down
        case 'W': rotation = Eigen::AngleAxisd(-0.1, Eigen::Vector3d::UnitX()) * rotation; break;//up
        case 'Q': rotation = Eigen::AngleAxisd(0.1, Eigen::Vector3d::UnitZ()) * rotation; break;//anti-horaire
        case 'E': rotation = Eigen::AngleAxisd(-0.1, Eigen::Vector3d::UnitZ()) * rotation; break;//horaire
        case 1: std::cout << "Dé lâché !" << std::endl; falling = true; break;
        default: return false;
    }
    updateTransform();

    return true;
}

Eigen::Vector3d findNearestFaceDynamic() {
    Eigen::Vector3d upVector = rotation * Eigen::Vector3d(0, 1, 0); // Normale actuelle du haut

    int bestFaceIndex = -1;
    double bestDot = -1.0;

    // Vérifier toutes les faces
    for (int i = 0; i < F.rows(); i++) {
        Eigen::Vector3d v0 = V.row(F(i, 0));
        Eigen::Vector3d v1 = V.row(F(i, 1));
        Eigen::Vector3d v2 = V.row(F(i, 2));

        // Calcul de la normale de la face
        Eigen::Vector3d normal = (v1 - v0).cross(v2 - v0).normalized();

        // Trouver la face la plus "vers le haut"
        double dot = upVector.dot(normal);
        if (dot > bestDot) {
            bestDot = dot;
            bestFaceIndex = i;
        }
    }

    // Retourner la normale de la meilleure face
    if (bestFaceIndex != -1) {
        Eigen::Vector3d v0 = V.row(F(bestFaceIndex, 0));
        Eigen::Vector3d v1 = V.row(F(bestFaceIndex, 1));
        Eigen::Vector3d v2 = V.row(F(bestFaceIndex, 2));
        return (v1 - v0).cross(v2 - v0).normalized();
    }

    return Eigen::Vector3d(0, 1, 0); // Valeur par défaut si problème
}

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
        velocity -= 0.001; // Gravité

        // Trouver la face qui devrait toucher le sol
        int targetFace = findFaceClosestToGround();
        Eigen::Vector3d targetNormal = faceNormals.row(targetFace).transpose();

        // Définir la rotation cible
        Eigen::Quaterniond targetRotation = Eigen::Quaterniond::FromTwoVectors(rotation * targetNormal, Eigen::Vector3d(0, -1, 0));

        // Interpolation progressive vers la bonne orientation
        Eigen::Quaterniond currentRotation(rotation);
        rotation = currentRotation.slerp(0.1, targetRotation).toRotationMatrix();

        // Ajouter une rotation aléatoire pendant la chute
        Eigen::Quaterniond randomRotation = Eigen::AngleAxisd((rand() % 100 - 50) / 2000.0, Eigen::Vector3d::UnitX()) *
                                            Eigen::AngleAxisd((rand() % 100 - 50) / 2000.0, Eigen::Vector3d::UnitZ());
        rotation = randomRotation.toRotationMatrix() * rotation;

        // Vérifier si le dé touche le sol
        if (position[1] < 0) {
            position[1] = 0;
            velocity *= -0.3; // Rebond léger

            if (std::abs(velocity) < 0.002) {
                falling = false;
                velocity = 0;
                std::cout << "Dé arrêté sur la face " << targetFace << " !" << std::endl;

                // Finaliser la rotation pour qu'elle soit parfaitement alignée
                rotation = targetRotation.toRotationMatrix();
            }
        }

        updateTransform();
    } else {
        updateTransform();
    }
    return false;
}


bool preDrawCallback1(igl::opengl::glfw::Viewer &) {
    if (falling) {
        // Appliquer la gravité
        position[1] += velocity;
        velocity -= 0.001; // Gravité

        // Déterminer la face cible dynamiquement
        Eigen::Vector3d targetFace = findNearestFaceDynamic();

        // Créer une rotation qui aligne progressivement la face cible avec -Y
        Eigen::Quaterniond targetRotation = Eigen::Quaterniond::FromTwoVectors(rotation * Eigen::Vector3d(0, 1, 0), targetFace);

        // Interpolation progressive vers la rotation cible
        Eigen::Quaterniond currentRotation(rotation);
        rotation = currentRotation.slerp(0.1, targetRotation).toRotationMatrix(); // 10% d'ajustement par frame

        // Ajouter un peu de rotation aléatoire pendant la chute
        double randomRotX = ((rand() % 100) - 50) / 2000.0;
        double randomRotZ = ((rand() % 100) - 50) / 2000.0;
        Eigen::Quaterniond randomRotation = Eigen::AngleAxisd(randomRotX, Eigen::Vector3d::UnitX()) *
                                            Eigen::AngleAxisd(randomRotZ, Eigen::Vector3d::UnitZ());
        rotation = randomRotation.toRotationMatrix() * rotation;

        // Vérifier si le dé touche le sol
        if (position[1] < -1) {
            position[1] = -1;
            velocity *= -0.3; // Rebond léger

            if (std::abs(velocity) < 0.002) {
                falling = false;
                velocity = 0;
                std::cout << "Dé arrêté sur une face !" << std::endl;

                // Finaliser la rotation vers la face correcte une fois posé
                rotation = targetRotation.toRotationMatrix();
            }
        }

        updateTransform();
    } else {
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

    init(argc > 1 ? std::stoi(argv[1]) : 6);

    viewer.callback_key_down = key_down_callback;
    viewer.callback_pre_draw = preDrawCallback;

    updateTransform();

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
