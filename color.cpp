#include "color.h"

#include <cmath>

Color::Color()
    :
      red(0),
      green(0),
      blue(0),
      alpha(0)
{}

Color::Color(int red_, int green_, int blue_):
    red(red_),
    green(green_),
    blue(blue_),
    alpha(0xff)
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

Color Color::operator-(Color other)
{
    Color ret;
    ret.red = red - other.red;
    ret.blue = blue - other.blue;
    ret.green = green - other.green;
    ret.alpha = alpha - other.alpha;
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

Color Color::operator*(Color other)
{
    Color ret;
    ret.red = red * other.red;
    ret.blue = blue * other.blue;
    ret.green = green * other.green;
    ret.alpha = alpha * other.alpha;
    return ret;
}

void Color::normalize()
{
    if (red < 0x00) red = 0x00;
    if (blue < 0x00) blue = 0x00;
    if (green < 0x00) green = 0x00;
    if (alpha < 0x00) alpha = 0x00;
    if (red > 0xff) red = 0xff;
    if (blue > 0xff) blue = 0xff;
    if (green > 0xff) green = 0xff;
    if (alpha > 0xff) alpha = 0xff;
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

