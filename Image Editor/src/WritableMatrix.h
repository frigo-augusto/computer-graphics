#ifndef WRITABLEMATRIX_H
#define WRITABLEMATRIX_H
#include "Point.h"
#include "WritableElement.h"

class WritableMatrix
{
public:
   WritableMatrix(int lines, int columns, int initx, int inity, int distx, int disty);
   virtual ~WritableMatrix();
   WritableElement ***getMainMatrix();
   int columns, lines;

private:
   WritableElement ***mainMatrix;
};

#endif // WRITABLEMATRIX_H
