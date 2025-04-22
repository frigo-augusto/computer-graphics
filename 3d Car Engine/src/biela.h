#ifndef BIELA_H
#define BIELA_H

#include "Vector3.h"
#include "math_util.h"
#include "gl_canvas2d.h"
#include <cmath>
#define VECTOR_LIMIT 400
#define VECTOR_DIST 350
#define VECTOR_INC 10
/*
Classe para gerenciamento da biela
*/

class Biela
{
public:
   Vector3 circleCenter;
   float circleRadius = 30;
   Vector3 square[4];
   Vector3 end1, d1Line, end2, d2Line, pontaCenter, originLine;
   Vector3 manivelaCenter;
   Vector3 squareCenter;
   Vector3 squareMalhas[3][MAT_SIZE][MAT_SIZE], d1LineMalha[MAT_SIZE][MAT_SIZE], d2LineMalha[MAT_SIZE][MAT_SIZE], end1malha[MAT_SIZE][MAT_SIZE], end2malha[MAT_SIZE][MAT_SIZE], cylinderMalha[MAT_SIZE][MAT_SIZE];
   float angInitManivela;
   float angRotatePistao;
   bool rightBiela = false;
   Vector3 translateDesc;
   Vector3 rotatedCircleCenter, rotatedPontaCenter;
   float previousRotateItself;
   Biela(Vector3 _circleCenter, bool _rightBiela)
   {
      circleCenter = _circleCenter;
      calculateSquare();
      calculatePoints();
      angInitManivela = 0;
      rightBiela = _rightBiela;
      if (rightBiela)
      {
         angRotatePistao = -PI / 4;
      }
      else
      {
         angRotatePistao = PI / 4;
      }
   }

   virtual ~Biela()
   {
   }

   void setCircleCenter(Vector3 c)
   {
      circleCenter = c;
   }

   void setManivelaCenter(Vector3 c)
   {
      manivelaCenter = c;
   }

   void calculateSquare()
   {
      float avgx = 0, avgy = 0, avgz = 0;
      int j = 45;
      int color = 4;
      for (int i = 0; i < 4; i++)
      {
         square[i].x = circleCenter.x + 2 * circleRadius * cos(degreesToRadians(j % 360)); // 2 raios, um circulo
         square[i].y = circleCenter.y + 2 * circleRadius * sin(degreesToRadians(j % 360));
         square[i].z = circleCenter.z;
         j += 90;
         avgx += square[i].x;
         avgy += square[i].y;
         avgz += square[i].z;
      }
      avgx /= 4;
      avgy /= 4;
      avgz /= 4;
      squareCenter.set(avgx, avgy, avgz, color);
   }

   // ajusta a descricao da translacao que a biela sofre
   void updateTranslationDescription(float rotateAroundManivela)
   {
      float angManivela = degreesToRadians(angInitManivela) + rotateAroundManivela;
      if (rightBiela)
      {
         angManivela += PI / 4;
      }
      else
      {
         angManivela -= PI / 4;
      }
      Vector3 translatePoint(circleRadius * 2 * cos(angManivela), circleRadius * 2 * sin(angManivela), 0, circleCenter.color);
      if (manivelaCenter.y * circleCenter.x > manivelaCenter.x * circleCenter.y)
      {
         translateDesc = translatePoint - manivelaCenter;
      }
      else
      {
         translateDesc = manivelaCenter - translatePoint;
      }
      translateDesc.z = MANIVELA_PROF;
   }

   // processa todas as malhas
   void proccessMalhas(float rotateItself, std::vector<Line> &lines, int *mp)
   {
      int color = 4;
      generateCylinderMalhaZAxis(circleCenter, cylinderMalha, circleRadius, BIELA_PROF, 1);
      rotateMatrixAlongZ(squareCenter, cylinderMalha, rotateItself);
      translate3d(cylinderMalha, translateDesc);
      rotateMatrixAlongZ(manivelaCenter, cylinderMalha, angRotatePistao);
      copyCilinderMalha(cylinderMalha, lines, mp);
      generateLineMalha(end1, d1Line, d1LineMalha, BIELA_PROF / MAT_SIZE, color);
      rotateMatrixAlongZ(squareCenter, d1LineMalha, rotateItself);
      translate3d(d1LineMalha, translateDesc);
      rotateMatrixAlongZ(manivelaCenter, d1LineMalha, angRotatePistao);
      copyLineMalha(d1LineMalha, lines, mp);
      generateLineMalha(end2, d2Line, d2LineMalha, BIELA_PROF / MAT_SIZE, color);
      rotateMatrixAlongZ(squareCenter, d2LineMalha, rotateItself);
      translate3d(d2LineMalha, translateDesc);
      rotateMatrixAlongZ(manivelaCenter, d2LineMalha, angRotatePistao);
      copyLineMalha(d2LineMalha, lines, mp);
      generateLineMalha(square[0], end1, end1malha, BIELA_PROF / MAT_SIZE, color);
      rotateMatrixAlongZ(squareCenter, end1malha, rotateItself);
      translate3d(end1malha, translateDesc);
      rotateMatrixAlongZ(manivelaCenter, end1malha, angRotatePistao);
      copyLineMalha(end1malha, lines, mp);
      generateLineMalha(square[0], end2, end2malha, BIELA_PROF / MAT_SIZE, color);
      rotateMatrixAlongZ(squareCenter, end2malha, rotateItself);
      translate3d(end2malha, translateDesc);
      rotateMatrixAlongZ(manivelaCenter, end2malha, angRotatePistao);
      copyLineMalha(end2malha, lines, mp);
      for (int i = 1; i < 4; i++)
      {
         generateLineMalha(square[i], square[(i + 1) % 4], squareMalhas[i - 1], BIELA_PROF / MAT_SIZE, color);
         rotateMatrixAlongZ(squareCenter, squareMalhas[i - 1], rotateItself);
         translate3d(squareMalhas[i - 1], translateDesc);
         rotateMatrixAlongZ(manivelaCenter, squareMalhas[i - 1], angRotatePistao);
         copyLineMalha(squareMalhas[i - 1], lines, mp);
      }
   }

   void updatePistaoReferences()
   {
      rotatedCircleCenter = getPointTranslated(circleCenter, translateDesc);
      rotatedPontaCenter = getPointTranslated(pontaCenter, translateDesc);
   }

   void renderSquare(Vector3 pistaoCenter, float pistaoRadius, float globlAng, std::vector<Line> &lines, int *mp)
   {
      calculateSquare();
      calculatePoints();
      updatePistaoReferences();
      updateTranslationDescription(globlAng);
      Vector3 director = pistaoCenter - rotatedCircleCenter;
      float rotateItself = atan2(director.y, director.x);
      rotateItself -= PI / 2;
      if (std::isnan(rotateItself))
         rotateItself = previousRotateItself;
      previousRotateItself = rotateItself;
      calculatePoints();
      CV::color(1, 1, 1);
      proccessMalhas(rotateItself, lines, mp);
   }

   void calculatePoints()
   {
      Vector3 d1 = square[1] - square[0];
      d1.normalize();
      end1 = square[0] + d1 * VECTOR_INC;
      Vector3 d2 = d1 * -1;
      end2 = square[1] + d2 * VECTOR_INC;
      Vector3 middleUpperPoint = getCenter(square[0], square[1]);
      Vector3 directorLimit = middleUpperPoint - circleCenter;
      directorLimit.normalize();
      Vector3 lineLimit = circleCenter + (directorLimit * VECTOR_LIMIT);
      Vector3 d1LineVec = lineLimit - square[0];
      d1LineVec.normalize();
      d1LineVec = d1LineVec * VECTOR_DIST;
      Vector3 d2LineVec = lineLimit - square[1];
      d2LineVec.normalize();
      d2LineVec = d2LineVec * VECTOR_DIST;
      d1Line = square[0] + d1LineVec;
      d2Line = square[1] + d2LineVec;
      float lradius = d1Line.distxy(d2Line) / 2;
      pontaCenter = getCenter(d1Line, d2Line);
      originLine = getCenter(end1, end2);
   }

   void renderPonta()
   {
   }
};

#endif
