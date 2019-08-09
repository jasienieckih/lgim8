#include "polygon.h"

Polygon::Polygon(Point *a, Point *b, Point *c, const Texture *texture)
    :
      textureValue(texture)
{
    points[0] = a;
    points[1] = b;
    points[2] = c;
}

Point Polygon::point(int index) const
{
    return *points[index];
}

const Texture *Polygon::texture() const
{
    return textureValue;
}

void Polygon::setPoint(int index, Point value)
{
    points[index]->set(value.x(), value.y(), value.z());
}
