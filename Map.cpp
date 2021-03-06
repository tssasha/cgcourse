#include "Map.h"


int max(int x, int y) {
    return x > y ? x : y;
}

void Map::ChangeTileTransparency(MapCoord coord, int tr) {
    map[coord.y * width + coord.x].tr = max(map[coord.y * width + coord.x].tr, tr);
    img->Redraw(MapCoordToPoint1(coord), map[coord.y * width + coord.x].tr);
}

void Map::ChangeTransparency(MapCoord start) {
    ChangeTileTransparency({start.x, start.y}, 255);
    if (start.x != width - 1) {
        ChangeTileTransparency({start.x + 1, start.y}, 255);
    }
    if (start.x != 0) {
        ChangeTileTransparency({start.x - 1, start.y}, 255);
    }
    if (start.y != height - 1) {
        ChangeTileTransparency({start.x, start.y + 1}, 255);
    }
    if (start.y != 0) {
        ChangeTileTransparency({start.x, start.y - 1}, 255);
    }

    if (start.x != width - 1 && start.y != height - 1) {
        ChangeTileTransparency({start.x + 1, start.y + 1}, 150);
    }
    if (start.x != width - 1 && start.y != 0) {
        ChangeTileTransparency({start.x - 1, start.y + 1}, 150);
    }
    if (start.x != 0 && start.y != height - 1) {
        ChangeTileTransparency({start.x + 1, start.y - 1}, 150);
    }
    if (start.x != 0 && start.y != 0) {
        ChangeTileTransparency({start.x - 1, start.y - 1}, 150);
    }

    if (start.x < width - 2) {
        ChangeTileTransparency({start.x + 2, start.y}, 100);
    }
    if (start.x > 1) {
        ChangeTileTransparency({start.x - 2, start.y}, 100);
    }
    if (start.y < height - 1) {
        ChangeTileTransparency({start.x, start.y + 2}, 100);
    }
    if (start.y > 1) {
        ChangeTileTransparency({start.x, start.y - 2}, 100);
    }

    if (start.x != width - 1 && start.y < height - 2) {
        ChangeTileTransparency({start.x + 1, start.y + 2}, 50);
    }
    if (start.x != width - 1 && start.y > 1) {
        ChangeTileTransparency({start.x + 1, start.y - 2}, 50);
    }
    if (start.x != 0 && start.y < height - 2) {
        ChangeTileTransparency({start.x - 1, start.y + 2}, 50);
    }
    if (start.x != 0 && start.y > 1) {
        ChangeTileTransparency({start.x - 1, start.y - 2}, 50);
    }

    if (start.x < width - 2 && start.y != height - 1) {
        ChangeTileTransparency({start.x + 2, start.y + 1}, 50);
    }
    if (start.x < width - 2 && start.y != 0) {
        ChangeTileTransparency({start.x + 2, start.y - 1}, 50);
    }
    if (start.x > 1 && start.y != height - 1) {
        ChangeTileTransparency({start.x - 2, start.y + 1}, 50);
    }
    if (start.x > 1 && start.y != 0) {
        ChangeTileTransparency({start.x - 2, start.y - 1}, 50);
    }
}

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

    Image *trap = new Image("../resources/dungeon_V.1.0.0_nyknck/Trap/TP001/TP001_03.png");

    Image *coin = new Image("../resources/dungeon_V.1.0.0_nyknck/Gold/G001/G001_01.png");

    img = new Image(width * tilesize, height * tilesize, 4);
    map = new Tile[width * height];
    FILE *in = fopen(a_path.c_str(), "r");
    if (in)
    {
        char c;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                fscanf(in, "%c", &map[i * width + j].c);
                if (map[i * width + j].c == 'S') {
                    start.x = j;
                    start.y = i;
                }
            }
            fscanf(in, "%c", &c);
        }
        ChangeTransparency(start);
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                c = map[i * width + j].c;
                if (c == '.') {
                    img->PasteImg(floor[rand() % 6], width * tilesize, i * tilesize, j * tilesize, map[i * width + j].tr);
                } else if (c == 'S') {
                    img->PasteImg(floor[rand() % 6], width * tilesize, i * tilesize, j * tilesize, map[i * width + j].tr);
                    start.x = j;
                    start.y = i;
                } else if (c == '#' && i != 0 && map[(i - 1) * width + j].c == '.') {
                    img->PasteImg(wall[rand() % 6], width * tilesize, i * tilesize, j * tilesize, map[i * width + j].tr);
                    img->PasteImg(wall[rand() % 6], width * tilesize, i * tilesize, j * tilesize + tilesize / 2, map[i * width + j].tr);
                } else if (c == 'X') {
                    img->PasteImg(door, width * tilesize, i * tilesize, j * tilesize, map[i * width + j].tr);
                } else if (c == 'T') {
                    img->PasteImg(trap, width * tilesize, i * tilesize, j * tilesize, map[i * width + j].tr);
                }
            }
        }
        perm_img = img;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (map[i * width + j].c == 'C') {
                    printf("C");
                    img->PasteImg(coin, width * tilesize, i * tilesize, j * tilesize, map[i * width + j].tr);
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

Point Map::MapCoordToPoint1(MapCoord coord) {
    return {coord.x * tilesize, coord.y * tilesize};
}

Point Map::Movement(Point p, Point p0, MovementDir dir) {
    std::set<char> tiles {'.', 'S', 'T'};
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

    death = map[coord.y * width + coord.x].c == 'T';
    win = map[coord.y * width + coord.x].c == 'X';

    if (map[coord.y * width + coord.x].c == 'T') {
        Image *trap = new Image("../resources/dungeon_V.1.0.0_nyknck/Trap/TP001/TP001_08.png");
        img->PasteImg(trap, width * tilesize, coord.y * tilesize, coord.x * tilesize, 255);
    }

    if(tiles.count(map[coord1.y * width + coord1.x].c) && tiles.count(map[coord2.y * width + coord2.x].c) &&
            tiles.count(map[coord3.y * width + coord3.x].c)  && tiles.count(map[coord4.y * width + coord4.x].c) ) {
        if(coord.x != this->PointToMapCoord(p0).x || coord.y != this->PointToMapCoord(p0).y) {
            ChangeTransparency(coord);
        }
        return p;
    }

    return p0;
}