/*********************************************************************
* Trabalho 3 de computacao grafica
* Augusto Pagnossim Frigo
*
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include "gl_canvas2d.h"

#include "bmp.h"
#include "BmpImg.h"
#include "Frames.h"
#include "EntityManager.h"
#include "Pontuacao.h"
#include "keys.h"

int screenWidth = 1200, screenHeight = 700;
Bmp *bmp;
BmpImg *bmpImg;
Frames *frames;
EntityManager *entityManager;
Bezier *bezier;
float fps = 60.0;
int globlkey[KEY_BUFFER];
bool draw = true;
int pontuacao = 0;

void render()
{
   fps = frames->getFrames();
   bmpImg->draw(draw, fps);
   CV::clear(0, 0, 0);
   entityManager->check();
   entityManager->keyboard(globlkey);
   drawPontuacao(pontuacao);
}

void keyboard(int key)
{
   addKey(globlkey, key);
   if (key == 'p')
      draw = !draw;
}

// funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
   removeKey(globlkey, key);
}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   entityManager->mouse(x, y);
   if (state == 0)
   {
      entityManager->click();
   }
}

static inline void initObjects()
{
   bmp = new Bmp(".\\Trab3AugustoPagnossimFrigo\\resources\\bitmap.bmp");
   bmp->convertBGRtoRGB();
   unsigned char *data = bmp->getImage();
   bezier = new Bezier();
   bmpImg = new BmpImg(data, bmp->getWidth(), bmp->getHeight(), 100, 100, bezier);
   frames = new Frames();
   entityManager = new EntityManager(bezier, &fps, &pontuacao);
   initKeys(globlkey);
}

int main(void)
{
   initObjects();
   CV::init(&screenWidth, &screenHeight, "Trabalho 3 de cg - Augusto Frigo");
   CV::run();
}
