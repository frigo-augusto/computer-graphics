/*********************************************************************
// Classe para gerenciamento de botoes que guardam input do teclado.
// *********************************************************************/

#include "WritableElement.h"
#define SHIFT 212
#define PI 3.141592

WritableElement::WritableElement(int _x, int _y, int _width, int _height, char *_label) : Button(_x, _y, _width, _height, _label)
{
}

WritableElement::~WritableElement()
{
   // dtor
}

inline float degreesToRadians(float degrees)
{
   return degrees * PI / 180;
}

//acha o fim do ponteiro de char e coloca mais um caractere
void WritableElement::addCharacter(const int toAdd)
{
   int i = 0;
   while (label[i] != '\0')
      i++;
   if (i < LABEL_SIZE && toAdd != SHIFT)
   {
      label[i] = (char)toAdd;
      label[i + 1] = '\0';
   }
}

void WritableElement::removeLastCharacter()
{
   int i = 0;
   while (label[i] != '\0')
   {
      i++;
   }
   if (i >= 0)
      label[i - 1] = '\0';
}

// pega o float correspondente a entrada
float WritableElement::getInputNumber(int i)
{
   char n[LABEL_SIZE];
   int j = 0;
   while (label[i] != ')' && label[i] != '\0')
   {
      n[j] = label[i];
      i++;
      j++;
   }
   n[j] = '\0';
   return strtof(n, NULL);
}

/*
Verifica se eh numero ou funcao seno/cosseno, e retorna o valor de acordo.
*/
float WritableElement::getValue()
{
   if (label[0] >= '0' && label[0] <= '9')
   {
      return getInputNumber(0);
   }
   else if (label[0] == 'c' && label[1] == 'o' && label[2] == 's')
   {
      return cos(degreesToRadians(getInputNumber(4)));
   }
   else if (label[0] == 's' && label[1] == 'i' && label[2] == 'n')
   {
      return sin(degreesToRadians(getInputNumber(4)));
   }
   else if (label[0] == '-' && label[1] == 'c' && label[2] == 'o' && label[3] == 's')
   {
      return -1 * cos(degreesToRadians(getInputNumber(5)));
   }
   else if (label[0] == '-' && label[1] == 's' && label[2] == 'i' && label[3] == 'n')
   {
      return -1 * sin(degreesToRadians(getInputNumber(5)));
   }
   return 0;
}

char *WritableElement::getLabel()
{
   return label;
}