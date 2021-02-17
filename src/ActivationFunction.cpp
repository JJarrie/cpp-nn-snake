#include "ActivationFunction.hpp"

double relu(double n) {
    return std::max(0.0, n);
}

double sigmoid(double n) {
    return 1 / (1 + exp(-n));
}