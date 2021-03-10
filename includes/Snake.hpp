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
        Direction::CardinalDirection direction;

        bool pointIsOutbound(const Point& p) const;
        bool pointIsInBody(const Point& p) const;
        void gainTimeleft();
        void generateFood();
        void takeDecision();
        std::vector<double> vision() const;
        std::vector<double> lookInDirection(const Direction::CardinalDirection& d) const;

    public:
        explicit Snake(const Vector& boardSize, const NeuralNetwork& neuralNetwork);
        Snake(const Snake& snake);
        bool isFinish() const;
        void nextFrame();
        double fitness() const;
        int getScore() const;
        Snake crossover(const Snake& partner) const;
        void mutate(const double& rate);
};

#endif