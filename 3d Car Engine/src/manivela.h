#ifndef MANIVELA_H
#define MANIVELA_H

#include "Vector3.h"
#include "math_util.h"
#include "gl_canvas2d.h"
#include "Matrix.h"
#include "MatrixHelper.h"
#include "defines.h"

/*
   Classe que gerencia a manivela
*/

class Manivela
{
public:
   Vector3 ponta;
   Vector3 center;
   Vector3 p1Init;
   Vector3 p1End;
   Vector3 p2Init;
   Vector3 p2End;
   Vector3 v1;
   Vector3 v2;
   Vector3 pontaManivela;
   Vector3 middle;
   Vector3 semiCircleMatrix[MAT_SIZE][MAT_SIZE];
   Vector3 l1Malha[MAT_SIZE][MAT_SIZE];
   Vector3 l2Malha[MAT_SIZE][MAT_SIZE];
   Vector3 pontaMalha[MAT_SIZE][MAT_SIZE];
   float circleRadius = 30;
   float zsize = 10;
   int color = 3;

   void rotate(float globlAng)
   {
      Vector3 oldManivela = center;
      ponta = ponta - oldManivela;
      v1 = v1 - oldManivela;
      v2 = v2 - oldManivela;
      center = center - oldManivela;
      Matrix rotation(getRotation2dMatrix(globlAng));
      v1 = rotation * v1;
      v2 = rotation * v2;
      ponta = rotation * ponta;
      center = rotation * center;
      ponta = ponta + oldManivela;
      v1 = v1 + oldManivela;
      v2 = v2 + oldManivela;
      center = center + oldManivela;
      updateVariables();
   }

   Manivela(Vector3 refCircle, float _circleRadius, float angRotate)
   {
      circleRadius = _circleRadius;
      v1.set(-15, -20, 0, 1); // vetores q formam o trapezio
      v1 = rotateVector(v1, degreesToRadians(90));
      v2.set(15, -20, 0, 1);
      v2 = rotateVector(v2, degreesToRadians(90));
      center.x = refCircle.x - 30 * cos(degreesToRadians(180)) * 2;
      center.y = refCircle.y - 30 * sin(degreesToRadians(180)) * 2;
      center.z = refCircle.z;
      updateVariables();
      translate(refCircle);
      updateVariables();
   }

   virtual ~Manivela()
   {
   }

   void updateVariables()
   {
      p1Init = ponta + (v1 - ponta).getNormalized() * 30;
      p2Init = ponta + (v2 - ponta).getNormalized() * 30;
      p1End = ponta + (v1 - ponta).getNormalized() * 150;
      p2End = ponta + (v2 - ponta).getNormalized() * 150;
      middle = getCenter(p1Init, p2Init);
   }

   void translateZ(float z)
   {
      ponta.z += z;
      v1.z += z;
      v2.z += z;
   }

   void translate(Vector3 refCircle)
   {
      Vector3 middlePoint = getCenter(p1Init, p2Init);
      CV::color(1, 0, 0);
      Vector3 dir = middlePoint - refCircle;
      ponta = ponta - dir;
      v1 = v1 - dir;
      v2 = v2 - dir;
   }

   // faz um semicirculo a partir dos vetores
   void drawSemiCircleFromSegment(float angz, std::vector<Line> &lines, int *mp)
   {
      Vector3 aux2 = p1End - ponta, aux1 = p2End - ponta;
      float radius = aux1.mod2d();
      float angaux1aux2 = changeQuadrant(atan2(aux1.y, aux1.x) - atan2(aux2.y, aux2.x));
      float angInit = changeQuadrant(atan2(aux2.y, aux2.x) + atan2(0, 1));
      float angEnd = angInit + angaux1aux2;
      float ang = angInit;
      for (int i = 0; i < MAT_SIZE; ang += (angEnd - angInit) / MAT_SIZE, i++)
      {
         for (int j = 0; j < MAT_SIZE; j++)
         {
            float x = ponta.x + radius * cos(ang);
            float y = ponta.y + radius * sin(ang);
            semiCircleMatrix[i][j].set(x, y, ponta.z + j * MANIVELA_PROF / MAT_SIZE, color);
         }
      }
      rotateMatrixAlongZ(center, semiCircleMatrix, angz);
      copyLineMalha(semiCircleMatrix, lines, mp);
   }

   void render(float angz, std::vector<Line> &lines, int *mp)
   {
      updateVariables();
      generateLineMalha(p1Init, p1End, l1Malha, MANIVELA_PROF / MAT_SIZE, color);
      generateLineMalha(p2Init, p2End, l2Malha, MANIVELA_PROF / MAT_SIZE, color);
      generateLineMalha(p1Init, p2Init, pontaMalha, MANIVELA_PROF / MAT_SIZE, color);
      rotateMatrixAlongZ(center, l1Malha, angz);
      rotateMatrixAlongZ(center, l2Malha, angz);
      rotateMatrixAlongZ(center, pontaMalha, angz);
      copyLineMalha(l1Malha, lines, mp);
      copyLineMalha(l2Malha, lines, mp);
      copyLineMalha(pontaMalha, lines, mp);
      drawSemiCircleFromSegment(angz, lines, mp);
   }
};

#endif
