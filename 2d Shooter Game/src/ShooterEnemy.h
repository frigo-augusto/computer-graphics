#ifndef SHOOTERENEMY_H
#define SHOOTERENEMY_H

#include "Entity.h"
#include "Bezier.h"
#include "time.h"
/***
 * Inimigo que atira
 */

class ShooterEnemy : public Entity
{
public:
   ShooterEnemy(Vector2 _initialPosition, float speed, Bezier *_bezier, int _id, int _projectileSpeed, float *_fps) : Entity(_initialPosition, speed, _id, _projectileSpeed, _fps)
   {
      bezier = _bezier;
      rotate(3.14); // mira fica pra baixo
   }
   virtual ~ShooterEnemy()
   {
   }
   void action() override
   {
   }
   void action(Vector2 target) override
   {
      if (difftime(time(NULL), lastShoot) >= 3.0)
      {
         lastShoot = time(NULL);
         shoot(target);
      }
      move();
   }

protected:
private:
   Bezier *bezier;
   void shoot(Vector2 playerPosition)
   {
      Vector2 v_director = getVDirector(projOrigin, playerPosition);
      Projectile projectile;
      projectile.shoot(v_director, projOrigin);
      projectiles.push_back(projectile);
   }
   void move()
   {
      if (bezier->checkCollision(points) && changes >= 20)
      { // tolerancia p nao colidir 2x
         speed *= -1;
         changes = 0;
      }
      translate(speed / (*fps), 0);
      changes++;
   }
   time_t lastShoot = time(NULL);
   int changes = 20;
};

#endif // SHOOTERENEMY_H
