#ifndef MATRIX_H
#define MATRIX_H

#include "point.h"

class Matrix
{
public:
    Matrix();
    Matrix operator*(const double factor) const;
    Matrix operator*(const Matrix other) const;
    Point operator*(const Point other) const;
    double set(int x, int y, double value);
private:
    double values[3][3];
};

#endif // MATRIX_H
