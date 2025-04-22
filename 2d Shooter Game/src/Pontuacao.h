#ifndef PONTUACAO_H
#define PONTUACAO_H
#include "gl_canvas2d.h"

/***
 * Funcoes para desenho da pontuacao
 */

char *itoc(int n)
{
    char buffer[10];
    std::snprintf(buffer, sizeof(buffer), "%d", n);
    char *numberChar = buffer;
    return numberChar;
}

void drawPontuacao(int pontuacao)
{
    CV::color(1, 1, 1);
    char *text = itoc(pontuacao);
    CV::text(50, 50, text);
    free(text);
}

#endif // PONTUACAO_H
