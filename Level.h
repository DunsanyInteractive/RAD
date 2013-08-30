/*
 *  Level.h
 *  Rad Adventure Development
 *
 *  Created by Oliver Plunkett, John Felderhof, Enda McNally.
 *  Copyright 2010 Dunsany Interactive. All rights reserved.
 *
 */
#ifndef LEVEL_H
#define LEVEL_H

#define SAFE_DELETE(p)	{if (p)	{ delete (p); (p) = NULL; } }

#include <list>

#include "MousePointer.h"
#include "Sprite.h"
#include "Physics/CollisionManager.h"

class Level
{
    MousePointer *mouse_pointer;

public:
    Level();
    ~Level();

//	std::list<Sound *> soundList;
    std::list<Sprite *> spriteList;
//	std::list<Sound*> levelSound;
    CollisionManager *collision_manager;

    void draw();

    void add( Sprite * );
    void remove( Sprite * );

    void sortSpriteList();
    void loadFile(std::string);

    static void CM_TIMED_CALL( void * );
};

#endif
