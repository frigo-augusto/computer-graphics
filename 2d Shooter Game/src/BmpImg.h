#ifndef BMP_IMG_H
#define BMP_IMG_H
#define SCENARIO_LIMIT 10
#define SCENARIO_INCREMENT 1000
#include "Bezier.h"

/***
 * Classe que le o bmp e pinta ele no cenario
 */

typedef struct bmpPoint
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    int x;
    int y;
} BmpPoint; // struct pra armazenar os dados de cada pixel

class BmpImg
{

public:
    void initVariables(int localWidth, int localHeight, int initialX, int initialY, Bezier *_bezier)
    {
        width = localWidth;
        height = localHeight;
        x = 0;
        y = 0;
        xScale = 1;
        yScale = 1;
        cicleCounter = 256;
        points = (BmpPoint *)malloc(width * height * sizeof(BmpPoint));
        bezier = _bezier;
    }
    void initStruct(unsigned char *data)
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
    }
    BmpPoint *getPoints()
    {
        return points;
    }
    BmpImg(unsigned char *data, int localWidth, int localHeight, int initialX, int initialY, Bezier *_bezier)
    {
        initVariables(localWidth, localHeight, initialX, initialY, _bezier);
        initStruct(data);
    }
    void draw(bool draw, float fps) // itera pelo bmp e faz ele loopar, ajustando a camera e pintando os pontos de acordo com onde esta a camera.
    {
        int NUM_FIGS = 10;
        int localHeight = SCREEN_HEIGHT;
        int passoMax = SCREEN_HEIGHT * (SCENARIO_LIMIT + 1);
        for (int i = cameraY * width; i < cameraY * width + localHeight * width; i++)
        {
            int j = i % (width * localHeight * NUM_FIGS);
            int localPasso = cameraY;
            if (j <= SCREEN_HEIGHT * width * 2 && cameraY > SCREEN_HEIGHT * (SCENARIO_LIMIT - 1))
            {
                localPasso -= SCREEN_HEIGHT * SCENARIO_LIMIT;
            }
            if (draw)
            {
                CV::color(points[j].r / 255.0, points[j].g / 255.0, points[j].b / 255.0);
                CV::point(points[j].x, points[j].y - localPasso);
            }
        }
        cameraY += (int)SCENARIO_INCREMENT * (1 / fps);
        if (cameraY >= passoMax)
        {
            cameraY = SCREEN_HEIGHT;
        }
        bezier->render(cameraY);
    }
    ~BmpImg()
    {
        free(points);
    }

private:
    int cameraY = 0;
    float xScale, yScale;
    BmpPoint *points;
    int width, height, x, y;
    float cicleCounter;
    bool firstRender = true;
    Bezier *bezier;
};

#endif
