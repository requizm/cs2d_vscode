#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

template <typename T>
class Vector2
{
public:
    T x, y;

    Vector2() : x(0), y(0)
    {
    }

    Vector2(T _v) : x(_v), y(_v)
    {
    }

    Vector2(T _x, T _y) : x(_x), y(_y)
    {
    }

    Vector2 Clone()
    {
        return Vector2(x, y);
    }

    Vector2 Magnitude()
    {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    Vector2 Normalize()
    {
        Vector2 a = this->Clone();
        return a / a.Magnitude();
    }

    T &operator[](int i)
    {
        switch (i)
        {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        default:
            break;
        }
    }

    Vector2 operator+(Vector2 const &obj)
    {
        return Vector2(x + obj.x, y + obj.y);
    }

    Vector2 operator-(Vector2 const &obj)
    {
        return Vector2(x - obj.x, y - obj.y);
    }

    Vector2 operator*(Vector2 const &obj)
    {
        return Vector2(x * obj.x, y * obj.y);
    }

    Vector2 operator/(Vector2 const &obj)
    {
        return Vector2(x / obj.x, y / obj.y);
    }

    bool operator==(Vector2 const &obj)
    {
        return (obj.x == x && obj.y == y);
    }

    bool operator!=(Vector2 const &obj)
    {
        return !(obj.x == x && obj.y == y);
    }

    Vector2 operator+(T obj)
    {
        return Vector2(x + obj, y + obj);
    }

    Vector2 operator-(T obj)
    {
        return Vector2(x - obj, y - obj);
    }

    Vector2 operator*(T obj)
    {
        return Vector2(x * obj, y * obj);
    }

    Vector2 operator/(T obj)
    {
        return Vector2(x / obj, y / obj);
    }
};

#endif