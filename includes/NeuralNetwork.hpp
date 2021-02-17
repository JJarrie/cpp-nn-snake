#ifndef __NEURAL_NETWORK_HPP__
#define __NEURAL_NETWORK_HPP__

#include <iostream>
#include <vector>
#include <iterator>

#include "WeightMatrix.hpp"
#include "ActivationFunction.hpp"

class NeuralNetwork {
    private:
        std::vector<WeightMatrix> weights;
    public:
        explicit NeuralNetwork(const std::vector<int>& sizing);
        NeuralNetwork(const NeuralNetwork& nn);
        void mutate(const double& rate);
        std::vector<double> output(const std::vector<double>& input) const;
        NeuralNetwork crossover(const NeuralNetwork& partner) const;

        friend std::ostream& operator<<(std::ostream& out, const NeuralNetwork& n);
};

#endif