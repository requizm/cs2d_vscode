#ifndef MATRIX4_H
#define MATRIX4_H

#include <array>

template <typename T>
class Matrix4
{
   public:
    Matrix4(T v)
    {
        this->data[0] = v;
        this->data[1] = 0;
        this->data[2] = 0;
        this->data[3] = 0;
        this->data[4] = 0;
        this->data[5] = v;
        this->data[6] = 0;
        this->data[7] = 0;
        this->data[8] = 0;
        this->data[9] = 0;
        this->data[10] = v;
        this->data[11] = 0;
        this->data[12] = 0;
        this->data[13] = 0;
        this->data[14] = 0;
        this->data[15] = v;
    }

    Matrix4(std::array<T, 16> v)
    {
        this->data = v;
    }

    Matrix4() = default;
    Matrix4(Matrix4 &&) = default;
    Matrix4(const Matrix4 &) = default;
    Matrix4 &operator=(Matrix4 &&) = default;
    Matrix4 &operator=(const Matrix4 &) = default;
    ~Matrix4() = default;


    Matrix4 Clone()
    {
        return Matrix4(*this);
    }

    const T *dataPtr() const { return this->data.data(); }

    T &Get(int a, int b) { return data[(a - 1) * 4 + (b - 1)]; }

    T &operator[](int i)
    {
        // assert(i < 16)
        return data[i];
    }

    Matrix4 operator+(const Matrix4 &obj)
    {
        Matrix4 temp = Clone();
        for (int i = 0; i < 16; i++)
        {
            temp[i] = temp[i] + obj[i];
        }
        return temp;
    }

    Matrix4 operator-(const Matrix4 &obj)
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
        const T *A = dataPtr();
        const T *B = obj.dataPtr();
        std::array<T, 16> C;

        for (int k = 0; k < 4; ++k)
        {
            for (int j = 0; j < 4; ++j)
            {
                C[k * 4 + j] =
                    A[0 * 4 + j] * B[k * 4 + 0] +
                    A[1 * 4 + j] * B[k * 4 + 1] +
                    A[2 * 4 + j] * B[k * 4 + 2] +
                    A[3 * 4 + j] * B[k * 4 + 3];
            }
        }
        return Matrix4(C);
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

    bool operator==(const Matrix4 &obj)
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

    bool operator!=(const Matrix4 &obj)
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
    std::array<T, 16> data;
};

#endif