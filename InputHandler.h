/*
 *  InputHandler.h
 *  Rad Adventure Development
 *
 *  Created by Enda McNally.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */

#include <queue>

#ifndef INPUT_HANDLER_H
#define	INPUT_HANDLER_H


namespace InputHandler {
/* Enum for user actions in game */
//	enum {
/* Character Movements */
//		UP,
//		DOWN,
//		LEFT,
//		RIGHT,

/* Misc */
//		ESC
//	};

enum {
    BUTTON_DOWN,
    BUTTON_UP,
    MOUSE_MOVEMENT
};


/* Types of events */
enum {
    KEYBOARD,
    MOUSE,
    JOYSTICK,
    XBOX,
    TEXT_ASCII
};

struct Keyboard {
    int code;
    bool key_pos;/* Scan code of key/button( dependant on II ) */
};

struct Mouse {
    int code;	/* Which button on the mouse */
    int x;				/* X position */
    int y;				/* Y position */
    int event_type;			/* BUTTON_UP or BUTTON_DOWN */
};

struct Legacy_Joystick {
    int code;	/* Which button on the mouse */
    int x;				/* X position */
    int y;				/* Y position */
    bool event_type;			/* BUTTON_UP or BUTTON_DOWN */
};

struct Xbox {
    int code;	/* Which button on the mouse */
    int x;				/* X position */
    int y;				/* Y position */
    bool event_type;			/* BUTTON_UP or BUTTON_DOWN */
};

struct Input_Event {
    int type;
    union {
        struct Keyboard keyboard;
        struct Mouse mouse;
        struct Legacy_Joystick legacyjoystick;
        struct Xbox xbox;
    };
};

extern Input_Event ievent;

extern int keytest;


/* Process Input */
/* Keys */
bool processKey( int );
bool bindKey( int, void (*)() );
void unbindKey( int );

/* Mouse */
bool processMouse( int );
bool bindMouse( int, void (*)(struct Mouse *) );
void unbindMouse( int );

/* Text */
bool bindText( void (*)( int ) );
void unbindText();

bool bindKeyConsole( void (*)( int ) );
void unbindKeyConsole();

/* Mouse Movement */
bool bindMouseMovement( void (*)( struct Mouse * ) );
void unbindMouseMovement();

void LeftClick( int b, int c, int d);

void update();

void setValue();


/* Keymap Files */
bool loadKeyMap( const char * );


}
#endif
