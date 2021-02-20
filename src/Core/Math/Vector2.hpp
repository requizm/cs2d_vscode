#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

#include <string>


template <typename T>
class Vector2 {
   public:
    T x, y;

    Vector2() : x(0), y(0) {}

    explicit Vector2(T _v) : x(_v), y(_v) {}

    Vector2(T _x, T _y) : x(_x), y(_y) {}

    Vector2 Clone() { return Vector2(x, y); }

    T Magnitude() { return sqrt(this->x * this->x + this->y * this->y); }

    Vector2<float> Normalize() {
        Vector2 a = this->Clone();
        float mag = static_cast<float>(a.Magnitude());
        return Vector2<float>(static_cast<float>(a.x) / mag,
                              static_cast<float>(a.y) / mag);
    }

    T &operator[](int i) {
        switch (i) {
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

    Vector2 operator+(Vector2 const &obj) {
        return Vector2(x + obj.x, y + obj.y);
    }

    Vector2 operator-(Vector2 const &obj) {
        return Vector2(x - obj.x, y - obj.y);
    }

    Vector2 operator*(Vector2 const &obj) {
        return Vector2(x * obj.x, y * obj.y);
    }

    Vector2 operator/(Vector2 const &obj) {
        return Vector2(x / obj.x, y / obj.y);
    }

    bool operator==(Vector2 const &obj) { return (obj.x == x && obj.y == y); }

    bool operator!=(Vector2 const &obj) { return !(obj.x == x && obj.y == y); }

    Vector2 operator+(T obj) { return Vector2(x + obj, y + obj); }

    Vector2 operator-(T obj) { return Vector2(x - obj, y - obj); }

    Vector2 operator*(T obj) { return Vector2(x * obj, y * obj); }

    Vector2 operator/(T obj) { return Vector2(x / obj, y / obj); }

    std::string ToString() {
        return std::string(std::to_string(x) + " - " + std::to_string(y));
    }
};

#endif