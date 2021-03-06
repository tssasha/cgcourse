#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Image.h"
#include "Map.h"

struct Player
{
  explicit Player(Point pos = {.x = 10, .y = 10}, Map *map = nullptr) : coords(pos), old_coords(coords), map(map) {};

  bool Moved() const;
  void ProcessInput(MovementDir dir, int n);
  Texture TextureData();
  void DeathAnimation(int n);

private:
  Point coords {.x = 10, .y = 10};
  Point old_coords {.x = 10, .y = 10};
  Pixel color {.r = 255, .g = 255, .b = 0, .a = 255};
  Image *img_left[4] = {new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk left1.png"),
                     new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk left2.png"),
                     new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk left3.png"),
                     new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk left4.png")};
  Image *img_right[4] = {new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk right1.png"),
                         new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk right2.png"),
                         new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk right3.png"),
                         new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk right4.png")};
  Image *img_up[4] = {new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk up1.png"),
                      new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk up2.png"),
                      new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk up3.png"),
                      new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk up4.png")};
  Image *img_down[4] = {new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk down1.png"),
                        new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk down2.png"),
                        new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk down3.png"),
                        new Image("../resources/Top down character template by RgsDev/Character without weapon/walk/walk down4.png")};
  Image *img_death[4] = {new Image("../resources/Top down character template by RgsDev/death animation/death1.png"),
                         new Image("../resources/Top down character template by RgsDev/death animation/death2.png"),
                         new Image("../resources/Top down character template by RgsDev/death animation/death3.png"),
                         new Image("../resources/Top down character template by RgsDev/death animation/death4.png")};
  Image *img_cur {img_right[0]};
  Map *map;
  Texture sprite = {.img = img_cur, .x_pos = coords.x - img_cur->Width() / 2, .y_pos = coords.y - img_cur->Height() / 2};
  int move_speed = 1;

};

#endif //MAIN_PLAYER_H
