#ifndef __SNAKE_HPP__
#define __SNAKE_HPP__

#include <vector>
#include <cmath>
#include <algorithm>

#include "SquareValue.hpp"
#include "Point.hpp"
#include "NeuralNetwork.hpp"
#include "Vector.hpp"
#include "Direction.hpp"

class Snake {
    private:
        int score;
        int lifetime;
        int timeleft;
        Vector boardSize;
        NeuralNetwork neuralNetwork;
        std::vector<Point> snake;
        std::vector<SquareValue> grid;
        Point foodPosition;
        Direction direction;

        Vector getDirectionVector() const;
        void gainTimeleft();
        void generateFood();

    public:
        Snake(const Vector& boardSize, const NeuralNetwork& neuralNetwork);
        bool isFinish() const;
        void nextFrame();
};

#endif