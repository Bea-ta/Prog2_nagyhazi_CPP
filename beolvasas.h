#ifndef BEOLVASAS_H_INCLUDED
#define BEOLVASAS_H_INCLUDED
#include <iostream>
#include "palya.h"

/// @brief Beolvasás megvalósítása
/// @param os ahova az üzenetet írja
/// @param is ahonnan az adatokat olvassa
/// @return a létrehozott pálya címe
Palya* beolvasas(std::ostream& os=std::cout, std::istream& is=std::cin);


#endif // BEOLVASAS_H_INCLUDED

