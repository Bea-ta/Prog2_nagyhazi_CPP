#include "palya.h"
#include <iostream>

// CELLA
Cella::Cella(int sorszam):sorszam(sorszam),jarmu(nullptr){};

int Cella::get_sorszam(){return sorszam;};

bool Cella::ures() {return jarmu == nullptr;};

char Cella::get_jel(){
    if (jarmu==nullptr) return Cella::URES_JEL;
    else return jarmu->get_jel();
};



Jarmu* Cella::get_jarmu(){return jarmu;};

void Cella::set_jarmu(Jarmu* jarmu) {
    this->jarmu = jarmu;
};

// PALYA
Palya::Palya (int hossz):hossz(hossz),jarmu_db(0){
    cellak= new Cella*[hossz];
    for (int i=0; i<hossz; i++) {
        cellak[i] = new Cella(i);
    }
};

Palya::Palya (int hossz, int jarmudarab, Veletlen& veletlen):Palya(hossz){
    if (jarmudarab>hossz) throw BajVan("Tul sok kocsi!");
    jarmu_db = jarmudarab;
    int idx;
    for (int i=0; i<jarmudarab; i++){
        idx=veletlen.get_rand(hossz);
        while (!cellak[idx]->ures()) {
            idx=veletlen.get_rand(hossz);
        };
        cellak[idx]->set_jarmu(new Auto(veletlen));
    }
    };



void Palya::helyez(int pozicio, Jarmu* jarmu){
    if (pozicio<0 || pozicio>=hossz) throw BajVan("Nemletezo pozicio");
    if (!cellak[pozicio]->ures()) throw BajVan("Nem ures cella!");
    cellak[pozicio]->set_jarmu(jarmu);
    jarmu_db++;
};

void Palya::mozgat(int honnan, int hova){
    if (honnan<0||honnan>=hossz||hova<0) throw BajVan("Nem letezo poziciok");
    if (cellak[honnan]->ures()) throw BajVan("A honnan ures!");
    Jarmu* jarmu = cellak[honnan]->get_jarmu();
    cellak[honnan]->set_jarmu(nullptr);
    if (hova<hossz){
    if (!cellak[hova]->ures()) throw BajVan("A hova nem ures!");
    cellak[hova]->set_jarmu(jarmu);
    }
    else{
        jarmu_db--;
    }
    };

void Palya::rajzol(std::ostream& os){
    for (Palya::Iterator it=this->eleje(); it!=this->vege(); ++it){
        if ((*it)==nullptr) throw "hianyzo cella";
        os<<(*it)->get_jel();
    }
    os<<std::endl<<"A palyan levo autok szama: "<<jarmu_db<<std::endl;
};

int Palya::elotte(int poz, int maximum){
    int tavolsag=0;
    while (tavolsag<maximum&&(poz+1+tavolsag>=hossz||cellak[poz+1+tavolsag]->ures())) tavolsag++;
    return tavolsag;
}

bool Palya::ures() {return jarmu_db == 0;}


// PALYA ITERATOR

bool Palya::Iterator::operator!=(Iterator& masik) {
    return p!=masik.p;
}

/// Palya Iterator Pre inkremens
Palya::Iterator& Palya::Iterator::operator++() {
    if (p == nullptr || p == pe)
        throw std::out_of_range("Rossz Iterator++");
    if (elorefele) p++;
    else p--;
    return *this;
}

/// Palya Iterator Csillag
Cella* Palya::Iterator::operator*() {
    if (p == nullptr || p == pe)
        throw "Rossz Iterator*";
    return *p;
}

/// Palya Iterator Nyil operator
Cella** Palya::Iterator::operator->() {
     if (p == nullptr || p == pe)
         throw "Rossz Iterator->";
     return p;
}

/// Palya destructor
Palya::~Palya(){
    for (int i = 0; i < hossz; ++i) {
        delete cellak[i];
    }
    delete[] cellak;
    };
