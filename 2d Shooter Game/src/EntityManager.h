#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#define SPACE 32

#include "Enemy.h"
#include "VectorHelper.h"
#include "Player.h"
#include "Vector2.h"
#include "ShooterEnemy.h"
#include "Bezier.h"
#include "Collision.h"
#include "keys.h"
#define PLAYER_INITIAL_X 200
#define PLAYER_INITIAL_Y 50
#define PLAYER_SPEED 150
#define PLAYER_PROJ_SPEED 300
#define ENEMY_WALK_SPEED 160
#define ENEMY_PROJ_SPEED 100
#define SHOOTER_ENEMY_SPEED 100

/***
 * Gerencia todas as entidades do jogo
 */

class EntityManager
{
public:
   EntityManager(Bezier *_bezier, float *_fps, int *_pontuacao)
   {
      fps = _fps;
      player = new Player(Vector2(PLAYER_INITIAL_X, PLAYER_INITIAL_Y), PLAYER_SPEED, PLAYER_PROJ_SPEED, fps);
      bezier = _bezier;
      pontuacao = _pontuacao;
   }
   virtual ~EntityManager()
   {
   }
   void check()
   {
      player->render();
      if (enemies.size() < 4)
      {
         int randX = L_LIMIT + INTERVAL + (rand() % (SCREEN_WIDTH - (L_LIMIT + INTERVAL + (SCREEN_WIDTH - (R_LIMIT)))));
         enemies.push_back(Enemy(Vector2(randX, rand() % SCREEN_HEIGHT), 0, ++entityId, ENEMY_WALK_SPEED, fps));
      }
      for (auto &e : enemies)
      {
         e.render();
         e.action(player->baricenter());
      }
      if (shooterEnemies.size() < 4)
      {
         int randX = L_LIMIT + INTERVAL + (rand() % (SCREEN_WIDTH - (L_LIMIT + INTERVAL + (SCREEN_WIDTH - (R_LIMIT)))));
         shooterEnemies.push_back(ShooterEnemy(Vector2(randX, SCREEN_HEIGHT - 150), SHOOTER_ENEMY_SPEED, bezier, ++entityId, ENEMY_PROJ_SPEED, fps));
      }
      for (auto &e : shooterEnemies)
      {
         e.render();
         e.action(player->baricenter());
      }
      checkCollisions();
   }

   void keyboard(int keys[])
   {
      for (int i = 0; i < KEY_BUFFER; i++)
      {
         if (keys[i] == INVALID_KEY)
            continue;
         int key = keys[i];
         int collision = bezier->checkCollision(player->points);
         if (key == 'w' && player->canMoveUp())
         {
            player->translate(0, player->speed / (*fps));
         }
         else if (key == 's' && player->canMoveDown())
         {
            player->translate(0, -1 * player->speed / (*fps));
         }
         else if (key == 'a' && collision != 1)
         {
            player->translate(-1 * player->speed / (*fps), 0);
         }
         else if (key == 'd' && collision != 2)
         {
            player->translate(player->speed / (*fps), 0);
         }
         if (key == SPACE)
         {
            player->specialAction(&enemies, &shooterEnemies);
         }
      }
   }

   void mouse(int mx, int my)
   {
      player->moveDirection(mx, my);
   }

   void click()
   {
      player->action();
   }

   void checkCollisions()
   {
      collisionBetweenEnemyAndPlayerProjectile((*player), enemies, *pontuacao);
      collisionBetweenEnemyAndPlayerSpecialProjectile((*player), enemies, *pontuacao);
      collisionBetweenEnemyAndPlayer((*player), enemies, shooterEnemies, *pontuacao);
      collisionBetweenShooterEnemyAndPlayerProjectile((*player), shooterEnemies, *pontuacao);
      collisionBetweenShooterEnemyAndPlayerSpecialProjectile((*player), shooterEnemies, *pontuacao);
      collisionBetweenShooterEnemyProjectileAndPlayer(*player, shooterEnemies, *pontuacao);
   }

protected:
private:
   Player *player;
   std::vector<Enemy> enemies;
   std::vector<ShooterEnemy> shooterEnemies;
   Bezier *bezier;
   int entityId = 0;
   float *fps;
   int *pontuacao;
};

#endif // ENTITYMANAGER_H
