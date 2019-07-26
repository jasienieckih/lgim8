#include "triangleptr.h"

TrianglePtr::TrianglePtr(Point* a, Point* b, Point* c)
{
    points[0] = a;
    points[1] = b;
    points[2] = c;
}

Point TrianglePtr::point(int index) const
{
    return *points[index];
}

void TrianglePtr::setPoint(int index, Point value)
{
    points[index]->set(value.x(), value.y());
}
