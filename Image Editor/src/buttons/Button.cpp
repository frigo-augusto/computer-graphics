/*********************************************************************
// Cria um botao clicavel. Classe base para os outros botoes. Baseada na classe Botao das demos.
// *********************************************************************/

#include "Button.h"

Button::Button(int _x, int _y, int _width, int _height, char *_label)
{
    height = _height;
    width = _width;
    x = _x;
    y = _y;
    strcpy(label, _label);
    color = {0, 1, 0};
}

Button::~Button()
{
}

void Button::render()
{
    CV::color(color.r, color.g, color.b);
    CV::rectFill(x, y, x + width, y + height);
    CV::color(0, 0, 0);
    CV::text(x + 5, y + height / 2, label); // texto mais ou menos no centro
}

// deteccao simples de colisao de um quadrado
bool Button::checkCollision(int mx, int my)
{
    if (mx >= x && mx <= (x + width) && my >= y && my <= (y + height))
    {
        return true;
    }
    return false;
}

void Button::action()
{
}
