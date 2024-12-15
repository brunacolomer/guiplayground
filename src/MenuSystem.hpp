#ifndef MENUSYSTEM_HPP
#define MENUSYSTEM_HPP

#include <string>
class PlotSystem; // Forward declaration

class MenuSystem {
public:
    MenuSystem(PlotSystem* plotSystem);
    void render();
private:
    void openCSVFile();
    PlotSystem* m_plotSystem; // Referència a PlotSystem per comunicar-se
};

#endif // MENUSYSTEM_HPP
