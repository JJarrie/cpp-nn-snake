#include "Population.hpp"

Population::Population(
    const Vector& boardSize,
    const double& mutationRate,
    const int& populationSize,
    const std::vector<int>& sizing
) : mutationRate(mutationRate),
    fitnessSum(0.0),
    generation(1),
    bestGeneration(0),
    bestScore(0),
    bestFitness(0.0)
{
    snakes = std::vector<Snake>();

    for (size_t i = 0; i < populationSize; ++i) {
        NeuralNetwork nn(sizing);
        snakes.push_back(Snake(boardSize, nn));
    }

    bestSnake = &(snakes.front());
}

bool Population::isGenerationFinish() const 
{
    std::vector<Snake>::const_iterator it = snakes.cbegin();

    for (it; it != snakes.cend(); ++it) {
        if (!(*it).isFinish()) {
            return false;
        }
    }

    if (!bestSnake->isFinish()) {
        return false;
    }

    return true;
}

void Population::nextCycle() 
{

}

void Population::nextGeneration() 
{

}

void Population::electBestSnake() {

}

Snake Population::pickParent() const {
    return snakes[0];
}