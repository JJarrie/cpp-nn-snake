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
    std::vector<Snake>::iterator it = snakes.begin();

    for (it; it != snakes.end(); ++it) {
        (*it).nextFrame();
    }

    bestSnake->nextFrame();
}

void Population::nextGeneration() 
{
    std::vector<Snake> nextGeneration;

    electBestSnake();
    calculateFitnessSum();

    std::vector<Snake>::iterator it = snakes.begin();

    for (it; it != snakes.end(); ++it) {
        Snake parent = pickParent();
        Snake partner = pickParent();
        Snake children = parent.crossover(partner);
        children.mutate(mutationRate);
        nextGeneration.push_back(children);
    }

    snakes = nextGeneration;
    generation++;
}

void Population::electBestSnake() {
    double maxFitness = 0.0;

    std::vector<Snake>::iterator it = snakes.begin();
    std::vector<Snake>::iterator generationBestSnake;

    for (; it != snakes.end(); ++it) {
        double snakeFitness = (*it).fitness();
        if (snakeFitness > maxFitness) {
            maxFitness = snakeFitness;
            generationBestSnake = it;
        }
    }

    if (maxFitness > bestFitness) {
        bestGeneration = generation;
        bestFitness = maxFitness;
        bestScore = (*bestSnake).getScore();
        bestSnake = &(*generationBestSnake);
    }
}

Snake Population::pickParent() const {
    double p = Randomizer::get().pick(0, fitnessSum);
    double sum = 0.0;

    std::vector<Snake>::const_iterator it = snakes.cbegin();

    for (; it != snakes.cend(); ++it) {
        sum += (*it).fitness();

        if (sum > p) {
            return *(it);
        }
    }

    return snakes.front();
}

void Population::calculateFitnessSum() {
    fitnessSum = 0.0;
    std::vector<Snake>::const_iterator it = snakes.cbegin();

    for (it; it != snakes.cend(); ++it) {
        fitnessSum += (*it).fitness();
    }
}
