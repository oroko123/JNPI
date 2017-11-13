// Opis testów
// grupa 1 przykład
// grupa 2 tworzenie obiektów
// grupa 3 poprawność funkcji składowych
// grupa 4 sprawdzanie ograniczeń na wiek mieszkańców i czas
// grupa 5 sprawdzenie logiki tick i podstawowego ataku
// grupa 6 sprawdzanie logiki zaawansowanego ataku

#if TEST_NUM == 100

#include <cassert>
#include "citizen.h"
#include "monster.h"
#include "smalltown.h"

int main(int argc, const char * argv[]) {
    auto groupOfMonsters = createGroupOfMonsters({
        createMummy(90, 1),
        createZombie(20, 1),
        createVampire(30, 1)
    });
    auto smallTown = SmallTown::Builder()
        .monster(groupOfMonsters)
        .startTime(3)
        .maxTime(27)
        .citizen(createSheriff(100, 35, 20))
        .citizen(createAdult(100, 21))
        .citizen(createTeenager(50, 14))
        .build();

    smallTown.tick(18);
    smallTown.tick(3);

    auto status = smallTown.getStatus();
    assert(status.getMonsterName() == "GroupOfMonsters");
    assert(status.getMonsterHealth() == 80);
    assert(status.getAliveCitizens() == 3);

    return 0;
}

#else

#include "citizen.h"
#include "monster.h"
#include "smalltown.h"
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void testTick(unsigned int max, bool attack = true) {
    auto town = SmallTown::Builder()
        .monster(createVampire(100, 10))
        .startTime(1).maxTime(max)
        .citizen(createSheriff(100, 35, 10))
	.build();
    town.tick(max - 1);
    town.tick(1);

    auto status = town.getStatus();
    assert(status.getMonsterHealth() == (attack ? 90 : 100));
}

int main() {
    #if TEST_NUM == 200
    Mummy(100, 10);
    Vampire(100, 10);
    Zombie(100, 10);
    #endif

    #if TEST_NUM == 201
    Adult(100, 35);
    Teenager(100, 15);
    Sheriff(100, 35, 10);
    #endif

    #if TEST_NUM == 202
    auto monster = createGroupOfMonsters({createVampire(100, 10)});
    #endif

    #if TEST_NUM == 203
    auto monster = createGroupOfMonsters({createZombie(100, 10)});
    #endif

    #if TEST_NUM == 204
    auto monster = createGroupOfMonsters({createMummy(100, 10)});
    #endif

    #if TEST_NUM == 205
    auto monster = createGroupOfMonsters({
        createZombie(100, 10),
        createVampire(100, 10),
        createMummy(100, 10)});
    #endif

    #if TEST_NUM == 206 // Ma nie być bezparametrowego konstruktora.
    Teenager();
    #endif

    #if TEST_NUM == 207 // Ma nie być bezparametrowego konstruktora.
    Sheriff();
    #endif

    #if TEST_NUM == 208 // Ma nie być bezparametrowego konstruktora.
    Adult();
    #endif

    #if TEST_NUM == 300
    Adult adult(100, 35);
    assert(adult.getHealth() == 100);
    assert(adult.getAge() == 35);
    #endif

    #if TEST_NUM == 301
    Teenager teen(100, 14);
    assert(teen.getHealth() == 100);
    assert(teen.getAge() == 14);
    #endif

    #if TEST_NUM == 302
    Sheriff citizen(100, 35, 10);
    assert(citizen.getHealth() == 100);
    assert(citizen.getAge() == 35);
    assert(citizen.getAttackPower() == 10);
    #endif

    #if TEST_NUM == 303
    Mummy monster(100, 10);
    assert(monster.getHealth() == 100);
    assert(monster.getAttackPower() == 10);
    #endif

    #if TEST_NUM == 304
    Zombie monster(100, 10);
    assert(monster.getHealth() == 100);
    assert(monster.getAttackPower() == 10);
    #endif

    #if TEST_NUM == 305
    Vampire monster(100, 10);
    assert(monster.getHealth() == 100);
    assert(monster.getAttackPower() == 10);
    #endif

    #if TEST_NUM == 306
    auto smallTown = SmallTown::Builder()
        .monster(createMummy(100, 1))
	.startTime(3).maxTime(27)
	.citizen(createSheriff(100, 35, 20))
        .citizen(createAdult(100, 21))
        .citizen(createTeenager(50, 14))
        .build();

    auto status = smallTown.getStatus();
    assert(status.getMonsterName() == "Mummy");
    assert(status.getMonsterHealth() == 100);
    assert(status.getAliveCitizens() == 3);
    #endif

    #if TEST_NUM == 307
    auto smallTown = SmallTown::Builder()
        .monster(createZombie(100, 1))
        .startTime(3).maxTime(27)
        .citizen(createSheriff(100, 35, 20))
        .build();

    auto status = smallTown.getStatus();
    assert(status.getMonsterName() == "Zombie");
    assert(status.getMonsterHealth() == 100);
    assert(status.getAliveCitizens() == 1);
    #endif

    #if TEST_NUM == 308
    auto smallTown = SmallTown::Builder()
        .monster(createVampire(100, 1))
        .startTime(3).maxTime(27)
        .citizen(createSheriff(100, 35, 20))
        .citizen(createAdult(100, 21))
        .build();

    auto status = smallTown.getStatus();
    assert(status.getMonsterName() == "Vampire");
    assert(status.getMonsterHealth() == 100);
    assert(status.getAliveCitizens() == 2);
    #endif

    #if TEST_NUM == 309
    auto groupOfMonsters = createGroupOfMonsters({
        createMummy(100, 1),
        createZombie(50, 1),
        createVampire(25, 1)});
    auto smallTown = SmallTown::Builder()
        .monster(groupOfMonsters)
        .startTime(3).maxTime(27)
        .citizen(createSheriff(100, 35, 20))
        .citizen(createAdult(100, 21))
        .citizen(createTeenager(50, 14))
        .build();

    auto status = smallTown.getStatus();
    assert(status.getMonsterName() == "GroupOfMonsters");
    assert(status.getMonsterHealth() == 175);
    assert(status.getAliveCitizens() == 3);
    #endif

    #if TEST_NUM == 310
    auto adult = Adult(100, 35);
    adult.takeDamage(10);
    assert(adult.getHealth() == 90);
    #endif

    #if TEST_NUM == 311
    auto vampire = Vampire(100, 10);
    vampire.takeDamage(10);
    assert(vampire.getHealth() == 90);
    #endif

    #if TEST_NUM == 312 // Monster nie może mieć getAge.
    Vampire monster(100, 10);
    monster.getAge();
    #endif

    #if TEST_NUM == 313 // Monster nie może mieć getAge.
    Mummy monster(100, 10);
    monster.getAge();
    #endif

    #if TEST_NUM == 314 // Monster nie może mieć getAge.
    Zombie monster(100, 10);
    monster.getAge();
    #endif

    #if TEST_NUM == 315 // Adult nie może mieć getAttackPower.
    Adult adult(100, 20);
    adult.getAttackPower();
    #endif

    #if TEST_NUM == 316 // Teenager nie może mieć getAttackPower.
    Teenager teen(100, 14);
    teen.getAttackPower();
    #endif

    #if TEST_NUM == 400
    Sheriff(100, 100, 100);
    #endif

    #if TEST_NUM == 401 // Błędne wywołanie konstruktora.
    Sheriff(100, 17, 10);
    #endif

    #if TEST_NUM == 402 // Błędne wywołanie konstruktora.
    Sheriff(100, 101, 10);
    #endif

    #if TEST_NUM == 403 // Błędne wywołanie konstruktora.
    Adult(100, 17);
    #endif

    #if TEST_NUM == 404 // Błędne wywołanie konstruktora.
    Adult(100, 101);
    #endif

    #if TEST_NUM == 405 // Błędne wywołanie konstruktora.
    Teenager(100, 18);
    #endif

    #if TEST_NUM == 406 // Błędne wywołanie konstruktora.
    Teenager(100, 10);
    #endif

    #if TEST_NUM == 407 // Błędne wartości parametrów.
    auto smallTown = SmallTown::Builder()
        .monster(createVampire(100, 1))
        .startTime(1).maxTime(0)
        .citizen(createAdult(100, 21))
        .build();
    #endif

    #if TEST_NUM == 500 || TEST_NUM == 501 || TEST_NUM == 502
    streambuf* oldCoutStreamBuffer = cout.rdbuf();
    ostringstream capturedCout;
    cout.rdbuf(capturedCout.rdbuf());
    #endif

    #if TEST_NUM == 500
    auto town = SmallTown::Builder()
	.monster(createVampire(100, 110))
	.startTime(1).maxTime(3)
	.citizen(createAdult(100, 21))
	.build();
    town.tick(2);
    town.tick(1);
    town.tick(1);

    assert(capturedCout.str() == "MONSTER WON\n" || capturedCout.str() == "MONSTER WON");
    assert(town.getStatus().getAliveCitizens() == 0);
    #endif

    #if TEST_NUM == 501
    auto town = SmallTown::Builder()
        .monster(createVampire(100, 10))
        .startTime(1).maxTime(3)
        .citizen(createSheriff(100, 21, 110))
        .build();
    town.tick(2);
    town.tick(1);
    town.tick(1);

    assert(capturedCout.str() == "CITIZENS WON\n" || capturedCout.str() == "CITIZENS WON");
    assert(town.getStatus().getMonsterHealth() == 0);
    #endif

    #if TEST_NUM == 502
    auto town = SmallTown::Builder()
        .monster(createVampire(100, 110))
        .startTime(1).maxTime(3)
        .citizen(createSheriff(100, 21, 110))
        .build();
    town.tick(2);
    town.tick(1);
    town.tick(1);

    assert(capturedCout.str() == "DRAW\n" || capturedCout.str() == "DRAW");
    auto status = town.getStatus();
    assert(status.getMonsterHealth() == 0);
    assert(status.getAliveCitizens() == 0);
    #endif

    #if TEST_NUM == 500 || TEST_NUM == 501 || TEST_NUM == 502
    cout.rdbuf(oldCoutStreamBuffer);
    #endif

    #if TEST_NUM == 503
    testTick(3);
    #endif

    #if TEST_NUM == 504
    testTick(7, false);
    #endif

    #if TEST_NUM == 505
    testTick(13);
    #endif

    #if TEST_NUM == 506
    testTick(3 * 7, false);
    #endif

    #if TEST_NUM == 507
    testTick(13 * 7, false);
    #endif

    #if TEST_NUM == 508
    testTick(3 * 6);
    #endif

    #if TEST_NUM == 509
    testTick(13 * 6);
    #endif

    #if TEST_NUM == 600
    auto town = SmallTown::Builder()
        .monster(createVampire(100, 10))
        .startTime(1).maxTime(23)
        .citizen(createSheriff(100, 35, 1))
        .citizen(createSheriff(100, 35, 1))
	.build();
    for (unsigned i = 0; i < 27; i++) town.tick(1);

    auto status = town.getStatus();
    assert(status.getMonsterHealth() == 84);
    assert(status.getAliveCitizens() == 2);
    #endif

    #if TEST_NUM == 601
    auto town = SmallTown::Builder()
        .monster(createVampire(100, 110))
        .startTime(1).maxTime(3)
        .citizen(createSheriff(100, 35, 1))
        .citizen(createSheriff(100, 35, 1))
        .build();
    town.tick(2);
    town.tick(1);

    auto status = town.getStatus();
    assert(status.getMonsterHealth() == 98);
    assert(status.getAliveCitizens() == 0);
    #endif

    #if TEST_NUM == 602
    auto town = SmallTown::Builder()
        .monster(createVampire(100, 110))
        .startTime(1).maxTime(3)
        .citizen(createSheriff(100, 35, 110))
        .citizen(createSheriff(100, 35, 1))
        .build();
    town.tick(2);
    town.tick(1);

    auto status = town.getStatus();
    assert(status.getMonsterHealth() == 0);
    assert(status.getAliveCitizens() == 1);
    #endif

    #if TEST_NUM == 603
    auto town = SmallTown::Builder()
        .monster(createVampire(100, 1))
        .startTime(1).maxTime(3)
        .citizen(createSheriff(100, 35, 110))
        .citizen(createSheriff(100, 35, 1))
        .build();
    town.tick(2);
    town.tick(1);

    auto status = town.getStatus();
    assert(status.getMonsterHealth() == 0);
    assert(status.getAliveCitizens() == 2);
    #endif

    #if TEST_NUM == 604
    auto monsters = createGroupOfMonsters({
        createVampire(100, 10),
        createZombie(50, 5),
        createMummy(10, 1)});
    auto town = SmallTown::Builder()
        .monster(monsters)
        .startTime(1).maxTime(3)
        .citizen(createSheriff(16, 35, 10))
        .citizen(createSheriff(15, 35, 40))
        .citizen(createSheriff(11, 35, 40))
        .build();
    town.tick(2);
    town.tick(1);

    auto status = town.getStatus();
    assert(status.getMonsterHealth() == 10);
    assert(status.getAliveCitizens() == 1);
    #endif

    #if TEST_NUM == 605
    auto monsters = createGroupOfMonsters({
        createVampire(100, 10),
        createZombie(50, 5),
        createMummy(10, 1)});
    auto town = SmallTown::Builder()
        .monster(monsters)
        .startTime(1).maxTime(3)
        .citizen(createSheriff(17, 35, 1))
        .build();
    town.tick(2);
    town.tick(1);

    auto status = town.getStatus();
    assert(status.getMonsterHealth() == 157);
    assert(status.getAliveCitizens() == 1);
    #endif

    return 0;
}

#endif
