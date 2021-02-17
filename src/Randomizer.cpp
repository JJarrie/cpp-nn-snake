#include "Randomizer.hpp"

Randomizer::Randomizer(): gen(std::random_device()()) {}

double Randomizer::pick(double a, double b) {
    std::uniform_real_distribution<double> dis(a, b);
    return dis(gen);
}

double Randomizer::pickNorm(double a, double b) {
    std::normal_distribution<double> dis(a, b);

    return dis(gen);
}