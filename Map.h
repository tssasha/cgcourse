#ifndef MAIN_MAP_H
#define MAIN_MAP_H


#include "Image.h"
#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <set>

struct MapCoord
{
    int x;
    int y;
};

struct Tile
{
    char c;
    int tr = 0;
};

struct Map {
    Map(int a_width, int a_height, const std::string &a_path);

    Point Movement(Point p, Point p0, MovementDir dir);
    MapCoord PointToMapCoord(Point p);
    Point MapCoordToPoint(MapCoord coord);
    Point MapCoordToPoint1(MapCoord coord);
    void ChangeTileTransparency(MapCoord coord, int tr);
    void ChangeTransparency(MapCoord start);

    Pixel* Data()        { return  img->Data(); }
    MapCoord Start() { return start; }
    bool Win() { return win; }
    bool Death() { return death; }
    Image* Img() { return img; }

private:
    Tile *map;
    Image *img, *perm_img;
    int width = -1;
    int height = -1;
    int tilesize = 16;
    MapCoord start = {-1, -1};
    bool death = false;
    bool win = false;
};


#endif //MAIN_MAP_H
