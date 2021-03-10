#ifndef __POPULATION_HPP__
#define __POPULATION_HPP__

#include <vector>
#include <iterator>

#include "Snake.hpp"

class Population {
    private:
        double bestFitness;
        int bestGeneration;
        int bestScore;
        Snake* bestSnake;
        double fitnessSum;
        int generation;
        double mutationRate;
        std::vector<Snake> snakes;

        void electBestSnake();
        Snake pickParent() const;
        void calculateFitnessSum();

    public:
        Population(
            const Vector& boardSize, 
            const double& mutationRate, 
            const int& populationSize, 
            const std::vector<int>& sizing
        );
        bool isGenerationFinish() const;
        void nextCycle();
        void nextGeneration();
};

#endif