#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include <QImage>

class Image
{
public:
    Image(std::string path);
    QImage& getImage();
private:
    QImage qImage;
};

#endif // IMAGE_H
