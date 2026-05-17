#include "application.hpp"
#include "widgets.hpp"
#include "graphics.hpp"
#include <SDL2/SDL.h>

using namespace genv;

Application::Application(int ablakSzel, int ablakMag) {
    gout.open(ablakSzel, ablakMag);
}

Application::~Application() {
    for (Widget* w : widgets)
        delete w;
}

void Application::register_widget(Widget* w) {
    widgets.push_back(w);
}

void Application::ujrarajzol() {
    for (Widget* w : widgets)
        if (w->isLathato()) w->draw();
    gout << refresh;
}

void Application::varakozas(int ms) {
    SDL_Delay(ms);
}

void Application::event_loop() {
    event esem;

    ujrarajzol();

    while (gin >> esem && esem.keycode != key_escape) {
        std::vector<Widget*> pillanatnyiLathatok;
        for (Widget* w : widgets)
            if (w->isLathato()) pillanatnyiLathatok.push_back(w);

        for (Widget* w : pillanatnyiLathatok)
            w->handle(esem);

        ujrarajzol();
    }
}
