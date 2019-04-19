#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include <QImage>

#include "blendingmode.h"
#include "color.h"

class Image
{
public:
    Image();
    Image(std::string path);
    QImage& getImage();
    Color getPixel(int x, int y);
    void setPixel(int x, int y, Color c);
    void clean();
    uchar *getBits();
    bool visible_;
    BlendingMode mode;
    float alpha_;
private:
    QImage qImage;
    uchar* bits;
};

#endif // IMAGE_H
