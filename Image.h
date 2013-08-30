/*
 * Structure to hold image file data for graphics engine
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <string>

namespace Graphics_Engine {
class Image {
public:
    struct Rect {
        Rect() {};
        Rect(float left, float right, float top, float bottom) {
            this->left = left;
            this->right = right;
            this->top = top;
            this->bottom = bottom;
        }

        float left;
        float right;
        float top;
        float bottom;
    };

private:
    unsigned int width;
    unsigned int height;

    inline void setSize(int width, int height) {
        this->width = width;
        this->height = height;
    };
    Image(char *p, int width, int height);
    Image(int i, int width, int height);
    ~Image();

    friend Image *createImage(int width, int height);
    friend void copyTo(Image *dst, Image *src, Rect &dst_rect, Rect &src_rect);
    friend void clean();
    friend void unload(Image *);
    friend Image *loadImageFromFile( char* );
    friend Image *loadImageFromFile( std::wstring* );

public:
    union {
        char *p;
        int i;
    } id;

    unsigned int getWidth();
    unsigned int getHeight();
// 	unsigned int width;
// 	unsigned int height;
//
// 	inline void setSize(int width, int height) {this->width = width; this->height = height;};
// 	Image(char *p, int width, int height);
// 	Image(int i, int width, int height);
// 	~Image();
//
// 	friend Image *createImage(int width, int height);
// 	friend void copyTo(Image *dst, Image *src, Image::Rect &dst_rect, Image::Rect &src_rect);
// 	friend void clean();
// 	friend void unload(Image *);
// 	friend Image *loadImageFromFile( char* );
// 	friend Image *loadImageFromFile( std::wstring* );

};
}

namespace GE = Graphics_Engine;
#endif
