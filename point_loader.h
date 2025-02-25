#ifndef POINT_LOADER
#define POINT_LOADER

#include <plot_point.h>
#include <string>

// From: https://stackoverflow.com/questions/12971499/how-to-get-the-file-separator-symbol-in-standard-c-c-or
const char path_separator =
#ifdef _WIN32
    '\\';
#else
    '/';
#endif

struct polygon
{
    point* points;
    int count;
    std::string name;
};

struct polygon_batch
{
    polygon* polygons;
    int count;
};

polygon_batch* getPolygons();

#endif