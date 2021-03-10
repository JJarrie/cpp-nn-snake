#include "Snake.hpp"

Snake::Snake(const Vector& boardSize, const NeuralNetwork& neuralNetwork): 
    boardSize(boardSize), 
    score(0), 
    neuralNetwork(neuralNetwork) ,
    direction(Direction::CardinalDirection::South),
    foodPosition({0, 0}),
    lifetime(0),
    timeleft(200)
{
    grid = std::vector<SquareValue>(boardSize.x * boardSize.y);
    snake.push_back(Point(0, 0));
    generateFood();
}

Snake::Snake(const Snake& snake):
    score(0),
    direction(Direction::CardinalDirection::South),
    foodPosition({0, 0}),
    lifetime(0),
    timeleft(200),
    boardSize(snake.boardSize),
    neuralNetwork(snake.neuralNetwork)
{
    grid = std::vector<SquareValue>(boardSize.x * boardSize.y);
    this->snake.push_back(Point(0, 0));
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

bool Snake::pointIsOutbound(const Point& p) const {
    return p.x < 0 || p.y < 0 || p.x >= boardSize.x || p.y >= boardSize.y;
}

bool Snake::pointIsInBody(const Point& p) const {
    return std::find(snake.cbegin() + 1, snake.cend(), p) == std::end(snake);
}

bool Snake::isFinish() const {
    Point head = snake[0];

    return pointIsOutbound(head) || pointIsInBody(head);
}

void Snake::nextFrame() {
    Point head = snake[0];
    Vector directionVector = getDirectionVector(direction);
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

double Snake::fitness() const {
    double fitness = lifetime + std::pow(2, score) + std::pow(score, 2.1) * 500 - std::pow(0.25 * lifetime, 1.3) * std::pow(score, 1.2);

    return std::max(0.1, fitness);
}

int Snake::getScore() const {
    return score;
}

Snake Snake::crossover(const Snake& partner) const {
    Snake s(*this);

    NeuralNetwork nn =  s.neuralNetwork.crossover(partner.neuralNetwork);
    s.neuralNetwork = nn;

    return s;
}

void Snake::mutate(const double& rate) {
    this->neuralNetwork.mutate(rate);
}

void Snake::takeDecision() {
    std::vector<double> input = vision();
    std::vector<double> output = neuralNetwork.output(input);
    int bestIndex = 0;
    double maxOutput = 0.0;

    std::vector<double>::const_iterator it = output.cbegin();

    for(it; it != output.cend(); ++it) {
        if (*(it) > maxOutput) {
            maxOutput = *(it);
            bestIndex = std::distance(output.cbegin(), it);
        }
    }

    switch (bestIndex)
    {
        case 0:
            break;
        case 1:
            direction = Direction::turn(direction, Direction::RelativeDirection::Left);
            break;
        case 2:
            direction = Direction::turn(direction, Direction::RelativeDirection::Right);
            break;
        default:
            break;
    }
}

std::vector<double> Snake::vision() const {
    std::vector<double> currentVision;
    
    std::vector<double> f = lookInDirection(Direction::turn(direction, Direction::RelativeDirection::Front));
    std::vector<double> fr = lookInDirection(Direction::turn(direction, Direction::RelativeDirection::FrontRight));
    std::vector<double> r = lookInDirection(Direction::turn(direction, Direction::RelativeDirection::Right));
    std::vector<double> br = lookInDirection(Direction::turn(direction, Direction::RelativeDirection::BackRight));
    std::vector<double> b = lookInDirection(Direction::turn(direction, Direction::RelativeDirection::Back));
    std::vector<double> bl = lookInDirection(Direction::turn(direction, Direction::RelativeDirection::BackLeft));
    std::vector<double> l = lookInDirection(Direction::turn(direction, Direction::RelativeDirection::Left));
    std::vector<double> fl = lookInDirection(Direction::turn(direction, Direction::RelativeDirection::FrontLeft));

    currentVision.insert(currentVision.end(), std::make_move_iterator(f.begin()), std::make_move_iterator(f.end()));
    currentVision.insert(currentVision.end(), std::make_move_iterator(fr.begin()), std::make_move_iterator(fr.end()));
    currentVision.insert(currentVision.end(), std::make_move_iterator(r.begin()), std::make_move_iterator(r.end()));
    currentVision.insert(currentVision.end(), std::make_move_iterator(br.begin()), std::make_move_iterator(br.end()));
    currentVision.insert(currentVision.end(), std::make_move_iterator(b.begin()), std::make_move_iterator(b.end()));
    currentVision.insert(currentVision.end(), std::make_move_iterator(bl.begin()), std::make_move_iterator(bl.end()));
    currentVision.insert(currentVision.end(), std::make_move_iterator(l.begin()), std::make_move_iterator(l.end()));
    currentVision.insert(currentVision.end(), std::make_move_iterator(fl.begin()), std::make_move_iterator(fl.end()));

    return currentVision;
}

std::vector<double> Snake::lookInDirection(const Direction::CardinalDirection& d) const {
    Vector v = Direction::getDirectionVector(d);
    int distance = 1;
    bool foodSeen = false;
    double foodDistance = 0.0;
    double bodyDistance = 0.0;
    bool bodySeen = false;
    Point p = snake[0] + v;

    while(!pointIsOutbound(p)) {
        if (!foodSeen && p == foodPosition) {
            foodSeen = true;
            foodDistance = static_cast<double>(distance);
        }

        if(!bodySeen && pointIsInBody(p)) {
            bodySeen = true;
            bodyDistance = static_cast<double>(distance);
        }

        p = p + v;
        distance++;
    }

    std::vector<double> inDirection({foodDistance, bodyDistance, static_cast<double>(distance)});

    return inDirection;
}