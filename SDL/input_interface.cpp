/*
 *  input_interface.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#include <iostream>
#include <SDL/SDL.h>
#include "../input_interface.h"
#include "../window_conf.h"

namespace Input_Interface {
SDL_Event sdl_event;

bool text_mode;

void init()
{
    text_mode = false;
}


void clean()
{
}

bool readInput( Input_Event *event )
{
redo:
    if( SDL_PollEvent( &sdl_event ) )
    {
        switch( sdl_event.type )
        {
        case SDL_KEYDOWN:
            if( text_mode && !( sdl_event.key.keysym.unicode & 0xff80 ) )
            {
                event->type = TEXT_ASCII;
                event->keyboard.code = sdl_event.key.keysym.unicode & 0x7f;
            }
            else
            {
                event->type = KEYBOARD;
                event->keyboard.code = sdl_event.key.keysym.sym;
                event->keyboard.key_pos = BUTTON_DOWN;
            }
            break;
        case SDL_KEYUP:
            if( text_mode && !( sdl_event.key.keysym.unicode & 0xff80 ) )
            {
                goto redo;
            }
            else
            {
                event->type = KEYBOARD;
                event->keyboard.code = sdl_event.key.keysym.sym;
                event->keyboard.key_pos = BUTTON_DOWN;
            }
        case SDL_MOUSEMOTION:
            event->type = MOUSE;
            event->mouse.event_type = MOUSE_MOVEMENT;
            event->mouse.x = sdl_event.button.x;
            event->mouse.y = WINDOW_HEIGHT - sdl_event.button.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            event->type = MOUSE;
            event->mouse.event_type = BUTTON_DOWN;
            event->mouse.code = sdl_event.button.button;

            event->mouse.x = sdl_event.button.x;
            event->mouse.y = WINDOW_HEIGHT - sdl_event.button.y;
            break;
        case SDL_MOUSEBUTTONUP:
            event->type = MOUSE;
            event->mouse.event_type = BUTTON_UP;
            event->mouse.code = sdl_event.button.button;

            event->mouse.x = sdl_event.button.x;
            event->mouse.y =  WINDOW_HEIGHT - sdl_event.button.y;
            break;
        default:
            return false;
        }
        return true;
    }

    return 0;
}

bool setTextMode( bool arg )
{
    text_mode = arg;

    if( arg )
    {
        SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL );
        SDL_EnableUNICODE( true );
    }
    else
    {
        SDL_EnableKeyRepeat( 0, SDL_DEFAULT_REPEAT_INTERVAL );
        SDL_EnableUNICODE( false );
    }

    return true;
}
};
