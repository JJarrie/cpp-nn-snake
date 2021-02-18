#ifndef __SNAKE_HPP__
#define __SNAKE_HPP__

#include <vector>
#include <cmath>
#include <algorithm>

#include "SquareValue.hpp"
#include "Point.hpp"
#include "NeuralNetwork.hpp"
#include "Vector.hpp"

class Snake {
    private:
        Vector boardSize;
        NeuralNetwork neuralNetwork;
        std::vector<Point> snake;
        std::vector<SquareValue> grid;
        int score;
        Randomizer randomizer;
        Point foodPosition;

    public:
        Snake(const Vector& boardSize, const NeuralNetwork& neuralNetwork);
        void generateFood();
        bool isFinish() const;
        void nextFrame();
};

#endif