/*
 *  Game.cpp
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett, John Felderhof, Enda McNally.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */

#include <iostream>
#include <stdexcept>

#include "ProcessManager.h"
#include "SoundManager.h"
#include "graphics_engine.h"
#include "Font_Handler.h"
#include "Console.h"

#include "Sound.h"
#include "LuaEngine.h"

#include "Game.h"

namespace Game {
bool appRunning;
bool pause;
bool closeLevel;
int mode = GAME;
std::string level_file;

Level *level;
MousePointer *mousePointer;
//Timer	*game_timer;

void clean() {
    GE::clean();
    II::clean();
    SM::clean();
// 	Console::clean();
// 	Font_Handler::clean();
    ProcessManager::clean();
    SAFE_DELETE(level);
    LuaEngine::clean();
}

void exit() {
    appRunning = false;
}

/* Initialise function */
void initialize() {
    SM::init();
    LuaEngine::init();

    closeLevel = false;
    Game::appRunning = true;
    //game_timer = new Timer();

    pause = false;
//      Font_Handler::init();
//      Console::init();
    InputHandler::loadKeyMap( DEFAULT_KEY_MAP );
    ProcessManager::init();
    CollisionManager::PHYSICS_DELAY = 0.5;
}

//Function to call all code that will update during each frame. Should be called everytime in the game loop.
void update() {
    if (closeLevel) {
        SAFE_DELETE(level);
        ProcessManager::purgeProcessList();
        level = new Level();
        level->loadFile(level_file);
    }
    InputHandler::update();
    ProcessManager::updateList();
    ProcessManager::processTimedCalls();
}

void pauseGame() {
    if (pause)
        pause = false;
    else
        pause = true;
}

void loadLevel( std::string file_name ) {
    //TODO: Check if file exists and throw error
    level_file = file_name;
    closeLevel = true;
}

static MousePointer *mouse_p = NULL;
void loadMouse( std::wstring file_name ) {
    mouse_p = MousePointer::load(file_name);
    mouse_p->visible = true;
    mouse_p->setSize(32, 32);
    mouse_p->layer = 1;
}

void unloadMouse() {
    mouse_p = NULL;
    MousePointer::unload();
}

void draw() {
    level->draw();
    if (mouse_p) GE::drawSprite(mouse_p);
}

void display() {
    GE::display();
}

void change_game_mode() {
    if (mode == GAME)
        mode = CONSOLE;
    else
        mode = GAME;
}
}

