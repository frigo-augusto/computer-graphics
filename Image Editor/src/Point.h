#ifndef POINT_H
#define POINT_H

class Point
{
public:
   Point();
   Point(int _x, int _y);
   virtual ~Point();
   int x, y;
};

#endif // POINT_H
