#ifndef __BOTAO_H__
#define __BOTAO_H__
#define LABEL_SIZE 100
#include "../gl_canvas2d.h"
#include "../color.h"

class Button
{

public:
  Button(int _x, int _y, int _width, int _height, char *_label);
  ~Button();
  bool checkCollision(int mx, int my);
  void render();
  virtual void action();

protected:
  char label[LABEL_SIZE];

private:
  int width, height, x, y;
  Color color;
};

#endif
