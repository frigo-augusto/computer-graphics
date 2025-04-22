/*********************************************************************
Trabalho 4 de computacao grafica
Augusto Pagnossim Frigo
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include "gl_canvas2d.h"
#include "Vector3.h"
#include "Frames.h"
#include "element.h"
#include <vector>
#include <algorithm>

#define ELEMENTS 3

Frames *frames;
float fps = 60;
int screenWidth = 1200, screenHeight = 800;
float globlAng = 0.001;
float accAng = globlAng;
float rotateYAng = 0.0;
float rotateXAng = 0.0;
std::vector<Line> lines;
int d = 100;
bool perspectiveActive = true;
int mp = 0;
bool stop = false;
std::vector<Element *> elements;

bool compare(Line l1, Line l2)
{
   float avg1 = (l1.p1.z + l1.p2.z) / 2;
   float avg2 = (l2.p1.z + l2.p2.z) / 2;
   return avg1 > avg2;
}

void render()
{
   CV::clear(0, 0, 0);
   CV::translate(screenWidth >> 1, screenHeight >> 1);
   fps = frames->getFrames();
   globlAng = 1 / fps;
   if (!stop)
      accAng += globlAng;
   if (accAng >= 2 * PI)
      accAng -= 2 * PI;
   for (auto e : elements)
   {
      e->generate(accAng, lines, &mp);
   }

   rotateMatrixAlongY(elements[elements.size() - 1]->manivela->center, lines, rotateYAng, &mp);
   rotateMatrixAlongX(elements[elements.size() - 1]->manivela->center, lines, rotateXAng, &mp);
   std::sort(lines.begin(), lines.end(), compare); // caso seu jogo tenha virado uma apresentacao de slides, comentar pode ser uma boa. Essa linha mostra as coisas na ordem certa.
   renderGlobalMatrix(lines, d, perspectiveActive);
   lines.clear();
   mp = 0;
}

void keyboard(int key)
{
   if (key == 'y')
   {
      rotateYAng += 0.1;
   }
   if (key == 'x')
   {
      rotateXAng += 0.1;
   }
   if (key == 'p')
   {
      perspectiveActive = !perspectiveActive;
   }
   if (key == 'd')
   {
      d++;
   }
   if (key == 'f')
   {
      stop = !stop;
   }
}

void keyboardUp(int key)
{
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
}

int main(void)
{
   frames = new Frames();
   for (int i = 0; i < ELEMENTS; i++)
   {
      elements.push_back(new Element(i));
   }

   CV::init(&screenWidth, &screenHeight, "Titulo da Janela: Canvas 2D - Pressione 1, 2, 3");
   CV::run();
}
