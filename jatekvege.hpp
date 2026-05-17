#ifndef JATEKVEGE_HPP
#define JATEKVEGE_HPP

#include <functional>
#include <string>
#include "widgets.hpp"

class JatekVege : public Widget {
public:
    JatekVege(Application* szulo, int ablakSzel, int ablakMag,
              std::function<void()> ujJatekFn,
              std::function<void()> fomenFn);
    void draw() const override;
    void handle(genv::event esem) override;
    void beallitEredmeny(std::string szoveg, int r, int g, int b);
private:
    bool zonaHit(int ex, int ey, int x, int y, int sx, int sy) const;

    std::function<void()> _ujJatekFn;
    std::function<void()> _fomenFn;
    std::string _eredmeny;
    int _er, _eg, _eb;

    int _px, _py, _psx, _psy;
};

#endif
