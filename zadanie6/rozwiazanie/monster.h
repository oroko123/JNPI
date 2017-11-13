#ifndef MONSTER_H
#define MONSTER_H

#include <vector>
#include <memory>

#include "helper.h"
#include "citizen.h"

class Monster : public Attacker {
public:

    Monster(HealthPoints h, AttackPower att)
            : Creature(h), Attacker(h, att) { }

    virtual std::string getName() const = 0;

};

class Zombie : public Monster {
public:
    // PW: niepoprawne wywoływanie konstruktorow (Creature niepotrzebnie)
    Zombie(HealthPoints h, AttackPower att)
            : Creature(h), Monster(h, att) { }

    virtual std::string getName() const override {
        return "Zombie";
    }
};

class Mummy : public Monster {
public:
    // PW: niepoprawne wywoływanie konstruktorow (Creature niepotrzebnie)
    Mummy(HealthPoints h, AttackPower att)
            : Creature(h), Monster(h, att) { }

    virtual std::string getName() const override {
        return "Mummy";
    }
};

class Vampire : public Monster {
public:
    // PW: niepoprawne wywoływanie konstruktorow (Creature niepotrzebnie)
    Vampire(HealthPoints h, AttackPower att)
            : Creature(h), Monster(h, att) { }

    virtual std::string getName() const override {
        return "Vampire";
    }
};

// PW: niepotrzebne dziedziczenie health/attack power z Monster
class GroupOfMonsters : public Monster {
    std::vector<std::shared_ptr<Monster> > monsters;
public:
    // PW: niepoprawne wywoływanie konstruktorow (Creature niepotrzebnie)
    // PW: monsters powinno byc przekazywane przez const&
    GroupOfMonsters(std::vector<std::shared_ptr<Monster> > monsters)
            : Creature(1), Monster(1, 1), monsters(monsters) { }

    GroupOfMonsters(std::initializer_list<std::shared_ptr<Monster> > monsters)
            : Creature(1), Monster(1, 1), monsters(monsters) { }

    virtual HealthPoints getHealth() const override {
        HealthPoints sum = 0;
        for (auto m : monsters) {
            sum += m->getHealth();
        }
        return sum;
    }

    virtual AttackPower getAttackPower() const override {
        AttackPower sum = 0;
        for (auto m : monsters) {
            sum += m->getAttackPower();
        }
        return sum;
    }

    virtual void takeDamage(AttackPower attack) override {
        for (auto m : monsters) {
            m->takeDamage(attack);
        }
    }

    virtual std::string getName() const override {
        return "GroupOfMonsters";
    }
};

// PW: bedzie powtorzona definicja i blad linkera, jesli plik zostanie wlaczony do dwoch roznych plikow zrodlowych .cxx
std::shared_ptr<Mummy> createMummy(HealthPoints h, AttackPower att) {
    return std::shared_ptr<Mummy>(new Mummy(h, att));
}

std::shared_ptr<Vampire> createVampire(HealthPoints h, AttackPower att) {
    return std::shared_ptr<Vampire>(new Vampire(h, att));
}

std::shared_ptr<Zombie> createZombie(HealthPoints h, AttackPower att) {
    return std::shared_ptr<Zombie>(new Zombie(h, att));
}

std::shared_ptr<GroupOfMonsters> createGroupOfMonsters(std::vector<std::shared_ptr<Monster> > monsters) {
    return std::shared_ptr<GroupOfMonsters>(new GroupOfMonsters(monsters));
}

std::shared_ptr<GroupOfMonsters> createGroupOfMonsters(std::initializer_list<std::shared_ptr<Monster> > monsters) {
    return std::shared_ptr<GroupOfMonsters>(new GroupOfMonsters(monsters));
}

#endif //MONSTER_H