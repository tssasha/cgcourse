#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Image.h"
#include "Map.h"

struct Player
{
  explicit Player(Point pos = {.x = 10, .y = 10}, Map *map = nullptr) : coords(pos), old_coords(coords), map(map) {};

  bool Moved() const;
  void ProcessInput(MovementDir dir);
  Texture TextureData();

private:
  Point coords {.x = 10, .y = 10};
  Point old_coords {.x = 10, .y = 10};
  Pixel color {.r = 255, .g = 255, .b = 0, .a = 255};
  Image *img_left = new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk left1.png");
  Image *img_right = new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk right1.png");
  Image *img_up = new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk up1.png");
  Image *img_down = new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk down1.png");
  Image *img_cur {img_right};
  Map *map;
  Texture sprite = {.img = img_cur, .x_pos = coords.x - img_cur->Width() / 2, .y_pos = coords.y - img_cur->Height() / 2};
  int move_speed = 1;

};

#endif //MAIN_PLAYER_H
