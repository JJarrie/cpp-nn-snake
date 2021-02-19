#include "Randomizer.hpp"

Randomizer::Randomizer(): gen(std::random_device()()) {}

Randomizer Randomizer::r;

double Randomizer::pick(double a, double b) {
    std::uniform_real_distribution<double> dis(a, b);
    return dis(gen);
}

int Randomizer::pickInt(int a, int b) {
    std::uniform_real_distribution<double> dis(a, b);

    return static_cast<int>(std::floor(dis(gen)));
}

double Randomizer::pickNorm(double a, double b) {
    std::normal_distribution<double> dis(a, b);

    return dis(gen);
}