#ifndef FIGURE_H
#define FIGURE_H
#include <vector>
#include <string>
#include "Point.h"
#include "color.h"
#include "matrix.h"
#include "bmp/BmpImg.h"
class Figure
{
public:
   Figure(Color color, bool _isIrregular);
   virtual ~Figure();
   void endCreation();
   void endCreation(int r, int g, int b);
   std::string getLabel();
   void changeReduce();
   void changeSelect(bool _selected);
   void transform(Matrix &transformMatrix);
   void concat();
   void fillFigure();
   void loadImg();
   bool checkCollision(int mx, int my);
   void drag(int *initialMx, int *initialMy, int mx, int my);
   void render();
   Color color;
   BmpImg *bmpImg = NULL;
   bool selected;
   bool isIrregular;
   std::vector<Point *> points;
   std::vector<Point *> renderPoints;

private:
   void getMaxMinCoordinates();
   bool isCreating, reduce, shouldFill = false;
   int xMax, yMax, xMin, yMin;
   std::vector<Point *> fillPoints;
};
#endif // FIGURE_H
