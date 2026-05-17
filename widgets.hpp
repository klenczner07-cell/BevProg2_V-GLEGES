#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include "graphics.hpp"
#include "application.hpp"

class Widget {
protected:
    Application* _parent;
    int _x, _y, _size_x, _size_y;
    bool _lathato;
public:
    Widget(Application* szulo, int x, int y, int sx, int sy);
    virtual ~Widget();
    virtual bool is_selected(int egx, int egy);
    virtual void draw() const = 0;
    virtual void handle(genv::event esem) = 0;

    void setLathato(bool l) { _lathato = l; }
    bool isLathato() const  { return _lathato; }
};

#endif
