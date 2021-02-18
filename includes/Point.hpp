#ifndef __POINT_HPP__
#define __POINT_HPP__

struct Point {
    int x;
    int y;
};


bool operator==(const Point& a, const Point& b) 
{
    return a.x == b.x && a.y == b.y;
}

#endif