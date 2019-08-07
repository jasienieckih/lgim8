#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>

#include "point.h"

class Texture
{
public:
    Texture(QString path);
    const uchar* bits() const;
    const Point& point(int index) const;
private:
    QImage image;
    Point points[3];
};

#endif // TEXTURE_H
