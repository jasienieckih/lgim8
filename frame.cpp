#include "frame.h"

#include "triangulationconfiguration.h"

Frame::Frame()
    :
      image(600, 600, QImage::Format::Format_RGB32)
{
    TriangulationConfiguration config;
    for (int t = 0; t < NUMBER_OF_TRIANGLES; ++t)
    {
        int* singleConfig = config.triangles[t].indexes;
        triangles[t] = new TrianglePtr(&points[singleConfig[0]],
                                       &points[singleConfig[1]],
                                       &points[singleConfig[2]]);
    }
}

