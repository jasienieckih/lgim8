#include "image.h"

Image::Image()
    :
      visible_(false),
      mode(BlendingMode::Normal),
      alpha_(0.0),
      qImage(800, 600, QImage::Format_ARGB32)
{}

Image::Image(std::__cxx11::string path)
    :
      visible_(false),
      mode(BlendingMode::Normal),
      alpha_(0.0),
      qImage(path.c_str())
{}

QImage &Image::getImage()
{
    return qImage;
}

void Image::clean()
{
    uchar *bits = getBits();
    for (int x = 0; x < 800; ++x)
    {
        for (int y = 0; y < 600; ++y)
        {
            int pixel = 4 * (800 * y + x);
            for (int c = 0; c < 4; ++c)
            {
                bits[pixel + c] = 0x00;
            }
        }
    }
}

uchar *Image::getBits()
{
    return qImage.bits();
}
