
/***
Gerencia todos os botoes, criando-os, renderizando e checando as colisoes.
***/
#include "ButtonManager.h"
#include "../buttons/FigureButton.h"
#include "../buttons/TransformButton.h"
#define SIZE 75
#define INTERVAL 20
#define INI_Y 610

void ButtonManager::render()
{
   for (auto b : buttons)
   {
      b->render();
   }
}

// cria os botoes e passa os ponteiros de funcao para a acao de cada um
ButtonManager::ButtonManager(FigureManager *figureManager, TransformationManager *transformationManager, int screenWidth, int screenHeight)
{
   buttons.push_back(new FigureButton(INTERVAL, INI_Y, SIZE, SIZE, "!regular", figureManager, &figureManager->newFigure));
   buttons.push_back(new FigureButton(INTERVAL, INI_Y - SIZE - INTERVAL, SIZE, SIZE, "bmp", figureManager, &figureManager->loadImg));
   buttons.push_back(new FigureButton(INTERVAL, INI_Y - SIZE * 2 - INTERVAL * 2, SIZE, SIZE, "save", figureManager, &figureManager->save));
   buttons.push_back(new FigureButton(INTERVAL, INI_Y - SIZE * 3 - INTERVAL * 3, SIZE, SIZE, "read", figureManager, &figureManager->read));
   buttons.push_back(new FigureButton(INTERVAL, INI_Y - SIZE * 4 - INTERVAL * 4, SIZE, SIZE, "regular", figureManager, &figureManager->newRegularFigure));
   buttons.push_back(new FigureButton(INTERVAL * 2 + SIZE, INI_Y, SIZE, SIZE, "concat", figureManager, &figureManager->concat));
   buttons.push_back(new FigureButton(INTERVAL * 2 + SIZE, INI_Y - SIZE - INTERVAL, SIZE, SIZE, "delete", figureManager, &figureManager->remove));
   buttons.push_back(new FigureButton(INTERVAL * 2 + SIZE, INI_Y - SIZE * 2 - INTERVAL * 2, SIZE, SIZE, "fill", figureManager, &figureManager->fillFigure));
   buttons.push_back(new FigureButton(INTERVAL * 2 + SIZE, INI_Y - SIZE * 3 - INTERVAL * 3, SIZE, SIZE, "reduce", figureManager, &figureManager->changeReduce));

   buttons.push_back(new TransformButton(INTERVAL * 3 + SIZE * 3, INI_Y, SIZE, SIZE, "add", transformationManager, &transformationManager->addMatrixToStack));
   buttons.push_back(new TransformButton(INTERVAL * 7 + SIZE * 4, INI_Y, SIZE, SIZE, "end", transformationManager, &transformationManager->endTransform));
}

ButtonManager::~ButtonManager()
{
   for (auto b : buttons)
   {
      delete b;
   }
}

// chama checagem de colisao
void ButtonManager::check(int mx, int my, int state)
{
   if (state != 0)
      return;
   for (auto b : buttons)
   {
      if (b->checkCollision(mx, my))
      {
         b->action();
         break;
      }
   }
}
