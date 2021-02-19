#ifndef __RANDOMIZE_HPP__
#define __RANDOMIZE_HPP__

#include <random>

class Randomizer {
    private:
        std::mt19937 gen;
        static Randomizer r;

        Randomizer();

    public:
        Randomizer(const Randomizer&) = delete;
        Randomizer& operator=(const Randomizer&) = delete;
        double pick(double a, double b);
        int pickInt(int a, int b);
        double pickNorm(double a, double b);

        static Randomizer& get() noexcept {
            return r;
        };
};

#endif