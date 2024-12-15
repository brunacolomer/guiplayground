#ifndef PLOTSYSTEM_HPP
#define PLOTSYSTEM_HPP

#include <vector>
#include <string>
#include <chrono>

struct DataPoint {
    float time;
    float x, y, z;
};

class PlotSystem {
public:

    bool loadCSV(const std::string& filepath); // Carrega el CSV
    void startPlot();                          // Inicia la gràfica
    void updatePlot();                         // Actualitza la gràfica a temps real
    void renderPlot();                         // Renderitza la gràfica

private:
    std::vector<DataPoint> data;               // Dades del CSV
    std::vector<float> times, xs, ys, zs;      // Dades a mostrar
    bool isPlotting = false;                   // Estat de la gràfica
    float elapsedTime = 0.0f;                  // Temps transcorregut
    std::chrono::steady_clock::time_point startTime; // Temps d'inici
    int lastIndex = 0;                         // Últim índex processat
};

#endif
