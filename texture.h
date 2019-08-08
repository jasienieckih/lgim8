#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>

#include "point.h"

class Texture
{
public:
    Texture(QString path,
            Point a, Point b, Point c,
            double ambientReflectionCoeff,
            double dispersedReflectionCoeff,
            double directReflectionCoeff,
            int surfaceSmoothnessCoeff);
    Texture(QString path,
            double ambientReflectionCoeff,
            double dispersedReflectionCoeff,
            double directReflectionCoeff,
            int surfaceSmoothnessCoeff);
    const uchar* bits() const;
    int width() const;
    int height() const;
    const Point& point(int index) const;
    double ambientReflectionCoeff() const;
    double dispersedReflectionCoeff() const;
    double directReflectionCoeff() const;
    int surfaceSmoothnessCoeff() const;
private:
    QImage image;
    Point points[3];
    double ambientReflectionCoeffValue;
    double dispersedReflectionCoeffValue;
    double directReflectionCoeffValue;
    int surfaceSmoothnessCoeffValue;
};

#endif // TEXTURE_H
