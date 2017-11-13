#include "citizen.h"
#include "monster.h"
#include "smalltown.h"
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>

// Opis testów
// grupa 1 tworzenie obiektów
// grupa 2 poprawność funkcji składowych
// grupa 3 poprawność parametrów szablonów
// grupa 4 sprawdzanie ograniczeń na wiek mieszkańców i czas
// grupa 5 sprawdzenie logiki tick
// grupa 6 poprawność funkcji attack

using namespace std;

int main() {
    #if TEST_NUM == 101
    Mummy<int>(100, 10);
    Vampire<int>(100, 10);
    Zombie<int>(100, 10);
    #endif

    #if TEST_NUM == 102
    Adult<int>(100, 35);
    Teenager<int>(100, 15);
    Sheriff<int>(100, 35, 10);
    #endif

    #if TEST_NUM == 103
    SmallTown<Vampire<int>, int, 0, 23, Adult<int>>(Vampire<int>(100, 10), Adult<int>(100, 35));
    #endif

    #if TEST_NUM == 104
    Mummy();
    #endif

    #if TEST_NUM == 105
    Vampire();
    #endif

    #if TEST_NUM == 106
    Zombie();
    #endif

    #if TEST_NUM == 107
    Mummy<int>();
    #endif

    #if TEST_NUM == 108
    Vampire<int>();
    #endif

    #if TEST_NUM == 109
    Zombie<int>();
    #endif

    #if TEST_NUM == 110
    Adult<int>(100, 35, 10);
    #endif

    #if TEST_NUM == 111
    Sheriff<int>(100, 35);
    #endif

    #if TEST_NUM == 201
    auto town = SmallTown<Vampire<int>, int, 0, 23, Adult<int>>(Vampire<int>(100, 10), Adult<int>(100, 35));
    assert(get<0>(town.getStatus()) != "");
    assert(get<1>(town.getStatus()) == 100);
    assert(get<2>(town.getStatus()) == 1);
    #endif

    #if TEST_NUM == 202
    auto vampire = Vampire<int>(100, 10);
    assert(vampire.getHealth() == 100);
    assert(vampire.getAttackPower() == 10);
    #endif

    #if TEST_NUM == 203
    auto adult = Adult<int>(100, 35);
    assert(adult.getHealth() == 100);
    assert(adult.getAge() == 35);
    #endif

    #if TEST_NUM == 204
    auto sheriff = Sheriff<int>(100, 35, 10);
    assert(sheriff.getHealth() == 100);
    assert(sheriff.getAge() == 35);
    assert(sheriff.getAttackPower() == 10);
    #endif

    #if TEST_NUM == 205
    auto adult = Adult<int>(100, 35);
    adult.takeDamage(10);
    assert(adult.getHealth() == 90);
    #endif

    #if TEST_NUM == 206
    auto vampire = Vampire<int>(100, 10);
    vampire.takeDamage(10);
    assert(vampire.getHealth() == 90);
    #endif

    #if TEST_NUM == 207
    auto adult = Adult<int>(100, 35);
    adult.getAttackPower();
    #endif

    #if TEST_NUM == 208
    auto adult = Adult<int>(100, 35);
    adult.takeDamage("10");
    #endif

    #if TEST_NUM == 209
    auto vampire = Vampire<int>(100, 10);
    vampire.takeDamage("10");
    #endif

    #if TEST_NUM == 210
    auto town = SmallTown<Vampire<int>, int, 0, 23, Adult<int>>(Vampire<int>(100, 10), Adult<int>(100, 35));
    town.tick("1");
    #endif

    #if TEST_NUM == 301
    Vampire<int>(100, "1.5");
    #endif

    #if TEST_NUM == 302
    Adult<int>(100, "1.5");
    #endif

    #if TEST_NUM == 303
    Adult<string>("100", "1.5");
    #endif

    #if TEST_NUM == 304
    SmallTown<Vampire<int>, int, 0, "23", Adult<int>>(Vampire<int>(100, 10), Adult<int>(100, 35));
    #endif

    #if TEST_NUM == 305
    SmallTown<Vampire<int>, int, 0, 23, Adult<int>>(Vampire<int>(100, 10), Adult<float>(100, 35));
    #endif

    #if TEST_NUM == 306
    SmallTown<Vampire<int>, int, 0, 23, Adult<int>>(Vampire<int>(100, 10), Adult<int>(100, 35), Adult<int>(100, 35));
    #endif

    #if TEST_NUM == 307
    SmallTown<Vampire<int>, int, 0, 23, Adult<int>, Adult<int>>(Vampire<int>(100, 10), Adult<int>(100, 35));
    #endif

    //#if TEST_NUM == 401
    //SmallTown<Vampire<int>, int, 0, 0, Adult<int>>(Vampire<int>(100, 10), Adult<int>(100, 35));
    //#endif

    #if TEST_NUM == 401
    SmallTown<Vampire<int>, int, 1, 0, Adult<int>>(Vampire<int>(100, 10), Adult<int>(100, 35));
    #endif

    #if TEST_NUM == 402
    Adult<int>(100, 15);
    #endif

    #if TEST_NUM == 403
    Adult<int>(100, 150);
    #endif

    #if TEST_NUM == 404
    Teenager<int>(100, 5);
    #endif

    #if TEST_NUM == 405
    Teenager<int>(100, 35);
    #endif

    #if TEST_NUM == 406
    Sheriff<int>(100, 15, 10);
    #endif

    #if TEST_NUM == 407
    Sheriff<int>(100, 150, 10);
    #endif

    #if TEST_NUM == 501 || TEST_NUM == 502 || TEST_NUM == 503
    streambuf* oldCoutStreamBuffer = cout.rdbuf();
    ostringstream capturedCout;
    cout.rdbuf(capturedCout.rdbuf());
    #endif

    #if TEST_NUM == 501
    auto town = SmallTown<Vampire<int>, int, 1, 3, Adult<int>>(Vampire<int>(100, 110), Adult<int>(100, 35));
    town.tick(1);
    town.tick(1);

    assert(capturedCout.str() == "MONSTER WON\n" || capturedCout.str() == "MONSTER WON");
    assert(get<2>(town.getStatus()) == 0);
    #endif

    #if TEST_NUM == 502
    auto town = SmallTown<Vampire<int>, int, 1, 3, Sheriff<int>>(Vampire<int>(100, 10), Sheriff<int>(100, 35, 110));
    town.tick(1);
    town.tick(1);

    assert(capturedCout.str() == "CITIZENS WON\n" || capturedCout.str() == "CITIZENS WON");
    assert(get<1>(town.getStatus()) == 0);
    #endif

    #if TEST_NUM == 503
    auto town = SmallTown<Vampire<int>, int, 1, 3, Sheriff<int>>(Vampire<int>(100, 110), Sheriff<int>(100, 35, 110));
    town.tick(1);
    town.tick(1);

    assert(capturedCout.str() == "DRAW\n" || capturedCout.str() == "DRAW");
    assert(get<1>(town.getStatus()) == 0);
    assert(get<2>(town.getStatus()) == 0);
    #endif

    #if TEST_NUM == 501 || TEST_NUM == 502 || TEST_NUM == 503
    cout.rdbuf(oldCoutStreamBuffer);
    #endif

    #if TEST_NUM == 504
    auto town = SmallTown<Vampire<int>, int, 1, 3, Sheriff<int>>(Vampire<int>(100, 10), Sheriff<int>(100, 35, 10));
    town.tick(1);

    assert(get<1>(town.getStatus()) == 90);
    assert(get<2>(town.getStatus()) == 1);
    #endif

    #if TEST_NUM == 505
    auto town = SmallTown<Vampire<int>, int, 0, 23, Sheriff<int>>(Vampire<int>(100, 1), Sheriff<int>(100, 35, 1));
    town.tick(1);
    town.tick(1);
    town.tick(2);
    town.tick(2);
    town.tick(2);
    town.tick(5);
    town.tick(1);
    town.tick(7);
    town.tick(1);

    assert(get<1>(town.getStatus()) == 95);
    assert(get<2>(town.getStatus()) == 1);
    #endif

    #if TEST_NUM == 506
    auto town = SmallTown<Vampire<int>, int, 0, 1, Sheriff<int>>(Vampire<int>(100, 1), Sheriff<int>(100, 35, 1));
    town.tick(2);
    town.tick(2);

    assert(get<1>(town.getStatus()) == 100);
    assert(get<2>(town.getStatus()) == 1);
    #endif

    #if TEST_NUM == 507
    auto town = SmallTown<Vampire<int>, int, 1, 3, Adult<int>, Adult<int>>(Vampire<int>(100, 90), Adult<int>(100, 35), Adult<int>(90, 35));
    town.tick(1);

    assert(get<1>(town.getStatus()) == 100);
    assert(get<2>(town.getStatus()) == 1);
    #endif

    #if TEST_NUM == 601
    auto vampire = Vampire<int>(100, 10);
    auto adult = Adult<int>(100, 35);

    attack(vampire, adult);

    assert(vampire.getHealth() == 100);
    assert(vampire.getAttackPower() == 10);
    assert(adult.getHealth() == 90);
    assert(adult.getAge() == 35);
    #endif

    #if TEST_NUM == 602
    auto vampire = Vampire<int>(100, 10);
    auto sheriff = Sheriff<int>(100, 35, 20);

    attack(vampire, sheriff);

    assert(vampire.getHealth() == 80);
    assert(vampire.getAttackPower() == 10);
    assert(sheriff.getHealth() == 90);
    assert(sheriff.getAge() == 35);
    assert(sheriff.getAttackPower() == 20);
    #endif

    return 0;
}
