#ifndef MAIN_IMAGE_H
#define MAIN_IMAGE_H

#include <string>
#include "structs.h"

constexpr int tileSize = 16;

struct Pixel
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

constexpr Pixel backgroundColor{7, 29, 41, 255};

struct Image
{
  explicit Image(const std::string &a_path);
  Image(int a_width, int a_height, int a_channels);

  void PasteImg(Image *img, int width, int x, int y, int tr);
  void doublesize();
  int Save(const std::string &a_path);

  int Width()    const { return width; }
  int Height()   const { return height; }
  int Channels() const { return channels; }
  size_t Size()  const { return size; }
  Pixel* Data()        { return  data; }
  void FadeOut(double coef);
  void Display(double coef);
  void Redraw(Point point, int tr);

  ~Image();

private:
  int width = -1;
  int height = -1;
  int channels = 3;
  size_t size = 0;
  Pixel *data = nullptr;
  bool self_allocated = false;
};

struct Texture
{
  Image *img = nullptr;
  int x_pos;
  int y_pos;
};


#endif //MAIN_IMAGE_H
