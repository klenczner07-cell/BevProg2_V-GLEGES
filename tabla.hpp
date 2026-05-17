#ifndef TABLA_HPP
#define TABLA_HPP

#include <functional>
#include "widgets.hpp"
#include "jatekmaster.hpp"

class Tabla : public Widget {
public:
    Tabla(Application* szulo, int x, int y, JatekMester* jm,
          std::function<void()> lepesutan,
          std::function<bool()> aiAktivE);
    void draw() const override;
    void handle(genv::event esem) override;
private:
    static const int CELL = 38;
    JatekMester* _jm;
    std::function<void()> _lepesutan;
    std::function<bool()> _aiAktivE;
    int _hovSor;
    int _hovOszlop;
};

#endif
