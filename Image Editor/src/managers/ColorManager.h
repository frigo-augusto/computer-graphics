/*
 * Classe para gerenciamento da paleta de cores. Gera o quadrado que contem as cores aceitas
 * pelo programa.
 */

#ifndef COLORMANAGER_H
#define COLORMANAGER_H
#include "../Point.h"
#include "../gl_canvas2d.h"
#include "../color.h"
#define CHAR_LIMIT 255.0f

class ColorManager
{
public:
   ColorManager(int _x, int _y, int _width)
   {
      width = _width;
      x = _x;
      y = _y;
      div = CHAR_LIMIT / _width;
      color.r = 1, color.g = 1, color.b = 1;
   }

   /*
   quanto mais a esquerda, mais vermelho
   mais pra cima, mais azul
   mais pra baixo, mais verde
   */
   void render()
   {
      for (int i = 0; i < width; i++)
      {
         for (int j = 0; j < width; j++)
         {
            CV::color(((width - j) * div) / CHAR_LIMIT, ((width - i) * div) / CHAR_LIMIT, (i * div) / CHAR_LIMIT);
            CV::point(x + j, y + i);
         }
      }
   }

   // recebe as coordenadas do mouse e retorna a cor de acordo com o calculo feito no render
   Color checkCollision(int mx, int my, int state)
   {
      if (mx >= x && mx <= (x + width) && my >= y && my <= (y + width) && state == 0)
      {
         color.r = (width - (mx - x)) * div;
         color.g = (width - (my - y)) * div;
         color.b = (my - y) * div;
      }
      return color;
   }

   virtual ~ColorManager()
   {
   }

private:
   Color color;
   int width, x, y;
   float div;
};

#endif // COLORMANAGER_H
