#ifndef COLOR_H
#define COLOR_H


class Color
{
public:
    Color();
    int red, green, blue, alpha;
    Color operator=(Color source);
    Color operator+(Color other);
    Color operator*(float factor);
};

#endif // COLOR_H
