#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"

class Triangle
{
public:
    Triangle();
    Point point(int index) const;
    void setPoint(int index, const Point value);
private:
    Point points[3];
};

#endif // TRIANGLE_H
