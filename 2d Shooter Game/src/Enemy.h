#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

/***
 * Inimigo que anda ate o player
 */

class Enemy : public Entity
{
public:
   Enemy(Vector2 _initialPosition, float speed, int _id, int _projectileSpeed, float *_fps) : Entity(_initialPosition, speed, _id, _projectileSpeed, _fps)
   {
   }
   virtual ~Enemy()
   {
   }
   void action() override
   {
   }
   void action(Vector2 playerPosition) override
   {
      goToPlayer(playerPosition);
   }

protected:
private:
   void goToPlayer(Vector2 playerPosition)
   {
      moveDirection(playerPosition.x, playerPosition.y);
      float ang = getAngToGo(v_director, playerPosition);
      translate(projSpeed * cos(ang) * (1 / (*fps)), projSpeed * sin(ang) * (1 / (*fps))); // o humor da tirinha eh q ele eh o projetil
   }
};

#endif // ENEMY_H
