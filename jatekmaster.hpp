#ifndef JATEKMASTER_HPP
#define JATEKMASTER_HPP

#include <utility>
#include <vector>

class JatekMester {
public:
    static const int SOROK = 15;
    static const int OSZLOPOK = 15;

    JatekMester();

    int getCella(int sor, int oszlop) const;
    int getAktualisJatekos() const;
    int getNyertes() const;
    bool vege() const;
    bool lepesKiserlet(int sor, int oszlop);
    bool nyertE(int jatekos) const;
    bool teleE() const;
    void reset();

    const std::vector<std::pair<int,int>>& getNyertesVonal() const;
    std::pair<int,int> aiLepes(int jatekos) const;

private:
    bool ellenorizVonal(int sor, int oszlop, int ds, int do_, int jatekos) const;
    bool keresMegNyertesVonalat(int jatekos, int& ks, int& ko, int& ds, int& do_) const;
    int  maxSorban(int sor, int oszlop, int jatekos) const;
    int  cellaPontszam(int sor, int oszlop, int jatekos) const;

    int  _tabla[SOROK][OSZLOPOK];
    int  _aktJatekos;
    int  _nyertes;
    bool _dontetlen;
    std::vector<std::pair<int,int>> _nyertesVonal;
};

#endif
