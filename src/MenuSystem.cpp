#include "imgui.h"
#include "MenuSystem.hpp"
#include <stdio.h>

void MenuSystem::render() {
    // Comença la barra de menú principal
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Fitxer")) {
            if (ImGui::MenuItem("Nou projecte", "Ctrl+N")) {
                printf("Nou projecte creat!\n");
            }
            if (ImGui::MenuItem("Obrir projecte", "Ctrl+O")) {
                printf("Projecte obert!\n");
            }
            if (ImGui::MenuItem("Guardar projecte", "Ctrl+S")) {
                printf("Projecte guardat!\n");
            }
            if (ImGui::MenuItem("Sortir", "Ctrl+Q")) {
                printf("Sortint...\n");
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Eines")) {
            if (ImGui::MenuItem("Opcions")) {
                printf("Obrint opcions...\n");
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Ajuda")) {
            if (ImGui::MenuItem("Documentació")) {
                printf("Obrint documentació...\n");
            }
            if (ImGui::MenuItem("Sobre...")) {
                printf("Mostrant informació sobre l'aplicació...\n");
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar(); // Finalitza la barra de menú principal
    }
}
