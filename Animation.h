/*
 *  Animation.h
 *  Rad Adventure Development
 *
 *  Created by John Felderhof, Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef ANIMATION_H
#define ANIMATION_H

#include "Image.h"

class Animation {
    int frame;
    int frame_height;
    int frame_width;

    /* Origin of reel in source image */
    struct {
        int left;
        int top;
    } source_origin;

    int frames;
    int row_length;

    /* Image frames are on */
    GE::Image *image;
    GE::Image::Rect *source_rect;

    void setFrames(int frames);
    void setFrameDim(int width, int height);
    void setOrigin(int left, int top);

public:
    Animation(GE::Image *image, int left, int top, int frame_width, int frame_height);
    ~Animation();

    void operator++();	/* Forward one frame */

    GE::Image *use(GE::Image::Rect *source_rect);
    void setFrame(int frame);
};

#endif
