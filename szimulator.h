#ifndef SZIMULATOR_H_INCLUDED
#define SZIMULATOR_H_INCLUDED
#include "palya.h"
#include "veletlen.h"

/// @brief Szimulációt megvalósító osztály
class Szimulator {
private:
    /// @brief a szimulátor futásának végét jelzi
    bool vege;
    /// @brief a pálya, amelyiken a szimuláció fut; tartalmazza a járműveket
    Palya* palya;
    /// @brief a véletlent adó osztály
    Veletlen& veletlen;
    /// @brief a szimuláció ciklusa, mely a sebességeket módosítja
    void sebesseg_valt_ciklus();
    /// @brief a szimuláció ciklusa, mely az aktuális sebességgel a járműveket mozgatja
    void hely_valt_ciklus();
public:
    /// Konstructor
    Szimulator(Palya* palya, Veletlen& veletlen);
    /// @brief szimuláció futtatását végző függvény
    /// @param os ahova az adatokat írja, default: standard out.
    void run(std::ostream& os=std::cout);
};

#endif // SZIMULATOR_H_INCLUDED
