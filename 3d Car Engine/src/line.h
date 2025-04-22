#ifndef LINE_H
#define LINE_H
#include "Vector3.h"

class Line
{
public:
   Vector3 p1;
   Vector3 p2;

   Line()
   {
   }

   Line(Vector3 _p1, Vector3 _p2)
   {
      p1 = _p1;
      p2 = _p2;
   }

   virtual ~Line() {}
};

#endif