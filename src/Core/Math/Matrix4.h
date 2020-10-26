#ifndef MATRIX4_H
#define MATRIX4_H

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

    Matrix4 operator*(Matrix4 const &obj)
    {
        Matrix4 o = obj;
        Matrix4 temp;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                temp.Get(i + 1, j + 1) = 0;
                for (int k = 0; k < 4; k++)
                    temp.Get(i + 1, j + 1) += this->Get(i + 1, k + 1) * o.Get(k + 1, j + 1);
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

    T values[16];
};

#endif