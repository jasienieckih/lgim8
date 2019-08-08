#ifndef POLYGON_H
#define POLYGON_H

#include "point.h"
#include "texture.h"

class Polygon
{
public:
    Polygon(Point *a, Point *b, Point *c, const Texture *texture);
    Point point(int index) const;
    const Texture* texture() const;
    void setPoint(int index, Point value);
private:
    Point* points[3];
    const Texture* textureValue;
};

#endif // POLYGON_H
