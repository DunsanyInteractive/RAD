/*
 *
 *  Font_Handler.cpp
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#include "Font_Handler.h"
#include "graphics_engine.h"
#include "Game.h"

#include <sstream>

namespace Font_Handler {

GE::Image *fontTexture;
std::list<Font*> font_list;
Font* cursor;
Font* input_mark;
int current_line;
std::stringstream *char_input;

void init()
{
    std::wstring *filename = new std::wstring(L"Assets/font_bitmap.png");
    fontTexture = GE::loadImageFromFile(filename);
    SAFE_DELETE(filename);
    input_mark = new Font(fontTexture);
    input_mark->setPosition(0, 320);
    input_mark->width = 32;
    input_mark->height = 32;
    input_mark->ascii = ((int)'>');
    input_mark->setScale(65);
    cursor = new Font(fontTexture);
    cursor->position.setVector((input_mark->position.x + input_mark->width), input_mark->position.y);
    setLetter(cursor, cursor->ascii);
    setLetter(input_mark, input_mark->ascii);
    font_list.push_back(input_mark);
    font_list.push_back(cursor);
    current_line = 1;
    char_input = new std::stringstream;
}

void createLetter(int ascii_code)
{
    switch( ascii_code )
    {
    case '\n':
    case '\r':
        if (Game::mode == CONSOLE)
        {
            cursor->position.x = input_mark->position.x + input_mark->width;
            for (std::list<Font *>::iterator iter = font_list.begin(); iter != font_list.end(); iter++)
            {
                if ((*iter)->line_number > 1)
                {
                    (*iter)->line_number++;
                    (*iter)->position.y += input_mark->height;
                }
                else if ((*iter)->line_number == 1)
                {
                    (*iter)->line_number++;
                    (*iter)->position.x -= input_mark->width;
                    (*iter)->position.y += input_mark->height;
                }
            }
        }
        else
        {
            //default Fonthandler Non-console code here
        }
        break;
    case '\b':
    case 127:
    {
        if (cursor->position.x <= (input_mark->position.x + input_mark->width))
        {
            cursor->position.x = (input_mark->position.x + input_mark->width);
        }
        else
        {
            std::list<Font *>::iterator fiter = font_list.begin();
            while (fiter != font_list.end())
            {
                if ((*fiter)->line_number == 1 && (*fiter)->position.x == (cursor->position.x - cursor->width) )
                {
                    std::list<Font *>::iterator citer;
                    citer = fiter;
                    citer++;
                    SAFE_DELETE((*fiter));
                    font_list.erase(fiter);
                    fiter = citer;
                }
                else if ((*fiter)->line_number == 1 && (*fiter)->position.x >= cursor->position.x)
                {
                    (*fiter)->position.x -= cursor->width;
                    fiter++;
                }
                else
                    fiter++;
            }
            cursor->position.x -= cursor->width;
        }
    }
    break;
    default:
        for (std::list<Font *>::iterator fiter = font_list.begin(); fiter != font_list.end(); fiter++)
        {
            if ((*fiter)->line_number == 1 && (*fiter)->position.x >= cursor->position.x)
                (*fiter)->position.x += (*fiter)->width;
        }
        int top = (((ascii_code - 32) / NUM_CHARS_PER_LINE) * FONT_Y_SIZE) + FONT_Y_START;
        int left = (ascii_code * FONT_X_SIZE) % FONT_TEX_WIDTH;
        font_list.push_back(new Font(fontTexture, 1, cursor->position.x, (cursor->position.y), (float)left - 5, (float)top, ascii_code));
        cursor->position.x += cursor->width;
    }
}

void setLetter(Font* font, int ascii_code)
{
    int top = (((ascii_code - 32) / NUM_CHARS_PER_LINE) * FONT_Y_SIZE) + FONT_Y_START;
    int left = (ascii_code * FONT_X_SIZE) % FONT_TEX_WIDTH;
    font->setSourceRect((float)top, (float)left, (float)(top + 32), (float)(left + 32));

}

void draw()
{
    if (!font_list.empty())
    {
        std::list<Font*>::iterator iter;
        iter = font_list.begin();
        while (iter != font_list.end())
        {
            (*iter)->draw();
            iter++;
        }
    }
}

void createString(std::string word)
{
    for (int i = 0; i < (int)word.length(); i++)
    {
        createLetter((int)word[i]);
    }
}

void deleteLine()
{
    for (std::list<Font *>::iterator iter = font_list.begin(); iter != font_list.end(); iter++)
    {
        if ((*iter)->line_number == 1)
        {
            SAFE_DELETE(*iter);
            font_list.erase(iter);
            iter = font_list.begin();
            cursor->position.x = input_mark->position.x + input_mark->width;
        }
    }
}

void clean()
{
    std::list<Font *>::iterator iter;
    for (iter = font_list.begin(); iter != font_list.end(); iter++)
    {
        SAFE_DELETE((*iter));
    }
    font_list.clear();

}
};
