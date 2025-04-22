/*********************************************************************
// Cria um botao de figura, que recebe um metodo do FigureManager
// *********************************************************************/

#include "FigureButton.h"

void FigureButton::action()
{
   (instance->*func)();
}

FigureButton::FigureButton(int _x, int _y, int _width, int _height, char *_label, FigureManager *_instance, FuncPtr _func) : Button(_x, _y, _width, _height, _label)
{
   instance = _instance;
   func = _func;
}

FigureButton::~FigureButton()
{
}
