/************
// Classe que implementa funcoes de utilidade para poligonos.
// O convexHull implementa o algoritmo de graham e eh baseado em https://www.geeksforgeeks.org/convex-hull-using-graham-scan/
//
*************/

#include <algorithm>
#include "polygonUtil.h"
#include <vector>

/*
Ray Casting
Traca uma linha do ponto desejado em uma direcao qualquer
Se o numero de cruzamentos da linha com as bordas do poligono for impar, esta dentro, do contrario, nao.
*/
extern bool isPointInsidePolygon(int mx, int my, const std::vector<Point *> &points)
{
    int crossings = 0, j = points.size() - 1;
    for (int i = 0; i < points.size(); j = i++) // compara cada ponto com seu proximo
    {

        if ((points[i]->y > my) == (points[j]->y > my)) // cruza se nao estiver acima ou abaixo dos 2 pontos
            continue;

        int xDiff = points[j]->x - points[i]->x, yDiff = points[j]->y - points[i]->y;
        float compare = (xDiff * (my - points[i]->y) / yDiff) + points[i]->x; // multiplica a diferenca dos x pela proporcao de y, e soma com o x do p inicial
        if (mx < compare)
            crossings++; // cruzou a linha
    }
    return (crossings % 2 == 1);
}

// obtem ponto logo abaixo da stack
Point nextToTop(std::stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

void swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - // determinante da condicao de alinhamento de 3 pontos
              (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0;             // colinear
    return (val > 0) ? 1 : 2; // sentido horario ou anti-horario
}

// distancia euclidiana ao quadrado
int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y);
}

Point *p0; // precisou ser global pq o std::sort() nao deixa passar argumentos

// ordena de acordo com o angulo polar
bool compare(Point *p1, Point *p2)
{
    int o = orientation(*p0, *p1, *p2);
    if (o == 0)
        return (distSq(*p0, *p2) >= distSq(*p0, *p1)) ? true : false;

    return (o == 2) ? true : false;
}

extern void convexHull(std::vector<Point *> points, std::vector<Point *> &renderPoints, int size)
{
    if (size < 2)
        return;

    int ymin = points[0]->y, min = 0;
    for (int i = 0; i < size; i++) // coloca o menor y no comeco da lista. Havendo empate, utiliza-se o x.
    {
        int y = points[i]->y;
        if ((y < ymin) || (ymin == y &&
                           points[i]->x < points[min]->x))
            ymin = points[i]->y, min = i;
    }
    std::swap(points[0], points[min]);

    p0 = points[0];
    std::sort(points.begin(), points.end(), compare);

    int m = 1; // tamanho do array modificado
    for (int i = 1; i < size; i++)
    {
        // loop ate o angulo de 2 elementos consecutivos ate o angulo ser diferente em relacao a p0
        while (i < size - 1 && orientation(*p0, *points[i],
                                           *points[i + 1]) == 0)
            i++;

        points[m] = points[i];
        m++;
    }

    // precisamos de 3 pontos no array modificado para poder aplicar o algoritmo
    if (m < 3)
        return;

    std::stack<Point> S;
    S.push(*points[0]);
    S.push(*points[1]);
    S.push(*points[2]);

    // ultimos n - 3 pontos
    for (int i = 3; i < m; i++)
    {
        // continua no while enquanto os 3 angulos e os pontos nao giram p a esquerda
        while (S.size() > 1 && orientation(nextToTop(S), S.top(), *points[i]) != 2)
            S.pop();
        S.push(*points[i]);
    }

    // manda o resultado pros pontos a serem renderizados
    while (!S.empty())
    {
        Point p = S.top();
        renderPoints.push_back(new Point(p.x, p.y));
        S.pop();
    }
}
