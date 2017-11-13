#ifndef SMALLTOWN_H
#define SMALLTOWN_H

#include <iostream>
#include <tuple>
#include <utility>
#include <array>
#include <set>
#include "monster.h"
#include "citizen.h"


template<typename M, typename U, U TIME_START, U TIME_END, typename... C>
class SmallTown
{
    static_assert(std::is_arithmetic<U>::value, "Time must be arithmetic");
    static_assert((TIME_START >= 0 && TIME_END > 0 && TIME_START <= TIME_END), "Time is incorrect");

    M monster;
    U time;
    std::tuple<C...> citizens;
    size_t aliveCitizens;

	template<typename TYPE, int T>
	class StaticFibonacci
	{
	private:
		static constexpr TYPE howManyFibonacciNumbers(TYPE max)
		{
		    TYPE a = 1, b = 0, count = 0, temp = 0;

		    while (a <= max)
		    {
		        temp = a;
		        a = a+b;
		        b = temp;
		        ++count;
		    }
		    return count;
		}

		static constexpr TYPE maxFibonacciLowerOrEqualThan(TYPE max)
		{
		    TYPE a = 1, b = 0, temp = 0;

		    while (a <= max)
		    {
		        temp = a;
		        a = a+b;
		        b = temp;
		    }
		    return b;
		}

		template<TYPE MAX, TYPE N, TYPE K, TYPE... S>
		struct MakeSequenceImp : MakeSequenceImp<MAX, N+K, N, K, S...> {};

		template<TYPE MAX, TYPE... S>
		struct MakeSequenceImp<MAX, MAX, S...>
		{
			using type = std::index_sequence<MAX, S...>;
		};

		template<TYPE MAX, TYPE N, TYPE K>
		using FibonacciGenerator = typename MakeSequenceImp<MAX, N, K>::type;

		template<std::size_t... Indices>
		static constexpr std::array<TYPE, sizeof...(Indices)> makeArrayHelper(std::index_sequence<Indices...>)
		{
		    return {{ Indices... }};
		}

		template<TYPE N>
		static constexpr std::array<TYPE, howManyFibonacciNumbers(N)> makeArray()
		{
		    return makeArrayHelper(FibonacciGenerator<maxFibonacciLowerOrEqualThan(N), 1, 1>{});
		}

	public:
		static constexpr std::array<TYPE, howManyFibonacciNumbers(T)> array = makeArray<T>();
	};

    static constexpr auto fibonacciArray = StaticFibonacci<U, TIME_END>::array;
   	std::set<U> fibonacciNumbers;

public:

    SmallTown(M const& _monster, C... _citizens) :
            monster(_monster), time(TIME_START), citizens(_citizens...)
    {
        aliveCitizens = sizeof...(_citizens);
        // doesn't compile without it (tho they will be already generated since wee have this pair
        // (U, TIME_END) in class field)
        static constexpr auto fibonacciArray = StaticFibonacci<U, TIME_END>::array;
        fibonacciNumbers = std::set<U>(fibonacciArray.begin(), fibonacciArray.end());
    }

    std::tuple<std::string, typename M::valueType, size_t> getStatus()
    {
        return std::make_tuple(monster.getName(), monster.getHealth(), aliveCitizens);
    }

    void tick(U timeStep)
    {
        computeResult();

        if (!isMonsterDead() && isAttackTime())
	        attackAll();

        time = (time + timeStep) % (TIME_END + 1);
    }

private:

	bool isAttackTime() const
	{
		return (fibonacciNumbers.find(time) != fibonacciNumbers.end());
	}


    bool isMonsterDead() const {
        return monster.getHealth() == 0;
    }

    void computeResult()
    {
        if (isMonsterDead())
        {
            if (aliveCitizens == 0)
                std::cout << "DRAW\n";
            else
                std::cout << "CITIZENS WON\n";
        }
        else if (aliveCitizens == 0)
            std::cout << "MONSTER WON\n";
    }

    void attackAll()
    {
        attackAllHelper<0, C...>();
    }

    template<size_t N>
    void attackOne()
    {
        auto& citizen = std::get<N>(citizens);

        if (citizen.getHealth() > 0)
        {
            attack(monster, citizen);
            if (citizen.getHealth() == 0)
                --aliveCitizens;
        }

    }

    template<int>
    void attackAllHelper() { }

    template<int, typename Arg, typename...Args>
    void attackAllHelper()
    {
        attackAllHelper<0, Args...>();
        attackOne<sizeof...(Args)>();
    }
};

#endif