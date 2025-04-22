#ifndef VECTORHELPER_H
#define VECTORHELPER_H

#include "Vector2.h"
#include <vector>

static float getAngToGo(Vector2 v_director, Vector2 target)
{
    v_director.normalize();
    return atan2(v_director.y, v_director.x);
}

static float pointsDistance(Vector2 p1, Vector2 p2)
{
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

static inline Vector2 getVDirector(Vector2 origin, Vector2 dest)
{
    Vector2 v_director = dest - origin;
    v_director.normalize();
    return v_director;
}

static bool isCircleInsidePolygon(const Vector2 &center, int radius, const std::vector<Vector2> &points)
{
    int crossings = 0, j = points.size() - 1;
    for (int i = 0; i < points.size(); j = i++)
    {
        int x1 = points[i].x;
        int y1 = points[i].y;
        int x2 = points[j].x;
        int y2 = points[j].y;

        if ((y1 <= center.y && y2 > center.y) || (y1 > center.y && y2 <= center.y))
        {
            float xIntersect = ((x2 - x1) / (y2 - y1)) * (center.y - y1) + x1;

            if (center.x < xIntersect)
                crossings++;
        }
    }

    return (crossings % 2 == 1);
}

static bool isPointInsidePolygon(Vector2 point, const std::vector<Vector2> points)
{
    int crossings = 0, j = points.size() - 1;
    for (int i = 0; i < points.size(); j = i++) // compara cada ponto com seu proximo
    {

        if ((points[i].y > point.y) == (points[j].y > point.y)) // cruza se nao estiver acima ou abaixo dos 2 pontos
            continue;

        int xDiff = points[j].x - points[i].x, yDiff = points[j].y - points[i].y;
        float compare = (xDiff * (point.y - points[i].y) / yDiff) + points[i].x; // multiplica a diferenca dos x pela proporcao de y, e soma com o x do p inicial
        if (point.x < compare)
            crossings++; // cruzou a linha
    }
    return (crossings % 2 == 1);
}

static bool isPolygonInsidePolygon(std::vector<Vector2> p1, std::vector<Vector2> p2)
{
    for (auto p : p1)
    {
        if (isPointInsidePolygon(p, p2))
        {
            return true;
        }
    }
    return false;
}

#endif // VECTORHELPER_H
