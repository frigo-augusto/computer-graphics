#ifndef COLLISION_H
#define COLLISION_H
/***
 * Gerencia as colisoes
 ***/

static void collisionBetweenEnemyAndPlayerProjectile(Player &player, std::vector<Enemy> &enemies, int &pontuacao)
{
   std::vector<Projectile> *proj = player.getProjectiles();
   for (int i = 0; i < proj->size(); i++)
   {
      bool broken = false;
      for (int j = 0; j < enemies.size(); j++)
      {
         if (isCircleInsidePolygon((*proj)[i].getPosition(), (*proj)[i].getRadius(), enemies[j].points))
         {
            proj->erase(proj->begin() + i);
            enemies.erase(enemies.begin() + j);
            pontuacao++;
            j--;
            broken = true;
            break;
         }
      }
      if (broken)
         i--;
   }
}

static void collisionBetweenShooterEnemyAndPlayerProjectile(Player &player, std::vector<ShooterEnemy> &shooterEnemies, int &pontuacao)
{
   std::vector<Projectile> *proj = player.getProjectiles();
   for (int i = 0; i < proj->size(); i++)
   {
      bool broken = false;
      for (int j = 0; j < shooterEnemies.size(); j++)
      {
         if (isCircleInsidePolygon((*proj)[i].getPosition(), (*proj)[i].getRadius(), shooterEnemies[j].points))
         {
            proj->erase(proj->begin() + i);
            shooterEnemies.erase(shooterEnemies.begin() + j);
            pontuacao++;
            j--;
            broken = true;
            break;
         }
      }
      if (broken)
         i--;
   }
}

static void collisionBetweenShooterEnemyProjectileAndPlayer(Player &player, std::vector<ShooterEnemy> &shooterEnemies, int &pontuacao)
{
   for (int i = 0; i < shooterEnemies.size(); i++)
   {
      std::vector<Projectile> *proj = shooterEnemies[i].getProjectiles();
      bool broken = false;
      for (int j = 0; j < proj->size(); j++)
      {
         if (isCircleInsidePolygon((*proj)[j].getPosition(), (*proj)[j].getRadius(), player.points))
         {
            proj->erase(proj->begin() + j);
            j--;
            broken = true;
            if (player.canDamage())
               pontuacao--;
            break;
         }
      }
      if (broken)
         i--;
   }
}

static void collisionBetweenEnemyAndPlayerSpecialProjectile(Player &player, std::vector<Enemy> &enemies, int &pontuacao)
{
   std::vector<SpecialProjectile> *proj = player.getSpecialProjectiles();
   for (int i = 0; i < proj->size(); i++)
   {
      bool broken = false;
      for (int j = 0; j < enemies.size(); j++)
      {
         if (isCircleInsidePolygon((*proj)[i].getPosition(), (*proj)[i].getRadius(), enemies[j].points))
         {
            enemies.erase(enemies.begin() + j);
            pontuacao++;
            j--;
            broken = true;
            break;
         }
      }
   }
}

static void collisionBetweenShooterEnemyAndPlayerSpecialProjectile(Player &player, std::vector<ShooterEnemy> &shooterEnemies, int &pontuacao)
{
   std::vector<SpecialProjectile> *proj = player.getSpecialProjectiles();
   for (int i = 0; i < proj->size(); i++)
   {
      bool broken = false;
      for (int j = 0; j < shooterEnemies.size(); j++)
      {
         if (isCircleInsidePolygon((*proj)[i].getPosition(), (*proj)[i].getRadius(), shooterEnemies[j].points))
         {
            shooterEnemies.erase(shooterEnemies.begin() + j);
            pontuacao++;
            j--;
            broken = true;
            break;
         }
      }
   }
}

static void collisionBetweenEnemyAndPlayer(Player &player, std::vector<Enemy> &enemies, std::vector<ShooterEnemy> &shooterEnemies, int &pontuacao)
{
   for (int i = 0; i < enemies.size(); i++)
   {
      if (isPolygonInsidePolygon(player.points, enemies[i].points))
      {
         enemies.erase(enemies.begin() + i);
         i--;
         if (player.canDamage())
            pontuacao--;
      }
   }

   for (int i = 0; i < shooterEnemies.size(); i++)
   {
      if (isPolygonInsidePolygon(player.points, shooterEnemies[i].points))
      {
         shooterEnemies.erase(shooterEnemies.begin() + i);
         i--;
         if (player.canDamage())
            pontuacao--;
      }
   }
}

#endif // COLLISION_H
