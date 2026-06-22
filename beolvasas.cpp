#include <memory>
#include <fstream>
#include "beolvasas.h"
#include "common.h"
#include "veletlen.h"

/// Számot bekérő segédfüggvény. Csak az adott tartományon belüli értékeket fogadja el.
/// @param os ahova az üzeneteket küldi
/// @param is ahonnan az adatokat olvassa
/// @param uzenet a küldendő üzenet (bekért adat leírása)
/// @param mini minimumérték
/// @param maxi maximumérték
/// @return a sikeresen beolvasott szám a tartományból
int szam_beker(std::ostream& os, std::istream& is, const std::string& uzenet, int mini, int maxi) {
    int szam;
    os << uzenet;
    is >> szam;
    while (szam < mini || szam > maxi) {
        os << "A megengedett tartomanyon kivuli ertek." << std::endl;
        os << uzenet;
        is >> szam;
    }
    return szam;
}

/// @brief Igen/Nem választ bekérő segédfüggyvény.
/// @param os ahova az üzeneteket küldi
/// @param is ahonnan az adatokat olvassa
/// @param uzenet a küldendő üzenet (bekért adat leírása)
/// @return a válasz bool formában
bool igen_e(std::ostream& os, std::istream& is, const std::string& uzenet) {
    char c;
    os << uzenet;
    is >> c;
    while (c != 'i' && c != 'I' && c != 'n' && c != 'N') {
        os << "Rossz formatumu valasz." << std::endl;
        os << uzenet;
        is >> c;
    }
    return (c == 'i' || c == 'I');
}

/// Default pályát előállító függvény
/// @return az elkészült pálya címe
Palya* palya_default() {
    return new Palya(100, 15, igazi);
}

/// Pálya létrehozása fájl tartalma alapján
/// @param filename a fájl neve
/// @param os a kimenet az üzenetek számára
/// @return az elkészült pálya címe, vagy nullptr, ha sikertelen
/// @throws std::runtime_error, BajVan a hibától függően
Palya* file_olvas(std::string filename, std::ostream& os=std::cout) {
    Palya* palya = nullptr;
    std::ifstream ifs;
    try {
        ifs.open(filename);
        if (!ifs.is_open()) {
          os << "Rossz fajl, nem nyithato meg." << std::endl;
        }
        else {
            int hossz;
            ifs >> hossz;
            int db;
            ifs >> db;
            bool generalt;
            ifs >> generalt;
            if (generalt) {
                palya = new Palya(hossz, db, igazi);
            }
            else {
                Palya* palya = new Palya(hossz);
                int poz, seb;
                for (int i=0;i<db;i++) {
                    ifs >> poz >> seb;
                    palya->helyez(poz, new Auto(seb));
                }
            }
        }
    } catch (BajVan& b) {
        os<<"Logikai hiba a beolvasas kozben: "<<b.uzenet()<<std::endl;
        palya=nullptr;
    } catch(std::exception& e) {
        os<<"Olvasasi hiba: fajl formatum hiba: "<<e.what()<<std::endl;
        palya=nullptr;
    } catch(...) {
        os<<"Olvasasi hiba: fajl formatum egyeb hiba."<<std::endl;
        palya=nullptr;
    }
    return palya;
}

/// @brief A fájlból beolvasandó pálya. Hiba esetén a default pályát adja vissza.
/// @param os ahova az üzenetet írja
/// @param is ahonnan az adatokat olvassa
/// @return az elkészült pálya címe
Palya* palya_filebol(std::ostream& os, std::istream& is) {
    os << "Fajlbeolvasas"<<std::endl;
        std::string filename;
    os << "Kerem a fajl nevet!\n";
    is >> filename;
    Palya* palya = file_olvas(filename, os);
    if (palya==nullptr) {
        os << "Default palya hasznalata." << std::endl;
        return palya_default();
    }
    else return palya;
}

/// @brief Kézi bevitel folyamata pálya készítéshez.
/// @param os ahova az üzenetet írja
/// @param is ahonnan az adatokat olvassa
/// @return a létrehozott pálya címe
Palya* palya_kezzel(std::ostream& os, std::istream& is) {
    int hossz = szam_beker(os, is, "Mekkora legyen a palya? (0-600) : ", 0, 600);
    int db = szam_beker(os, is, "Hany auto legyen? (0-" + std::to_string(hossz) + ") : ", 0, hossz);
    if (igen_e(os, is, "Sajat kezzel szeretne megadni az autok kezdeti helyzetet es sebesseget? (i/n) : ")) {
        Palya* palya = new Palya(hossz);
        os << "Kezibeolvasas"<<std::endl;
        int poz, seb;
        for (int i=0; i<db; i++){
            bool siker = false;
            while (!siker){
                os << "Kerem a(z) "<< i+1 <<". auto helyet es sebesseget (hely seb): ";
                is >> poz >> seb;
                try {
                    palya->helyez(poz, new Auto(seb));
                    siker=true;
                }
                catch (BajVan& b) {
                    os << b.uzenet()<<std::endl;
                }
            }
        }
        return palya;
    }
    else{
        os << "Random generalas"<<std::endl;
        return new Palya(hossz,db,igazi);
    }
}

/// @brief Beolvasás megvalósítása
/// @param os ahova az üzenetet írja
/// @param is ahonnan az adatokat olvassa
/// @return a létrehozott pálya címe
Palya* beolvasas(std::ostream& os, std::istream& is) {
    if (!igen_e(os, is, "Sajat adatokkat szeretne megadni? (i/n) : ")) {
        return palya_default();
    }

    if (igen_e(os, is, "Fajlbol? (i/n) : ")) {
        return palya_filebol(os, is);
    } else {
        return palya_kezzel(os, is);
    }
}

