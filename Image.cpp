#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>

void Image::doublesize() {
    Pixel *data1;
    int size = width * height * 4;
    data1 = new Pixel[size];
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            data1[height * 4 * i + 2 * j] = data[height * i + j];
            data1[height * 4 * i + 2 * j + 1] = data[height * i + j];
            data1[height * 2 * (i * 2 + 1) + 2 * j] = data[height * i + j];
            data1[height * 2 * (i * 2 + 1) + 2 * j + 1] = data[height * i + j];
        }
    }
    width *= 2;
    height *= 2;
    data = data1;
}

Image::Image(const std::string &a_path) {
    stbi_set_flip_vertically_on_load(true);
    if ((data = (Pixel *) stbi_load(a_path.c_str(), &width, &height, &channels, STBI_rgb_alpha)) != nullptr) {
        //data = doublesize(data, &width, &height);
        //data = doublesize(data, &width, &height);
        size = width * height;
    }
}

Image::Image(int a_width, int a_height, int a_channels) {
    data = new Pixel[a_width * a_height];
    if (data != nullptr) {
        width = a_width;
        height = a_height;
        size = a_width * a_height;
        channels = a_channels;
        self_allocated = true;
    }
    for (int i = 0; i < a_width * a_height; ++i) {
        data[i] = backgroundColor;
    }
}

void Image::PasteImg(Image *img, int width, int x, int y, int tr) {
    if (img) {
        for (int i1 = 0; i1 < img->Height(); ++i1) {
            for (int j1 = 0; j1 < img->Width(); ++j1) {
                Pixel newPixel = img->Data()[img->Width() * i1 + j1], oldPixel = data[width * x + y + width * i1 + j1];
                newPixel.r = newPixel.a / 255.0 * (newPixel.r - oldPixel.r) + oldPixel.r;
                newPixel.g = newPixel.a / 255.0 * (newPixel.g - oldPixel.g) + oldPixel.g;
                newPixel.b = newPixel.a / 255.0 * (newPixel.b - oldPixel.b) + oldPixel.b;
                //newPixel.a = 255;
                data[width * x + y + width * i1 + j1] = newPixel;
                data[width * x + y + width * i1 + j1].a = tr;
            }
        }
    }
}

int Image::Save(const std::string &a_path) {
    auto extPos = a_path.find_last_of('.');
    if (a_path.substr(extPos, std::string::npos) == ".png" || a_path.substr(extPos, std::string::npos) == ".PNG") {
        stbi_write_png(a_path.c_str(), width, height, channels, data, width * channels);
    } else if (a_path.substr(extPos, std::string::npos) == ".jpg" ||
               a_path.substr(extPos, std::string::npos) == ".JPG" ||
               a_path.substr(extPos, std::string::npos) == ".jpeg" ||
               a_path.substr(extPos, std::string::npos) == ".JPEG") {
        stbi_write_jpg(a_path.c_str(), width, height, channels, data, 100);
    } else {
        std::cerr << "Unknown file extension: " << a_path.substr(extPos, std::string::npos) << "in file name" << a_path
                  << "\n";
        return 1;
    }

    return 0;
}

void Image::Redraw(Point point, int tr) {
    for (int i = point.y; i < point.y + tileSize; ++i) {
        for (int j = point.x; j < point.x + tileSize; ++j) {
            data[i * width + j].a = tr;
        }
    }
}

void Image::FadeOut(double coef) {
    for (int i = 0; i < size; ++i) {
        data[i].a = data[i].a - coef > 0 ? data[i].a - coef : 0;
    }
};

void Image::Display(double coef) {
    for (int i = 0; i < size; ++i) {
        if (data[i].a) {
            data[i].a = data[i].a + coef < 255 ? data[i].a + coef : 255;
        }
    }
};

Image::~Image() {
    if (self_allocated)
        delete[] data;
    else {
        stbi_image_free(data);
    }
}