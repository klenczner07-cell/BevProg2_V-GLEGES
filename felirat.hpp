#ifndef FELIRAT_HPP
#define FELIRAT_HPP

#include <string>
#include "widgets.hpp"

class Felirat : public Widget {
public:
    Felirat(Application* szulo, int x, int y, int sx, int sy, std::string szoveg);
    void draw() const override;
    void handle(genv::event esem) override;
    void frissit(std::string ujSzoveg);
private:
    std::string _szoveg;
};

#endif
