#include <iostream>
#include <sstream>
#include <string>
#include "beolvasas.h"
#include "common.h"
#include "gtest_lite.h"
#include "jarmu.h"
#include "memtrace.h"
#include "palya.h"
#include "szimulator.h"
#include "veletlen.h"

/// TESZT 1.
void test_1() {
    std::cout<<"test_1 futtatasa"<<std::endl;
    Palya* palya = new Palya(10);
    palya->helyez(3, new Auto(2));
    Szimulator szimulator = Szimulator(palya,igazi);
    szimulator.run();
}

/// TESZT 2
void test_2() {
    std::cout<<"test_2 futtatasa"<<std::endl;
    Palya* palya = new Palya(10);
    palya->helyez(2, new Auto(5));
    palya->helyez(3, new Auto(1));
    double adat[] = {0.32424, 0.129947, 0.772372, 0.8212};
    Teszt teszt = Teszt(adat,sizeof(adat)/sizeof(double));
    Szimulator szimulator = Szimulator(palya,teszt);
    szimulator.run();
}

/// TESZT 3
void test_3() {
    std::cout<<"test_3 futtatasa"<<std::endl;
    Palya* palya = new Palya(20,5,igazi);
    Szimulator szimulator = Szimulator(palya,igazi);
    szimulator.run();
}

/// TESZT egy autoval vegig
std::string teszt_egyauto_vegig() {
    std::stringstream os;
    double adat[] = {0.324245, 0.129947, 0.772372, 0.821201, 0.433212, 0.556803, 0.646528, 0.224951, 0.984247, 0.154862};
    // a tesztveletlen
    Teszt teszt = Teszt(adat,sizeof(adat)/sizeof(double));
    Palya* palya = new Palya(10);
    palya->helyez(0,new Auto(0));
    Szimulator szimulator = Szimulator(palya, teszt);
    szimulator.run(os);
    return os.str();
}

const std::string EREDMENY_EGYAUTO = "X=========\nA palyan levo autok szama: 1\n=X========\nA palyan levo autok szama: 1\n==X=======\nA palyan levo autok szama: 1\n====X=====\nA palyan levo autok szama: 1\n=======X==\nA palyan levo autok szama: 1\n==========\nA palyan levo autok szama: 0\n";


int main()
{
#ifdef CPORTA
    // CPorta beküldés esetén gépi tesztelés
    TEST(SzimulatorTeszt, Minitesztek) {
        EXPECT_NO_THROW(test_1());
        EXPECT_NO_THROW(test_2());
        EXPECT_NO_THROW(test_3());
    } END
    TEST(SzimulatorTeszt, EgyAutoVegig) {
        EXPECT_TRUE(EREDMENY_EGYAUTO == teszt_egyauto_vegig());
    } END
    TEST(PalyaTeszt, Helyez) {
        Palya* palya = new Palya(10);
        EXPECT_THROW(palya->helyez(10,new Auto(5)), BajVan);
        EXPECT_THROW(palya->helyez(-1,new Auto(5)), BajVan);
        EXPECT_THROW(palya->helyez(15,new Auto(5)), BajVan);
        EXPECT_THROW(palya->helyez(-15,new Auto(5)), BajVan);
    } END
// veletlen teszt 50 db 0<= x < 1

#else
    std::cout << "Autopalya szimulator" << std::endl;
    Palya* palya = beolvasas();
    Szimulator szimulator = Szimulator(palya,igazi);
    szimulator.run();
#endif
	return 0;
}
