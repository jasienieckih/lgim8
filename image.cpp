#include "image.h"

Image::Image(std::__cxx11::string path)
    :
      qImage(path.c_str())
{}

QImage &Image::getImage()
{
    return qImage;
}
