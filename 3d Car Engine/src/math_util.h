#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include "math.h"
#include "Vector3.h"
#include "Matrix.h"
#include "MatrixHelper.h"
#include "line.h"
#include <vector>
#define PI 3.1415
#include "defines.h"

/*
   Funcoes de utilidade para calculos
*/

Vector3 yAxis(0, 1, 0, 1);

static inline float radiansToDegrees(float radians)
{
   return radians * 180.0f / PI;
}

static inline float degreesToRadians(int degrees)
{
   return degrees * PI / 180.0f;
}

float changeQuadrant(float ang)
{
   if (ang <= 0)
   {
      ang += 2 * PI;
   }
   return ang;
}

float getSquareSideByDiagonal(float diagonal)
{
   return sqrt(diagonal * diagonal / 2);
}

static inline float avg(float v1, float v2)
{
   return (v1 + v2) / 2;
}

static inline Vector3 getCenter(Vector3 p1, Vector3 p2)
{
   return Vector3(avg(p1.x, p2.x), avg(p1.y, p2.y), avg(p1.z, p2.z), p1.color);
}

static inline Vector3 getCenter(Vector3 vec[], int n)
{
   float avgx = 0, avgy = 0;
   for (int i = 0; i < n; i++)
   {
      avgx += vec[i].x;
      avgy += vec[i].y;
   }
   avgx /= n;
   avgy /= n;
   Vector3 aux(avgx, avgy, 0, vec[0].color);
   return aux;
}

void rotateSquare(Vector3 square[], float ang)
{
   Vector3 avg;
   for (int i = 0; i < 4; i++)
   {
      avg.x += square[i].x;
      avg.y += square[i].y;
   }
   avg.x /= 4;
   avg.y /= 4;
   for (int i = 0; i < 4; i++) // eu espero do fundo do meu coracao que nao precise de um define pra dizer q um quadrado tem 4 lados
   {
      square[i].x -= avg.x;
      square[i].y -= avg.y;
   }
   Matrix rotate(getRotation2dMatrix(ang));
   for (int i = 0; i < 4; i++)
   {
      square[i] = rotate * square[i];
   }
   for (int i = 0; i < 4; i++)
   {
      square[i].x += avg.x;
      square[i].y += avg.y;
   }
}

Vector3 rotateVector(Vector3 vector, float ang)
{
   Matrix rotate(getRotation2dMatrix(ang));
   vector = rotate * vector;
   return vector;
}

void generateLineMalha(Vector3 init, Vector3 end, Vector3 mat[][MAT_SIZE], float jIncrement, int color)
{
   for (int i = 0; i < MAT_SIZE; i++)
   {
      for (int j = 0; j < MAT_SIZE; j++)
      {
         float t = 1.0f / (j + 1);
         Vector3 aux = init + (end - init) * t;
         mat[i][j] = aux;
         mat[i][j].z = init.z + i * jIncrement;
         mat[i][j].color = color;
      }
   }
}

void generateCylinderMalhaYAxis(Vector3 center, Vector3 mat[][MAT_SIZE], float radius, float height, int color)
{
   float theta = 0;
   for (int i = 0; i < MAT_SIZE; i++, theta += 2 * PI / MAT_SIZE)
   {
      for (int j = 0; j < MAT_SIZE; j++)
      {
         mat[i][j].set(center.x + radius * cos(theta), center.y + j * height / MAT_SIZE, center.z + radius * sin(theta), color);
      }
   }
}

void generateCylinderMalhaXAxis(Vector3 center, Vector3 mat[][MAT_SIZE], float radius, float height, int color)
{
   float theta = 0;
   for (int i = 0; i < MAT_SIZE; i++, theta += 2 * PI / MAT_SIZE)
   {
      for (int j = 0; j < MAT_SIZE; j++)
      {
         mat[i][j].set(center.x + j * height / MAT_SIZE, center.y + radius * cos(theta), center.z + radius * sin(theta), color);
      }
   }
}

void generateCylinderMalhaZAxis(Vector3 center, Vector3 mat[][MAT_SIZE], float radius, float height, int color)
{
   float theta = 0;
   for (int i = 0; i < MAT_SIZE; i++, theta += 2 * PI / MAT_SIZE)
   {
      for (int j = 0; j < MAT_SIZE; j++)
      {
         mat[i][j].set(center.x + radius * cos(theta), center.y + radius * sin(theta), center.z + j * height / MAT_SIZE, color);
      }
   }
}

void copyLineMalha(Vector3 copy[][MAT_SIZE], std::vector<Line> &target, int *mp)
{
   target.reserve((target.size() + MAT_SIZE * MAT_SIZE * 3) * sizeof(Line));
   for (int l = 0; l < MAT_SIZE - 1; l++)
   {
      for (int c = 0; c < MAT_SIZE - 1; c++)
      {
         target.push_back({copy[l][c], copy[l][c + 1]});
         (*mp)++;
         target.push_back({copy[l][c], copy[l + 1][c]});
         (*mp)++;
         target.push_back({copy[l][c], copy[l + 1][c + 1]});
         (*mp)++;
      }
   }
}

void copyCilinderMalha(Vector3 copy[][MAT_SIZE], std::vector<Line> &target, int *mp)
{
   target.reserve((target.size() + MAT_SIZE * MAT_SIZE * 3) * sizeof(Line));
   for (int l = 0; l < MAT_SIZE; l++)
   {
      for (int c = 0; c < MAT_SIZE; c++)
      {
         target.push_back({copy[l][c], copy[l][(c + 1) % MAT_SIZE]});
         (*mp)++;
         target.push_back({copy[l][c], copy[(l + 1) % MAT_SIZE][c]});
         (*mp)++;
         target.push_back({copy[l][c], copy[(l + 1) % MAT_SIZE][(c + 1) % MAT_SIZE]});
         (*mp)++;
      }
   }
}

void renderGlobalMatrix(std::vector<Line> &lines, float d, bool perspectiveActive)
{
   for (int i = 0; i < lines.size(); i++)
   {
      CV::color(lines[i].p1.color);
      CV::line(lines[i].p1, lines[i].p2, d, perspectiveActive);
   }
}

void rotateMatrixAlongY(Vector3 center, std::vector<Line> &lines, float ang, int *mp)
{
   Matrix translation(getTranslation3dMatrix(-1 * center.x, -1 * center.y, -1 * center.z)); // tem que fazer essa rotacao funcionar direito. o centro ta errado. Tem que ter algum outro jeito que nao a media.
   Matrix rotation(getRotationYMatrix(ang));
   Matrix translation2(getTranslation3dMatrix(center.x, center.y, center.z));

   for (int i = 0; i < *mp; i++)
   {
      lines[i].p1 = translation * lines[i].p1;
      lines[i].p1 = rotation * lines[i].p1;
      lines[i].p1 = translation2 * lines[i].p1;
      lines[i].p2 = translation * lines[i].p2;
      lines[i].p2 = rotation * lines[i].p2;
      lines[i].p2 = translation2 * lines[i].p2;
   }
}

void rotateMatrixAlongX(Vector3 center, std::vector<Line> &lines, float ang, int *mp)
{
   Matrix translation(getTranslation3dMatrix(-1 * center.x, -1 * center.y, -1 * center.z)); // tem que fazer essa rotacao funcionar direito. o centro ta errado. Tem que ter algum outro jeito que nao a media.
   Matrix rotation(getRotationXMatrix(ang));
   Matrix translation2(getTranslation3dMatrix(center.x, center.y, center.z));

   for (int i = 0; i < *mp; i++)
   {
      lines[i].p1 = translation * lines[i].p1;
      lines[i].p1 = rotation * lines[i].p1;
      lines[i].p1 = translation2 * lines[i].p1;
      lines[i].p2 = translation * lines[i].p2;
      lines[i].p2 = rotation * lines[i].p2;
      lines[i].p2 = translation2 * lines[i].p2;
   }
}

void rotateMatrixAlongY(Vector3 center, Vector3 m[][MAT_SIZE], float ang)
{

   Matrix translation(getTranslation3dMatrix(-1 * center.x, -1 * center.y, -1 * center.z));
   Matrix rotation(getRotationYMatrix(ang));
   Matrix translation2(getTranslation3dMatrix(center.x, center.y, center.z));

   for (int i = 0; i < MAT_SIZE; i++)
   {
      for (int j = 0; j < MAT_SIZE; j++)
      {
         m[i][j] = translation * m[i][j];
         m[i][j] = rotation * m[i][j];
         m[i][j] = translation2 * m[i][j];
      }
   }
}

void rotateMatrixAlongZ(Vector3 center, Vector3 m[][MAT_SIZE], float ang)
{

   Matrix translation(getTranslation3dMatrix(-1 * center.x, -1 * center.y, -1 * center.z));
   Matrix rotation(getRotation2dMatrix(ang));
   Matrix translation2(getTranslation3dMatrix(center.x, center.y, center.z));

   for (int i = 0; i < MAT_SIZE; i++)
   {
      for (int j = 0; j < MAT_SIZE; j++)
      {
         m[i][j] = translation * m[i][j];
         m[i][j] = rotation * m[i][j];
         m[i][j] = translation2 * m[i][j];
      }
   }
}

void rotateMatrixAlongX(Vector3 m[][MAT_SIZE], float ang)
{
   float avgx = 0, avgy = 0, avgz = 0;
   for (int i = 0; i < MAT_SIZE; i++)
   {
      for (int j = 0; j < MAT_SIZE; j++)
      {
         avgx += m[i][j].x;
         avgy += m[i][j].y;
         avgz += m[i][j].z;
      }
   }

   avgx /= MAT_SIZE * MAT_SIZE;
   avgy /= MAT_SIZE * MAT_SIZE;
   avgz /= MAT_SIZE * MAT_SIZE;

   Matrix translation(getTranslation3dMatrix(-1 * avgx, -1 * avgy, -1 * avgz));
   Matrix rotation(getRotationXMatrix(ang));
   Matrix translation2(getTranslation3dMatrix(avgx, avgy, avgz));

   for (int i = 0; i < MAT_SIZE; i++)
   {
      for (int j = 0; j < MAT_SIZE; j++)
      {
         m[i][j] = translation * m[i][j];
         m[i][j] = rotation * m[i][j];
         m[i][j] = translation2 * m[i][j];
      }
   }
   CV::circleFill(0, 0, 10, 10);
}

void rotateMatrixAlongZ(Vector3 m[][MAT_SIZE], float ang)
{
   float avgx = 0, avgy = 0, avgz = 0;
   for (int i = 0; i < MAT_SIZE; i++)
   {
      for (int j = 0; j < MAT_SIZE; j++)
      {
         avgx += m[i][j].x;
         avgy += m[i][j].y;
         avgz += m[i][j].z;
      }
   }

   avgx /= MAT_SIZE * MAT_SIZE;
   avgy /= MAT_SIZE * MAT_SIZE;
   avgz /= MAT_SIZE * MAT_SIZE;

   Matrix translation(getTranslation3dMatrix(-1 * avgx, -1 * avgy, -1 * avgz));
   Matrix rotation(getRotation2dMatrix(ang));
   Matrix translation2(getTranslation3dMatrix(avgx, avgy, avgz));

   for (int i = 0; i < MAT_SIZE; i++)
   {
      for (int j = 0; j < MAT_SIZE; j++)
      {
         m[i][j] = translation * m[i][j];
         m[i][j] = rotation * m[i][j];
         m[i][j] = translation2 * m[i][j];
      }
   }
}

void translate3d(Vector3 m[][MAT_SIZE], float x, float y, float z)
{
   Matrix translation(getTranslation3dMatrix(x, y, z));
   for (int i = 0; i < MAT_SIZE; i++)
   {
      for (int j = 0; j < MAT_SIZE; j++)
      {
         m[i][j] = translation * m[i][j];
      }
   }
}

void translate3d(Vector3 m[][MAT_SIZE], Vector3 t)
{
   Matrix translation(getTranslation3dMatrix(t.x, t.y, t.z));
   for (int i = 0; i < MAT_SIZE; i++)
   {
      for (int j = 0; j < MAT_SIZE; j++)
      {
         m[i][j] = translation * m[i][j];
      }
   }
}

Vector3 getPointTranslated(Vector3 p, Vector3 t)
{
   Matrix translation(getTranslation3dMatrix(t.x, t.y, t.z));
   return translation * p;
}

#endif
