#include "point.h"

#include <cmath>
#include <ctgmath>

Point::Point() {}

Point::Point(double x, double y)
    :
      value_x(x),
      value_y(y)
{}

double Point::x() const
{
    return value_x;
}

double Point::y() const
{
    return value_y;
}

void Point::set(double x, double y)
{
    value_x = x;
    value_y = y;
}

void Point::setX(double x)
{
    value_x = x;
}

void Point::setY(double y)
{
    value_y = y;
}

Point Point::getRounded() const
{
    Point ret = Point(round(value_x), round(value_y));
    return ret;
}

Point Point::getAbsolute() const
{
    Point ret = Point(abs(value_x), abs(value_y));
    return ret;
}

Point Point::operator+(Point other)
{
    return Point(value_x + other.value_x, value_y + other.value_y);
}

Point Point::operator-(Point other)
{
    return Point(value_x - other.value_x, value_y - other.value_y);
}

Point Point::operator*(double coefficient)
{
    return Point(value_x * coefficient, value_y * coefficient);
}
