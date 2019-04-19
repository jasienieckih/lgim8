#include "color.h"

#include <cmath>

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
    if (ret.red > 0xff) ret.red = 0xff;
    if (ret.blue > 0xff) ret.blue = 0xff;
    if (ret.green > 0xff) ret.green = 0xff;
    if (ret.alpha > 0xff) ret.alpha = 0xff;
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

Color Color::operator*=(float factor)
{
    red = red * factor;
    blue = blue * factor;
    green = green * factor;
    alpha = alpha * factor;
    return *this;
}

bool Color::isLighterThan(Color other)
{
    return (lightness() > other.lightness());
}

bool Color::isDarkerThan(Color other)
{
    return (lightness() < other.lightness());
}

int Color::lightness()
{
    return red + green + blue;
}

