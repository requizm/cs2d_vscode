#ifndef PROJECTION_H
#define PROJECTION_H

#include "Matrix4.h"
#include "Vector3.h"
#include <math.h>

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

    //template <typename T>
    static float *value_ptr(Matrix4<float> &m)
    {
        return &(m.values[0]);
    }
};

#endif