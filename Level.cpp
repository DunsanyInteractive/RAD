/*
 *  Level.cpp
 *  Rad Adventure Development
 *
 *  Created by _______________.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#include <typeinfo>
#include <sstream>
#include "Animation.h"
#include "Button.h"
#include "Game.h"
#include "Physics/CM_Grid.h"
#include "Level.h"
#include "LuaEngine.h"
#include "window_conf.h"

#include "ProcessManager.h"
#include "Console.h"
#include "Font_Handler.h"

/*Class unused for now*/
#include "ParticleEmitter.h"

using namespace std;

/* Load LUA script */
Level::Level()
{
    ProcessManager::init();
// 	collision_manager = new CM_Grid( 2, 2 );
// 	ProcessManager::CallIn( CollisionManager::PHYSICS_DELAY, &CM_TIMED_CALL, collision_manager );
    std::wstring file(L"Assets/Mouse_Cursor.png");
}

Level::~Level()
{
    LuaEngine::collect_garbage();
    ProcessManager::clean();
// 	delete collision_manager;
    spriteList.clear();
}

void Level::loadFile(string file_name)
{
    /* Run lua script and set global level */
    LuaEngine::run( "level = Level.current()" );
    LuaEngine::runfile( file_name );

    Game::closeLevel = false;
    sortSpriteList();

    //TODO::TESTINg
// 	std::wstring file = std::wstring(L"Assets/Main_Menu.png");
// 	Sprite *test = new Sprite(file);
// 	test->setPosition(0,800);
// 	test->layer = 10;
// 	test->visible = true;
// 	test->setSize(1280, 800);
// 	test->rotation = 0;
// 	add(test);
}

void Level::draw()
{
    std::list<Sprite *>::iterator iter;
    iter = spriteList.begin();
    while (iter != spriteList.end()) {
        if ((*iter)->visible == true)
            (*iter)->draw();
        iter++;
    }
    if (Game::mode == CONSOLE) {
// 		Console::draw_console();
// 		Font_Handler::draw();
    }

// 	collision_manager->draw();
}

void Level::add( Sprite *sprite )
{
    spriteList.push_back(sprite);
}

void Level::remove( Sprite *sprite )
{
    spriteList.remove( sprite );
}

void Level::sortSpriteList()
{
    std::list<Sprite *>::iterator iter;
    std::list<Sprite *> sortedSprites;
    iter = spriteList.begin();
    for (int i = 10; i > 0; i--) {
        while (iter != spriteList.end()) {
            if ((*iter)->layer == i)
                sortedSprites.push_back(*iter);
            iter++;
        }
        iter = spriteList.begin();
    }
    spriteList.clear();
    spriteList = sortedSprites;
}

/* Should probably be changed */
void Level::CM_TIMED_CALL( void *arg ) {
    ((CollisionManager *)(arg))->update();
    ProcessManager::CallIn( CollisionManager::PHYSICS_DELAY, &CM_TIMED_CALL, arg );
}
