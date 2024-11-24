#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <unordered_map>
#include <iostream>

class GUIManager {
public:
    GUIManager(GLFWwindow* window);
    ~GUIManager();

    void init();   // Inicialitza ImGui
    void shutdown(); // Finalitza ImGui

    void beginFrame(); // Comença un frame d'ImGui
    void endFrame();   // Renderitza i acaba el frame

private:
    GLFWwindow* m_window;
};

#endif // GUIMANAGER_HPP