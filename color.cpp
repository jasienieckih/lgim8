#include "color.h"

Color::Color()
{}

Color Color::operator=(Color source)
{
    red = source.red;
    green = source.green;
    blue = source.blue;
    alpha = source.alpha;
    return *this;
}

Color Color::operator+(Color other)
{
    Color ret;
    ret.red = red + other.red;
    ret.blue = blue + other.blue;
    ret.green = green + other.green;
    ret.alpha = alpha + other.alpha;
    return ret;
}

Color Color::operator*(float factor)
{
    Color ret;
    ret.red = red * factor;
    ret.blue = blue * factor;
    ret.green = green * factor;
    ret.alpha = alpha * factor;
    return ret;
}

