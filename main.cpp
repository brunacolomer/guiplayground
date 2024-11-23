#include "glad/glad.h"   // GLAD ha d'anar primer
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "implot.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <vector>
#include <iostream>

// Variables globals per al FBO
unsigned int fbo, fboTexture, rbo;
const int fboWidth = 800;
const int fboHeight = 600;

// Vectors per emmagatzemar el moviment del ratolí
std::vector<float> mouseXData;
std::vector<float> mouseYData;

// Configuració del Framebuffer Object (FBO)
void setupFBO() {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &fboTexture);
    glBindTexture(GL_TEXTURE_2D, fboTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fboWidth, fboHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTexture, 0);

    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, fboWidth, fboHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "FBO is not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// Actualitza les dades del moviment del ratolí
void updateMouseData(float mouseX, float mouseY) {
    const size_t bufferSize = 100; // Mida màxima del buffer
    if (mouseXData.size() >= bufferSize) {
        mouseXData.erase(mouseXData.begin());
        mouseYData.erase(mouseYData.begin());
    }
    mouseXData.push_back(mouseX);
    mouseYData.push_back(mouseY);
}

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui + ImPlot Example", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Inicialitza Dear ImGui i ImPlot
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    setupFBO();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Captura la posició del ratolí dins la finestra
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        if (mouseX >= 0 && mouseX < 800 && mouseY >= 0 && mouseY < 600) {
            updateMouseData(static_cast<float>(mouseX), static_cast<float>(mouseY));
        }

        // Renderitza al FBO
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glViewport(0, 0, fboWidth, fboHeight);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.5f, -0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.0f, 0.5f);
        glEnd();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Comença un nou frame de Dear ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Finestra OpenGL
        ImGui::Begin("OpenGL Window");
        ImGui::Text("This is an embedded OpenGL window:");
        ImGui::Image((ImTextureID)(uintptr_t)fboTexture, ImVec2(fboWidth, fboHeight));
        ImGui::End();

        // Panell de control amb gràfica de moviment del ratolí
        ImGui::Begin("Control Panel");
        ImGui::Text("Mouse movement in OpenGL window:");

        if (ImPlot::BeginPlot("Mouse Movement", ImVec2(-1, 200))) {
            ImPlot::SetupAxes("Frame", "Position", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
            ImPlot::PlotLine("Mouse X", mouseXData.data(), mouseXData.size());
            ImPlot::PlotLine("Mouse Y", mouseYData.data(), mouseYData.size());
            ImPlot::EndPlot();
        }
        ImGui::End();

        // Renderitza ImGui
        ImGui::Render();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Finalitza ImGui i ImPlot
    ImPlot::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
