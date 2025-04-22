#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include "Vector2.h"

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700
#define INTERVAL 50
#define L_LIMIT 50
#define R_LIMIT 1100
#define BEZIER_INCREMENT 0.001
#include "gl_canvas2d.h"
#include "VectorHelper.h"

static Vector2 vectorXScalar(Vector2 p, double s)
{
   Vector2 aux(p.x * s, p.y * s);
   return aux;
}
static Vector2 getBezierPoint(Vector2 p0, Vector2 p1, Vector2 p2, Vector2 p3, float t)
{
   Vector2 aux(vectorXScalar(p0, pow(1 - t, 3)) + vectorXScalar(p1, 3 * t * pow(1 - t, 2)) + vectorXScalar(p2, 3 * pow(t, 2) * (1 - t)) + vectorXScalar(p3, pow(t, 3)));
   return aux;
}

class Bezier
{
public:
   Vector2 b1[12][4];
   Vector2 b2[12][4];
   Bezier()
   { // gera varias curvas de bezier com o ultimo ponto em comum
      for (int i = 0; i < 12; i++)
      {
         b1[i][0] = Vector2(L_LIMIT, i * SCREEN_HEIGHT);
         b2[i][0] = Vector2(R_LIMIT, i * SCREEN_HEIGHT);
         for (int j = 1; j < 3; j++)
         {
            b1[i][j] = Vector2(L_LIMIT + (rand() % INTERVAL), i * SCREEN_HEIGHT + (rand() % SCREEN_HEIGHT));
            b2[i][j] = Vector2(R_LIMIT + (rand() % INTERVAL), i * SCREEN_HEIGHT + (rand() % SCREEN_HEIGHT));
         }
         b1[i][3] = Vector2(L_LIMIT, (i + 1) * SCREEN_HEIGHT);
         b2[i][3] = Vector2(R_LIMIT, (i + 1) * SCREEN_HEIGHT);
      }
   }
   virtual ~Bezier()
   {
   }
   void render(int _cameraY) // renderiza a curva de acordo com onde esta a camera
   {
      cameraY = _cameraY;
      CV::color(0, 1, 1);
      int curRender = floor(cameraY / SCREEN_HEIGHT);
      for (int i = curRender; i <= curRender + 1; i++)
      {
         int index = i % 12;
         for (float t = 0; t <= 1.0; t += BEZIER_INCREMENT)
         {
            Vector2 p1 = getBezierPoint(b1[index][0], b1[index][1], b1[index][2], b1[index][3], t);
            Vector2 p2 = getBezierPoint(b2[index][0], b2[index][1], b2[index][2], b2[index][3], t);
            if (p1.y <= cameraY + SCREEN_HEIGHT && p1.y >= cameraY)
            {
               p1.y -= cameraY;
               CV::point(p1);
            }
            if (p2.y <= cameraY + SCREEN_HEIGHT && p2.y >= cameraY)
            {
               p2.y -= cameraY;
               CV::point(p2);
            }
         }
      }
   }

   int checkCollision(std::vector<Vector2> &polygon) // colisao entre poligono e bezier
   {
      int curRender = floor(cameraY / SCREEN_HEIGHT);
      for (int i = curRender; i <= curRender + 1; i++)
      {
         int index = i % 12;
         for (float t = 0; t <= 1.0; t += BEZIER_INCREMENT)
         {
            Vector2 p1 = getBezierPoint(b1[index][0], b1[index][1], b1[index][2], b1[index][3], t);
            Vector2 p2 = getBezierPoint(b2[index][0], b2[index][1], b2[index][2], b2[index][3], t);
            if (p1.y <= cameraY + SCREEN_HEIGHT && p1.y >= cameraY)
            {
               p1.y -= cameraY;
               if (isPointInsidePolygon(p1, polygon))
               {
                  return 1;
               }
            }
            if (p2.y <= cameraY + SCREEN_HEIGHT && p2.y >= cameraY)
            {
               p2.y -= cameraY;
               if (isPointInsidePolygon(p2, polygon))
               {
                  return 2;
               }
            }
         }
      }
      return false;
   }

protected:
private:
   int cameraY = 0;
};

#endif // BEZIER_H
