/*********************************************************************
// Classe que contem os metodos internos de cada figura.
// *********************************************************************/

#include "Figure.h"
#include "gl_canvas2d.h"
#include <stack>
#include <algorithm>
#include <string>
#include "polygonUtil.h"
#include "color.h"
#include "bmp/bmp.h"
#include "bmp/BmpImg.h"

#define CHAR_LIMIT 255.0f

Figure::Figure(Color _color, bool _isIrregular)
{
   color = _color;
   reduce = false;
   selected = false;
   isCreating = true;
   isIrregular = _isIrregular;
}

Figure::~Figure()
{
   for (auto &p : points)
   {
      delete p;
   }
   for (auto &p : renderPoints)
   {
      delete p;
   }
   for (auto &p : fillPoints)
   {
      delete p;
   }
   if (bmpImg)
      delete bmpImg;
}

void Figure::endCreation()
{
   isCreating = false;
   renderPoints.clear();
   renderPoints.resize(points.size());
   Matrix *m = new Matrix(2, 2);
   transform(*m); // aplica a transformacao da matriz identidade para aproveitar as copias
   delete m;
}

void Figure::endCreation(int r, int g, int b)
{
   color.r = (float)r, color.g = (float)g, color.b = (float)b;
   endCreation();
}

void Figure::getMaxMinCoordinates()
{
   xMax = INT_MIN, yMax = INT_MIN, xMin = INT_MAX, yMin = INT_MAX;
   for (auto p : renderPoints)
   {
      if (p->x > xMax)
         xMax = p->x;
      if (p->y > yMax)
         yMax = p->y;
      if (p->x < xMin)
         xMin = p->x;
      if (p->y < yMin)
         yMin = p->y;
   }
}

std::string Figure::getLabel()
{
   if (isIrregular)
      return "irregular";
   int size = points.size();
   if (size > 25)
      return "circulo/elipse";
   switch (size)
   {
   case 1:
      return "Ponto";
   case 2:
      return "Linha";
   case 3:
      return "Triangulo";
   case 4:
      return "Quadrado";
   default:
      return std::to_string(size) + "-agono";
   }
}

void Figure::changeReduce()
{
   reduce = !reduce;
   Matrix *m = new Matrix(2, 2); // aplica o convexHull
   transform(*m);
   delete (m);
}

void Figure::changeSelect(bool _selected)
{
   selected = _selected;
}

/*
Pega todos os pontos, os move para a origem, colocando em um vector auxiliar.
Apos, faz uma transformacao linear de acordo com a concatenacao de matrizes de transformacao
especificada pelo usuario
Apos transformar, move de volta para onde estava, e copia para o vetor de renderizacao,
de acordo com a especificacao do usuario (se o convexHull deve ser aplicado ou nao),
se deve haver fill, se deve carregar imagem.
*/
void Figure::transform(Matrix &transformMatrix)
{
   std::vector<Point *> transformPoints;
   Point *origin = new Point(0, 0);
   for (auto p : points)
   {
      origin->x += p->x;
      origin->y += p->y;
   }
   origin->x /= points.size(); // pega a media da posicao dos pontos
   origin->y /= points.size();
   transformPoints.resize(points.size());
   for (int i = 0; i < points.size(); i++)
   { // leva a origem
      transformPoints[i] = new Point(points[i]->x - origin->x, points[i]->y - origin->y);
   }

   for (auto &p : transformPoints)
   { // transforma
      p = transformMatrix * *p;
   }

   for (int i = 0; i < transformPoints.size(); i++)
   { // leva de volta
      transformPoints[i]->x += origin->x;
      transformPoints[i]->y += origin->y;
   }

   if (!renderPoints.empty())
   {
      for (auto &p : renderPoints)
         delete p;
   }
   renderPoints.clear();
   if (reduce)
   {
      convexHull(transformPoints, renderPoints, points.size());
   }
   else
   {
      renderPoints.resize(transformPoints.size());
      std::copy(transformPoints.begin(), transformPoints.end(), renderPoints.begin());
   }
   getMaxMinCoordinates();
   if (shouldFill)
      fillFigure();
   if (bmpImg)
      loadImg();
}

// a concat das duas listas eh feita no manager, aqui aplicamos o convexHull pois
// a concatenacao nao pode ser feita sem ele. A concatenacao nao preserva os pontos originais.
void Figure::concat()
{
   if (bmpImg)
   {
      delete bmpImg;
      bmpImg = NULL;
   }
   shouldFill = true; // para o metodo setar p false
   fillFigure();
   isIrregular = true;
   renderPoints.clear();
   convexHull(points, renderPoints, points.size());
   points.clear();
   std::copy(renderPoints.begin(), renderPoints.end(), points.begin());
}

/*
Itera todo o poligono como se fosse um quadrado
Se estiver dentro de acordo com a colisao, pinta.
*/
void Figure::fillFigure()
{
   for (auto &p : fillPoints)
   { // limpa a lista de pontos
      delete p;
   }
   fillPoints.clear();
   if (shouldFill)
   {
      shouldFill = false;
      return;
   }
   shouldFill = true;

   for (int i = xMin; i < xMax; i++)
   {
      for (int j = yMin; j < yMax; j++)
      {
         if (isPointInsidePolygon(i, j, renderPoints))
            fillPoints.push_back(new Point(i, j));
      }
   }
}

void Figure::loadImg()
{
   if (bmpImg)
   {
      delete bmpImg;
      bmpImg = NULL;
      return;
   }
   Bmp *bmp = new Bmp(".\\Trab1AugustoPagnossimFrigo\\figuras\\normal_1.bmp");
   bmp->convertBGRtoRGB();
   unsigned char *data = bmp->getImage();
   bmpImg = new BmpImg(data, bmp->getWidth(), bmp->getHeight(), (xMin + xMax) / 2, (yMin + yMax) / 2, renderPoints, &selected);
   delete bmp;
}

bool Figure::checkCollision(int mx, int my)
{
   return isPointInsidePolygon(mx, my, renderPoints);
}

// move a figura de acordo com onde o mouse esta.
// Atualiza tanto o render quanto os pontos originais, para que voltar com a figura ao estado original
// nao mude sua posicao na tela.
void Figure::drag(int *initialMx, int *initialMy, int mx, int my)
{
   for (auto p : renderPoints)
   {
      p->x += mx - *initialMx;
      p->y += my - *initialMy;
   }

   if (!fillPoints.empty())
   {
      for (auto p : fillPoints)
      {
         p->x += mx - *initialMx;
         p->y += my - *initialMy;
      }
   }

   for (auto p : points)
   {
      p->x += mx - *initialMx;
      p->y += my - *initialMy;
   }

   if (bmpImg)
   {
      for (auto &p : bmpImg->renderPoints)
      {
         p.x += mx - *initialMx;
         p.y += my - *initialMy;
      }
   }

   *initialMx = mx;
   *initialMy = my;
   getMaxMinCoordinates();
}

static inline void renderAux(std::vector<Point *> v, bool isCreating)
{
   int size = v.size();
   for (int i = 0; i < size - 1; i++)
   {
      CV::line(v[i]->x, v[i]->y, v[i + 1]->x, v[i + 1]->y);
   }
   if (size > 1 && !isCreating) // linha que conecta o fim dos pontos ao inicio, so eh adicionada qnd a figura esta completa.
      CV::line(v[size - 1]->x, v[size - 1]->y, v[0]->x, v[0]->y);
}

void Figure::render()
{
   if (selected)
   {
      CV::color(1, 1, 0);
   }
   else
   {
      CV::color(color.r / CHAR_LIMIT, color.g / CHAR_LIMIT, color.b / CHAR_LIMIT);
   }

   renderAux(renderPoints, isCreating); // renderiza as linhas da figura

   for (auto p : fillPoints)
      CV::point(p->x, p->y); // renderiza a pintura do poligono
   if (bmpImg)
      bmpImg->render(); // renderiza a imagem bmp
}
