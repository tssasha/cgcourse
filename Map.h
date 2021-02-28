#ifndef MAIN_MAP_H
#define MAIN_MAP_H


#include "Image.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>

struct MapCoord
{
    int x;
    int y;
};

struct Map {
    Map(int a_width, int a_height, const std::string &a_path);

    Point Movement(Point p, Point p0, MovementDir dir);
    MapCoord PointToMapCoord(Point p);
    Point MapCoordToPoint(MapCoord coord);
    Pixel* Data()        { return  img->Data(); }
    MapCoord Start() { return start; }
    bool Done() { return done; }
    Image Img() { return *img; }

private:
    char *map;
    Image *img;
    int width = -1;
    int height = -1;
    int tilesize = 16;
    MapCoord start = {-1, -1};
    bool done = false;
};


#endif //MAIN_MAP_H
