#ifndef MATRIX_H
#define MATRIX_H
#include "Point.h"

class Matrix
{
public:
   Matrix(int lines, int columns);
   virtual ~Matrix();
   Point *operator*(Point &p);
   Matrix *operator*(Matrix &b);
   float **getMainMatrix();
   int columns, lines;

private:
   float **mainMatrix;
};

#endif // MATRIX_H
