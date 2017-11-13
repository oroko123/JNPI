#ifndef MONSTER_H
#define MONSTER_H

#include "citizen.h"

template<typename T, const char *NAME>
class Monster
{
    static_assert(std::is_arithmetic<T>::value, "T must be arithmetic!");

    T health, attackPower;

public:
    Monster(T _health, T _attackPower) : health(_health), attackPower(_attackPower) { }

    typedef T valueType;

    const char* getName() const { return NAME; }

    T getHealth() const { return health; }

    T getAttackPower() const { return attackPower; }

    void takeDamage(T damage)
    {
        if (health > damage)
            health -= damage;
        else
            health -= health;
    }

};

char ZOMBIE_NAME[] = "Zombie";
char MUMMY_NAME[] = "Mummy";
char VAMPIRE_NAME[] = "Vampire";

template<typename T>
using Zombie = Monster<T, ZOMBIE_NAME>;

template<typename T>
using Mummy = Monster<T, MUMMY_NAME>;

template<typename T>
using Vampire = Monster<T, VAMPIRE_NAME>;

template<typename M, typename U>
void attack(M& monster, U& victim)
{
    victim.takeDamage(monster.getAttackPower());
}

template<typename M, typename T>
void attack(M& monster, Sheriff<T>& victim)
{
    victim.takeDamage(monster.getAttackPower());
    monster.takeDamage(victim.getAttackPower());
}

#endif //MONSTER_H
