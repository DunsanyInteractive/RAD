#include "Image.h"

namespace Graphics_Engine {
Image::Image(char *p, int width, int height) {
    id.p = p;
    setSize(width, height);
}

Image::Image(int i, int width, int height) {
    id.i = i;
    setSize(width, height);
}

Image::~Image() {}

unsigned int Image::getWidth() {
    return width;
}

unsigned int Image::getHeight() {
    return height;
}
}
