#ifndef PROJECTILE_H
#define PROJECTILE_H
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700

#include <cmath>
#include "Vector2.h"
#include "gl_canvas2d.h"
#include "VectorHelper.h"
/***
 * Classe que gerencia o projetil e sua trajetoria
 */

class Projectile
{
public:
   Projectile() {}
   virtual ~Projectile() {}
   void shoot(Vector2 _direction, Vector2 _playerPosition)
   {
      playerPosition = _playerPosition;
      ang = getAngToGo(_direction, _playerPosition);
   }
   bool render(int proj_speed, float fps, char r, char g, char b)
   {
      position = {playerPosition.x + inc * cos(ang), playerPosition.y + inc * sin(ang)};
      CV::color(r, g, b);
      CV::circleFill(position.x, position.y, radius, 1000);
      inc += proj_speed / fps;
      if (position.x > SCREEN_WIDTH || position.y > SCREEN_HEIGHT)
      {
         return false;
      }
      else
      {
         return true;
      }
   }

   Vector2 getPosition()
   {
      return position;
   }

   int getRadius()
   {
      return radius;
   }

protected:
   Vector2 playerPosition;
   Vector2 position;
   int radius = 10;

private:
   float ang;
   int inc = 0;
   Vector2 direction;
};

#endif // PROJECTILE_H
