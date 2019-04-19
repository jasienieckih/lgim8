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
    Color operator*=(float factor);
    Color operator*(Color other);
    bool isLighterThan(Color other);
    bool isDarkerThan(Color other);
    int lightness();
};

#endif // COLOR_H
