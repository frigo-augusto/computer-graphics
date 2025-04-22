#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__

#include <iostream>
#include <math.h>

class Vector2
{
public:
    float x, y, z;

    Vector2()
    {
        x = y = 0;
        z = 1;
    }

    Vector2(float _x, float _y)
    {
        x = _x;
        y = _y;
        z = 1;
    }

    void set(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    void normalize()
    {
        float norm = (float)sqrt(x * x + y * y);

        if (norm == 0.0)
        {
            return;
        }
        x /= norm;
        y /= norm;
    }

    Vector2 operator-(const Vector2 &v)
    {
        Vector2 aux(x - v.x, y - v.y);
        return (aux);
    }

    Vector2 operator+(const Vector2 &v)
    {
        Vector2 aux(x + v.x, y + v.y);
        return (aux);
    }

    Vector2 operator/(int div)
    {
        Vector2 aux(x / div, y / div);
        return (aux);
    }

    void print()
    {
        std::cout << std::fixed << "( " << x << ", " << y << ", " << z << " )" << std::endl;
    }

    // Adicionem os demais overloads de operadores aqui.
};

#endif
