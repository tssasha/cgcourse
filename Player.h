#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Image.h"

struct Point
{
  int x;
  int y;
};

enum class MovementDir
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

struct Player
{
  explicit Player(Image *img, Point pos = {.x = 10, .y = 10}) :
                 coords(pos), old_coords(coords), img(img) {};

  bool Moved() const;
  void ProcessInput(MovementDir dir);
  void Draw(Image &screen);
  Texture TextureData();

private:
  Point coords {.x = 10, .y = 10};
  Point old_coords {.x = 10, .y = 10};
  Pixel color {.r = 255, .g = 255, .b = 0, .a = 255};
  Image *img;
  Texture sprite = {.sprite = img, .x_pos = coords.x, .y_pos = coords.y};
  int move_speed = 4;

};

#endif //MAIN_PLAYER_H
