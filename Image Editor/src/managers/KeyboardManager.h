/******
 * /// Classe para tratamento dos eventos do teclado.
 * ///
 ******/

#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include "FigureManager.h"
#define ENTER 13

class KeyboardManager
{
public:
   KeyboardManager(FigureManager *_figureManager)
   {
      figureManager = _figureManager;
   }
   ~KeyboardManager()
   {
   }
   void checkKeys(int key)
   {
      switch (key)
      {
      case 'u':
         figureManager->changeVertexCount(1);
         break;
      case 'j':
         figureManager->changeVertexCount(-1);
         break;
      case 'i':
         figureManager->changeRx(50);
         break;
      case 'k':
         figureManager->changeRx(-50);
         break;
      case 'o':
         figureManager->changeRy(50);
         break;
      case 'l':
         figureManager->changeRy(-50);
         break;
      case 'c':
         figureManager->changeVertexCount(1000); // cria aproximacao para o circulo
         break;
      case 'p':
         figureManager->changeVertexCount(5);
         break;
      case ENTER:
         if (figureManager->figureCreating)
         {
            figureManager->figureCreating->endCreation();
            figureManager->figureCreating = NULL;
         }
         break;
      }

      if (!figureManager->figures.empty() && figureManager->figures.back()->bmpImg)
      { // verifica se esta vazio pois vai aplicar transformacoes na lista
         Figure *toApply = figureManager->figures.back();
         switch (key)
         {
         case 'r':
            toApply->bmpImg->convertToRedScale();
            break;
         case 'g':
            toApply->bmpImg->convertToGreenScale();
            break;
         case 'b':
            toApply->bmpImg->convertToBlueScale();
            break;
         case 'v':
            toApply->bmpImg->convertToGrayScale();
            break;
         case 'f':
            toApply->bmpImg->invertColors();
            break;
         }
      }
   }

private:
   FigureManager *figureManager;
};

#endif
