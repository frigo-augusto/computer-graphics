#include "entity.h"
#include <iostream>
#include "gl_canvas2d.h"
#include <math.h>
#include <algorithm>
#include <cmath>
#include "Matrix.h"

/***
 * Classe base que gerencia todas as entidades. Faz quadrados que serao os inimigos e o player
 *
 ***/

Entity::Entity(Vector2 _initialPosition, int _speed, int _id, int _projectileSpeed, float *_fps)
{
   Vector2 initialPosition = _initialPosition;
   speed = _speed;
   v_director = {0, 1}; // aponta p cima
   initSquare(initialPosition);
   id = _id;
   projSpeed = _projectileSpeed;
   fps = _fps;
}

Entity::~Entity()
{
   // dtor
}

void Entity::action()
{
}

void Entity::action(Vector2 target)
{
}

void Entity::initSquare(Vector2 position)
{
   points.push_back({position.x, position.y});
   points.push_back({position.x + size, position.y});
   points.push_back({position.x + size, position.y + size});
   points.push_back({position.x, position.y + size});
   renderPoints.resize(4);
   CV::line(renderPoints[1], renderPoints[2]);

   std::copy(points.begin(), points.end(), renderPoints.begin());
}

static inline Vector2 getPointsAverage(std::vector<Vector2> &points)
{
   Vector2 avg;
   std::for_each(points.begin(), points.end(), [&avg](Vector2 element)
                 {
      avg.x += element.x;
      avg.y += element.y; });
   avg.x /= points.size();
   avg.y /= points.size();
   return avg;
}

void Entity::moveToOrigin()
{
   currentAvg = getPointsAverage(points);
   std::for_each(points.begin(), points.end(), [&](Vector2 &element)
                 {
      element.x -= currentAvg.x;
      element.y -= currentAvg.y; });
}

void Entity::moveFromOrigin()
{
   for (auto &p : points)
   {
      p.x += currentAvg.x;
      p.y += currentAvg.y;
   }
   for (auto &p : renderPoints)
   {
      p.x += currentAvg.x;
      p.y += currentAvg.y;
   }
}

static inline void printPointsList(std::vector<Vector2> &points)
{
   for (auto p : points)
   {
      p.print();
   }
}

void Entity::moveDirection(int x, int y)
{
   v_director = getVDirector(projOrigin, Vector2(x, y));
   float ang = atan2(v_director.y, v_director.x); // retorna o angulo em relacao ao eixo x
   ang -= PI / 2;                                 // desloca 1 quadrante por conta do retorno da lib
   rotate(ang);
}

void Entity::rotate(float ang)
{
   currentRotationAngle = ang;
   moveToOrigin();
   float auxMatrix[][3] = {{cos(ang), -sin(ang), 0},
                           {sin(ang), cos(ang), 0},
                           {0, 0, 1}};
   Matrix rotate(auxMatrix);
   int i = 0;

   for (auto &p : points)
   {
      renderPoints[i] = rotate * p;
      i++;
   }
   moveFromOrigin();
}

Vector2 Entity::baricenter()
{
   return getPointsAverage(points);
}

void Entity::render(char r, char g, char b, char pr, char pg, char pb)
{
   CV::color(r, g, b);
   CV::line(renderPoints[0], renderPoints[1]);
   CV::line(renderPoints[1], renderPoints[2]);
   CV::line(renderPoints[2], renderPoints[3]);
   CV::line(renderPoints[3], renderPoints[0]);
   CV::color(0, 1, 0);
   projOrigin = (renderPoints[2] + renderPoints[3]) / 2;
   CV::point(projOrigin);
   CV::color(1 - r, 1 - g, 1 - b);
   for (int i = 0; i < projectiles.size(); i++)
   {
      if (!projectiles[i].render(projSpeed, *fps, pr, pg, pb))
      {
         projectiles.erase(projectiles.begin() + i);
      }
   }
}

void Entity::render()
{
   render(1, 0, 0, 0, 0, 1);
}

void Entity::translate(int x, int y)
{
   float auxMatrix[][3] = {{1, 0, x},
                           {0, 1, y},
                           {0, 0, 1}};
   Matrix translate(auxMatrix);
   for (auto &p : points)
   {
      p = translate * p;
   }
   for (auto &p : renderPoints)
   {
      p = translate * p;
   }
}
