#include "triangle.h"

Triangle::Triangle()
{

}

Point Triangle::point(int index) const
{
    return points[index];
}

void Triangle::setPoint(int index, const Point value)
{
    points[index] = value;
}

