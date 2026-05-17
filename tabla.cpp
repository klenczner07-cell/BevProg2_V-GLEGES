#include "tabla.hpp"
using namespace genv;

Tabla::Tabla(Application* szulo, int x, int y, JatekMester* jm,
             std::function<void()> lepesutan,
             std::function<bool()> aiAktivE) :
    Widget(szulo, x, y,
           JatekMester::OSZLOPOK * CELL,
           JatekMester::SOROK * CELL),
    _jm(jm), _lepesutan(lepesutan), _aiAktivE(aiAktivE),
    _hovSor(-1), _hovOszlop(-1)
{}

void Tabla::draw() const {
    gout << move_to(_x, _y)
         << color(195, 160, 105)
         << box(_size_x, _size_y);

    for (int s = 0; s < JatekMester::SOROK; s++) {
        for (int o = 0; o < JatekMester::OSZLOPOK; o++) {
            int px = _x + o * CELL;
            int py = _y + s * CELL;

            bool gepKore = _aiAktivE() && _jm->getAktualisJatekos() == 2;
            bool kiemelt = (s == _hovSor && o == _hovOszlop
                            && _jm->getCella(s, o) == 0
                            && !_jm->vege()
                            && !gepKore);
            if (kiemelt) {
                gout << move_to(px + 1, py + 1)
                     << color(170, 200, 150)
                     << box(CELL - 1, CELL - 1);
            }

            gout << move_to(px, py)
                 << color(100, 70, 35)
                 << box(CELL, 1)
                 << move_to(px, py)
                 << box(1, CELL);

            int jel = _jm->getCella(s, o);
            if (jel == 1) {
                gout << move_to(px + 5, py + 5)
                     << color(15, 15, 15)
                     << box(CELL - 10, CELL - 10);
            } else if (jel == 2) {
                gout << move_to(px + 5, py + 5)
                     << color(245, 245, 245)
                     << box(CELL - 10, CELL - 10)
                     << move_to(px + 11, py + 11)
                     << color(195, 160, 105)
                     << box(CELL - 22, CELL - 22);
            }
        }
    }

    gout << move_to(_x + JatekMester::OSZLOPOK * CELL, _y)
         << color(100, 70, 35)
         << box(1, JatekMester::SOROK * CELL)
         << move_to(_x, _y + JatekMester::SOROK * CELL)
         << box(JatekMester::OSZLOPOK * CELL, 1);

    if (_jm->getNyertes() != 0) {
        const auto& nyVonal = _jm->getNyertesVonal();
        for (const auto& cella : nyVonal) {
            int px = _x + cella.second * CELL + 3;
            int py = _y + cella.first  * CELL + 3;
            int csz = CELL - 6;
            gout << color(255, 210, 0)
                 << move_to(px,         py)         << box(csz, 4)
                 << move_to(px,         py + csz - 4) << box(csz, 4)
                 << move_to(px,         py)         << box(4, csz)
                 << move_to(px + csz - 4, py)       << box(4, csz);
        }
    }
}

void Tabla::handle(event esem) {
    if (esem.type != ev_mouse)
        return;
    if (_jm->vege())
        return;

    bool gepKore = _aiAktivE() && _jm->getAktualisJatekos() == 2;
    if (gepKore)
        return;

    int o = (esem.pos_x - _x) / CELL;
    int s = (esem.pos_y - _y) / CELL;
    if (o < 0 || o >= JatekMester::OSZLOPOK || s < 0 || s >= JatekMester::SOROK)
        return;

    _hovSor = s;
    _hovOszlop = o;

    if (esem.button == btn_left) {
        bool sikeres = _jm->lepesKiserlet(s, o);
        if (sikeres)
            _lepesutan();
    }
}
