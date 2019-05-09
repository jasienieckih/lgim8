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

int Point::x()
{
    return int(round(value_x));
}
int Point::y()
{
    return int(round(value_y));
}

void Point::set(int x, int y)
{
    value_x = x;
    value_y = y;
}

Point Point::operator+(Point other)
{
    return Point(value_x + other.value_x, value_y + other.value_y);
}

Point Point::operator*(double coefficient)
{
    return Point(value_x * coefficient, value_y * coefficient);
}
