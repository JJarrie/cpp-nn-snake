#ifndef __POINT_HPP__
#define __POINT_HPP__

#include "Vector.hpp"

struct Point {
    int x;
    int y;

    Point(int x, int y): x(x), y(y) {}

    inline bool operator==(const Point& p) const
    {
        return x == p.x && y == p.y;
    }

    inline Point operator+(const Vector& v) {
        return Point(x + v.x, y + v.y);
    }
};

#endif