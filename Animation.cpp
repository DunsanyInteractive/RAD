/*
 *  Animation.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof, Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */

#include "graphics_engine.h"
#include "ProcessManager.h"

#include "Animation.h"

Animation::Animation(GE::Image *image, int left, int top, int frame_width, int frame_height) {
    source_rect = new GE::Image::Rect(left, top, left + frame_width, top + frame_height);
    this->image = image;
}

Animation::~Animation() {
    GE::unload(image);
}

void Animation::setFrames(int frames) {
    this->frames = frames;
}

void Animation::setFrameDim(int width, int height) {
    row_length = image->getWidth() / frame_width;
    setFrames(row_length * image->getHeight() / frame_height);
}

void Animation::setOrigin(int left, int top) {
    source_origin.left = left;
    source_origin.top = top;
}

/* Increment frame */
void Animation::operator++() {
    frame = (frame + 1) % frames;
    if (frame) {
        source_rect->left += frame_width;
        if (source_rect->left >= image->getWidth()) {
            source_rect->left = 0;
            source_rect->right = 0;
            source_rect->top += frame_height;
            source_rect->bottom += frame_height;
        } else
            source_rect->right += frame_width;
    } else {
        source_rect->left = source_origin.left;
        source_rect->right = source_origin.left + frame_width;
        source_rect->top += source_origin.top;
        source_rect->bottom += source_origin.top + frame_height;
    }
}

GE::Image *Animation::use(GE::Image::Rect *source_rect) {
    this->source_rect = source_rect;
    setFrame(0);
    return image;
}

void Animation::setFrame(int frame) {
    int length = source_origin.left + frame * frame_width;
    int left = length % frame_width;
    int top = source_origin.top + frame_height * (length / frame_width);
    source_rect->left = left;
    source_rect->right = left + frame_width;
    source_rect->top = top;
    source_rect->bottom = top + frame_height;
    this->frame = frame;
}


