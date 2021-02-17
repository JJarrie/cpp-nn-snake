#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(const std::vector<int>& sizing) {
    this->weights = std::vector<WeightMatrix>();

    std::vector<int>::const_iterator it;

    for (it = sizing.begin(); it != sizing.end() - 1; ++it) {
        this->weights.push_back(WeightMatrix(*(it + 1), *it));
    }
}

std::ostream& operator<<(std::ostream& out, const NeuralNetwork& n) {
    for (WeightMatrix weight : n.weights) {
        out << weight << std::endl;
    }

    return out;
}