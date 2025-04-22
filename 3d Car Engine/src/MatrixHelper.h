#ifndef MATRIXHELPER_H
#define MATRIXHELPER_H

#include "Matrix.h"

/***
 * Definicoes das matrizes basicas
 */

static Matrix getTranslation3dMatrix(int x, int y, int z)
{
   float auxMatrix[][4] = {{1, 0, 0, x},
                           {0, 1, 0, y},
                           {0, 0, 1, z},
                           {0, 0, 0, 1}};
   return Matrix(auxMatrix);
}

static Matrix getRotation2dMatrix(float ang)
{
   float auxMatrix[][4] = {{cos(ang), -1 * sin(ang), 0, 0},
                           {sin(ang), cos(ang), 0, 0},
                           {0, 0, 1, 0},
                           {0, 0, 0, 1}};
   return Matrix(auxMatrix);
}

static Matrix getRotationYMatrix(float ang)
{
   float auxMatrix[][4] = {{cos(ang), 0, sin(ang), 0},
                           {0, 1, 0, 0},
                           {-1 * sin(ang), 0, cos(ang), 0},
                           {0, 0, 0, 1}};
   return Matrix(auxMatrix);
}

static Matrix getRotationXMatrix(float ang)
{
   float auxMatrix[][4] = {{1, 0, 0, 0},
                           {0, cos(ang), -1 * sin(ang), 0},
                           {0, sin(ang), cos(ang), 0},
                           {0, 0, 0, 1}};
   return Matrix(auxMatrix);
}

#endif // MATRIXHELPER_H
