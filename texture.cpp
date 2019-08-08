#include "texture.h"

Texture::Texture(QString path,
                 double ambientReflectionCoeff,
                 double dispersedReflectionCoeff,
                 double directReflectionCoeff,
                 int surfaceSmoothnessCoeff)
    :
      image(path),
      ambientReflectionCoeffValue(ambientReflectionCoeff),
      dispersedReflectionCoeffValue(dispersedReflectionCoeff),
      directReflectionCoeffValue(directReflectionCoeff),
      surfaceSmoothnessCoeffValue(surfaceSmoothnessCoeff)
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

double Texture::ambientReflectionCoeff() const
{
    return ambientReflectionCoeffValue;
}

double Texture::dispersedReflectionCoeff() const
{
    return dispersedReflectionCoeffValue;
}

double Texture::directReflectionCoeff() const
{
    return directReflectionCoeffValue;
}

int Texture::surfaceSmoothnessCoeff() const
{
    return surfaceSmoothnessCoeffValue;
}

