#include "image.h"

Image::Image()
    :
      visible_(false),
      mode(BlendingMode::Normal),
      alpha_(0.0),
      qImage(800, 600, QImage::Format_ARGB32),
      bits(qImage.bits())
{}

Image::Image(std::__cxx11::string path)
    :
      visible_(false),
      mode(BlendingMode::Normal),
      alpha_(1.0),
      qImage(path.c_str()),
      bits(qImage.bits())
{}

QImage &Image::getImage()
{
    return qImage;
}

Color Image::getPixel(int x, int y)
{
    int pixel = 4 * (800 * y + x);
    Color ret;
    ret.blue = bits[pixel + 0];
    ret.green = bits[pixel + 1];
    ret.red = bits[pixel + 2];
    ret.alpha = bits[pixel + 3];
    return ret;
}

void Image::setPixel(int x, int y, Color c)
{
    int pixel = 4 * (800 * y + x);
    bits[pixel + 0] = c.blue;
    bits[pixel + 1] = c.green;
    bits[pixel + 2] = c.red;
    bits[pixel + 3] = c.alpha;
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
    return bits;
}
