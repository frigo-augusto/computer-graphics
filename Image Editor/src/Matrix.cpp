/*********************************************************************
// Classe para utilizacao de matrizes de float, criada para possibilitar o uso de operators
// e encapsular a alocacao dinamica da matriz com base canonica.
// Os asserts possibilitam impedir que matrizes que geram pontos 3d sejam criadas no programa.
// *********************************************************************/


#include <stdlib.h>
#include <assert.h>
#include "Matrix.h"
#include "Point.h"
#include "WritableElement.h"

// cria matriz com base canonica
Matrix::Matrix(int _lines, int _columns)
{
   lines = _lines;
   columns = _columns;
   assert(lines == 2 && columns == 2 && "Two dimensions transforms only");
   mainMatrix = (float **)malloc(lines * sizeof(float *));
   assert(mainMatrix != NULL && "malloc fail");
   for (int i = 0; i < columns; i++)
   {
      mainMatrix[i] = (float *)malloc(columns * sizeof(float));
      assert(mainMatrix[i] != NULL && "malloc fail");
   }
   for (int i = 0; i < lines; i++)
   {
      for (int j = 0; j < columns; j++)
      {
         if (i == j)
         {
            mainMatrix[i][j] = 1;
         }
         else
         {
            mainMatrix[i][j] = 0;
         }
      }
   }
}

Matrix::~Matrix()
{
   for (int i = 0; i < lines; i++)
   {
      free(mainMatrix[i]);
   }
   free(mainMatrix);
}

// multiplica matriz por ponto
Point *Matrix::operator*(Point &p)
{
   float newX, newY;
   newX = p.x * mainMatrix[0][0] + p.y * mainMatrix[0][1];
   newY = p.x * mainMatrix[1][0] + p.y * mainMatrix[1][1];
   return new Point((int)newX, (int)newY);
}

// multiplica matriz por matriz
Matrix *Matrix::operator*(Matrix &b)
{
   float **ma = mainMatrix, **mb = b.getMainMatrix();
   Matrix *mc = new Matrix(lines, b.columns);
   for (int i = 0; i < lines; i++)
   {
      for (int j = 0; j < b.columns; j++)
      {
         mc->getMainMatrix()[i][j] = 0;
         for (int k = 0; k < columns; k++)
         {
            mc->getMainMatrix()[i][j] += ma[i][k] * mb[k][j];
         }
      }
   }
   return mc;
}

float **Matrix::getMainMatrix()
{
   return mainMatrix;
}
