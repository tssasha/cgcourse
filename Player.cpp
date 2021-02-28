#include "Player.h"

bool Player::Moved() const
{
  if(coords.x == old_coords.x && coords.y == old_coords.y)
    return false;
  else
    return true;
}

void Player::ProcessInput(MovementDir dir)
{
  int move_dist = move_speed * 1;
  switch(dir)
  {
    case MovementDir::UP:
      old_coords.y = coords.y;
      coords.y += move_dist;
      coords = map->Movement(coords, old_coords, dir);
      img_cur = img_up;
      break;
    case MovementDir::DOWN:
      old_coords.y = coords.y;
      coords.y -= move_dist;
      coords = map->Movement(coords, old_coords, dir);
      img_cur = img_down;
      break;
    case MovementDir::LEFT:
      old_coords.x = coords.x;
      coords.x -= move_dist;
      coords = map->Movement(coords, old_coords, dir);
      img_cur = img_left;
      break;
    case MovementDir::RIGHT:
      old_coords.x = coords.x;
      coords.x += move_dist;
      coords = map->Movement(coords, old_coords, dir);
      img_cur = img_right;
      break;
    default:
      break;
  }
}

Texture Player::TextureData()
{
    sprite.img = img_cur;
    sprite.x_pos = coords.x - img_cur->Width() / 2;
    sprite.y_pos = coords.y - img_cur->Height() / 2;
    return sprite;
}