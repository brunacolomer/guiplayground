#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h> // Inclou GLFW
#include <cstdio>
#include "GUIManager.hpp"
#include "MenuSystem.hpp"


int main() {
    // Inicialitza GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Configura la finestra GLFW amb OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crea una finestra GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "Simple GLFW + ImGui Example", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Inicialitza ImGui
    GUIManager guiManager(window);
    MenuSystem menu;
   
    // Bucle principal
    while (!glfwWindowShouldClose(window)) {
        // Processa esdeveniments de GLFW
        glfwPollEvents();
        guiManager.beginFrame();
        // Contingut d'ImGui
        ImGui::Begin("Hello, ImGui!"); // Comença una finestra
        ImGui::Text("Això és un exemple bàsic."); // Text simple
        if (ImGui::Button("Click me!")) { // Botó interactiu
            printf("Botó clicat!\n");
        }
        ImGui::End(); // Acaba la finestra
        menu.render();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        guiManager.endFrame();
        glfwSwapBuffers(window);
    }

    guiManager.shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
