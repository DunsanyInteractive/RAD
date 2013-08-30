/*
 *  Font.h
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#include "Font.h"

Font::Font(GE::Image* font_texture, int lineNumber , float posx, float posy, float texX, float texY, int ascii_code)
{

    setSourceRect(texY, texX, (texY + 32), (texX + 32) );
    position.x = posx;
    position.y = posy;
    layer = 1;

    width = 32;
    height = 32;
    setScale(65);
    visible = true;
    ascii = ascii_code;
    line_number = lineNumber;
    colour.v1.a = 255;
    colour.v2.a = 255;
    colour.v3.a = 255;
    colour.v4.a = 255;
    colour.v1.r = 255;
    colour.v2.r = 255;
    colour.v3.r = 255;
    colour.v4.r = 255;
    colour.v1.b = 255;
    colour.v2.g = 255;
    colour.v3.g = 255;
    colour.v4.g = 255;
    colour.v1.g = 255;
    colour.v2.b = 255;
    colour.v3.b = 255;
    colour.v4.b = 255;

}

Font::~Font()
{

}
