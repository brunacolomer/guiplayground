#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include "implot.h"
#include "GUIManager.hpp"
#include "MenuSystem.hpp"
#include "PlotSystem.hpp"

int main() {
    // Inicialitza GLFW
    if (!glfwInit()) {
        fprintf(stderr, "Error: No s'ha pogut inicialitzar GLFW\n");
        return -1;
    }

    // Configura la finestra GLFW amb OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crea una finestra GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "Simple GLFW + ImGui Example", nullptr, nullptr);
    if (!window) {
        fprintf(stderr, "Error: No s'ha pogut crear la finestra GLFW\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Habilita vsync

    // Inicialitza el sistema de gestió GUI
    GUIManager guiManager(window);
    ImPlot::CreateContext(); // ImPlot no es gestiona per GUIManager
    PlotSystem plotSystem;

    MenuSystem menu(&plotSystem);

    // Carrega el fitxer CSV
    if (!plotSystem.loadCSV("../data/Jano.csv")) {
        fprintf(stderr, "Error: No s'ha pogut carregar el fitxer CSV\n");
    }

    // Bucle principal
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); // Processa esdeveniments
        guiManager.beginFrame();

        // Dibuixa el menú
        ImGui::Begin("Menu");
        if (ImGui::Button("Inicia la gràfica")) {
            plotSystem.startPlot();
        }
        ImGui::End();

        // Actualitza i renderitza gràfica
        plotSystem.updatePlot();
        plotSystem.renderPlot();
        menu.render();

        // Esborra la pantalla
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        guiManager.endFrame(); // Finalitza el frame
        glfwSwapBuffers(window); // Intercanvia buffers
    }

    // Allibera recursos
    ImPlot::DestroyContext(); // ImPlot necessita destruir-se manualment
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
