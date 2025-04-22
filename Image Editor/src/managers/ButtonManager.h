#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H
#include <vector>
#include "../Figure.h"
#include "../buttons/Button.h"
#include "FigureManager.h"
#include "TransformationManager.h"

typedef unsigned char uchar;

class ButtonManager
{
public:
   using FuncPtr = void (FigureManager::*)();
   void render();
   void check(int mx, int my, int state);
   ButtonManager(FigureManager *figureManager, TransformationManager *transformationManager, int screenWidth, int screenHeight);
   virtual ~ButtonManager();
   std::vector<Button *> buttons;

private:
   void newFigure();
};

#endif // BUTTONMANAGER_H
