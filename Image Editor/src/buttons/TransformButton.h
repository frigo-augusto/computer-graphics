#include "Button.h"
#include "../managers/TransformationManager.h"

class TransformButton : public Button
{
   using FuncPtr = void (TransformationManager::*)();

public:
   TransformButton(int _x, int _y, int _width, int _height, char *_label, TransformationManager *_instance, FuncPtr _func);
   ~TransformButton();
   void action();

private:
   TransformationManager *instance;
   FuncPtr func;
};