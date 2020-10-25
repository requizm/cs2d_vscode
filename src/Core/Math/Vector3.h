#ifndef VECTOR3_H
#define VECTOR3_H

template <typename T>
class Vector3
{
public:
    T x, y, z;

    Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z)
    {
    }

    Vector3 Clone()
    {
        return Vector3(x, y, z);
    }

    int Magnitude()
    {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    Vector3 Normalize()
    {
        Vector3 a = this->Clone();
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
        case 2:
            return z;
            break;
        default:
            break;
        }
    }

    Vector3 operator+(Vector3 const &obj)
    {
        return Vector3(x + obj.x, y + obj.y, z + obj.z);
    }

    Vector3 operator-(Vector3 const &obj)
    {
        return Vector3(x - obj.x, y - obj.y, z - obj.z);
    }

    Vector3 operator*(Vector3 const &obj)
    {
        return Vector3(x * obj.x, y * obj.y, z * obj.z);
    }

    Vector3 operator/(Vector3 const &obj)
    {
        return Vector3(x / obj.x, y / obj.y, z / obj.z);
    }

    Vector3 operator+(T obj)
    {
        return Vector3(x + obj, y + obj, z + obj);
    }

    Vector3 operator-(T obj)
    {
        return Vector3(x - obj, y - obj, z - obj);
    }

    Vector3 operator*(T obj)
    {
        return Vector3(x * obj, y * obj, z * obj);
    }

    Vector3 operator/(T obj)
    {
        return Vector3(x / obj, y / obj, z / obj);
    }
};

#endif