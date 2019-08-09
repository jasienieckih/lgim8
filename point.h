#ifndef POINT_H
#define POINT_H

namespace Ui {
    class Point;
}

class Point
{
public:
    Point();
    Point(double x, double y, double z);
    double x() const;
    double y() const;
    double z() const;
    double coord(int index) const;
    double distanceFrom(Point other) const;
    void set(double x, double y, double z);
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    Point getRounded() const;
    double norm() const;
    Point operator+(Point other) const;
    Point operator-(Point other) const;
    Point operator*(double coefficient) const;
    Point operator/(double coefficient) const;
    double operator*(Point other) const; // dot product
    Point operator^(Point other) const; // cross product
private:
    double value_x, value_y, value_z;
};


#endif // POINT_H
