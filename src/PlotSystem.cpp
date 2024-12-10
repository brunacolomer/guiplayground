#include "PlotSystem.hpp"
#include "imgui.h"
#include "implot.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <algorithm> // Per min_element i max_element

void PlotSystem::loadCSV(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "No s'ha pogut obrir el fitxer CSV!" << std::endl;
        return;
    }

    std::string line;
    char comma;
    std::getline(file, line); // Ignora l'encapçalament

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        DataPoint point;
        ss >> point.time >> comma >> point.x >> comma >> point.y >> comma >> point.z;
        data.push_back(point);
    }

    file.close();
}

void PlotSystem::startPlot() {
    isPlotting = true;
    elapsedTime = 0.0f;
    times.clear();
    zs.clear();
    startTime = std::chrono::steady_clock::now();
}

void PlotSystem::updatePlot() {
    if (!isPlotting) return;

    // Calcula el temps transcorregut
    auto now = std::chrono::steady_clock::now();
    elapsedTime = std::chrono::duration<float>(now - startTime).count();

    for (const auto& point : data) {
        if (point.time <= elapsedTime) {
            times.push_back(point.time);
            zs.push_back(point.z);
        } else {
            break;
        }
    }
}

void PlotSystem::renderPlot() {
    if (zs.empty()) return; // No renderitza si no hi ha dades

    // Calcula el mínim i màxim de la component 'z'
    float z_min = *std::min_element(zs.begin(), zs.end());
    float z_max = *std::max_element(zs.begin(), zs.end());

    // Configura el gràfic amb escales ajustades
    if (ImPlot::BeginPlot("Real-Time Z Component")) {
        ImPlot::SetupAxisLimits(ImAxis_X1, 0, elapsedTime + 5, ImGuiCond_Always);    // Ajusta escala horitzontal
        ImPlot::SetupAxisLimits(ImAxis_Y1, z_min - 10, z_max + 10, ImGuiCond_Always); // Ajusta escala vertical

        ImPlot::PlotScatter("Z (m)", times.data(), zs.data(), times.size()); // Mostra punts
        ImPlot::EndPlot();
    }
}

