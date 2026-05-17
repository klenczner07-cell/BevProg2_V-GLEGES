#include "jatekvege.hpp"
using namespace genv;

JatekVege::JatekVege(Application* szulo, int ablakSzel, int ablakMag,
                     std::function<void()> ujJatekFn,
                     std::function<void()> fomenFn) :
    Widget(szulo, 0, 0, ablakSzel, ablakMag),
    _ujJatekFn(ujJatekFn), _fomenFn(fomenFn),
    _eredmeny(""), _er(255), _eg(255), _eb(255)
{
    _psx = 440;
    _psy = 250;
    _px  = ablakSzel / 2 - _psx / 2;
    _py  = ablakMag  / 2 - _psy / 2;
}

bool JatekVege::zonaHit(int ex, int ey, int x, int y, int sx, int sy) const {
    return ex >= x && ex < x + sx && ey >= y && ey < y + sy;
}

void JatekVege::beallitEredmeny(std::string szoveg, int r, int g, int b) {
    _eredmeny = szoveg;
    _er = r; _eg = g; _eb = b;
}

void JatekVege::draw() const {
    gout << move_to(0, 0)
         << color(0, 0, 0)
         << box(_size_x, _size_y);

    gout << move_to(_px, _py)
         << color(35, 35, 35)
         << box(_psx, _psy)
         << move_to(_px + 3, _py + 3)
         << color(58, 58, 58)
         << box(_psx - 6, _psy - 6);

    gout << move_to(_px + 12, _py + 18)
         << color(120, 120, 120)
         << box(_psx - 24, 2);

    gout.load_font("LiberationSans-Regular.ttf", 15);
    // "- Játék vége -" ~120px széles, a párbeszédablak közepére igazítva
    gout << move_to(_px + (_psx - 120) / 2, _py + 34)
         << color(145, 145, 145)
         << text("- J\xc3\xa1t\xc3\xa9k v\xc3\xa9ge -");

    gout.load_font("LiberationSans-Regular.ttf", 34);
    // Az eredmény szöveg vízszintesen középre a párbeszédablakban
    // Leghosszabb szöveg "Fehér nyert!" ~220px → bal margó ~110px
    gout << move_to(_px + 50, _py + 100)
         << color(_er, _eg, _eb)
         << text(_eredmeny);

    int g1x = _px + 20,  gy = _py + 172, gsx = 165, gsy = 54;
    int g2x = _px + 255;

    gout << move_to(g1x, gy)
         << color(30, 80, 30)
         << box(gsx, gsy)
         << move_to(g1x + 2, gy + 2)
         << color(50, 130, 50)
         << box(gsx - 4, gsy - 4);
    gout.load_font("LiberationSans-Regular.ttf", 18);
    gout << move_to(g1x + 16, gy + 19)
         << color(220, 255, 220)
         << text("\xc3\x9aj j\xc3\xa1t\xc3\xa9k");

    gout << move_to(g2x, gy)
         << color(85, 30, 30)
         << box(gsx, gsy)
         << move_to(g2x + 2, gy + 2)
         << color(138, 50, 50)
         << box(gsx - 4, gsy - 4);
    gout << move_to(g2x + 16, gy + 19)
         << color(255, 215, 215)
         << text("F\xc5\x91men\xc3\xbc");
}

void JatekVege::handle(event esem) {
    if (!_lathato) return;
    if (esem.type != ev_mouse || esem.button != btn_left)
        return;

    int ex = esem.pos_x, ey = esem.pos_y;
    int g1x = _px + 20,  gy = _py + 172, gsx = 165, gsy = 54;
    int g2x = _px + 255;

    if (zonaHit(ex, ey, g1x, gy, gsx, gsy)) {
        _lathato = false;
        _ujJatekFn();
    } else if (zonaHit(ex, ey, g2x, gy, gsx, gsy)) {
        _lathato = false;
        _fomenFn();
    }
}
