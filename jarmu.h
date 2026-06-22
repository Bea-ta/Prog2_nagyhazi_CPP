#ifndef JARMU_H_INCLUDED
#define JARMU_H_INCLUDED
#include "common.h"
#include "veletlen.h"

/// Jarmu osztály.
/// Járművek sebességét és bénázási faktorát tartalmazza
class Jarmu {
protected:
    int sebesseg;                           ///< jármű sebessege
public:
    /// visszaadja a jármű jelét (elkéri a fajtájától)
    /// pure virtual függvény
    virtual char get_jel() const = 0;

    /// visszaadja a jármű maximum sebességét (elkéri a fajtájától)
    /// pure virtual függvény
    virtual int get_max_sebesseg() const = 0;

    /// visszaadja a jármű bénázását (elkéri a fajtájától)
    /// pure virtual függvény
    virtual int get_bena_szazalek() const = 0;

    /// visszaadja a jármű sebességét
    int get_sebesseg();

    ///beállítja a jármű sebesságét
    /// BajVan("Hibas sebesseg!") kivételt dob, ha a beállítani kívánt sebesség túl nagy/kicsi
    /// @param sebesseg - új sebesség
    virtual void set_sebesseg(int sebesseg);

    /// eggyel megnöveli a jármű sebességét, ha még nem érte el a maximum sebességét
    virtual void gyorsit();

    ///eggyel csökkenti a jármű sebességét bena_szazalek valószínűséggel, ha az még nem 0
    /// @param veletlen - véletlen referencia
    virtual void bena(Veletlen& veletlen);
};

/// Járműtípus template osztály.
/// A jármű jelét, maximum sebességét és bénázási százalékét tartalmazza
template<char JEL, int MAXSEB, int BENA_SZ>
class JarmuTipus: public Jarmu {
public:
    /// Konstruktor megadott sebességgel
    /// @param sebesség - sebesség
    JarmuTipus(int sebesseg);

    /// Konstruktor véletlennel
    /// @param veletlen - véletlen referencia
    JarmuTipus(Veletlen& veletlen);

    /// visszaadja az autó jelét
    char get_jel() const ;

    /// visszaadja a jármű maximum sebességét
    int get_max_sebesseg() const ;

    /// visszaadja a bénaság százalékát
    int get_bena_szazalek() const ;
};

template class JarmuTipus<'X', 5, 15>;
typedef JarmuTipus<'X', 5, 15> Auto;
#endif // JARMU_H_INCLUDED
