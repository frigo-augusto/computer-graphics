#ifndef TRANSFORMATIONMANAGER_H
#define TRANSFORMATIONMANAGER_H
#include <stack>
#include "../matrix.h"
#include "../WritableMatrix.h"
#include "FigureManager.h"
class TransformationManager
{
public:
   TransformationManager(FigureManager *_figureManager);
   virtual ~TransformationManager();
   void addMatrixToStack();
   void endTransform();
   void render();
   void checkCollision(int mx, int my, int state, int *gbli, int *gblj);
   bool checkWrite(int transformi, int transformj, int key);

private:
   std::stack<Matrix *> transformationStack;
   WritableMatrix *currentMatrix;
   FigureManager *figureManager;
};

#endif // TRANSFORMATIONMANAGER_H
