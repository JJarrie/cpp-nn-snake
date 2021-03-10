#include "Direction.hpp"

Direction::CardinalDirection Direction::turn(const Direction::CardinalDirection& c, const Direction::RelativeDirection& r) {
    int degree = static_cast<int>(c) + static_cast<int>(r);

    if (degree >= 360) {
        degree -= 360;
    }

    if (degree < 0) {
        degree += 360;
    }

    return Direction::intToCardinalDirection(degree);
}


Vector Direction::getDirectionVector(const Direction::CardinalDirection& d) {
    Vector v(0, 0);
    
    switch (d)
    {
        case Direction::CardinalDirection::North:
            v.y = -1;
        break;
        case Direction::CardinalDirection::NorthEast:
            v.x = 1;
            v.y = -1;
        break;
        case Direction::CardinalDirection::East:
            v.x = 1;
        break;
        case Direction::CardinalDirection::SouthEast:
            v.x = 1;
            v.y = 1;
        break;
        case Direction::CardinalDirection::South:
            v.y = 1;
        break;
        case Direction::CardinalDirection::SouthWest:
            v.x = -1;
            v.y = 1;
        break;
        case Direction::CardinalDirection::West:
            v.x = -1;
        break;
        case Direction::CardinalDirection::NorthWest:
            v.y = -1;
            v.x = -1;
        break;
    }

    return v;
}

Direction::CardinalDirection Direction::intToCardinalDirection(int degree) {
    switch (degree)
    {
        case 0:
            return Direction::CardinalDirection::North;
        case 45:
            return Direction::CardinalDirection::NorthEast;
        case 90:
            return Direction::CardinalDirection::East;
        case 135:
            return Direction::CardinalDirection::SouthEast;
        case 180:
            return Direction::CardinalDirection::South;
        case 225:
            return Direction::CardinalDirection::SouthWest;
        case 270:
            return Direction::CardinalDirection::West;
        case 315:
            return Direction::CardinalDirection::NorthWest;
        default:
            return Direction::CardinalDirection::North;
    };
};