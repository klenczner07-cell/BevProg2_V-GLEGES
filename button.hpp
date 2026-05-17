#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>
#include <string>
#include "widgets.hpp"

class Button : public Widget {
public:
    Button(Application* szulo, int x, int y, int sx, int sy,
           std::string felirat, std::function<void()> fn);
    void draw() const override;
    void handle(genv::event esem) override;
    void kattint();
    void cimkecsere(std::string ujFelirat);
protected:
    std::string _felirat;
    std::function<void()> _fn;
};

#endif
