#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__
#include <iostream>

class Vector3
{
public:
    float x, y, z;
    int color = 5;

    Vector3()
    {
        x = y = z = 0;
    }

    Vector3(float _x, float _y, float _z, int _color)
    {
        x = _x;
        y = _y;
        z = _z;
        color = _color;
    }

    void set(float _x, float _y, float _z, int _color)
    {
        x = _x;
        y = _y;
        z = _z;
        color = _color;
    }

    void normalize()
    {
        float norm = (float)sqrt(x * x + y * y + z * z);

        if (norm == 0.0)
        {
            printf("\n\nNormalize::Divisao por zero");
            x = 1;
            y = 1;
            return;
        }
        x /= norm;
        y /= norm;
        z /= norm;
    }

    Vector3 getNormalized()
    {
        float norm = (float)sqrt(x * x + y * y + z * z);
        Vector3 aux;
        if (norm == 0.0)
        {
            return aux;
        }
        aux.x = x / norm;
        aux.y = y / norm;
        aux.z = z / norm;
    }

    Vector3 operator-(const Vector3 &v)
    {
        Vector3 aux(x - v.x, y - v.y, z - v.z, color);
        return (aux);
    }

    Vector3 operator*(const int mult)
    {
        Vector3 aux(x * mult, y * mult, z * mult, color);
        return aux;
    }

    Vector3 operator*(const float mult)
    {
        Vector3 aux(x * mult, y * mult, z * mult, color);
        return aux;
    }

    Vector3 operator+(const Vector3 &v)
    {
        Vector3 aux(x + v.x, y + v.y, z + v.z, color);
        return (aux);
    }

    float distxy(const Vector3 &v)
    {
        return sqrt((x - v.x) * (x - v.x) + (y - v.y) * (y - v.y));
    }

    float dot2d(const Vector3 &v)
    {
        return x * v.x + y * v.y;
    }

    float mod2d()
    {
        return (float)sqrt(x * x + y * y);
    }

    float ang2d(Vector3 &v)
    {
        return acos(dot2d(v) / (mod2d() * v.mod2d()));
    }

    void print()
    {
        std::cout << "x: " << x << " "
                  << "y: " << y << " "
                  << "z: " << z << std::endl;
    }
};

#endif
