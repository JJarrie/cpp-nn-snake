#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

struct Vector
{
    int x;
    int y;

    Vector(): x(0), y(0) {}
    Vector (int x, int y): x(x), y(y) {}
    Vector(const Vector& v): x(v.x), y(v.y) {}
};

#endif
