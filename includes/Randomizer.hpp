#ifndef __RANDOMIZE_HPP__
#define __RANDOMIZE_HPP__

#include <random>

class Randomizer {
    private:
        std::mt19937 gen;
    public:
        Randomizer();
        double pick(double a, double b);
        double pickNorm(double a, double b);
};

#endif