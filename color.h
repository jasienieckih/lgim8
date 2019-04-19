#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
    Color();
    Color(int red, int green, int blue);
    int red, green, blue, alpha;
    Color operator=(Color source);
    Color operator+(Color other);
    Color operator-(Color other);
    Color operator*(float factor);
    Color operator*=(float factor);
    Color operator*(Color other);
    void normalize();
    bool isLighterThan(Color other);
    bool isDarkerThan(Color other);
    int lightness();
};

#endif // COLOR_H
