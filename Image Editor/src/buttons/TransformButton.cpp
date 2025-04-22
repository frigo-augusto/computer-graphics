/*********************************************************************
// Cria um botao de transformacao, que crecebe um metodo do TransformationManager
// *********************************************************************/

#include "TransformButton.h"

void TransformButton::action()
{
   (instance->*func)();
}

TransformButton::TransformButton(int _x, int _y, int _width, int _height, char *_label, TransformationManager *_instance, FuncPtr _func) : Button(_x, _y, _width, _height, _label)
{
   instance = _instance;
   func = _func;
}

TransformButton::~TransformButton()
{
}
