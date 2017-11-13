#ifndef CITIZEN_H
#define CITIZEN_H

#include <cassert>
#include <type_traits>


template<typename T, int MIN_AGE, int MAX_AGE, bool CAN_SHOOT>
class Citizen
{
    static_assert(std::is_arithmetic<T>::value, "T must be arithmetic!");

    T health, age, attackPower;

public:

    template<bool U = CAN_SHOOT, typename = typename std::enable_if<!U>::type>
    Citizen(T _health, T _age) : health(_health), age(_age)
    {
        assert(age >= MIN_AGE && age <= MAX_AGE);
    }

    template<bool U = CAN_SHOOT, typename = typename std::enable_if<U>::type>
    Citizen(T _health, T _age, T _attackPower) :
            health(_health), age(_age), attackPower(_attackPower)
    {
        assert(age >= MIN_AGE && age <= MAX_AGE);
    }

    T getHealth() const { return health; }

    T getAge() const { return age; }

    template<bool U = CAN_SHOOT, typename = typename std::enable_if<U>::type>
    T getAttackPower() const { return attackPower; }

    void takeDamage(T damage)
    {
        if (health > damage)
            health -= damage;
        else
            health -= health;
    }
};

template<typename T>
using Teenager = Citizen<T, 11, 17, false>;

template<typename T>
using Adult = Citizen<T, 18, 100, false>;

template<typename T>
using Sheriff = Citizen<T, 18, 100, true>;


#endif //CITIZEN_H