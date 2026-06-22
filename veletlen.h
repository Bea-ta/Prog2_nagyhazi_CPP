#ifndef VELETLEN_H_INCLUDED
#define VELETLEN_H_INCLUDED
#include <random>
#include <ctime>
#include "common.h"

/// absztrakt osztály a véletlenek kezelésére (egyenletes eloszlás)
class Veletlen {
public:
    /// @brief százalékos valószínűséget tesztelő függvény
    /// @param szazalek a valószínűség megadása százalékban
    /// @return a generált szám a határ alatt van-e
    virtual bool rand_alatt(int szazalek)=0;

    /// @brief nemnegatív egész szám generálása
    /// @param maximum a generálandó szám felső korlátja (szigorú)
    /// @return a generált egész a 0..(maximum-1) tartományból
    virtual int get_rand(int maximum)=0;
};


/// @brief informatikai értelemben valódi véletlent megvalósító osztály
class Igazi: public Veletlen {
    std::mt19937 generator;
    std::uniform_real_distribution<double> tartomany; // Uniform integer distribution
public:
    Igazi();
    bool rand_alatt(int szazalek);
    int get_rand(int maximum);
};

/// @brief a valódi véletlen állapotmentes, újrafelhasználható, elég ezt a példányt csak használni
static Igazi igazi = Igazi();

/// @brief teszteléshez használt "irányított" véletlen
/// A rendelkezésre bocsátott adatokat olvassa körkörösen újra és újra.
class Teszt: public Veletlen {
private:
    static const int max_elem = 50;
    double adat[max_elem];
    size_t meret;
    size_t idx;
public:
    Teszt(const double* adat, int meret);
    bool rand_alatt(int szazalek);
    int get_rand(int maximum);
};

#endif // VELETLEN_H_INCLUDED
