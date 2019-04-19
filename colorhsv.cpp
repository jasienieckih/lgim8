#include "colorhsv.h"

#include <iostream>

ColorHsv::ColorHsv(Color color)
{
    double rd, gd, bd;
    rd = color.red / 256.0;
    gd = color.green / 256.0;
    bd = color.blue / 256.0;

    double max = rd;
    if (gd > max)
        max = gd;
    if (bd > max)
        max = bd;
    double min = rd;
    if (gd < min)
        min = gd;
    if (bd < min)
        min = bd;

    if (max == min)
    {
        hue = 0.0;
    }
    else if (max == rd)
    {
        hue = gd - bd;
        hue /= max - min;
    }
    else if (max == gd)
    {
        hue = bd - rd;
        hue /= max - min;
        hue += 2.0;
    }
    else
    {
        hue = rd - gd;
        hue /= max - min;
        hue += 4.0;
    }
    if (hue < 0.0)
        hue += 6.0;
    saturation = (max == 0.0) ? (0.0) : ((max - min) / max);
    value = max;
}

double mod(double d, double i)
{
    while (d >= i)
    {
        d -= i;
    }
    return d;
}

double double_abs(double x)
{
    return (x < 0.0) ? -x : x;
}

Color ColorHsv::convertToColor()
{
    Color color;

    double chroma = value * saturation;
    double hue_denormalized = hue;
    double chroma_dual = chroma * (1.0 - double_abs(mod(hue_denormalized, 2.0) - 1.0));

    double rd, gd, bd;
    rd = gd = bd = 0.0;

    if (hue_denormalized < 1.0)
    {
        rd = chroma;
        gd = chroma_dual;
    }
    else if (hue_denormalized < 2.0)
    {
        gd = chroma;
        rd = chroma_dual;
    }
    else if (hue_denormalized < 3.0)
    {
        gd = chroma;
        bd = chroma_dual;
    }
    else if (hue_denormalized < 4.0)
    {
        bd = chroma;
        gd = chroma_dual;
    }
    else if (hue_denormalized < 5.0)
    {
        bd = chroma;
        rd = chroma_dual;
    }
    else
    {
        rd = chroma;
        bd = chroma_dual;
    }

    double vc_diff = value - chroma;
    rd += vc_diff;
    bd += vc_diff;
    gd += vc_diff;

    color.red = int(rd * 256);
    color.blue = int(bd * 256);
    color.green = int(gd * 256);
    color.alpha = 0xff;

    return color;
}

