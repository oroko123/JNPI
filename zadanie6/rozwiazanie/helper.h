#ifndef HELPER_H
#define HELPER_H

#include <string>

using Age = unsigned int;
using HealthPoints = unsigned int;
using AttackPower = unsigned int;
using Time = unsigned int;

class Status {
    std::string monsName;
    HealthPoints monsHealth;
    size_t aliveCitizens;
public:
    Status(const std::string &monsName, HealthPoints monHealth, size_t aliveCit)
            : monsName(monsName), monsHealth(monHealth), aliveCitizens(aliveCit) { }

    const std::string &getMonsterName() const {
        return monsName;
    }

    HealthPoints getMonsterHealth() const {
        return monsHealth;
    }

    size_t getAliveCitizens() const {
        return aliveCitizens;
    }

};

class Creature {
protected:
    HealthPoints health;
public:

    Creature(HealthPoints h) : health(h) {
        assert(h > 0);
    }
    // PW: brak wirtualnych destruktorow

    virtual HealthPoints getHealth() const {
        return health;
    }

    virtual bool isAlive() const {
        return health > 0;
    }

    virtual void takeDamage(AttackPower attack) {
        health -= attack > health ? health : attack;
    }
};

class Attacker : public virtual Creature {
protected:
    AttackPower attack;
public:
    Attacker(HealthPoints h, AttackPower att) : Creature(h), attack(att) {
        assert(att > 0);
    }

    virtual AttackPower getAttackPower() const {
        return isAlive() ? attack : 0;
    }
};


class BaseAttackTimeStrategy {
public:
    virtual bool isAttackTime(Time t) const = 0;
};

class NeverAttackTimeStrategy : public BaseAttackTimeStrategy {
    NeverAttackTimeStrategy() = default;

public:
    static NeverAttackTimeStrategy &getInstance() {
        static NeverAttackTimeStrategy instance;
        return instance;
    }

    virtual bool isAttackTime(Time t) const { return false; }
};

class FirstAttackTimeStrategy : public BaseAttackTimeStrategy {
public:
    static FirstAttackTimeStrategy &getInstance() {
        static FirstAttackTimeStrategy instance;
        return instance;
    }

    virtual bool isAttackTime(Time t) const {
        return ((t % 3 == 0) || (t % 13 == 0)) && (t % 7 != 0);
    }
};

#endif //HELPER_H