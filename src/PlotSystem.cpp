#include "PlotSystem.hpp"
#include "imgui.h"
#include "implot.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <algorithm> // Per min_element i max_element

bool PlotSystem::loadCSV(const std::string& filepath) {
    std::cout << "hola soc jo" << std::endl;
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "No s'ha pogut obrir el fitxer CSV!" << std::endl;
        return false;
    }

    std::string line;
    char comma;
    std::getline(file, line); // Ignora l'encapçalament

    while (std::getline(file, line)) {
        std::cout << line << std::endl;
        std::stringstream ss(line);
        DataPoint point;
        ss >> point.time >> comma >> point.x >> comma >> point.y >> comma >> point.z;
        data.push_back(point);
    }

    file.close();
    return true;
}

void PlotSystem::startPlot() {
    std::cout << "Starting plot" << std::endl;
    isPlotting = true;
    elapsedTime = 0.0f;
    times.clear();
    zs.clear();
    lastIndex = 0;
    startTime = std::chrono::steady_clock::now();
}

void PlotSystem::updatePlot() {
    if (!isPlotting) return;
    std::cout << "Updating plot" << std::endl;
    // Calcula el temps transcorregut
    auto now = std::chrono::steady_clock::now();
    elapsedTime = std::chrono::duration<float>(now - startTime).count();

    // Continua des d'on es va deixar la última vegada
    for (int i = lastIndex; i < data.size(); ++i) {
        const auto& point = data[i];
        if (point.time <= elapsedTime) {
            times.push_back(point.time);
            zs.push_back(point.z);
            lastIndex = i + 1; // Actualitza l'índex
        } else {
            break;
        }
    }
}

void PlotSystem::renderPlot() {
    if (zs.empty()) return; // No renderitza si no hi ha dades
    std::cout<<"Rendering plot"<<std::endl;

    float z_min = *std::min_element(zs.begin(), zs.end());
    float z_max = *std::max_element(zs.begin(), zs.end());
    ImGui::Begin("Plot");

    if (ImPlot::BeginPlot("Real-Time Z Component")) {
        ImPlot::SetupAxisLimits(ImAxis_X1, 0, elapsedTime + 5, ImGuiCond_Always);    // escala horitzontal
        ImPlot::SetupAxisLimits(ImAxis_Y1, z_min - 10, z_max + 10, ImGuiCond_Always); // escala vertical

        // estil de línies i punts
        ImPlot::PushStyleVar(ImPlotStyleVar_LineWeight, 1.0f);   // Línies 
        ImPlot::PushStyleVar(ImPlotStyleVar_MarkerSize, 2.0f);   // Punts 
        ImPlot::PushStyleVar(ImPlotStyleVar_MarkerWeight, 0.5f); // Contorn punts


        ImPlot::PlotLine("Z (m)", times.data(), zs.data(), times.size());

        ImPlot::PopStyleVar(3);

        ImPlot::EndPlot();

    }
    ImGui::End();
}


