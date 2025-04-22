/*********************************************************************
// Classe para utilizacao de matrizes de WritableElements, criada para possibilitar o uso de operators
// e encapsular a alocacao dinamica da matriz com base canonica.
// Os asserts possibilitam impedir que matrizes que geram pontos 3d sejam criadas no programa.
// *********************************************************************/

#include <stdlib.h>
#include <assert.h>

#include "WritableMatrix.h"

// inicializa matriz com base canonica
WritableMatrix::WritableMatrix(int _lines, int _columns, int initx, int inity, int distx, int disty)
{
   lines = _lines;
   columns = _columns;
   assert(lines == 2 && columns == 2 && "Two dimensional transforms only");
   mainMatrix = (WritableElement ***)malloc(lines * sizeof(WritableElement **));
   assert(mainMatrix != NULL && "malloc fail");
   for (int i = 0; i < lines; i++)
   {
      mainMatrix[i] = (WritableElement **)malloc(lines * sizeof(WritableElement *));
      assert(mainMatrix[i] != NULL && "malloc fail");
   }
   for (int i = 0; i < lines; i++)
   {
      for (int j = 0; j < columns; j++)
      {
         if (i == j)
         {
            mainMatrix[i][j] = new WritableElement(initx + j * distx, inity - i * disty, 100, 50, "1");
         }
         else
         {
            mainMatrix[i][j] = new WritableElement(initx + j * distx, inity - i * disty, 100, 50, "0");
         }
      }
   }
}

WritableMatrix::~WritableMatrix()
{
   for (int i = 0; i < lines; i++)
   {
      for (int j = 0; j < columns; j++)
      {
         delete mainMatrix[i][j];
      }
      free(mainMatrix[i]);
   }
   free(mainMatrix);
}

WritableElement ***WritableMatrix::getMainMatrix()
{
   return mainMatrix;
}
