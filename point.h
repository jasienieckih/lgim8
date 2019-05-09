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
    Point(int x, int y);
    int x();
    int y();
    void set(int x, int y);

    Point operator+(Point other);
    Point operator*(double coefficient);
private:
    double value_x, value_y;
};


#endif // POINT_H
