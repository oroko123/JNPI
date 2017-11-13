#ifndef CITIZEN_H
#define CITIZEN_H

#include <cassert>
#include <memory>

#include "helper.h"
#include "monster.h"

class Citizen : public virtual Creature{
protected:
    Age age;
public:
    Citizen(HealthPoints h, Age a) :Creature(h), age(a) { }

    Age getAge() const {
        return age;
    }

    virtual void beAttacked(Monster &monster) {
        takeDamage(monster.getAttackPower());
    }
};

class Teenager : public Citizen {
public :
    Teenager(HealthPoints h, Age a)
            :Creature(h), Citizen(h, a) {
        static const int minAge = 11;
        static const int maxAge = 17;
        assert(a >= minAge && a <= maxAge);
    }
};

class Adult : public Citizen {
public :
    Adult(HealthPoints h, Age a)
            :Creature(h), Citizen(h, a) {
        static const int minAge = 18;
        static const int maxAge = 100;
        assert(a >= minAge && a <= maxAge);
    }
};

class Sheriff : public Adult, public Attacker {
public:
    Sheriff(HealthPoints h, Age a, AttackPower att)
            :Creature(h), Adult(h, a), Attacker(h, att) {
        assert(att >= 0);
    }

    virtual void beAttacked(Monster &monster) override {
        AttackPower myDamage = this->getAttackPower();
        AttackPower monsterDamage = monster.getAttackPower();

        monster.takeDamage(myDamage);
        takeDamage(monsterDamage);
    }
};

std::shared_ptr<Teenager> createTeenager(HealthPoints health, Age age) {
    return std::shared_ptr<Teenager>(new Teenager(health, age));
}

std::shared_ptr<Adult> createAdult(HealthPoints health, Age age) {
    return std::shared_ptr<Adult>(new Adult(health, age));
}

std::shared_ptr<Sheriff> createSheriff(HealthPoints health, Age age, AttackPower attack) {
    return std::shared_ptr<Sheriff>(new Sheriff(health, age, attack));
}

#endif // CITIZEN_H