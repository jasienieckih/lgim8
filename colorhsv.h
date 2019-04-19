#ifndef COLORHSV_H
#define COLORHSV_H

#include "color.h"

class ColorHsv
{
public:
    double hue, saturation, value;
    ColorHsv(Color);
    Color convertToColor();
};

#endif // COLORHSV_H
