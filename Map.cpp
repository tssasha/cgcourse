#include "Map.h"
#include <iostream>

Map::Map(int a_width, int a_height, const std::string &a_path) : width(a_width), height(a_height) {
    Image *floor[6] = {new Image("../resources/dungeon_V.1.0.0_nyknck/Tile/t1.png"),
                       new Image("../resources/dungeon_V.1.0.0_nyknck/Tile/t2.png"),
                       new Image("../resources/dungeon_V.1.0.0_nyknck/Tile/t3.png"),
                       new Image("../resources/dungeon_V.1.0.0_nyknck/Tile/t4.png"),
                       new Image("../resources/dungeon_V.1.0.0_nyknck/Tile/t5.png"),
                       new Image("../resources/dungeon_V.1.0.0_nyknck/Tile/t6.png")};

    Image *wall[6] =  {new Image("../resources/dungeon_V.1.0.0_nyknck/Tile/w1.png"),
                       new Image("../resources/dungeon_V.1.0.0_nyknck/Tile/w2.png"),
                       new Image("../resources/dungeon_V.1.0.0_nyknck/Tile/w3.png"),
                       new Image("../resources/dungeon_V.1.0.0_nyknck/Tile/w4.png"),
                       new Image("../resources/dungeon_V.1.0.0_nyknck/Tile/w5.png"),
                       new Image("../resources/dungeon_V.1.0.0_nyknck/Tile/w6.png")};

    Image *door = new Image("../resources/dungeon_V.1.0.0_nyknck/Tile/d.png");

    img = new Image(width * tilesize, height * tilesize, 4);
    map = new char[width * height];
    FILE *in = fopen(a_path.c_str(), "r");
    if (in)
    {
        Image *img1;
        char c;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                fscanf(in, "%c", &map[i * width + j]);
            }
            fscanf(in, "%c", &c);
        }
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                c = map[i * width + j];
                if (c == '.') {
                    img->PasteImg(floor[rand() % 6], width * tilesize, i * tilesize, j * tilesize);
                } else if (c == 'S') {
                    img->PasteImg(floor[rand() % 6], width * tilesize, i * tilesize, j * tilesize);
                    start.x = j;
                    start.y = i;
                } else if (c == '#' && i != 0 && map[(i - 1) * width + j] == '.') {
                    img->PasteImg(wall[rand() % 6], width * tilesize, i * tilesize, j * tilesize);
                    img->PasteImg(wall[rand() % 6], width * tilesize, i * tilesize, j * tilesize + tilesize / 2);
                } else if (c == 'X') {
                    img->PasteImg(door, width * tilesize, i * tilesize, j * tilesize);
                }
            }
        }
    }
    fclose(in);
}

MapCoord Map::PointToMapCoord(Point p) {
    return {p.x / tilesize, p.y / tilesize};
}

Point Map::MapCoordToPoint(MapCoord coord) {
    return {coord.x * tilesize + tilesize / 2, coord.y * tilesize + tilesize / 2};
}

Point Map::Movement(Point p, Point p0, MovementDir dir) {
    Point p1 = {p.x, p.y};
    Point p2 = {p.x, p.y - 7};
    Point p3 = {p.x + 2, p.y};
    Point p4 = {p.x - 5, p.y};
    MapCoord coord = this->PointToMapCoord(p);
    MapCoord coord1 = this->PointToMapCoord(p1);
    MapCoord coord2 = this->PointToMapCoord(p2);
    MapCoord coord3 = this->PointToMapCoord(p3);
    MapCoord coord4 = this->PointToMapCoord(p4);
    if (coord.x >= width || coord.y >= height) {
        printf("ERROR\n");
    }
    if((map[coord1.y * width + coord1.x] == '.' || map[coord1.y * width + coord1.x] == 'S') &&
            (map[coord2.y * width + coord2.x] == '.' || map[coord2.y * width + coord2.x] == 'S') &&
            (map[coord3.y * width + coord3.x] == '.' || map[coord3.y * width + coord3.x] == 'S') &&
            (map[coord4.y * width + coord4.x] == '.' || map[coord4.y * width + coord4.x] == 'S')) {
        return p;
    }

    done = map[coord.y * width + coord.x] == 'X';
    return p0;
}