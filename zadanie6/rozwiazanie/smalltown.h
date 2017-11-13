#ifndef SMALLTOWN_H
#define SMALLTOWN_H

#include <iostream>
#include <vector>
#include <utility>
#include <memory>

#include "helper.h"
#include "citizen.h"
#include "monster.h"

class SmallTown {
    std::shared_ptr<Monster> monsters;
    // PW: brak wyodrebnionego Clock
    Time currentTime;
    Time maxTime;
    // PW: brak nazwanych typow...
    std::vector<std::shared_ptr<Citizen>> citizens;
    std::shared_ptr<BaseAttackTimeStrategy> strategy;
public:
    // ...i sygnatury sa bardzo dlugie.
    SmallTown(std::shared_ptr<Monster> &mons, Time curr, Time max,
              const std::vector<std::shared_ptr<Citizen>> &citizens, std::shared_ptr<BaseAttackTimeStrategy> &strat)
            : monsters(mons), currentTime(curr), maxTime(max), citizens(citizens), strategy(strat) {
    }

    Status getStatus() {
        size_t alive = 0;
        for (auto &cit : citizens)
            if (cit->isAlive()) ++alive;
        return Status(monsters->getName(), monsters->getHealth(), alive);
    }

    void tick(Time timeStep) {
        auto status = getStatus();
        if (status.getMonsterHealth() == 0 && status.getAliveCitizens() == 0) {
            std::cout << "DRAW" << std::endl;
            return;
        }
        if (status.getMonsterHealth() == 0) {
            std::cout << "CITIZENS WON" << std::endl;
            return;
        }
        if (status.getAliveCitizens() == 0) {
            std::cout << "MONSTER WON" << std::endl;
            return;
        }
        if (strategy->isAttackTime(currentTime)) {
            for (auto &cit : citizens) {
                cit->beAttacked(*monsters);
            }
        }

        currentTime += timeStep;
        currentTime %= (maxTime + 1);
    }

    class Builder {
        std::shared_ptr<BaseAttackTimeStrategy> baseStrategy;
        std::shared_ptr<Monster> monsterPtr;
        Time start;
        Time max;
        std::vector<std::shared_ptr<Citizen>> citizens;
    public:
        Builder() {
            baseStrategy = std::shared_ptr<FirstAttackTimeStrategy>(new FirstAttackTimeStrategy());
        }

        Builder &monster(const std::shared_ptr<Monster> &m) {
            monsterPtr = m;
            return (*this);
        }

        Builder &startTime(Time startT) {
            start = startT;
            return (*this);
        }

        Builder &maxTime(Time end) {
            max = end;
            return (*this);
        }

        Builder &citizen(const std::shared_ptr<Citizen> &cit) {
            for (auto &citiz : citizens) if (citiz == cit) return (*this);
            citizens.push_back(cit);
            return (*this);
        }

        Builder &strategy(const std::shared_ptr<BaseAttackTimeStrategy> &strat) {
            baseStrategy = strat;
            return (*this);
        }

        SmallTown build() {
            return SmallTown(monsterPtr, start, max, citizens, baseStrategy);
        }
    };
};

#endif //SMALLTOWN_H