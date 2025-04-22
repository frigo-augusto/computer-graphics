#ifndef MATRIXHELPER_H
#define MATRIXHELPER_H

#include "Matrix.h"

/***
 * Definicoes das matrizes basicas
 */

static Matrix getTranslationMatrix(int x, int y)
{
   float auxMatrix[][3] = {{1, 0, x},
                           {0, 1, y},
                           {0, 0, 1}};
   return Matrix(auxMatrix);
}

static Matrix getRotationMatrix(float ang)
{
   float auxMatrix[][3] = {{cos(ang), -1 * sin(ang), 0},
                           {sin(ang), cos(ang), 0},
                           {0, 0, 1}};
   return Matrix(auxMatrix);
}

#endif // MATRIXHELPER_H
