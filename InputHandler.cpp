/*
 *  InputHandler.cpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof, Enda McNally.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */

#include <map>
#include <fstream>
#include "Game.h"
#include "InputHandler.h"

#define BUTTON2BASE(button) (button - 1000)

namespace InputHandler {

std::queue<struct Input_Event *> event_queue;

std::map<int, void (*)()> key_map;
std::map<int, void (*)(struct InputHandler::Mouse *)> mouse_map;
void (*text_function)(int);
void (*console_function)(int);
void (*mouse_function)(struct InputHandler::Mouse *);

Input_Event ievent;

bool bindKey( int key, void (*func)() )
{
    std::map<int, void (*)()>::iterator it;

    it = key_map.find( key );
    if( it != key_map.end() )
        return false;

    key_map[ key ] = func;

    return true;
}

bool bindKeyConsole(void (*func)( int ) )
{
    if( func != NULL )
    {
        console_function = func;
        return true;
    }
    else
        return false;

}

void unbindKeyConsole()
{
    text_function = NULL;
}

void unbindKey( int key )
{
    key_map.erase( key_map.find( key ) );
}

bool processKey( int key )
{
    std::map<int, void (*)()>::iterator it;

    it = key_map.find( key );
    if( it == key_map.end() )
        return false;

    key_map[key]();

    return true;
}

/* Function pointer of the form func( x, y, event_type ) */
bool bindMouse( int button, void (*func)(struct Mouse *) )
{
    std::map<int, void (*)(struct Mouse *)>::iterator it;

    it = mouse_map.find( BUTTON2BASE(button) );
    if( it != mouse_map.end() )
        return false;

    mouse_map[ BUTTON2BASE(button) ] = func;

    return true;
}

void unbindMouse( int button )
{
    mouse_map.erase( mouse_map.find( BUTTON2BASE(button) ) );
}

bool processMouse( struct Mouse *mouse )
{
    std::map<int, void (*)(struct Mouse *)>::iterator it;

    it = mouse_map.find( mouse->code );
    if( it == mouse_map.end() )
        return false;

    mouse_map[ievent.mouse.code]( mouse );

    return true;
}

/* Text binding functions */
bool bindText( void (*func)( int ) )
{
    if( func != NULL )
    {

        II::setTextMode( true );
        text_function = func;
        return true;
    }
    else
        return false;
}

void unbindText()
{
    II::setTextMode( false );
    text_function = NULL;
}

bool bindMouseMovement( void (*func)( struct Mouse * ) )
{
    if( func != NULL )
    {
        mouse_function = func;
        return true;
    }
    else
        return false;
}

void unbindMouseMovement()
{
    mouse_function = NULL;
}

/* Handle queued input */
void update()
{
    while(II::readInput(&ievent))
    {
        switch( ievent.type )
        {
        case KEYBOARD:
            /*Just kinda temp code in so that only certain functions are called depending on key_pos or event_type
            i.e BUTTON_UP OR BUTTON_DOWN*/
            if (ievent.keyboard.key_pos == BUTTON_DOWN)
            {
                if( II::text_mode )
                    console_function(ievent.keyboard.code );
                else
                    processKey( ievent.keyboard.code );
            }
            else
            {

            }
            break;
        case MOUSE:
            if(ievent.mouse.event_type == MOUSE_MOVEMENT && mouse_function) {
                mouse_function((struct InputHandler::Mouse *)(&ievent.mouse));
                break;
            }
            else
                processMouse( &ievent.mouse );
            break;
        case JOYSTICK:
            processKey( ievent.legacyjoystick.code );
            break;
        case XBOX:
            processKey( ievent.xbox.code );
            break;
        case TEXT_ASCII:
            if( ievent.keyboard.code )
                text_function(ievent.keyboard.code );
            break;
        }

    }
}


/*
 * File formatt:
 *	action				scancode
 *
 */
typedef void (*ptr2func)();
ptr2func action_func[] = {
    NULL,					/* UP */
    NULL,					/* DOWN */
    NULL,					/* LEFT */
    NULL,				/* RIGHT */
    &Game::exit,			/* ESC */
    &Game::pauseGame
    //		&Game::test

};


/*
 * File format:
 *	action				scancode
 */

bool loadKeyMap( const char *file_name )
{
    using namespace std;
    int action;
    int key;

    ifstream file( file_name, ifstream::in );
    if( file.fail() )
        return false;

    /* Iterate over each line */
    while( file.good() )
    {
        file >> action;
        file >> key;

        if( action >= 0 && (action < sizeof( action_func ) ))
        {
            if( action_func[ action ] != NULL )
            {
                bindKey( key, action_func[ action ] );
            }
        }
        else
            cerr << "Bad key mapping" << endl;
    }

    file.close();

    return true;
}

}
