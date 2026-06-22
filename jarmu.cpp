#include "jarmu.h"
#include <iostream>

/// visszaadja a jármű sebességét
int Jarmu::get_sebesseg(){return sebesseg;};

///beállítja a jármű sebesságét
/// BajVan("Hibas sebesseg!") kivételt dob, ha a beállítani kívánt sebesség túl nagy/kicsi
/// @param sebesseg - új sebesség
void Jarmu::set_sebesseg(int sebesseg){
    if (sebesseg<0 || sebesseg>get_max_sebesseg()) throw BajVan("Hibas sebesseg!");
    this->sebesseg=sebesseg;
}

/// eggyel megnöveli a jármű sebességét, ha még nem érte el a maximum sebességét
void Jarmu::gyorsit() {
    if (sebesseg<get_max_sebesseg()) sebesseg+=1;
};

///eggyel csökkenti a jármű sebességét bena_szazalek valószínűséggel, ha az még nem 0
/// @param veletlen - veletlen referencia
void Jarmu::bena(Veletlen& veletlen) {
    if (sebesseg>0&&veletlen.rand_alatt(get_bena_szazalek())) sebesseg--;
};

/// Konstruktor megadott sebességgel
/// @param sebesség - sebesség
template<char JEL, int MAXSEB, int BENA_SZ>
JarmuTipus<JEL,MAXSEB,BENA_SZ>::JarmuTipus(int sebesseg){
     if (sebesseg<0 || sebesseg>MAXSEB) throw BajVan("Hibas sebesseg!");
    this->sebesseg = sebesseg;
};

/// Konstruktor véletlen sebességgel
/// @param veletlen - veletlen referencia
template<char JEL, int MAXSEB, int BENA_SZ>
JarmuTipus<JEL,MAXSEB,BENA_SZ>::JarmuTipus(Veletlen& veletlen):JarmuTipus(veletlen.get_rand(MAXSEB+1)) {};

/// visszaadja a járműtípus jelét
template<char JEL, int MAXSEB, int BENA_SZ>
char JarmuTipus<JEL,MAXSEB,BENA_SZ>::get_jel() const { return JEL;}

/// visszaadja a járműtípus maximum sebességét
template<char JEL, int MAXSEB, int BENA_SZ>
int JarmuTipus<JEL,MAXSEB,BENA_SZ>::get_max_sebesseg() const {return MAXSEB;}

/// visszaadja a járműtípus bénasági százalékát
template<char JEL, int MAXSEB, int BENA_SZ>
int JarmuTipus<JEL,MAXSEB,BENA_SZ>::get_bena_szazalek() const {return BENA_SZ;}
