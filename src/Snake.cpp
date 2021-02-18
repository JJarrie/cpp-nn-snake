#include "Snake.hpp"

Snake::Snake(const Vector& boardSize, const NeuralNetwork& neuralNetwork): 
    boardSize(boardSize), 
    score(0), 
    neuralNetwork(neuralNetwork) 
{
    grid = std::vector<SquareValue>(boardSize.x * boardSize.y);
    randomizer = Randomizer();
}

void Snake::generateFood() {
    int p;
    do {
        p = randomizer.pick(0, grid.size());
    } while (grid[p] == SquareValue::Body);
    
    foodPosition.x = p % boardSize.x;
    foodPosition.y = static_cast<int>(std::floor(p / boardSize.x));
}

bool Snake::isFinish() const {
    Point head;
    head.x = snake[0].x;
    head.y = snake[0].y;

    return head.x < 0 || head.y < 0 || head.x >= boardSize.x 
        || head.y >= boardSize.y 
        || (std::find(snake.cbegin() + 1, snake.cend(), head) == std::end(snake));
}

void Snake::nextFrame() {
    
}