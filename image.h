#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include <QImage>

#include "blendingmode.h"

class Image
{
public:
    Image(std::string path);
    QImage& getImage();
    uchar *getBits();
    bool visible_;
    BlendingMode mode;
    float alpha_;
private:
    QImage qImage;
};

#endif // IMAGE_H
