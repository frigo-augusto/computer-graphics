#ifndef BMP_IMG_H
#define BMP_IMG_H

#include <vector>
#include "../Point.h"
#include "../gl_canvas2d.h"
#include "../polygonUtil.h"

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
    void initVariables(int localWidth, int localHeight, int initialX, int initialY, bool *_selected);
    void initStruct(unsigned char *data);
    BmpImg(unsigned char *data, int localWidth, int localHeight, int initialX, int initialY, std::vector<Point *>, bool *_selected);
    void render();
    void convertToGrayScale();
    void convertToRedScale();
    void convertToGreenScale();
    void convertToBlueScale();
    void showRedHistogram();
    void showGreenHistogram();
    void showBlueHistogram();
    void invertColors();
    ~BmpImg();
    std::vector<bmpPoint> renderPoints;

private:
    bool *selected;
    BmpPoint *points;
    float xScale, yScale;
    int width, height, x, y;
};

#endif
