#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <ctime>
#include <random>

class Random
{
    public:

        static void Initialize()
        {
            Generator.seed(time(0));
        }

        static int Get(int min, int max)
        {
            return std::uniform_int_distribution<int>(min, max)(Generator);
        }

    private:

        static std::mt19937 Generator;
};

#endif // RANDOM_H
