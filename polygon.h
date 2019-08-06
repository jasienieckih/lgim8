#ifndef POLYGON_H
#define POLYGON_H

#include "point.h"

class Polygon
{
public:
    Polygon(Point *a, Point *b, Point *c);
    Point point(int index) const;
    void setPoint(int index, Point value);
private:
    Point* points[3];
};

#endif // POLYGON_H
