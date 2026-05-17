#include "application.hpp"
#include "button.hpp"
#include "felirat.hpp"
#include "tabla.hpp"
#include "jatekmaster.hpp"
#include "kezdokepernyo.hpp"
#include "jatekvege.hpp"
#include <string>

static const int ABLAK_SZEL = 950;
static const int ABLAK_MAG  = 600;

class AmobaApp : public Application {
public:
    AmobaApp() : Application(ABLAK_SZEL, ABLAK_MAG), _jm(), _aiBekapcsolva(true) {
        _allapotSor = new Felirat(this, 598, 12,  340, 44, "");
        _aiJelzo    = new Felirat(this, 598, 66,  340, 44, "");
        _tabla      = new Tabla(this, 12, 12, &_jm,
                                [this]() { lepesUtanTeendo(); },
                                [this]() { return _aiBekapcsolva; });
        _resetGomb  = new Button(this, 598, 120, 340, 42,
                                 "\xc3\x9aj j\xc3\xa1t\xc3\xa9k", [this]() {
            _jm.reset();
            _jatekVege->setLathato(false);
            allapotFrissit();
        });
        _aiGomb     = new Button(this, 598, 172, 340, 42,
                                 "G\xc3\xa9p: BE", [this]() {
            _aiBekapcsolva = !_aiBekapcsolva;
            _aiGomb->cimkecsere(_aiBekapcsolva ? "G\xc3\xa9p: BE" : "G\xc3\xa9p: KI");
            // Ha most kapcsoltuk BE a gepet es epp a gep kore van,
            // azonnal leptetjuk – kulonben a jatek befagyott allapotban maradna
            if (_aiBekapcsolva && !_jm.vege() && _jm.getAktualisJatekos() == 2) {
                auto [as, ao] = _jm.aiLepes(2);
                _jm.lepesKiserlet(as, ao);
            }
            allapotFrissit();
            vegeredmenyMutat(_aiBekapcsolva);
        });
        _jatekNev   = new Felirat(this, 598, 224, 340, 44,
                                  "Am\xc5\x91" "ba \xe2\x80\x93 5 egym\xc3\xa1s mell\xc3\xa9");

        _jatekVege  = new JatekVege(this, ABLAK_SZEL, ABLAK_MAG,
                                    [this]() { ujJatekIndit(); },
                                    [this]() { fomenureVissza(); });

        _kezdoKep   = new KezdoKepernyo(this, ABLAK_SZEL, ABLAK_MAG,
                                        [this](bool ai) { jatekIndit(ai); });

        jatekWidgetekRejt();
        _jatekVege->setLathato(false);
    }

private:
    void jatekIndit(bool aiMod) {
        _aiBekapcsolva = aiMod;
        _aiGomb->cimkecsere(aiMod ? "G\xc3\xa9p: BE" : "G\xc3\xa9p: KI");
        _jm.reset();
        _kezdoKep->setLathato(false);
        _jatekVege->setLathato(false);
        jatekWidgetekMutat();
        allapotFrissit();
    }

    void ujJatekIndit() {
        _jm.reset();
        _jatekVege->setLathato(false);
        allapotFrissit();
    }

    void fomenureVissza() {
        _jm.reset();
        _jatekVege->setLathato(false);
        jatekWidgetekRejt();
        _kezdoKep->setLathato(true);
    }

    void jatekWidgetekMutat() {
        _allapotSor->setLathato(true);
        _aiJelzo->setLathato(true);
        _tabla->setLathato(true);
        _resetGomb->setLathato(true);
        _aiGomb->setLathato(true);
        _jatekNev->setLathato(true);
    }

    void jatekWidgetekRejt() {
        _allapotSor->setLathato(false);
        _aiJelzo->setLathato(false);
        _tabla->setLathato(false);
        _resetGomb->setLathato(false);
        _aiGomb->setLathato(false);
        _jatekNev->setLathato(false);
    }

    void lepesUtanTeendo() {
        // Az AI-mod erteket rogton rogzitjuk, mielott barmi mas megvaltoztathatna
        bool aiVolt = _aiBekapcsolva;

        if (!_jm.vege() && aiVolt && _jm.getAktualisJatekos() == 2) {
            auto [as, ao] = _jm.aiLepes(2);
            _jm.lepesKiserlet(as, ao);
        }
        allapotFrissit();
        vegeredmenyMutat(aiVolt);
    }

    // Megjeleníti a játék vége párbeszédablakot, ha a játéknak vége.
    // Az aiVolt paraméter rögzíti, hogy AI-mód volt-e AKTÍV a döntő lépés pillanatában.
    void vegeredmenyMutat(bool aiVolt) {
        if (!_jm.vege()) return;
        ujrarajzol();
        varakozas(2500);
        int ny = _jm.getNyertes();
        if (ny == 1)
            _jatekVege->beallitEredmeny("Fekete nyert!", 80, 220, 80);
        else if (ny == 2)
            _jatekVege->beallitEredmeny(
                aiVolt ? "A g\xc3\xa9p nyert!" : "Feh\xc3\xa9r nyert!",
                220, 120, 60);
        else
            _jatekVege->beallitEredmeny("D\xc3\xb6ntetlen!", 180, 180, 180);
        _jatekVege->setLathato(true);
    }

    void allapotFrissit() {
        int ny = _jm.getNyertes();
        if (ny == 1) {
            _allapotSor->frissit("Fekete nyert!");
        } else if (ny == 2) {
            _allapotSor->frissit(
                _aiBekapcsolva
                    ? "A g\xc3\xa9p nyert!"
                    : "Feh\xc3\xa9r nyert!");
        } else if (_jm.teleE()) {
            _allapotSor->frissit("D\xc3\xb6ntetlen!");
        } else {
            int akt = _jm.getAktualisJatekos();
            if (_aiBekapcsolva && akt == 2)
                _allapotSor->frissit("G\xc3\xa9p gondolkodik...");
            else if (akt == 1)
                _allapotSor->frissit(
                    _aiBekapcsolva
                        ? "Te l\xc3\xa9psz (fekete)"
                        : "Fekete l\xc3\xa9p");
            else
                _allapotSor->frissit("Feh\xc3\xa9r l\xc3\xa9p");
        }
        _aiJelzo->frissit(
            _aiBekapcsolva
                ? "M\xc3\xb3" "d: ember vs g\xc3\xa9p"
                : "M\xc3\xb3" "d: k\xc3\xa9t ember");
    }

    JatekMester      _jm;
    bool             _aiBekapcsolva;
    Tabla*           _tabla;
    Felirat*         _allapotSor;
    Felirat*         _aiJelzo;
    Felirat*         _jatekNev;
    Button*          _resetGomb;
    Button*          _aiGomb;
    KezdoKepernyo*   _kezdoKep;
    JatekVege*       _jatekVege;
};

int main() {
    AmobaApp app;
    app.event_loop();
    return 0;
}
