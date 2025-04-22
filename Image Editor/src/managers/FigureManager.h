#ifndef FIGUREMANAGER_H
#define FIGUREMANAGER_H

#include <vector>
#include "../Figure.h"
#include "../color.h"
#include "../matrix.h"

class FigureManager
{
public:
   FigureManager(Color *_color);
   virtual ~FigureManager();
   void newFigure();
   void checkNewFigure(int state, int mx, int my);
   void newRegularFigure();
   void changeVertexCount(int v);
   void changeRx(int _rx);
   void changeRy(int _ry);
   void save();
   void read();
   void changeReduce();
   void concat();
   void fillFigure();
   void loadImg();
   void remove();
   void render(int mx, int my);
   void renderLabels();
   void checkDrag(int state, int mx, int my);
   Figure *figureCreating = NULL;
   std::vector<Figure *> figures;
   Color *color;

protected:
private:
   int index = 0, initialMx, initialMy;
   bool dragging = false;
   int rx = 100, ry = 100, vertexCount = 5;
};

#endif // FIGUREMANAGER_H
