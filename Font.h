/*
 *  Font.h
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef FONT_H
#define FONT_H

#include "Sprite.h"

class Font : public Sprite {
public:

    Font(GE::Image* font_texture, int lineNumber = 0 , float posx = 32, float posy = -512, float texX = 0, float texY = 0, int ascii_code = (int)'_');
    ~Font();

    int ascii, line_number;

};

#endif
