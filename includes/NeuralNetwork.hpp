#ifndef __NEURAL_NETWORK_HPP__
#define __NEURAL_NETWORK_HPP__

#include <iostream>
#include <vector>
#include <iterator>

#include "WeightMatrix.hpp"

class NeuralNetwork {
    private:
        std::vector<WeightMatrix> weights;
    public:
        explicit NeuralNetwork(const std::vector<int>& sizing);

        friend std::ostream& operator<<(std::ostream& out, const NeuralNetwork& n);
};

#endif