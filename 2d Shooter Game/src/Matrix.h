#ifndef MATRIX_H
#define MATRIX_H

#define LINE 3
#define COL 3

#include <iostream>
#include "Vector2.h"

class Matrix
{ // classe de matriz bidimensional que usa coordenadas homogeneas
public:
   float m[LINE][COL];
   Matrix operator*(Matrix m2)
   { // nao eh para funcionar com matrizes nao quadradas, se fosse o caso receberia o tamanho de m2 tbm.
      Matrix result;
      for (int i = 0; i < LINE; i++)
      {
         for (int j = 0; j < COL; j++)
         {
            result.m[i][j] = 0.0f;
            for (int k = 0; k < COL; k++)
            {
               result.m[i][j] += m[i][k] * m2.m[k][j];
            }
         }
      }
      return result;
   }
   Vector2 operator*(Vector2 p)
   { // multiplica a matriz pelo ponto
      Vector2 result;
      result.x = m[0][0] * p.x + m[0][1] * p.y + m[0][2] * p.z;
      result.y = m[1][0] * p.x + m[1][1] * p.y + m[1][2] * p.z;
      result.z = m[2][0] * p.x + m[2][1] * p.y + m[2][2] * p.z;
      return result;
   }
   Matrix()
   { // cria a identidade por padrao
      for (int i = 0; i < LINE; i++)
      {
         for (int j = 0; j < COL; j++)
         {
            if (i == j)
            {
               m[i][j] = 1.0f;
            }
            else
            {
               m[i][j] = 0.0f;
            }
         }
      }
   }
   Matrix(float _m[][COL])
   { // recebe uma matriz como argumento
      for (int i = 0; i < LINE; i++)
      {
         for (int j = 0; j < COL; j++)
         {
            m[i][j] = _m[i][j];
         }
      }
   }
   void print()
   {
      for (int i = 0; i < LINE; ++i)
      {
         for (int j = 0; j < COL; ++j)
         {
            std::cout << m[i][j] << " ";
         }
         std::cout << std::endl;
      }
   }

   ~Matrix()
   {
   }
};

#endif // MATRIX_H
