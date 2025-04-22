#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "time.h"
#include "Entity.h"
#include "Enemy.h"
#include "ShooterEnemy.h"
#include "SpecialProjectile.h"

/***
 * Gerencia o player
 */

class Player : public Entity
{
public:
   Player(Vector2 _initialPosition, float speed, int _projectileSpeed, float *fps) : Entity(_initialPosition, speed, 0, _projectileSpeed, fps)
   {
   }
   virtual ~Player()
   {
   }
   void action() override
   {
      Projectile projectile;
      if (difftime(time(NULL), lastShoot) >= 0.1)
      {
         lastShoot = time(NULL);
         projectile.shoot(v_director, projOrigin);
         projectiles.push_back(projectile);
      }
   }
   void action(Vector2 target) override
   {
   }
   void render() override
   {
      Entity::render(1, 1, 0, 1, 1, 1);
      for (int i = 0; i < specialProjectiles.size(); i++)
      {
         if (!specialProjectiles[i].render(*fps))
         {
            specialProjectiles.erase(specialProjectiles.begin() + i);
         }
      }
   }
   std::vector<SpecialProjectile> *getSpecialProjectiles()
   {
      return &specialProjectiles;
   }
   void specialAction(std::vector<Enemy> *enemies, std::vector<ShooterEnemy> *shooterEnemies)
   {
      if ((difftime(time(NULL), lastSpecialShoot) <= 0.2))
      {
         return;
      }
      lastSpecialShoot = time(NULL);
      float minDist = INT_MAX;
      char type = 's';
      int index;
      for (int i = 0; i < enemies->size(); i++)
      {
         float temp = pointsDistance(baricenter(), (*enemies)[i].baricenter());
         if (temp < minDist)
         {
            minDist = temp;
            type = 'e';
            index = i;
         }
      }
      for (int i = 0; i < shooterEnemies->size(); i++)
      {
         float temp = pointsDistance(baricenter(), (*shooterEnemies)[i].baricenter());
         if (temp < minDist)
         {
            minDist = temp;
            type = 's';
            index = i;
         }
      }
      specialProjectiles.push_back(SpecialProjectile(baricenter(), enemies, shooterEnemies, type, index));
   }

   bool canMoveDown()
   {
      if (points[0].y >= 0)
      {
         return true;
      }
      return false;
   }

   bool canMoveUp()
   {
      if (points[2].y <= SCREEN_HEIGHT)
      {
         return true;
      }
      return false;
   }

   bool canDamage()
   {
      if (difftime(time(NULL), lastHit))
      {
         lastHit = time(NULL);
         return true;
      }
   }

protected:
private:
   time_t lastShoot = time(NULL);
   time_t lastSpecialShoot = time(NULL);
   time_t lastHit = time(NULL);
   std::vector<SpecialProjectile> specialProjectiles;
};

#endif // PLAYER_H
