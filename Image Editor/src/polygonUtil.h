
#pragma once

#include "Point.h"
#include <stack>

extern bool isPointInsidePolygon(int mx, int my, const std::vector<Point *> &points);
extern void convexHull(std::vector<Point *> points, std::vector<Point *> &renderPoints, int size);
