#include "button.hpp"
using namespace genv;

Button::Button(Application* szulo, int x, int y, int sx, int sy,
               std::string felirat, std::function<void()> fn) :
    Widget(szulo, x, y, sx, sy),
    _felirat(felirat), _fn(fn)
{}

void Button::draw() const {
    gout.load_font("LiberationSans-Regular.ttf", 18);
    gout << move_to(_x, _y)
         << color(90, 90, 90)
         << box(_size_x, _size_y)
         << move_to(_x + 2, _y + 2)
         << color(205, 205, 205)
         << box(_size_x - 4, _size_y - 4)
         << move_to(_x + 11, _y + 14)
         << color(20, 20, 20)
         << text(_felirat);
}

void Button::handle(event esem) {
    if (esem.type == ev_mouse && esem.button == btn_left
            && is_selected(esem.pos_x, esem.pos_y))
        kattint();
}

void Button::kattint() {
    _fn();
}

void Button::cimkecsere(std::string ujFelirat) {
    _felirat = ujFelirat;
}
