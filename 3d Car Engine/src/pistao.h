#ifndef PISTAO_H
#define PISTAO_H

#include "Vector3.h"
#include "math_util.h"
#include "gl_canvas2d.h"
#include "biela.h"
#include "manivela.h"
#include "defines.h"
#include <cmath>
/*
   Classe que gerencia o pistao
*/
class Pistao
{
public:
   float radius;
   Vector3 center;
   Vector3 pistaoSquare[4];
   Vector3 squareMalha[MAT_SIZE][MAT_SIZE];
   Biela *biela;
   Manivela *manivela;
   bool firstCall = true;
   float dist;
   float ang = 0.0;
   float previousAng = 0.0;
   int color = 9;
   bool rightPistao = false;
   float angRotate;

   Pistao(Biela *_biela, Manivela *_manivela, bool _rightPistao)
   {
      biela = _biela;
      manivela = _manivela;
      rightPistao = _rightPistao;
      if (rightPistao)
      {
         angRotate = -PI / 4;
      }
      else
      {
         angRotate = PI / 4;
      }
      calculateCoords();
   }
   virtual ~Pistao()
   {
   }

   void calculateCoords()
   {
      if (rightPistao)
      {
         center.x = biela->circleCenter.x + biela->circleRadius * 2;
      }
      else
      {
         center.x = biela->circleCenter.x;
      }
      Vector3 bielaPonta1 = biela->d1Line;
      Vector3 bielaPonta2 = biela->d2Line;
      radius = bielaPonta1.distxy(bielaPonta2);
      Vector3 centerPontaBiela = biela->rotatedPontaCenter;
      center.y = centerPontaBiela.y;
      dist = centerPontaBiela.distxy(center);
      float ang = centerPontaBiela.ang2d(center);
      if (std::isnan(ang))
         ang = previousAng;
      previousAng = ang;
      center.y -= dist * ((float)sin(ang));
      center.z = centerPontaBiela.z;
   }

   void render(float globlAng, std::vector<Line> &lines, int *mp)
   {
      calculateCoords();
      float radiusSquare = 60; // arbitrario
      Vector3 dir(0, 1, 0, 1);
      dir.normalize();
      float ang = degreesToRadians(atan2(dir.y, dir.x));
      int j = 0;
      for (int i = 45; i < 360; i += 90)
      {
         if (cos(degreesToRadians(i)) >= 0)
         {
            pistaoSquare[j].x = center.x - radiusSquare;
         }
         else
         {
            pistaoSquare[j].x = center.x + radiusSquare;
         }
         pistaoSquare[j].y = center.y + radiusSquare * sin(degreesToRadians(i));
         pistaoSquare[j].z = center.z;
         j++;
      }
      float malhaRadius = 75, malhaHeight = 100;
      generateCylinderMalhaYAxis(center, squareMalha, malhaRadius, malhaHeight, color);
      translate3d(squareMalha, 0, -1 * malhaRadius / 2, 0);
      rotateMatrixAlongZ(manivela->center, squareMalha, angRotate);
      copyCilinderMalha(squareMalha, lines, mp);
   }
};

#endif
