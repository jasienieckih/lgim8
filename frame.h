#ifndef FRAME_H
#define FRAME_H

#include <QImage>

#include "constants.h"
#include "point.h"
#include "triangleptr.h"

class Frame
{
public:
    Frame();
    QImage image;
    Point points[NUMBER_OF_POINTS];
    TrianglePtr *triangles[NUMBER_OF_TRIANGLES];
};

#endif // FRAME_H
