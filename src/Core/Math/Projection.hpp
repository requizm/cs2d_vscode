#ifndef PROJECTION_H
#define PROJECTION_H

#include <math.h>

#include "Matrix4.hpp"
#include "Vector3.hpp"
class Projection
{
public:
    Projection()
    {
    }

    template <typename T>
    static Matrix4<T> ortho(T l, T r, T b, T t,
                            T n, T f)
    {
        Matrix4<T> M;

        // set OpenGL perspective projection matrix
        M.Get(1, 1) = 2 / (r - l);
        M.Get(1, 2) = 0;
        M.Get(1, 3) = 0;
        M.Get(1, 4) = 0;

        M.Get(2, 1) = 0;
        M.Get(2, 2) = 2 / (t - b);
        M.Get(2, 3) = 0;
        M.Get(2, 4) = 0;

        M.Get(3, 1) = 0;
        M.Get(3, 2) = 0;
        M.Get(3, 3) = -2 / (f - n);
        M.Get(3, 4) = 0;

        M.Get(4, 1) = -(r + l) / (r - l);
        M.Get(4, 2) = -(t + b) / (t - b);
        M.Get(4, 3) = -(f + n) / (f - n);
        M.Get(4, 4) = 1;

        return M;
    }

    template <typename T>
    static Matrix4<T> ortho(T l, T r, T b, T t)
    {
        Matrix4<T> M;

        // set OpenGL perspective projection matrix
        M.Get(1, 1) = 2 / (r - l);
        M.Get(1, 2) = 0;
        M.Get(1, 3) = 0;
        M.Get(1, 4) = 0;

        M.Get(2, 1) = 0;
        M.Get(2, 2) = 2 / (t - b);
        M.Get(2, 3) = 0;
        M.Get(2, 4) = 0;

        M.Get(3, 1) = 0;
        M.Get(3, 2) = 0;
        M.Get(3, 3) = -1;
        M.Get(3, 4) = 0;

        M.Get(4, 1) = -(r + l) / (r - l);
        M.Get(4, 2) = -(t + b) / (t - b);
        M.Get(4, 3) = 0;
        M.Get(4, 4) = 1;

        return M;
    }

    template <typename T>
    static Matrix4<T> translate(Matrix4<T> m, Vector3<T> v)
    {
        Matrix4<T> R = m.Clone();

        R.Get(4, 1) = m.Get(1, 1) * v[0] + m.Get(2, 1) * v[1] + m.Get(3, 1) * v[2] + m.Get(4, 1);
        R.Get(4, 2) = m.Get(1, 2) * v[0] + m.Get(2, 2) * v[1] + m.Get(3, 2) * v[2] + m.Get(4, 2);
        R.Get(4, 3) = m.Get(1, 3) * v[0] + m.Get(2, 3) * v[1] + m.Get(3, 3) * v[2] + m.Get(4, 3);
        R.Get(4, 4) = m.Get(1, 4) * v[0] + m.Get(2, 4) * v[1] + m.Get(3, 4) * v[2] + m.Get(4, 4);

        return R;
    }

    template <typename T>
    static Matrix4<T> rotate(Matrix4<T> m, T angle, Vector3<T> v)
    {
        T const a = angle;
        T const c = cos(a);
        T const s = sin(a);

        Vector3<T> axis = v.Normalize();
        Vector3<T> temp = Vector3(axis * (T(1) - c));

        Matrix4<T> Rotate;
        Rotate.Get(1, 1) = c + temp[0] * axis[0];
        Rotate.Get(1, 2) = temp[0] * axis[1] + s * axis[2];
        Rotate.Get(1, 3) = temp[0] * axis[2] - s * axis[1];

        Rotate.Get(2, 1) = temp[1] * axis[0] - s * axis[2];
        Rotate.Get(2, 2) = c + temp[1] * axis[1];
        Rotate.Get(2, 3) = temp[1] * axis[2] + s * axis[0];

        Rotate.Get(3, 1) = temp[2] * axis[0] + s * axis[1];
        Rotate.Get(3, 2) = temp[2] * axis[1] - s * axis[0];
        Rotate.Get(3, 3) = c + temp[2] * axis[2];

        Matrix4<T> R;

        R.Get(1, 1) = m.Get(1, 1) * Rotate.Get(1, 1) + m.Get(2, 1) * Rotate.Get(1, 2) + m.Get(3, 1) * Rotate.Get(1, 3);
        R.Get(1, 2) = m.Get(1, 2) * Rotate.Get(1, 1) + m.Get(2, 2) * Rotate.Get(1, 2) + m.Get(3, 2) * Rotate.Get(1, 3);
        R.Get(1, 3) = m.Get(1, 3) * Rotate.Get(1, 1) + m.Get(2, 3) * Rotate.Get(1, 2) + m.Get(3, 3) * Rotate.Get(1, 3);
        R.Get(1, 4) = m.Get(1, 4) * Rotate.Get(1, 1) + m.Get(2, 4) * Rotate.Get(1, 2) + m.Get(3, 4) * Rotate.Get(1, 3);

        R.Get(2, 1) = m.Get(1, 1) * Rotate.Get(2, 1) + m.Get(2, 1) * Rotate.Get(2, 2) + m.Get(3, 1) * Rotate.Get(2, 3);
        R.Get(2, 2) = m.Get(1, 2) * Rotate.Get(2, 1) + m.Get(2, 2) * Rotate.Get(2, 2) + m.Get(3, 2) * Rotate.Get(2, 3);
        R.Get(2, 3) = m.Get(1, 3) * Rotate.Get(2, 1) + m.Get(2, 3) * Rotate.Get(2, 2) + m.Get(3, 3) * Rotate.Get(2, 3);
        R.Get(2, 4) = m.Get(1, 4) * Rotate.Get(2, 1) + m.Get(2, 4) * Rotate.Get(2, 2) + m.Get(3, 4) * Rotate.Get(2, 3);

        R.Get(3, 1) = m.Get(1, 1) * Rotate.Get(3, 1) + m.Get(2, 1) * Rotate.Get(3, 2) + m.Get(3, 1) * Rotate.Get(3, 3);
        R.Get(3, 2) = m.Get(1, 2) * Rotate.Get(3, 1) + m.Get(2, 2) * Rotate.Get(3, 2) + m.Get(3, 2) * Rotate.Get(3, 3);
        R.Get(3, 3) = m.Get(1, 3) * Rotate.Get(3, 1) + m.Get(2, 3) * Rotate.Get(3, 2) + m.Get(3, 3) * Rotate.Get(3, 3);
        R.Get(3, 4) = m.Get(1, 4) * Rotate.Get(3, 1) + m.Get(2, 4) * Rotate.Get(3, 2) + m.Get(3, 4) * Rotate.Get(3, 3);

        R.Get(4, 1) = m.Get(4, 1);
        R.Get(4, 2) = m.Get(4, 2);
        R.Get(4, 3) = m.Get(4, 3);
        R.Get(4, 4) = m.Get(4, 4);

        return R;
    }

    template <typename T>
    static Matrix4<T> scale(Matrix4<T> m, Vector3<T> v)
    {
        Matrix4<T> R = m.Clone();

        R.Get(1, 1) = m.Get(1, 1) * v[0];
        R.Get(1, 2) = m.Get(1, 2) * v[0];
        R.Get(1, 3) = m.Get(1, 3) * v[0];
        R.Get(1, 4) = m.Get(1, 4) * v[0];

        R.Get(2, 1) = m.Get(2, 1) * v[1];
        R.Get(2, 2) = m.Get(2, 2) * v[1];
        R.Get(2, 3) = m.Get(2, 3) * v[1];
        R.Get(2, 4) = m.Get(2, 4) * v[1];

        R.Get(3, 1) = m.Get(3, 1) * v[2];
        R.Get(3, 2) = m.Get(3, 2) * v[2];
        R.Get(3, 3) = m.Get(3, 3) * v[2];
        R.Get(3, 4) = m.Get(3, 4) * v[2];

        R.Get(4, 1) = m.Get(4, 1);
        R.Get(4, 2) = m.Get(4, 2);
        R.Get(4, 3) = m.Get(4, 3);
        R.Get(4, 4) = m.Get(4, 4);

        return R;
    }

    static float *value_ptr(Matrix4<float> &m)
    {
        return &(m.values[0]);
    }

    static float radians(float degrees)
    {
        return degrees * (0.01745329251994329576923690768489F);
    }

    static float degrees(float radians)
    {
        return radians * (57.295779513082320876798154814105F);
    }

    static Matrix4<float> inverse(Matrix4<float> m)
    {
        Matrix4<float> inv, r;
        float det;
        int i;

        inv[0] = m[5] * m[10] * m[15] -
                 m[5] * m[11] * m[14] -
                 m[9] * m[6] * m[15] +
                 m[9] * m[7] * m[14] +
                 m[13] * m[6] * m[11] -
                 m[13] * m[7] * m[10];

        inv[4] = -m[4] * m[10] * m[15] +
                 m[4] * m[11] * m[14] +
                 m[8] * m[6] * m[15] -
                 m[8] * m[7] * m[14] -
                 m[12] * m[6] * m[11] +
                 m[12] * m[7] * m[10];

        inv[8] = m[4] * m[9] * m[15] -
                 m[4] * m[11] * m[13] -
                 m[8] * m[5] * m[15] +
                 m[8] * m[7] * m[13] +
                 m[12] * m[5] * m[11] -
                 m[12] * m[7] * m[9];

        inv[12] = -m[4] * m[9] * m[14] +
                  m[4] * m[10] * m[13] +
                  m[8] * m[5] * m[14] -
                  m[8] * m[6] * m[13] -
                  m[12] * m[5] * m[10] +
                  m[12] * m[6] * m[9];

        inv[1] = -m[1] * m[10] * m[15] +
                 m[1] * m[11] * m[14] +
                 m[9] * m[2] * m[15] -
                 m[9] * m[3] * m[14] -
                 m[13] * m[2] * m[11] +
                 m[13] * m[3] * m[10];

        inv[5] = m[0] * m[10] * m[15] -
                 m[0] * m[11] * m[14] -
                 m[8] * m[2] * m[15] +
                 m[8] * m[3] * m[14] +
                 m[12] * m[2] * m[11] -
                 m[12] * m[3] * m[10];

        inv[9] = -m[0] * m[9] * m[15] +
                 m[0] * m[11] * m[13] +
                 m[8] * m[1] * m[15] -
                 m[8] * m[3] * m[13] -
                 m[12] * m[1] * m[11] +
                 m[12] * m[3] * m[9];

        inv[13] = m[0] * m[9] * m[14] -
                  m[0] * m[10] * m[13] -
                  m[8] * m[1] * m[14] +
                  m[8] * m[2] * m[13] +
                  m[12] * m[1] * m[10] -
                  m[12] * m[2] * m[9];

        inv[2] = m[1] * m[6] * m[15] -
                 m[1] * m[7] * m[14] -
                 m[5] * m[2] * m[15] +
                 m[5] * m[3] * m[14] +
                 m[13] * m[2] * m[7] -
                 m[13] * m[3] * m[6];

        inv[6] = -m[0] * m[6] * m[15] +
                 m[0] * m[7] * m[14] +
                 m[4] * m[2] * m[15] -
                 m[4] * m[3] * m[14] -
                 m[12] * m[2] * m[7] +
                 m[12] * m[3] * m[6];

        inv[10] = m[0] * m[5] * m[15] -
                  m[0] * m[7] * m[13] -
                  m[4] * m[1] * m[15] +
                  m[4] * m[3] * m[13] +
                  m[12] * m[1] * m[7] -
                  m[12] * m[3] * m[5];

        inv[14] = -m[0] * m[5] * m[14] +
                  m[0] * m[6] * m[13] +
                  m[4] * m[1] * m[14] -
                  m[4] * m[2] * m[13] -
                  m[12] * m[1] * m[6] +
                  m[12] * m[2] * m[5];

        inv[3] = -m[1] * m[6] * m[11] +
                 m[1] * m[7] * m[10] +
                 m[5] * m[2] * m[11] -
                 m[5] * m[3] * m[10] -
                 m[9] * m[2] * m[7] +
                 m[9] * m[3] * m[6];

        inv[7] = m[0] * m[6] * m[11] -
                 m[0] * m[7] * m[10] -
                 m[4] * m[2] * m[11] +
                 m[4] * m[3] * m[10] +
                 m[8] * m[2] * m[7] -
                 m[8] * m[3] * m[6];

        inv[11] = -m[0] * m[5] * m[11] +
                  m[0] * m[7] * m[9] +
                  m[4] * m[1] * m[11] -
                  m[4] * m[3] * m[9] -
                  m[8] * m[1] * m[7] +
                  m[8] * m[3] * m[5];

        inv[15] = m[0] * m[5] * m[10] -
                  m[0] * m[6] * m[9] -
                  m[4] * m[1] * m[10] +
                  m[4] * m[2] * m[9] +
                  m[8] * m[1] * m[6] -
                  m[8] * m[2] * m[5];

        det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

        if (det == 0)
            return false;

        det = 1.0F / det;

        for (i = 0; i < 16; i++)
            r[i] = inv[i] * det;

        return r;
    }
};

#endif