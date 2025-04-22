/*********************************************************************
// Trabalho 1 de computacao grafica - Augusto Pagnossim Frigo
// Programa para manipulacao de figuras vetoriais.
// Para instrucoes de uso, consulte o readme.
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include "gl_canvas2d.h"
#include "Figure.h"
#include "managers/ButtonManager.h"
#include "managers/ColorManager.h"
#include "managers/TransformationManager.h"
#include "managers/KeyboardManager.h"

int mx = 0, my = 0, transformi = -1, transformj = -1;
ButtonManager *buttonManager;
FigureManager *figureManager;
ColorManager *colorManager;
TransformationManager *transformationManager;
KeyboardManager *keyboardManager;
Color color;

void render()
{
   CV::clear(0, 0, 0);
   figureManager->render(mx, my);
   figureManager->renderLabels();
   buttonManager->render();
   colorManager->render();
   transformationManager->render();
}

void keyboard(int key)
{
   bool typing = transformationManager->checkWrite(transformi, transformj, key);
   if (!typing)
      keyboardManager->checkKeys(key);
}

// nao ta sendo usada mas da erro se removida
void keyboardUp(int key)
{
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   figureManager->checkNewFigure(state, mx, my);
   buttonManager->check(mx, my, state);
   figureManager->checkDrag(state, mx, my);
   transformationManager->checkCollision(mx, my, state, &transformi, &transformj);
   color = colorManager->checkCollision(mx, my, state);
   mx = x;
   my = y;
}

void begin(int screenWidth, int screenHeight)
{
   figureManager = new FigureManager(&color);
   transformationManager = new TransformationManager(figureManager);
   buttonManager = new ButtonManager(figureManager, transformationManager, screenWidth, screenHeight);
   colorManager = new ColorManager(15, 15, 200);
   keyboardManager = new KeyboardManager(figureManager);
}

void end()
{
   delete figureManager;
   delete buttonManager;
   delete colorManager;
   delete transformationManager;
   delete keyboardManager;
}

int main(void)
{
   int screenWidth = 1300, screenHeight = 700;
   begin(screenWidth, screenHeight);
   CV::init(&screenWidth, &screenHeight, "Trabalho 1 de cg - Augusto Frigo");
   CV::run();
   end();
}
