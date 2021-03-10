#ifndef __DIRECTION_HPP_
#define __DIRECTION_HPP_

#include "Vector.hpp"

namespace Direction {

enum CardinalDirection {
    North = 0,
    NorthEast = 45,
    East = 90,
    SouthEast = 135,
    South = 180,
    SouthWest = 225,
    West = 270,
    NorthWest = 315,
};

enum RelativeDirection {
    Front = 0,
    FrontRight = 45,
    Right = 90,
    BackRight = 135,
    Back = 180,
    BackLeft = -135,
    Left = -90,
    FrontLeft = -45,
};

CardinalDirection turn(const Direction::CardinalDirection& c, const Direction::RelativeDirection& r);
Vector getDirectionVector(const Direction::CardinalDirection& d);
CardinalDirection intToCardinalDirection(int degree);

}

#endif