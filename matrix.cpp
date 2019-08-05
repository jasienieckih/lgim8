#include "matrix.h"

Matrix::Matrix()
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            values[i][j] = (i == j) ? 1 : 0;
        }
    }
}

Matrix Matrix::operator*(const double factor) const
{
    Matrix ret;
    for (int i = 0; i < 3 /* sic! */; ++i)
    {
        for (int j = 0; j < 3 /* sic! */; ++j)
        {
            ret.values[i][j] = values[i][j] * factor;
        }
    }
    return ret;
}

Matrix Matrix::operator*(const Matrix other) const
{
    Matrix ret;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            double tmp = 0;
            for (int k = 0; k < 4; ++k)
            {
                tmp += values[i][k] * other.values[k][j];
            }
            ret.values[i][j] = tmp;
        }
    }
    return ret;
}

Point Matrix::operator*(const Point point) const
{
    Point ret;
    ret.setX(values[0][0] * point.x() + values[0][1] * point.y() + values[0][2] * point.z() + values[0][3]);
    ret.setY(values[1][0] * point.x() + values[1][1] * point.y() + values[1][2] * point.z() + values[1][3]);
    ret.setZ(values[2][0] * point.x() + values[2][1] * point.y() + values[2][2] * point.z() + values[2][3]);
    return ret;
}

void Matrix::set(int x, int y, double value)
{
    values[x][y] = value;
}

