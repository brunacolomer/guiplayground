#include "MenuSystem.hpp"
#include "PlotSystem.hpp"
#include <cstdio>
#include "imgui.h"
#include "nfd.h" // Llibreria Native File Dialog (cal afegir-la al projecte)

MenuSystem::MenuSystem(PlotSystem* plotSystem) : m_plotSystem(plotSystem) {}

void MenuSystem::render() {
    // Comença la barra de menú principal
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Fitxer")) {
            if (ImGui::MenuItem("Obrir fitxer CSV...", "Ctrl+O")) {
                openCSVFile(); // Funció per obrir el quadre de diàleg i carregar el fitxer
            }
            if (ImGui::MenuItem("Sortir", "Ctrl+Q")) {
                printf("Sortint...\n");
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar(); // Finalitza la barra de menú principal
    }
}

void MenuSystem::openCSVFile() {
    nfdchar_t* outPath = nullptr;
    nfdresult_t result = NFD_OpenDialog("csv", nullptr, &outPath);

    if (result == NFD_OKAY) {
        printf("Fitxer seleccionat: %s\n", outPath);
        if (m_plotSystem->loadCSV(outPath)) {
            printf("Fitxer CSV carregat correctament!\n");
        } else {
            printf("Error en carregar el fitxer CSV!\n");
        }
        free(outPath); // Allibera la memòria del camí retornat
    } else if (result == NFD_CANCEL) {
        printf("Selecció de fitxer cancel·lada.\n");
    } else {
        printf("Error al seleccionar el fitxer: %s\n", NFD_GetError());
    }
}
