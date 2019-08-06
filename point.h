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
    void set(double x, double y, double z);
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    Point getRounded() const;
    Point operator+(Point other);
    Point operator*(double coefficient);
private:
    double value_x, value_y, value_z;
};


#endif // POINT_H