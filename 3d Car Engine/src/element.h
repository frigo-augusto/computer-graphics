#ifndef ELEMENT_H
#define ELEMENT_H

#include "manivela.h"
#include "pistao.h"
#include "biela.h"
#include "defines.h"
#include <vector>
#define ELEM_DIST 400
#define ELEM_INIT 75
/*
 Classe que gerencia cada "elemento" do motor
*/

class Element
{
public:
   Manivela *manivela;
   Biela *biela;
   Pistao *pistao;
   Manivela *manivela2;
   Biela *biela2;
   Pistao *pistao2;
   Vector3 vir1[MAT_SIZE][MAT_SIZE];
   Vector3 vir2[MAT_SIZE][MAT_SIZE];
   int dist;

   Element(int _dist)
   {
      int color = 11;
      dist = _dist;
      biela = new Biela(Vector3(0, 0, ELEM_INIT + ELEM_DIST * dist, 1), false);
      manivela = new Manivela(biela->circleCenter, biela->circleRadius, 0);
      biela->setManivelaCenter(manivela->center);
      biela->setCircleCenter(manivela->middle);
      pistao = new Pistao(biela, manivela, false);

      biela2 = new Biela(Vector3(0, 0, BIELA_PROF + ELEM_INIT + ELEM_DIST * dist, 1), true);
      manivela2 = new Manivela(biela2->circleCenter, biela2->circleRadius, 0);
      biela2->setManivelaCenter(manivela2->center);
      biela2->setCircleCenter(manivela2->middle);
      pistao2 = new Pistao(biela2, manivela2, true);
      manivela2->translateZ(MANIVELA_PROF + BIELA_PROF);

      Vector3 v1Center(manivela->center.x, manivela->center.y, ELEM_DIST * dist, color);
      generateCylinderMalhaZAxis(v1Center, vir1, MAIN_RADIUS, ELEM_INIT, color);

      Vector3 v2Center(manivela->center.x, manivela->center.y, ELEM_DIST * dist + ELEM_INIT + MANIVELA_PROF * 2 + BIELA_PROF * 2, color);
      generateCylinderMalhaZAxis(v2Center, vir2, MAIN_RADIUS, ELEM_DIST - ELEM_INIT - BIELA_PROF * 2 - MANIVELA_PROF * 2, color);
   }

   virtual ~Element()
   {
   }

   void generate(float accAng, std::vector<Line> &lines, int *mp)
   {
      pistao->render(accAng, lines, mp);
      pistao2->render(accAng, lines, mp);
      biela->renderSquare(pistao->center, pistao->radius, accAng, lines, mp);
      biela2->renderSquare(pistao2->center, pistao2->radius, accAng, lines, mp);
      manivela->render(accAng, lines, mp);
      manivela2->render(accAng, lines, mp);
      if (dist != 0)
         copyCilinderMalha(vir1, lines, mp);
      copyCilinderMalha(vir2, lines, mp);
   }
};
#endif
