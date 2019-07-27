#include "frame.h"

Frame::Frame()
    :
      image(600, 600, QImage::Format::Format_RGB32)
{
    triangles[0] = new TrianglePtr(&points[0], &points[1], &points[2]);
    triangles[1] = new TrianglePtr(&points[0], &points[2], &points[3]);
}

