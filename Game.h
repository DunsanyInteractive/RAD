/*
 *  Game.h
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett, John Felderhof, Enda McNally.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef GAME_H
#define GAME_H

//STL includes
#include <list>
#include <string>
#include "input_interface.h"
#include "Level.h"
#include "MousePointer.h"

//OS Specific Includes
#ifdef _WIN32
#define DEFAULT_KEY_MAP	"LUA/KeyBinds.txt"
#else
#define DEFAULT_KEY_MAP	"LUA/KeyBinds_Mac.txt"
#endif

enum {
    GAME,
    CONSOLE
};


#define SAFE_DELETE(p)	{if (p)	{ delete (p); (p) = NULL; } }


namespace Game {
const int NUM_OF_LEVELS = 2;

/* Variables */
extern bool appRunning;
extern bool pause;
extern bool closeLevel;
extern int mode;

/* Functions */
void initialize();
void clean();
void exit();
void loadLevel( std::string );
void loadMouse(std::wstring);
void unloadMouse();
void pauseGame();
void unPauseGame();

/* Graphics related */
void update();
void draw();
void display();

void change_game_mode();

/* Input related */
std::list<std::wstring*> getGfxFile();

/* Binding functions */
void menu_mouse_click(struct InputHandler::Mouse *);
void COL_TIMED_CALL( void * );

extern Level *level;
extern std::string level_file;
extern std::string currentLevelFile;
};

#endif
