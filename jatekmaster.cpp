#include "jatekmaster.hpp"
#include <cstring>
#include <algorithm>

JatekMester::JatekMester() : _aktJatekos(1), _nyertes(0), _dontetlen(false) {
    memset(_tabla, 0, sizeof(_tabla));
}

int JatekMester::getCella(int sor, int oszlop) const {
    return _tabla[sor][oszlop];
}

int JatekMester::getAktualisJatekos() const {
    return _aktJatekos;
}

int JatekMester::getNyertes() const {
    return _nyertes;
}

bool JatekMester::vege() const {
    return _nyertes != 0 || _dontetlen;
}

bool JatekMester::teleE() const {
    for (int s = 0; s < SOROK; s++)
        for (int o = 0; o < OSZLOPOK; o++)
            if (_tabla[s][o] == 0)
                return false;
    return true;
}

bool JatekMester::lepesKiserlet(int sor, int oszlop) {
    if (sor < 0 || sor >= SOROK || oszlop < 0 || oszlop >= OSZLOPOK)
        return false;
    if (_tabla[sor][oszlop] != 0)
        return false;
    if (vege())
        return false;

    _tabla[sor][oszlop] = _aktJatekos;

    int ks, ko, ds, do_;
    if (keresMegNyertesVonalat(_aktJatekos, ks, ko, ds, do_)) {
        _nyertes = _aktJatekos;
        _nyertesVonal.clear();
        for (int k = 0; k < 5; k++)
            _nyertesVonal.push_back({ks + k * ds, ko + k * do_});
    } else if (teleE()) {
        _dontetlen = true;
    } else {
        _aktJatekos = (_aktJatekos == 1) ? 2 : 1;
    }

    return true;
}

bool JatekMester::ellenorizVonal(int sor, int oszlop, int ds, int do_, int jatekos) const {
    for (int k = 0; k < 5; k++) {
        int ns = sor + k * ds;
        int no = oszlop + k * do_;
        if (ns < 0 || ns >= SOROK || no < 0 || no >= OSZLOPOK)
            return false;
        if (_tabla[ns][no] != jatekos)
            return false;
    }
    return true;
}

bool JatekMester::keresMegNyertesVonalat(int jatekos, int& ks, int& ko,
                                          int& ds, int& do_) const {
    int iranyok[4][2] = {{0,1},{1,0},{1,1},{1,-1}};
    for (int s = 0; s < SOROK; s++) {
        for (int o = 0; o < OSZLOPOK; o++) {
            if (_tabla[s][o] != jatekos) continue;
            for (auto& ir : iranyok) {
                if (ellenorizVonal(s, o, ir[0], ir[1], jatekos)) {
                    ks = s; ko = o; ds = ir[0]; do_ = ir[1];
                    return true;
                }
            }
        }
    }
    return false;
}

bool JatekMester::nyertE(int jatekos) const {
    for (int s = 0; s < SOROK; s++) {
        for (int o = 0; o < OSZLOPOK; o++) {
            if (_tabla[s][o] != jatekos) continue;
            if (ellenorizVonal(s, o, 0,  1, jatekos)) return true;
            if (ellenorizVonal(s, o, 1,  0, jatekos)) return true;
            if (ellenorizVonal(s, o, 1,  1, jatekos)) return true;
            if (ellenorizVonal(s, o, 1, -1, jatekos)) return true;
        }
    }
    return false;
}

const std::vector<std::pair<int,int>>& JatekMester::getNyertesVonal() const {
    return _nyertesVonal;
}

void JatekMester::reset() {
    memset(_tabla, 0, sizeof(_tabla));
    _aktJatekos = 1;
    _nyertes = 0;
    _dontetlen = false;
    _nyertesVonal.clear();
}

int JatekMester::maxSorban(int sor, int oszlop, int jatekos) const {
    int iranyok[4][2] = {{0,1},{1,0},{1,1},{1,-1}};
    int legjobb = 0;

    for (auto& ir : iranyok) {
        int db = 1;
        for (int k = 1; k < 5; k++) {
            int ns = sor + k * ir[0];
            int no = oszlop + k * ir[1];
            if (ns < 0 || ns >= SOROK || no < 0 || no >= OSZLOPOK) break;
            if (_tabla[ns][no] != jatekos) break;
            db++;
        }
        for (int k = 1; k < 5; k++) {
            int ns = sor - k * ir[0];
            int no = oszlop - k * ir[1];
            if (ns < 0 || ns >= SOROK || no < 0 || no >= OSZLOPOK) break;
            if (_tabla[ns][no] != jatekos) break;
            db++;
        }
        legjobb = std::max(legjobb, db);
    }
    return legjobb;
}

int JatekMester::cellaPontszam(int sor, int oszlop, int jatekos) const {
    if (_tabla[sor][oszlop] != 0)
        return -1;

    int ellenfel = (jatekos == 1) ? 2 : 1;

    const_cast<int*>(_tabla[sor])[oszlop] = jatekos;
    int sajat = maxSorban(sor, oszlop, jatekos);
    const_cast<int*>(_tabla[sor])[oszlop] = 0;

    const_cast<int*>(_tabla[sor])[oszlop] = ellenfel;
    int ellenf = maxSorban(sor, oszlop, ellenfel);
    const_cast<int*>(_tabla[sor])[oszlop] = 0;

    if (sajat >= 5)  return 200000;
    if (ellenf >= 5) return 180000;

    int pont = 0;
    pont += sajat  * sajat  * sajat  * 10;
    pont += ellenf * ellenf * ellenf * 7;

    int kozepSor    = SOROK / 2;
    int kozepOszlop = OSZLOPOK / 2;
    int tavolsag = std::abs(sor - kozepSor) + std::abs(oszlop - kozepOszlop);
    pont += std::max(0, 10 - tavolsag);

    return pont;
}

std::pair<int,int> JatekMester::aiLepes(int jatekos) const {
    int legjSor = SOROK / 2;
    int legjOszlop = OSZLOPOK / 2;
    int legjPont = -1;

    for (int s = 0; s < SOROK; s++) {
        for (int o = 0; o < OSZLOPOK; o++) {
            int pont = cellaPontszam(s, o, jatekos);
            if (pont > legjPont) {
                legjPont = pont;
                legjSor = s;
                legjOszlop = o;
            }
        }
    }

    return {legjSor, legjOszlop};
}
