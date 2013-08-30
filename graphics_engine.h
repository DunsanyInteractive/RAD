/*
 *  graphics_engine.h
 *  Rad Adventure Development
 *
 *  Created by John Felderhof on 2/10/10.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */
#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H
#include <string>

#include "Image.h"
#include "Sprite.h"

namespace Graphics_Engine {
#define LAYER_DIFF	0.03125

/* Init related functions */
void init();
void clean();

/* Drawing related functions */
void display();
void drawCircle(float, float, float , float = 1, float = 0, float = 0);
void drawLine(float, float, float, float);
void drawSprite( Sprite * );

/* Misc */
bool *createBitmask( Sprite * );
const int supportedLayers();
void useLayer( int );

/* Image functions */
Image *createImage(int width, int height);
void copyTo(Image *dst, Image *src, Image::Rect &dst_rect, Image::Rect &src_rect);

/* Factory methods for sprites */
Image *loadImageFromFile( char* );
Image *loadImageFromFile( std::wstring* );

/* Remove one occurance of image */
void unload(Image *image);
};

namespace GE = Graphics_Engine;

#endif
