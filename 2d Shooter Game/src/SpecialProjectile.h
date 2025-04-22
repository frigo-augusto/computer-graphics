#ifndef SPECIALPROJECTILE_H
#define SPECIALPROJECTILE_H

#include "Vector2.h"
#include "Bezier.h"
#include "Projectile.h"
#include "Enemy.h"
#include "ShooterEnemy.h"
/***
 * Projetil que segue trajetoria curva em direcao ao inimigo
 */

class SpecialProjectile : public Projectile
{
public:
   SpecialProjectile(Vector2 _origin, std::vector<Enemy> *_enemies, std::vector<ShooterEnemy> *_shooterEnemies, char _type, int _targetIndex)
   {
      enemies = _enemies;
      shooterEnemies = _shooterEnemies;
      playerPosition = _origin;
      p1 = Vector2(playerPosition.x + (rand() % 100), playerPosition.y + (rand() % 100));
      p2 = Vector2(playerPosition.x + (rand() % 100), playerPosition.y + (rand() % 100));
      radius = 20;
      targetType = _type;
      targetIndex = _targetIndex;
      targetId = getEntityId();
   }
   virtual ~SpecialProjectile() {}

   bool render(float fps)
   {
      if (isTargetAlive())
      {
         lastEnemyPosition = getEnemyPosition();
      }
      position = getBezierPoint(playerPosition, p1, p2, lastEnemyPosition, t);
      t += 0.8 / fps;
      CV::color(0, 1, 1);
      CV::circle(position.x, position.y, radius, 100);
      if (position.x >= SCREEN_WIDTH || position.y >= SCREEN_HEIGHT)
      {
         return false;
      }
      return true;
   }

protected:
private:
   int getEntityId()
   {
      if (targetType == 'e')
      {
         return (*enemies)[targetIndex].id;
      }
      else
      {
         return (*shooterEnemies)[targetIndex].id;
      }
   }
   bool isTargetAlive()
   {
      for (int i = 0; i < enemies->size(); i++)
      {
         if (targetId == (*enemies)[i].id)
            return true;
      }
      for (int i = 0; i < shooterEnemies->size(); i++)
      {
         if (targetId == (*shooterEnemies)[i].id)
            return true;
      }
      return false;
   }

   Vector2 getEnemyPosition()
   {
      if (targetType == 'e')
      {
         return (*enemies)[targetIndex].baricenter();
      }
      else
      {
         return (*shooterEnemies)[targetIndex].baricenter();
      }
   }
   int targetIndex = 0;
   int targetId = 0;
   Vector2 lastEnemyPosition;
   char targetType;
   float t = 0.0;
   Vector2 p1, p2;
   std::vector<Enemy> *enemies;
   std::vector<ShooterEnemy> *shooterEnemies;
};

#endif // SPECIALPROJECTILE_H
