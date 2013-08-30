/*
 *
 *  Font_Handler.h
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef FONT_HANDLER_H
#define FONT_HANDLER_H

#include "Font.h"
#define NUM_CHARS_PER_LINE 16
#define FONT_Y_START 0
#define FONT_X_SIZE 32
#define FONT_Y_SIZE 32
#define FONT_TEX_WIDTH 512


#define SAFE_DELETE(p)	{if (p)	{ delete (p); (p) = NULL; } }

namespace Font_Handler {
extern GE::Image *fontTexture;
extern std::list<Font*> font_list;
extern Font *cursor;
extern std::stringstream *char_input;

void init();
void createLetter(int ascii_code);
void setLetter(Font* font, int ascii_code);
void createString(std::string words);
void draw();
void clean();
void deleteLine();
};


#endif
