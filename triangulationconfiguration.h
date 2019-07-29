#ifndef TRIANGULATIONCONFIGURATION_H
#define TRIANGULATIONCONFIGURATION_H

#include "constants.h"
#include "point.h"

class TriangleConfiguration
{
public:
    int indexes[3];
};

class TriangulationConfiguration
{
public:
    TriangulationConfiguration();
    Point points[2][NUMBER_OF_POINTS];
    TriangleConfiguration triangles[NUMBER_OF_TRIANGLES];
};

#endif // TRIANGULATIONCONFIGURATION_H
