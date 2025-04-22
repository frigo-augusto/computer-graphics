#ifndef WRITABLEELEMENT_H
#define WRITABLEELEMENT_H

#include "buttons/Button.h"

class WritableElement : public Button
{
public:
   WritableElement(int _x, int _y, int _width, int _height, char *_label);
   virtual ~WritableElement();
   void addCharacter(const int toAdd);
   void removeLastCharacter();
   float getInputNumber(int i);
   float getValue();
   char *getLabel();

private:
   float value = 0;
};

#endif // WRITABLEELEMENT_H
