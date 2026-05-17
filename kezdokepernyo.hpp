#ifndef KEZDOKEPERNYO_HPP
#define KEZDOKEPERNYO_HPP

#include <functional>
#include <string>
#include "widgets.hpp"

class KezdoKepernyo : public Widget {
public:
    KezdoKepernyo(Application* szulo, int ablakSzel, int ablakMag,
                  std::function<void(bool aiAktiv)> inditCallback);
    void draw() const override;
    void handle(genv::event esem) override;
private:
    void rajzolGomb(int x, int y, int sx, int sy,
                    std::string szoveg, bool kiemelve) const;
    bool zonaHit(int ex, int ey, int x, int y, int sx, int sy) const;

    std::function<void(bool)> _inditCallback;
    bool _aiMod;
};

#endif
