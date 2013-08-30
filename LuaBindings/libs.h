/*
 *  Sprite.hpp
 *  Rad Adventure Development
 *
 *  Created by John Felderhof.
 *  Copyright 2010 DunsanyInteractive. All rights reserved.
 *
 */

#ifndef LUA_LIBS_H
#define LUA_LIBS_H

#include "../LuaEngine.h"

void libanimation( lua_State *L );
void libbutton( lua_State *L );
void libgame( lua_State *L );
void liblevel( lua_State *L );
void libprocessManager( lua_State *L );
void libsound( lua_State *L );
void libsprite( lua_State *L );

#endif

