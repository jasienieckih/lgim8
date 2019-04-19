#include "image.h"

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

uchar *Image::getBits()
{
    return qImage.bits();
}
