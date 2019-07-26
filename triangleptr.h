#ifndef TRIANGLEREF_H
#define TRIANGLEREF_H

#include "point.h"

class TrianglePtr
{
public:
    TrianglePtr(Point *a, Point *b, Point *c);
    Point point(int index) const;
    void setPoint(int index, Point value);
private:
    Point* points[3];
};

#endif // TRIANGLEREF_H
