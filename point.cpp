#include "point.h"

#include <cmath>

Point::Point() {}

Point::Point(double x, double y, double z)
    :
      value_x(x),
      value_y(y),
      value_z(z)
{}

double Point::x() const
{
    return value_x;
}

double Point::y() const
{
    return value_y;
}

double Point::z() const
{
    return value_z;
}

double Point::coord(int index) const
{
    if (index == 0) return value_x;
    return value_y;
}

double Point::distanceFrom(Point other) const
{
    Point d = Point(value_x - other.value_x, value_y - other.value_y, value_z - other.value_z);
    d.value_x *= d.value_x;
    d.value_y *= d.value_y;
    d.value_z *= d.value_z;
    double ret = sqrt(d.value_x + d.value_y + d.value_z);
    return ret;
}

void Point::set(double x, double y, double z)
{
    value_x = x;
    value_y = y;
    value_z = z;
}

void Point::setX(double x)
{
    value_x = x;
}

void Point::setY(double y)
{
    value_y = y;
}

void Point::setZ(double z)
{
    value_z = z;
}

Point Point::getRounded() const
{
    Point ret = Point(round(value_x), round(value_y), round(value_z));
    return ret;
}

double Point::norm() const
{
    return distanceFrom(Point(0.0, 0.0, 0.0));
}

Point Point::operator+(Point other) const
{
    return Point(value_x + other.value_x, value_y + other.value_y, value_z + other.value_z);
}

Point Point::operator-(Point other) const
{
    return Point(value_x - other.value_x, value_y - other.value_y, value_z - other.value_z);
}

Point Point::operator*(double coefficient) const
{
    return Point(value_x * coefficient, value_y * coefficient, value_z * coefficient);
}

Point Point::operator/(double coefficient) const
{
    return Point(value_x / coefficient, value_y / coefficient, value_z / coefficient);
}

double Point::operator*(Point other) const
{
    return value_x * other.value_x + value_y * other.value_y + value_z * other.value_z;
}

Point Point::operator^(Point other) const
{
    return Point(
                value_y * other.value_z - value_z * other.value_y,
                value_z * other.value_x - value_x * other.value_z,
                value_x * other.value_y - value_y * other.value_x);
}
