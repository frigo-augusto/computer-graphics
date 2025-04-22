/***
Classe que cria e gerencia uma imagem bmp armazenada em uma struct. Tem metodo para
criar e para fazer todas as transformacoes na imagem
***/

#include "BmpImg.h"

#define COLOR_SIZE 256
#define CHAR_LIMIT 255.0f
#define CHAR_LIMIT_I 255
#define HIST_X 750
#define HIST_Y 500
#define HIST_INCREMENT 200
#define HIST_SCALE 10

void BmpImg::initVariables(int localWidth, int localHeight, int initialX, int initialY, bool *_selected)
{
    width = localWidth;
    height = localHeight;
    x = initialX;
    y = initialY;
    xScale = 1;
    yScale = 1;
    points = (BmpPoint *)malloc(width * height * sizeof(BmpPoint));
    selected = _selected;
}

// pega o bitmap e transforma para um vetor de struct
void BmpImg::initStruct(unsigned char *data)
{
    int xCounter = 0;
    int yCounter = 0;
    int i = 0;
    int j = 0;
    while (xCounter < width && yCounter < height)
    {
        points[j].r = data[i];
        points[j].g = data[i + 1];
        points[j].b = data[i + 2];
        points[j].x = xCounter;
        points[j].y = yCounter;
        xCounter++;
        i += 3;
        j++;

        if (xCounter >= width)
        {
            xCounter = 0;
            yCounter++;
        }
    }
    for (int i = 0; i < width * height; i++)
    {
        points[i].x += x;
        points[i].y += y;
        points[i].x -= width / 2; // move a imagem p o centro da figura
        points[i].y -= height / 2;
    }
}

BmpImg ::BmpImg(unsigned char *data, int localWidth, int localHeight, int initialX, int initialY, std::vector<Point *> _renderPoints, bool *_selected)
{
    initVariables(localWidth, localHeight, initialX, initialY, _selected);
    initStruct(data);
    for (int i = 0; i < width * height; i++)
    {
        if (isPointInsidePolygon(points[i].x, points[i].y, _renderPoints))
        { // adiciona o que estiver dentro do poligono p ser renderizado
            renderPoints.push_back(points[i]);
        }
    }
}

BmpImg::~BmpImg()
{
    free(points);
}

// renderiza a imagem
void BmpImg::render()
{

    Vector2 p;
    for (int j = 0; j < renderPoints.size(); j++)
    {
        CV::color(renderPoints[j].r / CHAR_LIMIT, renderPoints[j].g / CHAR_LIMIT, renderPoints[j].b / CHAR_LIMIT);
        p.set(renderPoints[j].x, renderPoints[j].y);
        CV::point(p);
    }
    if (*selected)
    {
        showRedHistogram();
        showBlueHistogram();
        showGreenHistogram();
    }
}

// calcula uma novo valor para a imagem cinza
void BmpImg::convertToGrayScale()
{
    for (int i = 0; i < renderPoints.size(); i++)
    {
        int lum = renderPoints[i].r * 0.21 + renderPoints[i].g * 0.72 + renderPoints[i].b * 0.07; // equacao de conversao para escala cinza
        renderPoints[i].r = lum;
        renderPoints[i].g = lum;
        renderPoints[i].b = lum;
    }
}

void BmpImg::convertToRedScale()
{ // escala de vermelho zerando outras cores
    for (int i = 0; i < renderPoints.size(); i++)
    {
        renderPoints[i].g = 0;
        renderPoints[i].b = 0;
    }
}

void BmpImg::convertToGreenScale()
{ // escala de verde zerando outras cores
    for (int i = 0; i < renderPoints.size(); i++)
    {
        renderPoints[i].r = 0;
        renderPoints[i].b = 0;
    }
}

void BmpImg::convertToBlueScale()
{ // escala de azul zerando outras cores
    for (int i = 0; i < renderPoints.size(); i++)
    {
        renderPoints[i].r = 0;
        renderPoints[i].g = 0;
    }
}

void BmpImg::showRedHistogram()
{
    int histX = HIST_X;
    int histY = HIST_Y;
    Vector2 p;

    float occurences[COLOR_SIZE];
    for (int i = 0; i < COLOR_SIZE; i++)
    {
        occurences[i] = 0;
    }

    for (int i = 0; i < renderPoints.size(); i++)
    {
        (occurences[renderPoints[i].r])++; // incrementa a posicao referente ao valor de R, gerando assim as informacoes
    }
    for (int i = 0; i < COLOR_SIZE; i++)
    {
        occurences[i] = log(occurences[i]) * HIST_SCALE; // logaritmico pra ficar visivel
    }

    for (int i = 0; i < COLOR_SIZE; i++)
    {
        int j = occurences[i];
        while (j > 0)
        { // desenha o ponto ate a coordenada inicial
            CV::color(255 / CHAR_LIMIT, 0 / CHAR_LIMIT, 0 / CHAR_LIMIT);
            p.set(histX + i, histY + j);
            CV::point(p);
            j--;
        }
    }
}

void BmpImg::showGreenHistogram()
{
    int histX = HIST_X;
    int histY = HIST_Y - HIST_INCREMENT;
    Vector2 p;

    float occurences[COLOR_SIZE];
    for (int i = 0; i < COLOR_SIZE; i++)
    {
        occurences[i] = 0;
    }

    for (int i = 0; i < renderPoints.size(); i++)
    {
        (occurences[renderPoints[i].g])++; // incrementa a posicao referente ao valor de G, gerando assim as informacoes
    }
    for (int i = 0; i < COLOR_SIZE; i++)
    {
        occurences[i] = log(occurences[i]) * HIST_SCALE; // logaritmico pra ficar visivel
    }

    for (int i = 0; i < COLOR_SIZE; i++)
    {
        int j = occurences[i];
        while (j > 0)
        { // desenha o ponto ate a coordenada inicial
            CV::color(0, 255 / CHAR_LIMIT, 0 / CHAR_LIMIT);
            p.set(histX + i, histY + j);
            CV::point(p);
            j--;
        }
    }
}

void BmpImg::showBlueHistogram()
{
    int histX = HIST_X;
    int histY = HIST_Y - HIST_INCREMENT*2;
    Vector2 p;

    float occurences[COLOR_SIZE];
    for (int i = 0; i < COLOR_SIZE; i++)
    {
        occurences[i] = 0;
    }

    for (int i = 0; i < renderPoints.size(); i++)
    { // incrementa a posicao referente ao valor de B, gerando assim as informacoes
        (occurences[renderPoints[i].b])++;
    }
    for (int i = 0; i < COLOR_SIZE; i++)
    {
        occurences[i] = log(occurences[i]) * HIST_SCALE; // logaritmico pra ficar visivel, * 10 eh escala
    }

    for (int i = 0; i < COLOR_SIZE; i++)
    {
        int j = occurences[i];
        while (j > 0)
        { // desenha o ponto ate a coordenada inicial
            CV::color(0, 0, 255 / CHAR_LIMIT);
            p.set(histX + i, histY + j);
            CV::point(p);
            j--;
        }
    }
}

// calculo basico de inversao de cores
void BmpImg::invertColors()
{
    for (int i = 0; i < renderPoints.size(); i++)
    {
        renderPoints[i].r = CHAR_LIMIT_I - renderPoints[i].r;
        renderPoints[i].g = CHAR_LIMIT_I - renderPoints[i].g;
        renderPoints[i].b = CHAR_LIMIT_I - renderPoints[i].b;
    }
}
