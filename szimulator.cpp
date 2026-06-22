#include "szimulator.h"
#include <iostream>

Szimulator::Szimulator(Palya* palya, Veletlen& veletlen): vege(false),palya(palya),veletlen(veletlen) {};

void Szimulator::sebesseg_valt_ciklus(){
    for (Palya::Iterator it=palya->eleje(); it!=palya->vege(); ++it){
        if (!(*it)->ures()) {
            Jarmu* jarmu = (*it)->get_jarmu();
            jarmu->gyorsit();
            jarmu->set_sebesseg(palya->elotte((*it)->get_sorszam(), jarmu->get_sebesseg()));
            jarmu->bena(veletlen);
        }
    }
};

void Szimulator::hely_valt_ciklus(){
    for (Palya::Iterator it=palya->eleje(false); it!=palya->vege(false); ++it){
        if (!(*it)->ures()) {
            palya->mozgat((*it)->get_sorszam(), ((*it)->get_sorszam()+(*it)->get_jarmu()->get_sebesseg()));
        }
    }
};

void Szimulator::run(std::ostream& os){
    palya->rajzol(os);
    while (!vege){
        sebesseg_valt_ciklus();
        hely_valt_ciklus();
        palya->rajzol(os);
        vege=palya->ures();
    }
};
