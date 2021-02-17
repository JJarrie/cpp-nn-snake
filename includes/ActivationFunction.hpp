#ifndef __ACTIVATION_FUNCTION__
#define __ACTIVATION_FUNCTION__

#include <algorithm>
#include <cmath>

double relu(double n) {
    return std::max(0.0, n);
}

double sigmoid(double n) {
    return 1 / (1 + exp(-n));
}

#endif