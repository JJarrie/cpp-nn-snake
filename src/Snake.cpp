#include "Snake.hpp"

Snake::Snake(const Vector& boardSize, const NeuralNetwork& neuralNetwork): 
    boardSize(boardSize), 
    score(0), 
    neuralNetwork(neuralNetwork) ,
    direction(Direction::South),
    foodPosition({0, 0}),
    lifetime(0),
    timeleft(200)
{
    grid = std::vector<SquareValue>(boardSize.x * boardSize.y);
    snake.push_back(Point(0, 0));
    generateFood();
}

void Snake::generateFood() {
    int p;
    do {
        p = Randomizer::get().pickInt(0, grid.size() - 1);
    } while (grid[p] == SquareValue::Body);
    
    foodPosition.x = p % boardSize.x;
    foodPosition.y = static_cast<int>(std::floor(p / boardSize.x));
}

bool Snake::isFinish() const {
    Point head = snake[0];

    return head.x < 0 || head.y < 0 || head.x >= boardSize.x 
        || head.y >= boardSize.y 
        || (std::find(snake.cbegin() + 1, snake.cend(), head) == std::end(snake));
}

void Snake::nextFrame() {
    Point head = snake[0];
    Vector directionVector = getDirectionVector();
    Point newHead = head + directionVector;

    snake.pop_back();
    snake.insert(snake.begin(), newHead);

    if (newHead == foodPosition) {
        gainTimeleft();
        snake.push_back(foodPosition);
        score++;
        generateFood();
    }
}

void Snake::gainTimeleft() {
    timeleft = std::min(500, timeleft + 100);
}

Vector Snake::getDirectionVector() const {
    Vector v(0, 0);

    switch(direction) {
        case Direction::North:
            v.y = -1;
            break;
        case Direction::South:
            v.y = 1;
            break;
        case Direction::East:
            v.x = 1;
            break;
        case Direction::West:
            v.x = -1;
            break;
    }

    return v;
}