# BevProg2_VÉGLEGES


Amőba – változások v4-ről 1.0-ra:


1. HIBAJAVÍTÁS – Főmenü gomb nem működött megfelelően

Hiba: A „Főmenübe" gombra kattintva a program azonnal
új játékot indított a főmenü helyett.

Ok: Az eseménykezelő (event_loop) minden eseményt az
összes látható widgetre küldött. Amikor a JatekVege
widget kezelte a kattintást és meghívta a fomenureVissza()
függvényt, a KezdoKepernyo éppen láthatóvá vált – és
ugyanabban az iterációban megkapta azt a kattintást,
amelyik véletlenül a „JÁTÉK INDÍTÁSA" gomb területére esett.

Javítás (application.cpp): Az event_loop most a kattintás
előtt pillanatfelvételt (snapshot) készít a látható
widgetekről, és csak ezeknek küldi el az eseményt.
Így az újonnan megjelenő widgetek nem kapják meg az
aktuális eseményt.


2. HIBAJAVÍTÁS – Nyertes öt cella kiemelése 2,5 másodpercig

Fejlesztés: Győzelem esetén a nyertes öt cella arany
kerettel (sárga vonallal) van kiemelve. A játék vége
képernyő csak 2,5 másodperc múlva ugrik fel, így a
játékosoknak van idejük látni, hol dőlt el a mérkőzés.

Érintett fájlok:
- jatekmaster.cpp/hpp: új keresMegNyertesVonalat() belső
  metódus eltárolja az 5 nyertes cella koordinátáit;
  getNyertesVonal() visszaadja ezeket.
- tabla.cpp: a draw() az öt nyertes cellára arany keretet
  rajzol a rendes megjelenítés után.
- application.cpp: új ujrarajzol() és varakozas(ms) metódus.
- main.cpp: lepesUtanTeendo() győzelem után meghívja az
  ujrarajzol()-t, majd varakozas(2500)-t, és csak ezután
  jeleníti meg a JatekVege popupot.

3. FEJLESZTÉS – Ablak mérete megnövelve

Régi méret: 720 × 530 képpont
Új méret:   950 × 600 képpont

A táblacella mérete 34-ről 38 képpontra nőtt, így a
játéktér kényelmesebben látható és könnyebb rákattintani.

4. FEJLESZTÉS – Magyar ékezetes szövegek

Minden szöveg magyarosítva lett, beleértve:
- A főcím: „AMŐBA" (korábban „AMOBA")
- „Fekete lép" / „Fehér lép" (korábban „1. jatekos lep")
- „Gép gondolkodik…"
- „Döntetlen!"
- „Mód: ember vs gép" / „Mód: két ember"
- „Új játék" / „Főmenü"
- „Játék vége"
- „Te lépsz (fekete)"
Az ékezetes karakterek UTF-8 formátumban kerültek be a
forráskódba. Az SDL_TTF könyvtár TTF_RenderUTF8_Blended()
függvénye helyesen jeleníti meg őket.

5. FEJLESZTÉS – Játékos neve a státuszsorban

Korábban: „1. jatekos lep" / „2. jatekos lep"
Mostantól: „Fekete lép" / „Fehér lép"
Két emberes módban ez egyértelműbbé teszi, hogy ki következik.

6. FEJLESZTÉS – Gombfelirat frissítve

Az AI be/ki kapcsoló gomb felirata „AI: BE/KI" helyett
„Gép: BE/KI" lett, jobban illeszkedve a többi szöveghez.

Összefoglalás érintett fájlok szerint:
  application.hpp/cpp  – snapshot fix, ujrarajzol(), varakozas()
  jatekmaster.hpp/cpp  – getNyertesVonal(), keresMegNyertesVonalat()
  tabla.hpp/cpp        – CELL=38, nyertes kiemelés rajzolása
  main.cpp             – 950×600 ablak, ékezetes szövegek, 2,5 mp várakozás
  kezdokepernyo.cpp    – AMŐBA cím, nagyobb elrendezés
  jatekvege.cpp        – nagyobb ablakhoz igazított panel, ékezetek
  felirat.cpp          – font méret 16→17
  button.cpp           – font méret 17→18
