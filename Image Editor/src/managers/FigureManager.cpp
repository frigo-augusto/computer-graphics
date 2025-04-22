/*********************************************************************
// Classe para gerenciamento de figuras, contem os metodos de manipulacao de figuras.
// *********************************************************************/

#include "FigureManager.h"
#include "../gl_canvas2d.h"
#include "../encryption.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#define CRYPT_KEY 32

FigureManager::FigureManager(Color *_color)
{
   color = _color;
}

FigureManager::~FigureManager()
{
   for (auto f : figures)
   {
      delete f;
   }
}

void FigureManager::newFigure()
{
   if (!figureCreating)
   {
      if (!figures.empty())
         figures.back()->changeSelect(false);
      figureCreating = new Figure(*color, true);
      figures.push_back(figureCreating);
   }
}

// chamado constantemente para saber se deve adicionar pontos a figura sendo criada.
void FigureManager::checkNewFigure(int state, int mx, int my)
{
   if (figureCreating && state == 0)
   {
      figureCreating->points.push_back(new Point(mx, my));
      figureCreating->renderPoints.push_back(new Point(mx, my));
   }
}

/*cria um n-agono com base na equacao do circulo. Tem 2 raios para ser possivel criar
 a figura com base em uma elipse.
*/
void FigureManager::newRegularFigure()
{
   float xc = 500, yc = 500;
   float increment = 2 * PI / vertexCount;
   figureCreating = new Figure(*color, false);

   for (float i = 0; i < 2 * PI; i += increment)
   {
      figureCreating->points.push_back(new Point((int)(xc + rx * cos(i)), (int)(yc + ry * sin(i))));
      figureCreating->renderPoints.push_back(new Point((int)(xc + rx * cos(i)), (int)(yc + ry * sin(i))));
   }

   figures.push_back(figureCreating);
   figureCreating->endCreation();
   figureCreating = NULL;
}

void FigureManager::changeVertexCount(int v)
{
   if (vertexCount + v > 1)
      vertexCount += v;
}

void FigureManager::changeRx(int _rx)
{
   if (rx + _rx > 0)
      rx += _rx;
}

void FigureManager::changeRy(int _ry)
{
   if (ry + _ry > 0)
      ry += _ry;
}

// salva em um formato legivel.
void FigureManager::save()
{
   std::stringstream strs;
   std::ofstream File("Trab1AugustoPagnossimFrigo/points.txt");
   std::string toWrite;
   for (auto f : figures)
   {
      if (f->isIrregular)
      {
         strs << "!";
      }
      else
      {
         strs << "$";
      }
   }
   strs << "=";
   for (auto f : figures)
   {
      for (auto p : f->renderPoints)
      {
         strs << p->x << "#" << p->y << ",";
      }
      strs << "@" << (int)f->color.r << "@" << (int)f->color.g << "@" << (int)f->color.b << "@";
      strs << ";";
   }
   toWrite = strs.str();
   toWrite = encryptString(toWrite, CRYPT_KEY);
   File << toWrite;
   File.close();
}

// le a figura e computa todos os pontos na memoria.
// le os pontos ate achar um @. Os pontos sao separados por # e , e as cores por #.
// as figuras sao separadas por ;
// tem uma header pra dizer se a figura eh regular ou nao.
void FigureManager::read()
{
   std::string buffer, x, y;
   std::ifstream File;
   std::string colors[3];
   std::vector<bool> isIrregulars;
   File.open("Trab1AugustoPagnossimFrigo/points.txt");
   File >> buffer;
   buffer = decryptString(buffer, CRYPT_KEY);
   for (auto &f : figures)
      delete f;
   figures.clear();
   int i = 0;
   while (buffer[i] != '=')
   {
      if (buffer[i] == '!')
      {
         isIrregulars.push_back(true);
      }
      else
      {
         isIrregulars.push_back(false);
      }
      i++;
   } // pega os dados de regularidade da figura
   i++;
   int currentFigure = 0;
   while (i < buffer.length())
   {
      figureCreating = new Figure(*color, isIrregulars[currentFigure]);
      figures.push_back(figureCreating);
      while (buffer[i] != '@')
      {
         while (buffer[i] != '#')
         {
            x.push_back(buffer[i]);
            i++;
         }
         i++;
         while (buffer[i] != ',')
         {
            y.push_back(buffer[i]);
            i++;
         }
         i++;
         figureCreating->points.push_back(new Point(atoi(x.c_str()), atoi(y.c_str())));
         x.clear();
         y.clear();
      }
      i++;
      int j = 0;
      while (buffer[i] != ';')
      {
         while (buffer[i] != '@')
         {
            colors[j].push_back(buffer[i]);
            i++;
         }
         j++;
         i++;
      }
      i++;
      figureCreating->endCreation(atoi(colors[0].c_str()), atoi(colors[1].c_str()), atoi(colors[2].c_str()));
      for (int i = 0; i < 3; i++)
         colors[i].clear();
      currentFigure++;
   }
   figureCreating = NULL;
   File.close();
}

// altera o booleano que define se o convexHull deve ser aplicado na figura ou nao.
void FigureManager::changeReduce()
{
   if (!figures.empty() && figures.back()->selected)
      figures.back()->changeReduce();
}

// concatena as 2 ultimas figuras na lista (ou seja, as ultimas 2 clicadas).
void FigureManager::concat()
{
   if (figures.size() < 2 || !figures.back()->selected)
      return;

   figures[figures.size() - 2]->points.insert(figures[figures.size() - 2]->points.end(), figures.back()->points.begin(), figures.back()->points.end());
   figures.pop_back();
   figures.back()->concat();
}

void FigureManager::fillFigure()
{
   if (!figures.empty() && figures.back()->selected)
      figures.back()->fillFigure();
}

void FigureManager::loadImg()
{
   if (!figures.empty() && figures.back()->selected)
      figures.back()->loadImg();
}

// remove a ultima figura da lista.
void FigureManager::remove()
{
   if (figures.empty() || !figures.back()->selected)
      return;

   Figure *aux = figures.back();
   delete aux;
   figures.pop_back();
}

// renderiza as figuras e a linha de criacao se estiver sendo criada.
void FigureManager::render(int mx, int my)
{
   for (auto f : figures)
      f->render();
   if (figureCreating && !figures.empty() && !figures.back()->points.empty())
   {
      CV::color(color->r, color->g, color->b);
      CV::line(figureCreating->points.back()->x, figureCreating->points.back()->y, mx, my);   // renderiza a linha que acompanha o mouse na criacao da figura.
      CV::line(mx, my, figureCreating->points.front()->x, figureCreating->points.front()->y); // renderiza a linha que acompanha o mouse na criacao da figura.
   }
}

void FigureManager::renderLabels()
{
   CV::color(1, 1, 1);
   float y = 610;
   int size;
   if (figures.size() < 10)
      size = figures.size();
   else
   {
      size = 10;
   }
   for (int i = figures.size() - 1; i >= 0; i--)
   {
      CV::text(1100.0f, y, figures[i]->getLabel().c_str());
      y -= 50;
   }
}

/*
Verifica se deve mover a figura. O drag so acontece quando uma figura nao esta sendo criada, e ha clique do mouse
na area de colisao da figura. Ao clicar/arrastar, a figura tambem eh selecionada, sendo movida ao fim da lista.
*/
void FigureManager::checkDrag(int state, int mx, int my)
{
   if (state == 0) // clicou
   {
      for (int i = figures.size() - 1; i >= 0; i--)
      { // verifica a colisao de todas as figuras
         if (!figures.empty() && !figureCreating)
         {
            if (figures[i]->checkCollision(mx, my))
            {
               if (!dragging)
               {
                  initialMx = mx;
                  initialMy = my;
               }
               dragging = true;
               figures.back()->changeSelect(false);
               std::swap(figures[i], figures.back());
               figures.back()->changeSelect(true);
               break;
            }
         }
      }
   }
   if (state == 1)
   {
      dragging = false;
   }

   if (dragging && !figureCreating)
      figures.back()->drag(&initialMx, &initialMy, mx, my);
}
