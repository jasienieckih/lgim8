#include "texture.h"

Texture::Texture(QString path)
    :
      image(path)
{
    double width = image.width();
    double height = image.height();
    points[1] = Point(0.0, height - 1, 1.0);
    points[2] = Point(width - 1, height - 1, 1.0);
    points[0] = Point(width / 2, height - width * 0.866025404, 1.0);
}

const uchar *Texture::bits() const
{
    return image.bits();
}

const Point &Texture::point(int index) const
{
    return points[index];
}

