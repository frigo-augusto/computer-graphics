
#include "Button.h"
#include "../managers/FigureManager.h"

class FigureButton : public Button
{
   using FuncPtr = void (FigureManager::*)();

public:
   FigureButton(int _x, int _y, int _width, int _height, char *_label, FigureManager *_instance, FuncPtr _func);
   ~FigureButton();
   void action();

private:
   FigureManager *instance;
   FuncPtr func;
};
