#ifndef MATRIX4_H
#define MATRIX4_H

#include <glm/gtc/type_ptr.hpp>

template <typename T>
class Matrix4
{
public:
    Matrix4(T v)
    {
        for (int i = 0; i < 16; i++)
        {
            if (i == 0 || i == 5 || i == 10 || i == 15)
                values[i] = v;
            else
                values[i] = 0;
        }
    }

    Matrix4()
    {
        for (int i = 0; i < 16; i++)
            values[i] = 0;
    }

    Matrix4 Clone()
    {
        Matrix4 m;
        for (int i = 0; i < 16; i++)
        {
            m[i] = values[i];
        }
        return m;
    }

    T &Get(int a, int b)
    {
        return values[(a - 1) * 4 + (b - 1)];
    }

    T &operator[](int i)
    {
        //assert(i < 16)
        return values[i];
    }

    Matrix4 operator+(Matrix4 const &obj)
    {
        Matrix4 temp = Clone();
        for (int i = 0; i < 16; i++)
        {
            temp[i] = temp[i] + obj[i];
        }
        return temp;
    }

    Matrix4 operator-(Matrix4 const &obj)
    {
        Matrix4 temp = Clone();
        for (int i = 0; i < 16; i++)
        {
            temp[i] = temp[i] - obj[i];
        }
        return temp;
    }

    Matrix4 operator*(Matrix4 &obj)
    {
        Matrix4 temp;
        Matrix4 m1 = this->Clone();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                temp.Get(j + 1, i + 1) = 0.0F;
                for (int k = 0; k < 4; k++)
                {
                    temp.Get(j + 1, i + 1) = temp.Get(j + 1, i + 1) + m1.Get(k + 1, i + 1) * obj.Get(j + 1, k + 1);
                }
            }
        }
        return temp;
    }

    Matrix4 operator+(T obj)
    {
        Matrix4 temp = Clone();
        for (int i = 0; i < 16; i++)
        {
            temp[i] = temp[i] + obj;
        }
        return temp;
    }

    Matrix4 operator-(T obj)
    {
        Matrix4 temp = Clone();
        for (int i = 0; i < 16; i++)
        {
            temp[i] = temp[i] - obj;
        }
        return temp;
    }

    Matrix4 operator*(T obj)
    {
        Matrix4 temp = Clone();
        for (int i = 0; i < 16; i++)
        {
            temp[i] = temp[i] * obj;
        }
        return temp;
    }

    Matrix4 operator/(T obj)
    {
        Matrix4 temp = Clone();
        for (int i = 0; i < 16; i++)
        {
            temp[i] = temp[i] / obj;
        }
        return temp;
    }

    bool operator==(Matrix4 &obj)
    {
        Matrix4 temp = Clone();

        for (int i = 0; i < 16; i++)
        {
            if (obj[i] != temp[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(Matrix4 &obj)
    {
        Matrix4 temp = Clone();

        for (int i = 0; i < 16; i++)
        {
            if (obj[i] != temp[i])
            {
                return true;
            }
        }
        return false;
    }

    T values[16];
};

#endif