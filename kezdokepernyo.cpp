#include "kezdokepernyo.hpp"
using namespace genv;

// Az ablak 950x600. Minden elemet ehhez igazítunk, vízszintesen középre.
// Tábla jobb széle ~594px → a főmenü az egész 950px-es felületet használja.

KezdoKepernyo::KezdoKepernyo(Application* szulo, int ablakSzel, int ablakMag,
                              std::function<void(bool)> inditCallback) :
    Widget(szulo, 0, 0, ablakSzel, ablakMag),
    _inditCallback(inditCallback), _aiMod(true)
{}

bool KezdoKepernyo::zonaHit(int ex, int ey, int x, int y, int sx, int sy) const {
    return ex >= x && ex < x + sx && ey >= y && ey < y + sy;
}

void KezdoKepernyo::rajzolGomb(int x, int y, int sx, int sy,
                                std::string szoveg, bool kiemelve) const {
    gout << move_to(x, y)
         << color(kiemelve ? 50 : 30, kiemelve ? 110 : 75, kiemelve ? 50 : 30)
         << box(sx, sy)
         << move_to(x + 2, y + 2)
         << color(kiemelve ? 75 : 48, kiemelve ? 155 : 108, kiemelve ? 75 : 48)
         << box(sx - 4, sy - 4);
    gout.load_font("LiberationSans-Regular.ttf", 18);
    gout << move_to(x + 16, y + 17)
         << color(kiemelve ? 255 : 190, 255, kiemelve ? 255 : 190)
         << text(szoveg);
}

void KezdoKepernyo::draw() const {
    // ── Háttér ──────────────────────────────────────────────────────────────
    gout << move_to(0, 0)
         << color(16, 55, 28)
         << box(_size_x, _size_y);

    // Rácsminta
    gout << color(20, 65, 33);
    for (int i = 0; i < _size_x; i += 38)
        gout << move_to(i, 0) << box(1, _size_y);
    for (int i = 0; i < _size_y; i += 38)
        gout << move_to(0, i) << box(_size_x, 1);

    // ── Cím doboz  (középre: 950/2 = 475, doboz 480px széles → x=235) ─────
    const int CIM_X = 235, CIM_Y = 65, CIM_SX = 480, CIM_SY = 105;
    gout << move_to(CIM_X, CIM_Y)
         << color(14, 50, 24)
         << box(CIM_SX, CIM_SY)
         << move_to(CIM_X + 2, CIM_Y + 2)
         << color(22, 72, 36)
         << box(CIM_SX - 4, CIM_SY - 4);

    // ÁMŐBA felirat – font 60px, ~230px széles, középre a dobozban
    gout.load_font("LiberationSans-Regular.ttf", 60);
    gout << move_to(CIM_X + (CIM_SX - 230) / 2, CIM_Y + 8)
         << color(215, 172, 60)
         << text("AM\xc5\x90" "BA");   // AMŐBA (Ő = C5 90)

    // ── Alcím szöveg ────────────────────────────────────────────────────────
    gout.load_font("LiberationSans-Regular.ttf", 17);
    // "5 egyforma korongot kell egymás mellé kirakni" ~430px, középre → x≈260
    gout << move_to(260, 142)
         << color(150, 210, 160)
         << text("5 egyforma korongot kell egym\xc3\xa1s mell\xc3\xa9 kirakni");

    // ── Elválasztó vonal (175-tól 600px széles, középszimmetrikus) ──────────
    gout << move_to(175, 192)
         << color(55, 110, 65)
         << box(600, 2);

    // ── "Válassz játékmódot:" felirat – középre ──────────────────────────────
    gout.load_font("LiberationSans-Regular.ttf", 16);
    // ~170px széles szöveg → x = 475 - 85 = 390
    gout << move_to(392, 212)
         << color(170, 210, 175)
         << text("V\xc3\xa1lassz j\xc3\xa1t\xc3\xa9km\xc3\xb3" "dot:");

    // ── Módválasztó gombok (255px szélesek, 30px rés, összesen 540px → x1=205, x2=490) ─
    const int G_Y = 238, G_SX = 255, G_SY = 54;
    const int G1X = 205, G2X = 490;
    rajzolGomb(G1X, G_Y, G_SX, G_SY, "Ember vs G\xc3\xa9p", _aiMod);
    rajzolGomb(G2X, G_Y, G_SX, G_SY, "K\xc3\xa9t Ember",    !_aiMod);

    // ── Indítás gomb (320px széles, középre → x=315) ─────────────────────────
    const int IND_X = 315, IND_Y = 335, IND_SX = 320, IND_SY = 72;
    gout << move_to(IND_X, IND_Y)
         << color(130, 88, 14)
         << box(IND_SX, IND_SY)
         << move_to(IND_X + 3, IND_Y + 3)
         << color(195, 140, 25)
         << box(IND_SX - 6, IND_SY - 6);
    gout.load_font("LiberationSans-Regular.ttf", 26);
    // "JÁTÉK INDÍTÁSA" ~230px → középre a gombon belül
    gout << move_to(IND_X + (IND_SX - 228) / 2, IND_Y + 22)
         << color(28, 18, 4)
         << text("J\xc3\x81T\xc3\x89K IND\xc3\x8dT\xc3\x81SA");

    // ── Infósor alul ─────────────────────────────────────────────────────────
    gout.load_font("LiberationSans-Regular.ttf", 13);
    gout << move_to(10, _size_y - 18)
         << color(55, 100, 60)
         << text("Am\xc5\x91" "ba  |  BevProg2 beadand\xc3\xb3  |  Nyom\xc3\xb3j ESC-et a kil\xc3\xa9p\xc3\xa9shez");
}

void KezdoKepernyo::handle(event esem) {
    if (esem.type != ev_mouse || esem.button != btn_left)
        return;

    int ex = esem.pos_x, ey = esem.pos_y;

    const int G_Y = 238, G_SX = 255, G_SY = 54;
    const int G1X = 205, G2X = 490;
    const int IND_X = 315, IND_Y = 335, IND_SX = 320, IND_SY = 72;

    if (zonaHit(ex, ey, G1X, G_Y, G_SX, G_SY))
        _aiMod = true;
    else if (zonaHit(ex, ey, G2X, G_Y, G_SX, G_SY))
        _aiMod = false;
    else if (zonaHit(ex, ey, IND_X, IND_Y, IND_SX, IND_SY))
        _inditCallback(_aiMod);
}
