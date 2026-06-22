#include "veletlen.h"

Igazi::Igazi():generator(static_cast<double>(std::time(nullptr))), tartomany(0.0, 1.0){};
bool Igazi::rand_alatt(int szazalek){return tartomany(generator)<((double)szazalek)/100;};
int Igazi::get_rand(int maximum){return (int)(tartomany(generator)*maximum);};

Teszt::Teszt(const double* adat, int meret):meret(meret), idx(0){
    if (meret > max_elem) {
            throw BajVan("A veletlen nem tud ennyi elemet tarolni.");
    }
    for (int i=0;i<meret;i++) {
        if (adat[i]<0.0 || adat[i]>=1.0) {
            throw BajVan("A veletlen szamok 0-nal nem kisebbek es 1-nel nem nagyobbak lehetnek.");
        }
        this->adat[i]=adat[i];
    }
};

bool Teszt::rand_alatt(int szazalek){
    if (idx==meret) idx = 0;
    return adat[idx++]<((double)szazalek)/100;
};
int Teszt::get_rand(int maximum){
    if (idx==meret) idx = 0;
    return (int)(adat[idx++]*maximum);
};
