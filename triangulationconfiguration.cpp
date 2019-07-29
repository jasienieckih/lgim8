#include "triangulationconfiguration.h"

TriangulationConfiguration::TriangulationConfiguration()
{
    points[0][0] = Point(277, 313);
    points[0][1] = Point(276, 306);
    points[0][2] = Point(275, 318);
    points[0][3] = Point(248, 320);
    points[0][4] = Point(296, 309);
    points[0][5] = Point(382, 303);
    points[0][6] = Point(381, 298);
    points[0][7] = Point(380, 307);
    points[0][8] = Point(402, 304);
    points[0][9] = Point(358, 304);
    points[0][10] = Point(318, 279);
    points[0][11] = Point(318, 261);

    points[1][0] = Point(214, 203);
    points[1][1] = Point(217, 198);
    points[1][2] = Point(209, 227);
    points[1][3] = Point(189, 202);
    points[1][4] = Point(231, 211);
    points[1][5] = Point(380, 212);
    points[1][6] = Point(382, 206);
    points[1][7] = Point(390, 230);
    points[1][8] = Point(405, 212);
    points[1][9] = Point(368, 218);
    points[1][10] = Point(301, 176);
    points[1][11] = Point(302, 144);

    triangles[0] = {0, 1, 3};
    triangles[1] = {0, 1, 4};
    triangles[2] = {0, 2, 3};
    triangles[3] = {0, 2, 4};
    triangles[4] = {5, 6, 8};
    triangles[5] = {5, 6, 9};
    triangles[6] = {5, 7, 8};
    triangles[7] = {5, 7, 9};
    triangles[8] = {1, 4, 10};
    triangles[9] = {1, 10, 11};
    triangles[10] = {6, 9, 10};
    triangles[11] = {6, 10, 11};
}

