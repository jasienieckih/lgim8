#ifndef POINT_H
#define POINT_H

namespace Ui {
    class Point;
}

class Point
{
public:
    Point();
    Point(double x, double y);
    double x() const;
    double y() const;
    void set(double x, double y);
    void setX(double x);
    void setY(double y);
    Point getRounded() const;
    Point getAbsolute() const;
    Point operator+(Point other);
    Point operator-(Point other);
    Point operator*(double coefficient);
private:
    double value_x, value_y;
};


#endif // POINT_H
