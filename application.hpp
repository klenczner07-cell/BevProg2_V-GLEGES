#ifndef APPLICATION_HPP
#define APPLICATION_HPP

class Widget;
#include <vector>

class Application {
public:
    Application(int ablakSzel, int ablakMag);
    virtual ~Application();
    void event_loop();
    void register_widget(Widget* w);
    void ujrarajzol();
    void varakozas(int ms);
protected:
    std::vector<Widget*> widgets;
};

#endif
