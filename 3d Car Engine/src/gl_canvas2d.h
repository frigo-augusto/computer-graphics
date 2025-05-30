#ifndef __CANVAS_2D__H__
#define __CANVAS_2D__H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include "Vector3.h"
#include <list>
#define PI_2 6.28318530717
#define PI 3.14159265359

#define Y_CANVAS_CRESCE_PARA_CIMA 1

class CV // classe Canvas2D
{
public:
    // funcoes para desenho de ponto e linha
    static void point(float x, float y, float z, float d, bool perspectiveActive); // coordeandas do ponto
    static void point(Vector3 pos, float d, bool perspectiveActive);               // coordeandas do ponto
    static void point(std::list<Vector3> &points);

    static void line(float x1, float y1, float x2, float y2);                  // coordenadas da linha x1, y1, x2, y2
    static void line(Vector3 p1, Vector3 p2, float d, bool perspectiveActive); // coordenadas da linha (p1, p2)

    // desenha um retangulo alinhado nos eixos x e y
    static void rect(float x1, float y1, float x2, float y2); // coordenadas do retangulo x1, y1, x2, y2
    static void rect(Vector3 p1, Vector3 p2);                 // coordenadas do retangulo (p1, p2) - TO DO

    static void rectFill(float x1, float y1, float x2, float y2); // coordenadas do retangulo x1, y1, x2, y2
    static void rectFill(Vector3 p1, Vector3 p2);                 // coordenadas do retangulo (p1, p2)

    // desenha um poligono CONVEXO. Para um retangulo, deve-se passar 4 vertices
    static void polygon(float vx[], float vy[], int n_elems);
    static void polygonFill(float vx[], float vy[], int n_elems);

    // centro e raio do circulo
    static void circle(float x, float y, float radius, int div);
    static void circle(Vector3 pos, float radius, int div);

    static void circleFill(float x, float y, float radius, int div);
    static void circleFill(Vector3 pos, float radius, int div);

    // especifica a cor de desenho e de limpeza de tela
    static void color(float r, float g, float b);
    static void color(float r, float g, float b, float alpha);
    static void color(int index);

    static void clear(float r, float g, float b);

    // desenha texto na coordenada (x,y)
    static void text(float x, float y, const char *t);
    static void text(Vector3 pos, const char *t);

    // coordenada de offset para desenho de objetos.
    static void translate(float x, float y);
    static void translate(Vector3 pos);

    // funcao de inicializacao da Canvas2D. Recebe a largura, altura, e um titulo para a janela
    static void init(int *w, int *h, const char *title);

    // funcao para executar a Canvas2D
    static void run();
};

#endif
