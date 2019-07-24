#include "point.h"

#include <cmath>

Point::Point() {}

Point::Point(double x, double y)
    :
      value_x(x),
      value_y(y)
{}

Point::Point(int x, int y)
    :
      value_x(x),
      value_y(y)
{}

double Point::x() const
{
    return int(round(value_x));
}

double Point::y() const
{
    return int(round(value_y));
}

void Point::set(int x, int y)
{
    value_x = x;
    value_y = y;
}

void Point::setX(int x)
{
    value_x = x;
}

void Point::setY(int y)
{
    value_y = y;
}

Point Point::getRounded() const
{
    Point ret = Point(round(value_x), round(value_y));
    return ret;
}

Point Point::operator+(Point other)
{
    return Point(value_x + other.value_x, value_y + other.value_y);
}

Point Point::operator*(double coefficient)
{
    return Point(value_x * coefficient, value_y * coefficient);
}
