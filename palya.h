#ifndef PALYA_H_INCLUDED
#define PALYA_H_INCLUDED
#include "common.h"
#include "jarmu.h"
#include "veletlen.h"
#include <iostream>

///Jarmu osztály elõdeklarációja
class Jarmu;

/// Cella osztály.
/// A cellák sorszámát és Jármû pointereket tartalmaz
class Cella {
private:
    int sorszam;        ///< cella sorszáma
    Jarmu* jarmu;       ///< jármû pointer
public:
    static const char URES_JEL = '=';

    /// Konstruktor adott sorszámmal
    /// A jármű nullpointer.
    /// @param sorszam - sorszám
    Cella(int sorszam);

    /// visszaadja a cella sorszámát
    /// @return - sorszám
    int get_sorszam();

    /// megadja a cellában tárolt jármű jelét ha van, egyébként az üres jelet.
    char get_jel();

    /// Eldönti, hogyüres-e a cella
    /// @return - üres-e
    bool ures();

    /// visszaadja a cellában tárolt járművet
    /// @return - jármű
    Jarmu* get_jarmu();

    /// átírja a cellában tárolt járművet a kapottra
    /// @param - jármű referencia
    void set_jarmu(Jarmu* jarmu);
};

/// Palya osztály.
/// A pálya celláit, számát, bennük lévő jármûvek számát tartalmazza
class Palya {
    private:
    Cella** cellak;         ///< cellák tömbja
    int hossz;              ///< pálya hossza/ cella darabszám
    int jarmu_db;           ///< pályán lévő járművek száma
    public:
    ///Jarmu osztály elõdeklarációja
    class Iterator;

    /// Konstruktor megadott hosszal
    /// Járművek száma=0
    /// A cellak celláit már a megfelelő sorszámmal hozza létre
    /// @param hossz - hossz
    Palya(int hossz);

    /// Konstruktor megadott hosszal, jámű darabszámmal, használt véletlennel
    /// Meghívja a pálya hosszal megadott konstruktorát, és lhelyez jarmudarab járművet a pályán véletlen kezdősebességgel
    /// Ha túl sok autót próbálna meg elhelyezni BajVan("Tul sok kocsi!") kivételt dob
    /// @param hossz - hossz
    /// @param jarmudarab - jámű darabszám
    /// @param veletlen - veletlen referencia
    Palya(int hossz, int jarmudarab, Veletlen& veletlen);

    /// Elhelyez egy járművet a pálya megadott pozíciójú cellájába
    /// Nem megfelelő cél cellára (nem létezik/ már foglalt) BajVan("Nemletezo pozicio")/BajVan("Nem üres cella!") kivételt dob
    /// @param poz - cél cella pozíciója
    /// @param - jármű referencia
    void helyez(int pozicio, Jarmu* jarmu);

    /// Visszaadja az adott pozíciójú cella után hány cella üres (max a sebességével előrébb lévő celláig)
    /// @param poz - a cella pozíciója
    /// @param maximum - a jármű sebessége, maximum távolság amire vizsgáljuk
    /// @return - távolság
    int elotte(int poz, int maximum);

    /// Átmozgat egy járművet a megadott honnan cellából a hova cellába
    /// Nem megfelelő honnan, hova esetén BajVan("Nem létező pozíciók"), BajVan("A honnan ures!"), BajVan("A hova nem ures!") kivételt dob
    /// @param honnan - a cella pozíciója amiből kiszedjük a járművet
    /// @param hova - a cella pozíciója amibe berakjuk a járművet
    void mozgat(int honnan, int hova);

    /// Kirajzolja a pályát
    void rajzol(std::ostream& os);

    /// Eldönti, hogyüres-e a pálya (van-e még rajta jármű)
    /// @return - üres-e
    bool ures();

    /// Visszaad egy pálya elejére mutató iterátort attól függően
    /// @param honnan - a cella pozíciója amiből kiszedjük a járművet
    /// @return - üres-e
    Iterator eleje(bool elore=true){
        return Iterator(*this, 0, elore);};
    Iterator vege(bool elore=true){
        return Iterator(*this, hossz, elore);};

    class Iterator {
        Cella **p;        // aktuális pointer
        Cella **pe;       // végpointer
        bool elorefele;
    public:
        /// Inicializálatlan iterátor
        Iterator() :p(nullptr), pe(nullptr), elorefele(true) {}

        /// Konstruktor a eleje-hez és a vege-hez
        /// @param palya - palya
        /// @param n - akt. index
        /// @param elore - balrol jobbra halad-e
        Iterator(Palya& palya, int n = 0, bool elore=true)
            :elorefele(elore){
                p=&palya.cellak[0]+(elore?n:palya.hossz-1-n);
                pe=&palya.cellak[0]+(elore?palya.hossz:-1);
            }

        /// !=
        bool operator!=(const Iterator& it) const {
            return p != it.p;
        }

        /// ==
        bool operator==(Iterator& it) {
            return p == it.p;
        }

        /// Pre inkremens
        Iterator& operator++();

        /// Post inkremens
        Iterator operator++(int);

        /// Csillag
        Cella* operator*();

        /// Nyíl operátor
        Cella** operator->();

        /// Egyenlotlenseg operátor
        bool operator!=(Iterator& masik);
        };

    ~Palya();
};


#endif // PALYA_H_INCLUDED
