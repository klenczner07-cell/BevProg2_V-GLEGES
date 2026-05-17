#include "felirat.hpp"
using namespace genv;

Felirat::Felirat(Application* szulo, int x, int y, int sx, int sy, std::string szoveg) :
    Widget(szulo, x, y, sx, sy), _szoveg(szoveg)
{}

void Felirat::draw() const {
    gout.load_font("LiberationSans-Regular.ttf", 17);
    gout << move_to(_x, _y)
         << color(40, 40, 40)
         << box(_size_x, _size_y)
         << move_to(_x + 1, _y + 1)
         << color(62, 62, 62)
         << box(_size_x - 2, _size_y - 2)
         << move_to(_x + 9, _y + 14)
         << color(235, 235, 235)
         << text(_szoveg);
}

void Felirat::handle(event esem) {}

void Felirat::frissit(std::string ujSzoveg) {
    _szoveg = ujSzoveg;
}
