#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(const std::vector<int>& sizing) {
    this->weights = std::vector<WeightMatrix>();

    std::vector<int>::const_iterator it;

    for (it = sizing.begin(); it != sizing.end() - 1; ++it) {
        this->weights.push_back(WeightMatrix(*it + 1, *(it + 1)));
    }
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork& nn) {
    weights = std::vector<WeightMatrix>(nn.weights);
}

void NeuralNetwork::mutate(const double& rate) {
    std::vector<WeightMatrix>::iterator it;
    for (it = weights.begin(); it != weights.end(); ++it) {
        (*it).mutate(rate);
    }
}

NeuralNetwork NeuralNetwork::crossover(const NeuralNetwork& partner) const {
    NeuralNetwork nn = *this;
    std::vector<WeightMatrix> crossed;

    for (size_t i = 0; i < nn.weights.size(); ++i) {
        crossed.push_back(nn.weights[i].crossover(partner.weights[i]));
    }

    nn.weights = std::vector<WeightMatrix>(crossed);

    return nn;

}

std::vector<double> NeuralNetwork::output(const std::vector<double>& input) const {
    WeightMatrix m = WeightMatrix(input);

    for (size_t i = 0; i < this->weights.size() - 1; ++i) {
        m = this->weights[i] * m;
        m.activate(relu);
        m = WeightMatrix(m.getVector());
    }

    WeightMatrix x = *(weights.end() - 1);

    m = x * m;
    m.activate(relu);

    return m.getVector();
}

std::ostream& operator<<(std::ostream& out, const NeuralNetwork& n) {
    for (WeightMatrix weight : n.weights) {
        out << weight << std::endl;
    }

    return out;
}