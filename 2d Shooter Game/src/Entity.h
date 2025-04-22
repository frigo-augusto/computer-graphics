#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2.h"
#include "Projectile.h"
#include <vector>

class Entity
{
public:
   Entity(Vector2 _initialPosition, int _speed, int _id, int _projectileSpeed, float *fps);
   virtual ~Entity();
   void attack();
   virtual void render(char r, char g, char b, char pr, char pg, char pb);
   virtual void render();
   void moveDirection(int mx, int my);
   void translate(int x, int y);
   virtual void action(Vector2 target) = 0;
   virtual void action() = 0;
   Vector2 baricenter();
   Vector2 v_director;
   std::vector<Projectile> *getProjectiles()
   {
      return &projectiles;
   }
   Vector2 projOrigin;
   std::vector<Vector2> renderPoints;
   int size = 50;
   int id;
   float speed;
   float projSpeed;
   float currentRotationAngle = 0.0;
   void rotate(float ang);
   std::vector<Vector2> points;

protected:
   std::vector<Projectile> projectiles;
   float *fps;

private:
   Vector2 currentAvg;
   void initSquare(Vector2 position);
   void moveToOrigin();
   void moveFromOrigin();
};

#endif // ENTITY_H
